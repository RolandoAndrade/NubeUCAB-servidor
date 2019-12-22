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

		void start()
		{
			cout<<"Iniciando servidor en el puerto: "<<port<<endl;

			try
			{
				//Crea un socket a la escucha de los clientes
				ServerSocket server(port);
				ServerSocket *serverSocket = new ServerSocket();
				//Espera peticiones
				while(1)
				{
					try
					{
						server.accept(*serverSocket);
						//Se debería crear un proceso hijo, de lo contrario cierra el socket
						if(!fork())
						{
							server.close();
							communicate(serverSocket);
							(*serverSocket).close();
							exit(0);
						}
						(*serverSocket).close();
					} 
					catch(SocketException &e)
					{
						cout<<"Ha ocurrido un error: "<<e.getMessage()<<endl;
						continue;
					}
				}
			} 
			catch(SocketException &e)
			{
				cout<<"Ha ocurrido un error: "<<e.getMessage()<<endl;
				return;
			}
		}

		void help()
		{
			
		}

		/*Listar archivos del directorio*/

		int ls(string args, string &response, int print = 0)
		{
			int code;
			string request = FTPRequest("ls -l",args).getRequest("\n");
			response = execute("ls",request,code);
			if(print)
			{
				cout<<response;
			}
			return code;
		}

		/*Información del sistema*/

		string uname(int print = 0)
		{
			int code;
			string request = FTPRequest("uname").getRequest("\n");
			string response = execute("uname",request,code);

			if(print)
			{
				cout<<response;
			}

			return response;
		}

		/*Directorio actual*/

		string pwd(int print = 0)
		{
			int code;
			string request = FTPRequest("pwd","").getRequest("\n");
			string response = execute("pwd",request, code);

			if(print)
			{
				cout<<response;
			}

			return response;
		}

		/*Entrar en directorio*/

		int cd(string args, int print = 0)
		{
			int code;
			string response = execute("cd",args,code);

			if(print)
			{
				cout<<response;
			}
			return code;
		}

		int mkd(string args, string &response, int print = 0)
		{
			int code;
			response = execute("mkdir",args,code);

			if(print)
			{
				cout<<response;
			}

			return code;
		}


		int quit()
		{
			return 0;
		}

		int setRootDir(string, bool print = false);
		LoginInfo formLoginInfoList();
		void communicate(ServerSocket *);
};