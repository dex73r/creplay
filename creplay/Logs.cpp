#include "stdafx.h"
#include "Logs.h"

namespace Globals {
	namespace Logs {
		Logs::CConsole::CConsole( ) : m_BaseFlag( CONSOLE_MESSAGE ) {
			m_strBaseTitle = "Replay Analyzer";
			m_osBasic_stream.open( "RALog.txt" );
			m_strErrorBaseTitle = Errors::Error( ERRORCODE_UNEXPECTED );
			m_osBasic_stream << "=== " << m_strBaseTitle << " started successfully ===\n";
		}

		void Logs::CConsole::Error( std::string error_message ) {
			Write( m_strErrorBaseTitle, error_message, CONSOLE_ERROR );
		}

		Logs::CConsole::~CConsole( ) {
			m_osBasic_stream << "=== LOG END ===";
			m_osBasic_stream.close( );
		}
	}

}
namespace Errors {
	std::string Error( int errorcode ) {
		switch ( errorcode ) {
			case ERRORCODE_UNEXPECTED:
				return "Unexcepted runtime error code 0x01!";
			case ERRORCODE_UNDEFINED:
				return "Undefined runtime error code 0x02!";
			default: throw( std::exception { "Fatal error in errorcodes!" } );
		}
	}
}