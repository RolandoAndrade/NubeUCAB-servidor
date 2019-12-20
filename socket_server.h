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

		~ServerSocket();
		ServerSocket& operator << (std::string&);
		ServerSocket& operator >> ( std::string& );
		void accept(ServerSocket&);
		void close();
		int fd();
		int port();
		std::string host();
};