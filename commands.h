#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "socket_exceptions.h"

using namespace std;

/*Revisar si el host existe*/

int lookup(string s)
{
	const char *host = s.c_str();
	struct sockaddr_in inaddr;
	struct hostent *hostp;

	if ((host == NULL) || (*host == '\0'))
	{
		return(INADDR_ANY);
	}

	memset ((char * ) &inaddr, 0, sizeof inaddr);

	if ((int)(inaddr.sin_addr.s_addr = inet_addr(host)) == -1)
	{
		hostp = gethostbyname(host);
		if (hostp == NULL)
		{
			throw SocketException(strerror(errno));
		}
		if (hostp->h_addrtype != AF_INET)
		{ 
			errno = EPROTOTYPE;
			throw SocketException(strerror(errno));
		}
		memcpy((char * ) &inaddr.sin_addr, (char * ) hostp->h_addr, sizeof(inaddr.sin_addr));
	}
	return(inaddr.sin_addr.s_addr);
}

int isANumber(string s)
{
	for(char c: s)
	{
		if(!isdigit(c))
		{
			return 0;
		}
	}
	return 1;
}

/*Obtener contraseña en consola linux*/
string getPassword()
{
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	string pass;
	getline(cin, pass);
	getline(cin, pass);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	cout<<endl;
	return pass;
}

/*Obtener nombre del archivo*/

string getFileName(string s)
{
	string::size_type pos = s.find_last_of("/\\");
	return s.substr(pos+1);
}

string getFilePath(string s)
{
	string::size_type pos = s.find_last_of("/\\");
	if(pos==string::npos)
	{
		return "";
	}
	return s.substr(0,pos);
}

void pwd(stringstream &data, int &code)
{
	char buff[2048];
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		code = 1;
		data<<"\""<<buff<<"\""<<endl;
	}
	else 
	{
		data<<"\"Ha ocurrido un error: "<<strerror(errno)<<"\""<<endl;
	}
}

void cd(stringstream &data, int &code, string directory)
{
	if(chdir(directory.c_str()) == 0)
	{
		code = 1;
		data<<"Se ha cambiado de directorio: "<<directory<<endl;
	}
	else
	{
		data<<"Ha ocurrido un error: "<<strerror(errno)<<endl;
	}
}

void mkdirectory(stringstream &data, int &code, string directory)
{
	if(!mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
	{
		code = 1;
		data<<"Creado directorio: \""<<directory<<"\""<<endl;
	}
	else
	{
		data<<"Error: "<<strerror(errno)<<endl;
	}
}

string execute(string type, string command, int &code)
{
	FILE *in;
	stringstream data;
	code = 0;
	
	if(type == "pwd")
	{
		pwd(data, code);
	}
	else if(type == "cd")
	{
		cd(data, code, command);
	}
	else if(type == "mkdir")
	{
		mkdirectory(data,code,command);
	}

	return data.str();
}



vector<string> tokenize(string, string);
bool parseCommand(string, string&, string&);
bool parseCommand(string, string&, vector<string>&, vector<string>&);
