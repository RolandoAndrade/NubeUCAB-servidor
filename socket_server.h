#include "socket.h"
#include "socket_exceptions.h"

class ServerSocket : private Socket
{
	public:
		ServerSocket()
		{
			if(!Socket::create())
			{
				throw SocketException(strerror(errno));
			}
		}

		ServerSocket(int port)
		{
			if(!Socket::create())
			{
				throw SocketException(strerror(errno));
			}

			if(!Socket::bind(port))
			{
				throw SocketException(strerror(errno));
			}

			if(!Socket::listen())
			{
				throw SocketException(strerror(errno));
			}
		}

		~ServerSocket()
		{

		}
		/*Función para mandar datos desde el socket*/

		ServerSocket& operator << (std::string& data)
		{
			if(Socket::send(data)==-1)
			{
				throw SocketException(strerror(errno));
			}

			return *this;
		}

		ServerSocket& operator >> (std::string& data)
		{
			if(Socket::recv(data)==-1)
			{
				throw SocketException(strerror(errno));
			}

			return *this;
		}

		void accept(ServerSocket &ssocket)
		{
			if(!Socket::accept(ssocket))
			{
				throw SocketException(strerror(errno));
			}
		}

		void close()
		{
			if(!Socket::close())
			{
				throw SocketException(strerror(errno));
			}
		}

		int fd();
		int port();
		std::string host();
};