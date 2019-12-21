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

int lookup(string);
bool isNumber(string);
string getPassword();
string getFileName(string);
string getFilePath(string);
string execute(string, string,int& code = 0);
vector<string> tokenize(string, string);
bool parseCommand(string, string&, string&);
bool parseCommand(string, string&, vector<string>&, vector<string>&);
