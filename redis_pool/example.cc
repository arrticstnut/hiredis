///
/// @file    test.cc
/// @author  
/// @date    2018-08-10 18:53:08
///
#include "./include/redisPool.h"
#include <sstream>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

template<typename C>
void display(const C & c){
	for(const auto & e: c){
		cout << e << endl;
	}
}

int main()
{
    cc::RedisPool redis("127.0.0.1",6379);
	stringstream ss;
	string hashKey = "myHashTest";
	string field = "湖北省会";
	string value = "武汉";
	string field1 = "湖南省会";
	string value1 = "长沙";
	string field2 = "广东省会";
	string value2 = "广州";

	vector<string> result;
	redis.ExecuteCmd("HSET myHashTest 广西省会  南宁",result);
	display(result);

	redis.ExecuteCmdBy_4_InputArgs("HSET",hashKey,field,value,result);
	display(result);

	redis.ExecuteCmdBy_4_InputArgs("HSET",hashKey,field1,value1,result);
	display(result);

	redis.ExecuteCmdBy_4_InputArgs("HSET",hashKey,field2,value2,result);
	display(result);

	redis.ExecuteCmdBy_2_InputArgs("HGETALL",hashKey,result);
	display(result);

	return 0;
}

