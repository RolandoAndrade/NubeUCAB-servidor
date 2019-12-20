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
		cmd = c;
		argv = "";
	}

	FTPRequest(string c,string a)
	{
		cmd = c;
		argv = " "+a;
	}

	FTPRequest(string c, vector<string> flags)
	{
		cmd = c;
		argv = "";
		for(string f: flags)
		{
			argv += " " + f;
		}
	}

	FTPRequest(string, vector<string>, vector<string>);
	
	void setRequest(string);
	void setRequest(string,string);
	void setRequest(string, vector<string>);
	void setRequest(string, vector<string>, vector<string>);
	string getRequest();
	string getRequest(string);

};