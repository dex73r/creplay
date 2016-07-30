#pragma once
#include "Replay.hpp"
#include "Beatmap.hpp"

class CReplayAnalyze {
public:
	// *arg1: A beatmap
	// *arg2: A replay
	CReplayAnalyze( CBeatmap&, CReplay& );
private:
	CBeatmap		m_Beatmap;
	CReplay			m_Replay;
};
