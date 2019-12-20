#include "socket.h"
#include "socket_exceptions.h"

class ServerSocket : private Socket
{
	public:
		ServerSocket();
		ServerSocket(int port);
		~ServerSocket();
		ServerSocket& operator << (std::string&);
		ServerSocket& operator >> ( std::string& );
		void accept(ServerSocket&);
		void close();
		int fd();
		int port();
		std::string host();
};