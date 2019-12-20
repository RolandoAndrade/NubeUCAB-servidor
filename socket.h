#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>

class Socket
{
	private:
		/*File descriptor del socket*/
		int sockfd;

		/*Dirección del socket*/
		struct sockaddr_in maddress;

	public:

		Socket()
		{
			memset(&maddress, 0, sizeof maddress);
			sockfd = -1;
		}

		~Socket()
		{
			if(is_valid())
			{
				close();
			}
		}

		int is_valid()
		{ 
			return sockfd != -1; 
		}

		int create()
		{
			sockfd = socket(PF_INET, SOCK_STREAM, 0);

			if(!is_valid()) 
			{
				return 0;
			}

			int accept = 1;

			return setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&accept,sizeof(int)) != -1;
		}

		/*Servidor: Forjar enlace a puerto*/
		int bind(int port)
		{
			if(!is_valid())
			{
				return 0;
			}

			maddress.sin_family = AF_INET;
			maddress.sin_port = htons(port);
			memset(maddress.sin_zero, '\0', sizeof maddress.sin_zero);

			return ::bind(sockfd, (struct sockaddr *)&maddress, sizeof(maddress)) != -1;
		}

		/*Servidor: Escuchar conexiones entrantes*/
		int listen();

		/*Servidor: Aceptar conexión*/
		int accept(Socket&);

		/*Cliente: Conecta al servicio del host en el puerto*/
		int connect(std::string host,int port)
		{
			if(!is_valid())
			{
				return 0;
			}

			maddress.sin_family = AF_INET;
			maddress.sin_port = htons(port);
			maddress.sin_addr.s_addr = std::stoi(host);

			return ::connect(sockfd, (sockaddr *)&maddress, sizeof(maddress)) != -1;
		}

		/*Envía una cadena de caracteres*/
		int send(std::string str);

		/*Recibir una cadena de caracteres y retorna la longitud de la cadena*/
		int recv(std::string& buf);

		/*Cerrar conexión*/
		int close();

		int getPort();

		std::string getHost();

		int getFD(){ return sockfd;}

		void setFD(int fd){}

		/*Longitud del nombre del host*/
		const int MAXHOSTNAME = 200;

		/*Puerto de datos*/
		const int BACKLOG = 20;

		/*Número de conexiones permitidas*/
		const int MAXCONNECTIONS = 10;

		/*Longitud máxima de datos que se puede recibir*/
		const int MAXRECV = 2048;
};