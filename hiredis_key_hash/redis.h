///
/// @file    redis.h
/// @author  
/// @date    2018-08-10 18:21:06
///
#ifndef __CC_REDIS_H__
#define __CC_REDIS_H__

#include "redisConf.h"
#include <hiredis/hiredis.h>
#include <typeinfo>
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
			template<typename ValueT>
				void setString(const string & key,ValueT value){//用于转换成SET语句
					stringstream ss;
					ss << "SET " << key << " " << value;
					string s;
					getline(ss, s);
					setString(s);
				}
			template<typename ValueT>
				void setHashString(const string & key,const string & field,ValueT value){//用于转换成HSET语句
					stringstream ss;
					ss << "HSET " << key << " " << field <<  " " << value;
					string s;
					getline(ss, s);
					setHashString(s);
				}
		public:
			template<typename ValueT>
				void getHashString(const string & key,const string & field,ValueT & value){//将HGET的结果存到value中
					getHashString(key,field);
					if(!isError() && _reply->type == REDIS_REPLY_STRING)
					{
						std::istringstream ss(_reply->str);
						ss >> value;
					}
				}

			template<typename ValueT>
				void getString(const string & key,ValueT & value){//将GET的结果存到value中
					getString(key);
					if(!isError() && _reply->type == REDIS_REPLY_STRING)
					{
						std::istringstream ss(_reply->str);
						ss >> value;
					}
				}
		public:
			void del(const string & key);//删除key,hash,set等所有对象
		private:
			void setString(const string & data);//执行SET
			void setHashString(const string & data);//执行HSET
		private:
			void getHashString(const string & key,const string & field);//执行HGET
			void getString(const string & key);//执行GET
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
