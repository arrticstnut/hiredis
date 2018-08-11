///
/// @file    test.cc
/// @author  
/// @date    2018-08-10 18:53:08
///
#include "redisPool.h"
#include <sstream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

int main()
{
    cc::RedisPool redis("127.0.0.1",6379);
	stringstream ss;
	string hashKey = "myHashTest";
	string field = "湖北省会";
	string value = "武汉";

	ss << "HSET" << " " << hashKey << " " << field << " " << value;
	string cmd = ss.str();
	string result;
	cout << cmd << endl;
	redis.ExecuteCmd(cmd,result);
	cout << result << endl;

	ss.str("");//注意要清空
	ss << "HGET" << " " << hashKey << " " << field;
	cmd = ss.str();
	cout << cmd << endl;
	redis.ExecuteCmd(cmd,result);
	cout << result << endl;
}
