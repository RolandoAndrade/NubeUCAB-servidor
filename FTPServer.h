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

		int hello(ServerSocket **serverSocket, string &responseMsg)
		{
			try
			{
				ServerSocket *ax;
				responseMsg = FTPResponse("200","(NubeUCAB)").getResponse();
				(*ax) << responseMsg;
				*serverSocket = ax;
				return 1;
			} 
			catch(SocketException &e)
			{
				std::cout<<"Ha ocurrido un error: "<<e.getMessage()<<std::endl;
				return 0; 
			}
		}

		string getUser(LoginInfo &info, string &user, string args)
		{
			info = formLoginInfoList();
			user = args;
			return FTPResponse("331","Introduce la contraseña").getResponse();
		}

		string getPassword(LoginInfo info, string user, string pass, int &isLogged)
		{
			string responseMsg;
			if(info.find(user) != info.end())
			{
				if(info[user].first == pass)
				{
					cd(info[user].second);
					isLogged = 1;
					responseMsg = FTPResponse("230","Login successful.").getResponse();
				}
			}

			if(!isLogged)
			{
				responseMsg = FTPResponse("530","Login incorrect.").getResponse();
			}
			return responseMsg;
		}


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

		LoginInfo formLoginInfoList()
		{
			LoginInfo list;
			ifstream in("users/users.info", ios::in| ios::binary);

			if(in)
			{
				string user, pass, home;
				while (in >> user >> pass >> home)
				{
				    list[user] = make_pair(pass,home);
				}
			}
			
			return list;
		}

		void communicate(ServerSocket * serverSocket)
		{
			string data="",responseMsg="",cmd,args,user;
			ServerSocket *dataSocket;
			LoginInfo list;
			int isLogged = 0;
			int isBinaryMode = 0;
			// El servidor saluda
			if(!hello(&(serverSocket),responseMsg)) return;
			// a la escucha
			while(1)
			{
				args.clear();
				cmd.clear();
				try
				{
					//Recibir datos del cliente
					*serverSocket >> data;
					if(parseCommand(data,cmd,args))
					{
						cout<<"Comando recibido: "<<cmd<<std::endl;
						// Obtener usuario
						if(cmd=="USER"&&args.size())
						{
							responseMsg = getUser(list, user,args);
							*serverSocket << responseMsg;
						}
						else if(cmd=="PASS" && args.length())
						{
							responseMsg = getPassword(list, user,args, isLogged);
							*serverSocket << responseMsg;
						}
						else if(cmd=="SYST" && !args.size())
						{
							responseMsg = FTPResponse("215",uname()).getResponse();
							*serverSocket << responseMsg;
						}
						else if(cmd=="PWD"  && !args.size() && isLogged)
						{
							responseMsg = FTPResponse("257","\""+pwd()+"\"").getResponse();
							*serverSocket << responseMsg;
						}



					}
				} 
				catch(SocketException &e)
				{
					std::cout<<"Ha ocurrido un error : "<<e.getMessage()<<std::endl;
					return ;
				}
			}
		}
};