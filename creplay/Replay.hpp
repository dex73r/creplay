#pragma once
#include "Constants.hpp"
#include "github/Binary-Reader/file_stream.hpp"
#include "Classes.hpp"

#ifndef uint
using UInt = unsigned int;
#endif

#if !defined(VNAME) && !defined(VDUMP)
	#define VNAME(x) #x
	#define VDUMP(x) std::cout << #x << " " << x << std::endl
#endif

class CReplay {
public:


	CReplay( ) {};
	CReplay( CReplay &&other );
	// *arg1: std::string reference to path of the replay
	// *arg2: bool to know whether to full load or not
	CReplay( std::string, bool );
	~CReplay( );

	// ==============================
	// Debug
	void DumpInfo( );
	// ==============================


	CReplay &CReplay::operator=( CReplay&& other );
protected:
	// a stream of binary information of .osr file
	BinaryReader< file_stream > replayReader;
private:

	// docummentation https://osu.ppy.sh/wiki/Osr_(file_format)
	// loads all information up to mod info
	void LoadHeader( );
	// loads the rest of it
	void Load( );

	std::string		m_MapHash;
	std::string		m_PlayerName;
	std::string		m_ReplayHash;
	std::string		m_GameMode_String;
	std::string		m_ReplayFile;
	UInt16			m_Count300;
	UInt16			m_Count100;
	UInt16			m_Count50;
	UInt16			m_CountGeki;
	UInt16			m_CountKatu;
	UInt16			m_CountMiss;
	UInt16			m_MaxCombo;
	UInt			m_TotalScore;
	int				m_FileFormat;
	bool			m_bIsPerfect;
	bool			m_bAxisFlip;
	OsuMods_t		m_Mods;
	OsuGameModes_t	m_GameMode;

	// switches
	bool headerLoaded;
	bool fullload_done;

	// contains Time and Percentage inside
	std::vector < LifeFrame_t > LifeFrames;

	//DateTime PlayTime;

	// a length of replay data
	int ReplayLength;

	// every single frame of replay is stored here
	std::vector < ReplayFrame_t > ReplayFrames;

	int Seed;
};

