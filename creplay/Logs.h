#pragma once

namespace Logs {

	class CConsole {
	public:
		// *arg1: set the base title of console,
		// *arg2: file stream
		// allocates log file
		CConsole( std::string );
		// *arg1: caption,
		// *arg2: debug message,
		// *arg3: flag, usually CONSOLE_MESSAGE
		void Write( std::string, std::string, ConsoleLog_t );
		void Write( std::string, std::string );
		void Write( std::string, ConsoleLog_t );
		void Write( std::string );

		// *arg1: error meesage
		// function calls Write function with error flag
		void Error( std::string );

		// end the file stream
		~CConsole( );
	protected:
		// *arg1: caption is stated, message is defined by programmer, status is always CONSOLE_ERROR,
		// throws exception
		
	private:
		std::ofstream m_osBasic_stream;
		std::string m_strBaseTitle;
		std::string m_strErrorBaseTitle;
		ConsoleLog_t m_BaseFlag;

	};
}

namespace Errors {
	
	// ERRORS:
	// 0x01 - "Unexcepted runtime error code 0x01!"
	// 0x02 - "Undefined runtime error code 0x02!"

	std::string Error( int errorcode );
}