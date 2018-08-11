///
/// @file    test.cc
/// @author  
/// @date    2018-08-10 18:53:08
///
#include "redis.h"

#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

int main()
{
    cc::Redis redis;
    redis.Connect();
    redis.setString("name", "lii");

    string s;
    redis.getString("name", s);
    cout << s << endl;

    redis.setString("age", "30");
    redis.getString("age", s);
    cout << s << endl;
    
    int i;
    redis.getString("age", i);
    cout << i << endl;    

    redis.disConnect();
}
