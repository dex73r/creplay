#include "stdafx.h"

CReplayAnalyze::CReplayAnalyze( CBeatmap& beatmap, CReplay& replay ) {
	m_Beatmap = beatmap;
	m_Beatmap.Debug_printhitobj( );
	m_Replay = std::move(replay);
	m_Replay.DumpInfo( );
}
