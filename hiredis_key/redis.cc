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


#if 0
#define SETSTRING(key, value) \
	stringstream ss;\
	ss << "SET " << key << " " << value;\
	string s;\
	getline(ss, s);\
	setString(s);
#endif

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

	void Redis::setString(const string & data)
	{
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, data.c_str());
		if(!isError()) {
			if (!(_reply->type == REDIS_REPLY_STATUS && strcasecmp(_reply->str,"OK") == 0)) {
				cout << "Failed to execute SET(string)" << endl;
			}    
		}
	}

#if 0
	template<typename ValueT>
		void Redis::setString(const string & key,ValueT value){
			stringstream ss;
			ss << "SET " << key << " " << value;
			string s;
			getline(ss, s);
			setString(s);
		}
#endif

#if 0
	void Redis::setString(const string & key, const string & value) {

		SETSTRING(key, value);

	}

	void Redis::setString(const string & key, const int & value) {
		SETSTRING(key, value);
	}

	void Redis::setString(const string & key, const float & value) {
		SETSTRING(key, value);
	}

#endif
	void Redis::getString(const string & key) {
		freeReply();
		_reply = (redisReply*)::redisCommand(_context, "GET %s", key.c_str());
	}

	void Redis::getString(const string & key, string & value) {
		getString(key);
		if(!isError() && _reply->type == REDIS_REPLY_STRING) {
			value = _reply->str;
		}
	}

	void Redis::getString(const string & key, int & value) {
		getString(key);
		if(!isError() && _reply->type == REDIS_REPLY_STRING) {
			value = ::atoi(_reply->str);
		}
	}

	void Redis::getString(const string & key, float & value) {
		getString(key);
		if(!isError() && _reply->type == REDIS_REPLY_STRING) {
			value = ::atof(_reply->str);
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
