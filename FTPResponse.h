#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;

class FTPResponse {
	private:
		string message;
		string status;

	public:
		FTPResponse()
		{

		}

		~FTPResponse()
		{
			message = "";
			status = "";
		}

		FTPResponse(string response)
		{
			setResponse(response);
		}

		FTPResponse(string response,string code)
		{
			message = response;
			status = code;
		}
		
		void setResponse(string)
		{
			message = response;
			status = "";
		}

		string parseResponse()
		{
			string::size_type firstPos = message.find_first_not_of(" ", 0);
			if(isdigit(message[firstPos]))
			{
				string::size_type lastPos = message.find(" ",firstPos);
				status = message.substr(firstPos,lastPos-firstPos);
				firstPos = message.find_first_not_of(" ", lastPos);
			}
			return message.substr(firstPos);
		}

		int returnCode();
		
		string parseResponse(int&);
		string formResponse();
		int getPort();
};