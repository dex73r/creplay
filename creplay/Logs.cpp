#include "stdafx.h"
#include "Logs.h"

namespace Logs {
	Logs::CConsole::CConsole( std::string title ) : m_BaseFlag( CONSOLE_MESSAGE ) {
		m_strBaseTitle = "Replay Analyser";
		m_osBasic_stream.open( "RALog.txt" );
		m_strErrorBaseTitle = Errors::Error( ERRORCODE_UNEXPECTED );
		m_osBasic_stream << "=== " << m_strBaseTitle << " started successfully ===\n";
	}

	void Logs::CConsole::Write( std::string text ) {
		Write( text, m_strBaseTitle, m_BaseFlag );
	}

	void Logs::CConsole::Write( std::string caption, std::string text ) {
		Write( text, caption, m_BaseFlag );
	}

	void Logs::CConsole::Write( std::string caption, ConsoleLog_t logstatus ) {
		Write( m_strBaseTitle, caption, logstatus );
	}

	void Logs::CConsole::Write( std::string caption, std::string text, ConsoleLog_t logstatus = CONSOLE_MESSAGE ) {
		switch ( logstatus ) {
				//TODO: add time line
			case CONSOLE_WARNING:
				m_osBasic_stream << "[WARNING] " << text << '\n';
				break;
			case CONSOLE_ERROR:
				m_osBasic_stream << "[ERROR] " << text << '\n';
				break;
			case CONSOLE_MESSAGE:
				m_osBasic_stream << text << '\n';
				break;
			default:
				throw std::runtime_error { Errors::Error( ERRORCODE_UNEXPECTED ) };
		}
	}

	void Logs::CConsole::Error( std::string error_message ) {
		Write( m_strErrorBaseTitle, error_message, CONSOLE_ERROR );
	}

	Logs::CConsole::~CConsole( ) {
		m_osBasic_stream << "=== LOG END ===";
		m_osBasic_stream.close( );
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

