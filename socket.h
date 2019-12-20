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
		Socket();

		~Socket();

		int is_valid(){ return sockfd != -1; }

		int create();

		/*Servidor: Forjar enlace a puerto*/
		int bind(int port);

		/*Servidor: Escuchar conexiones entrantes*/
		int listen();

		/*Servidor: Aceptar conexión*/
		int accept(Socket&);

		/*Cliente: Conecta al servicio del host en el puerto*/
		int connect(std::string host,int port);

		/*Envía una cadena de caracteres*/
		int send(std::string str);

		/*Recibir una cadena de caracteres y retorna la longitud de la cadena*/
		int recv(std::string& buf);

		/*Cerrar conexión*/
		int close();

		int getPort();

		std::string getHost();

		int getFD(){ return sockfd}

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