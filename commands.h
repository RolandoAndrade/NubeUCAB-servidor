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

string getPassword();
string getFileName(string);
string getFilePath(string);
string execute(string, string,int& code = 0);
vector<string> tokenize(string, string);
bool parseCommand(string, string&, string&);
bool parseCommand(string, string&, vector<string>&, vector<string>&);
