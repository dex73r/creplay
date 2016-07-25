#pragma once
namespace Errors {

	// ERRORS:
	// 0x01 - "Unexcepted runtime error code 0x01!"
	// 0x02 - "Undefined runtime error code 0x02!"

	std::string Error( int errorcode );
}

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
		template < typename Type >
		__forceinline void Write( std::string caption, Type txt, ConsoleLog_t logstatus ) {
			if ( logstatus )
				m_osBasic_stream << caption << " - ";
			switch ( logstatus ) {
				//TODO: add time line
				case CONSOLE_WARNING:
					m_osBasic_stream << "[WARNING] " << txt << '\n';
					break;
				case CONSOLE_ERROR:
					m_osBasic_stream << "[ERROR] " << txt << '\n';
					break;
				case CONSOLE_MESSAGE:
					m_osBasic_stream << txt << '\n';
					break;
				default:
					throw std::runtime_error { Errors::Error( ERRORCODE_UNEXPECTED ) };
			}
		}
		template < typename Type > void Write( std::string caption, Type txt ) { Write( caption, txt, CONSOLE_MESSAGE ); }
		template < typename Type > void Write( Type txt, ConsoleLog_t logstatus ) { Write( m_strBaseTitle, txt, logstatus ); }
		template < typename Type > void Write( Type txt ) { Write( m_strBaseTitle, txt, CONSOLE_MESSAGE ); }

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