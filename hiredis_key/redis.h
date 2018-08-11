///
/// @file    redis.h
/// @author  
/// @date    2018-08-10 18:21:06
///
#ifndef __CC_REDIS_H__
#define __CC_REDIS_H__

#include "redisConf.h"
#include <hiredis/hiredis.h>
#include <sstream>
using std::stringstream;

namespace cc
{

	class Redis
	{
		public:
			Redis();
		public:
			void Connect();
			void disConnect();
		public:
#if 1
	template<typename ValueT>
		void setString(const string & key,ValueT value){
			stringstream ss;
			ss << "SET " << key << " " << value;
			string s;
			getline(ss, s);
			setString(s);
		}
#endif
#if 0
			void setString(const string & key, const string & value);
			void setString(const string & key, const int & value);
			void setString(const string & key, const float & value);
#endif
		private:
			void setString(const string & data);
		public:
			void getString(const string & key, string & value);
			void getString(const string & key, int & value);
			void getString(const string & key, float & value);
		private:
			void getString(const string & key);
		private:
			void freeReply();
			bool isError();
		private:
			RedisConf _conf;
			redisContext * _context;
			redisReply * _reply;
	};
}//end of namespace

#endif
