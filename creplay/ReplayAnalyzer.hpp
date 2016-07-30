#pragma once
#include "Replay.hpp"
#include "Beatmap.hpp"

class CReplayAnalyze {
public:
	// *arg1: A beatmap
	// *arg2: A replay
	CReplayAnalyze( CBeatmap&, CReplay& );
protected:
	void CheckTiming( );
private:
	CBeatmap		m_Beatmap;
	CReplay			m_Replay;
};
