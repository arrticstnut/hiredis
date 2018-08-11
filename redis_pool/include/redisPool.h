///
/// @file    redisPool.h
/// @author  
/// @date    2018-08-10 18:21:06
///
#ifndef __CC_REDISPOOL_H__
#define __CC_REDISPOOL_H__

#include <string>
#include <mutex>
#include <hiredis/hiredis.h>
#include <queue>
#include <memory>
using std::stringstream;
using std::queue;
using std::string;

namespace cc
{

	class RedisPool
	{
		public:
			RedisPool(const string & serverIp,int serverPort,int timeout = 50000);//连接超时默认为5000毫秒
			~RedisPool();

		public:
			void disConnect();//释放所有连接
			void releaseContext(redisContext *ctx,bool active);//释放连接（如果连接可用，则归还到连接池,如果连接不可用，则是真正释放连接)
			redisContext* createContext();//创建连接
			bool ExecuteCmd(const string & cmd,string &response);//执行命令，结果存储在response中,（不支持返回结果为数组类型的命令）
		private:
			redisReply* ExecuteCmd(const string & cmd);
		private:
			string _serverIp;
			int _serverPort;
			int _timeout;
			std::mutex _mutex;//锁
			queue<redisContext *> _contextQue;//连接池
	};
}//end of namespace

#endif
