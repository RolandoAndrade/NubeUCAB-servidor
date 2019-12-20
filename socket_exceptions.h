#include <string>
#include <cerrno>

class SocketException 
{
	private:
		std::string message;

	public:
		SocketException(std::string);
		~SocketException();
		std::string getMessage();
};