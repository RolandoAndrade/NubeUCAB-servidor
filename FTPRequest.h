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

	FTPRequest(string c,string argv)
	{
		cmd = c;
		argv = " "+argv;
	}

	FTPRequest(string, vector<string>);
	FTPRequest(string, vector<string>, vector<string>);
	
	void setRequest(string);
	void setRequest(string,string);
	void setRequest(string, vector<string>);
	void setRequest(string, vector<string>, vector<string>);
	string getRequest();
	string getRequest(string);

};