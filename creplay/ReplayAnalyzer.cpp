#include "stdafx.h"
#include "Logs.h"

CReplayAnalyze::CReplayAnalyze( CBeatmap& beatmap, CReplay& replay ) {
	m_Beatmap = beatmap;
	m_Replay = std::move(replay);
	m_Replay.DumpInfo( );
// 	std::cout << m_Beatmap.m_vecHitObjects.at( 1 ).StartTime << '\n';
// 	std::cout << m_Replay.ReplayFrames.size( ) << '\n';
	int count = 0;
	for ( const auto& x : m_Replay.ReplayFrames ) {
		count++;
		if ( x.Keys < 4 ) continue;
		std::string tmp = { "Frame " + std::to_string( count ) + " : " + std::to_string( x.Keys ) + '\n' };
		Globals::Logs::g_Console.Write( tmp );
	}
}


void CReplayAnalyze::CheckTiming( ) {
	
}
