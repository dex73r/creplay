// creplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main ( ) {
	
	std::string file = "replay.osr";

	CReplay x( file, true );
	x.DumpInfo( );

    return 0;
}

