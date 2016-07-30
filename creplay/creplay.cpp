// creplay.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main ( ) {


	//TODO: proper replay finding
	std::string path_replay = "C:\\replay.osr";
	std::string path_beat	= "C:\\beatmap.osu";

#ifdef _DEBUG
	//b.Debug_printhitobj( );
#endif

	CReplay r( path_replay, true );
	CBeatmap b;
	b.ReadFile( path_beat );
	CReplayAnalyze cr( b, r );

    return 0;
}
