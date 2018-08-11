///
/// @file    redisConf.h
/// @author  
/// @date    2018-08-10 18:14:02
///
#ifndef __CC_REDISCONF_H__
#define __CC_REDISCONF_H__
#include <string>
using std::string;
namespace cc
{
	class RedisConf
	{
		public:
			RedisConf();
			void getConf();
			string getIP();
			int getPort();
		private:
			string _ip;
			int _port;
	};
}//end of namespace
#endif
