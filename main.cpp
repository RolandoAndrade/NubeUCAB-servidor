#include "FTPServer.h"

int main(int argc, char const *argv[])
{
	if(argc == 2)
	{
		int port = atoi(argv[1]);
		FTPServer server(port);
		server.start();
	}
	return 0;
}