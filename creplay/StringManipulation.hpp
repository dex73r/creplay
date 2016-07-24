#pragma once
#include "stdafx.h"

//TODO: When this grows bigger, make it a class.
__forceinline std::vector< std::string > split( const std::string &text, char sep, bool skipEmpty ) {
	std::vector< std::string > tokens;
	std::size_t start = 0, end = 0;
	if ( !skipEmpty ) {
		while ( ( end = text.find( sep, start ) ) != std::string::npos ) {
			tokens.push_back( text.substr( start, end - start ) );
			start = end + 1;
		}
		tokens.push_back( text.substr( start ) );
		return tokens;
	}
	while ( ( end = text.find( sep, start ) ) != std::string::npos ) {
		std::string temp = text.substr( start, end - start );
		if ( temp != "" )
			tokens.push_back( temp );
		start = end + 1;
	}
	std::string temp = text.substr( start );
	if ( temp != "" )
		tokens.push_back( temp );
	return tokens;
}