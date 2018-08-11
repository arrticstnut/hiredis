///
/// @file    redis.cc
/// @author  
/// @date    2018-08-10 18:25:18
///
#include "redis.h"
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


	Redis::Redis()
		: _conf()
		,_reply(NULL)
	{}

	void Redis::Connect() {
		_context = ::redisConnect(_conf.getIP().c_str(), _conf.getPort());
		std::cout << _conf.getIP() << "-" << _conf.getPort() << std::endl;
		if(_context && _context->err) {
			cout << "connect redis error" << endl;
			exit(EXIT_FAILURE);
		}
		cout << "redis Connect success" << endl;
	}

	void Redis::disConnect() {
		::redisFree(_context);
		cout << "redis disConnect success" << endl;
	}

	void Redis::setHashString(const string & data){
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, data.c_str());
		if(!isError()) {
			if (!(_reply->type == REDIS_REPLY_INTEGER && _reply->integer == 1)) {
				cout << "Failed to execute HSET(string)" << endl;
			}    
		}
	}

	void Redis::setString(const string & data) {
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, data.c_str());
		if(!isError()) {
			if (!(_reply->type == REDIS_REPLY_STATUS && strcasecmp(_reply->str,"OK") == 0)) {
				cout << "Failed to execute SET(string)" << endl;
			}    
		}
	}


	void Redis::getHashString(const string & key,const string & field){
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, "HGET %s %s", key.c_str(),field.c_str());
	}

	void Redis::getString(const string & key) {
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, "GET %s", key.c_str());
	}

	void Redis::del(const string & key){
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, "DEL %s", key.c_str());
		if(!isError()) {
			if (!(_reply->type == REDIS_REPLY_INTEGER && _reply->integer == 1)) {
				cout << "Failed to execute DEL(string)" << endl;
			}
		}
	}

	void Redis::freeReply() {
		if(_reply) {
			::freeReplyObject(_reply);
			_reply = NULL;
		}
	}

	bool Redis::isError() {
		if(NULL == _reply) {
			freeReply();
			disConnect();
			Connect();
			return true;
		}
		return false;
	}

}
