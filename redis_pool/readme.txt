一、使用:
	可以通过两种方式执行命令：
	1.通过完整的命令执行：
	bool ExecuteCmd(const string & cmd,vector<string> &response);//传入完整命令，结果存储在response中

	2.有时候通过1的方式会因为空格等格式错误，无法正确执行，可以通过传入参数的方式执行命令：
	bool ExecuteCmdBy_2_InputArgs(const string & arg1,const string & arg2,vector<string> & response);
	其中2表示有两个输入参数，response存放的是返回的结果

二、无需先连接，直接执行即可。以上2种方式自动会获取连接，自动释放。

三、提供了获取连接和释放连接的接口，可根据需要将连接放入连接池或真正释放。

