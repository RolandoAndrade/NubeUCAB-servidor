#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "socket_server.h"
#include "commands.h"
#include "FTPRequest.h"
#include "FTPResponse.h"

typedef map<string, pair<string, string> > LoginInfo;

class FTPServer
{
	private:
		int port;
	public:
		FTPServer(int pport)
		{
			cout<<"NubeUCAB-servidor ha iniciado"<<endl;
			port = pport;
		}
		~FTPServer()
		{

		}
		
		void start();
		void help();
		void get(string);
		void put(string);
		void add();
		int ls(string, string&, bool print = false);
		string syst(bool print = false);
		string pwd(bool print = false);
		int cd(string, bool print = false);
		int mkd(string, string&, bool print= false);
		int pasv();
		bool quit();
		int setRootDir(string, bool print = false);
		LoginInfo formLoginInfoList();
		void communicate(ServerSocket *);
};