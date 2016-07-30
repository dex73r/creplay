#pragma once
namespace Errors {

	// ERRORS:
	// 0x01 - "Unexcepted runtime error code 0x01!"
	// 0x02 - "Undefined runtime error code 0x02!"

	std::string Error( int errorcode );
}

namespace Globals {

	namespace Logs {

		class CConsole {
		public:

			CConsole( );
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
		private:
			std::ofstream m_osBasic_stream;
			std::string m_strBaseTitle;
			std::string m_strErrorBaseTitle;
			ConsoleLog_t m_BaseFlag;

		};

		static CConsole g_Console;
	}
}