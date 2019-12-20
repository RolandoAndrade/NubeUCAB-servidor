#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

class FTPRequest 
{
private:

	string cmd;
	string argv;

public:

	FTPRequest()
	{

	};
	~FTPRequest()
	{

	}

	FTPRequest(string c)
	{
		setRequest(c);
	}

	FTPRequest(string c,string args)
	{
		setRequest(c,args);
	}

	FTPRequest(string c, vector<string> flags)
	{
		setRequest(c,flags);
	}

	FTPRequest(string c, vector<string> flags, vector<string> args)
	{
		setRequest(c,flags,args);
	}
	
	void setRequest(string c)
	{
		cmd = c;
		argv = "";
	}

	void setRequest(string c,string args)
	{
		cmd = c;
		argv = " "+args;
	}

	void setRequest(string c, vector<string> flags)
	{
		cmd = c;
		argv = "";
		for(string f: flags)
		{
			argv += " " + f;
		}
	}

	void setRequest(string c, vector<string> flags, vector<string> args)
	{
		setRequest(c,flags);
		for(string f: args)
		{
			argv += " " + f;
		}
	}

	string getRequest();
	string getRequest(string);

};