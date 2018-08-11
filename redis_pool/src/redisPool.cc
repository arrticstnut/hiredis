///
/// @file    redisPool.cc
/// @author  
/// @date    2018-08-10 18:25:18
///
#include "redisPool.h"
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>

using std::cout;
using std::endl;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
namespace cc
{



	RedisPool::RedisPool(const string & serverIp,int serverPort,int timeout)
	:_serverIp(serverIp)
	,_serverPort(serverPort)
	,_timeout(timeout)
	,_mutex()
	{}

	RedisPool::~RedisPool(){
		disConnect();
	}

	void RedisPool::releaseContext(redisContext *ctx,bool active){
		if(ctx == NULL) return;
		if(!active) {redisFree(ctx); return;}
		std::lock_guard<std::mutex> lockGuard(_mutex);//保护类，用于函数异常退出时候释放锁
		_contextQue.push(ctx);
	}

	redisContext* RedisPool::createContext(){
		{
			std::lock_guard<std::mutex> lockGuard(_mutex);//保护类，用于函数异常退出时候释放锁
			if(!_contextQue.empty()){
				redisContext *ctx = _contextQue.front();
				_contextQue.pop();
				return ctx;
			}
		}
		//如果连接池为空，则申请一个新的连接（为了时效性，不能等其他线程释放连接）
		
	struct timeval tv;
	tv.tv_sec = _timeout / 1000;
	tv.tv_usec = (_timeout % 1000)* 1000;
	//超时连接是指的连接服务器连不上的时候多少时间超时返回，不是指的返回后的连接的有效时间
	redisContext *ctx = redisConnectWithTimeout(_serverIp.c_str(), _serverPort,tv);
		if(ctx == NULL || ctx->err != 0)
		{
			if(ctx != NULL) redisFree(ctx);
			return NULL;
		}
		return ctx;
	}

	bool RedisPool::ExecuteCmd(const string & cmd,string &response)
	{
		redisReply *reply = ExecuteCmd(cmd);
		if(reply == NULL) return false;
		std::shared_ptr<redisReply> autoFree(reply,freeReplyObject);
		if(reply->type == REDIS_REPLY_INTEGER)
		{
			response = std::to_string(reply->integer);
			return true;
		}
		else if(reply->type == REDIS_REPLY_STRING)
		{
			response.assign(reply->str, reply->len);
			return true;
		}
		else if(reply->type == REDIS_REPLY_STATUS)
		{
			response.assign(reply->str, reply->len);
			return true;
		}
		else if(reply->type == REDIS_REPLY_NIL)
		{
			response = "";
			return true;
		}
		else if(reply->type == REDIS_REPLY_ERROR)
		{
			response.assign(reply->str, reply->len);
			return false;
		}
		else if(reply->type == REDIS_REPLY_ARRAY)
		{
			response = "Not Support Array Result!!!";
			return false;
		}
		else
		{
			response = "Undefine Reply Type";
			return false;
		}
	}
	redisReply* RedisPool::ExecuteCmd(const string & cmd) {
		redisContext *ctx = createContext();
		if(ctx == NULL) return NULL;
		redisReply *reply = (redisReply*)redisCommand(ctx,cmd.c_str());
		releaseContext(ctx, reply != NULL);//reply == NULL则真正释放连接，reply != NULL则归还到连接池
		return reply;
	}


	void RedisPool::disConnect() {
		std::lock_guard<std::mutex> lockGuard(_mutex);//保护类
		while(!_contextQue.empty())
		{
			redisContext *ctx = _contextQue.front();
			redisFree(ctx);
			_contextQue.pop();
		}
		//cout << "redis disConnect success" << endl;
	}

	
}
