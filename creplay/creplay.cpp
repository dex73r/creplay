// creplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main ( ) {
	//TODO: proper replay finding
	std::string file = "C:\\replay.osr";

	CReplay x( file, true );
	x.DumpInfo( );

	CBeatmap b;
	b.ReadFile( "C:\\beatmap.osu" );
#ifdef _DEBUG
	b.Debug_printhitobj( );
#endif
	CReplayAnalyze cr( b, x );

    return 0;
}
