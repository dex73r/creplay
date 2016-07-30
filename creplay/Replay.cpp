#include "stdafx.h"
#include "Replay.hpp"

namespace Logs {
	CConsole g_Console( "Replay analyzer" );
}

CReplay::CReplay( std::string strPath, bool bFull_load = true ) {
	m_ReplayFile = strPath;
	replayReader = BinaryReader< file_stream >( m_ReplayFile, std::ios::in | std::ios::binary ); {
		LoadHeader( );

		if ( bFull_load ) {
			Load( );
		}
	}
}

CReplay::~CReplay( ) {
	// ?
}

void CReplay::LoadHeader( ) {

	m_GameMode = OsuGameModes_t( replayReader.read_byte( ) );
	m_FileFormat = replayReader.read_int32( );
	m_MapHash = replayReader.read_string( );
	m_PlayerName = replayReader.read_string( );
	m_ReplayHash = replayReader.read_string( );
	m_Count300 = replayReader.read_type< uint16_t >( );
	m_Count100 = replayReader.read_type< uint16_t >( );
	m_Count50 = replayReader.read_type< uint16_t >( );
	m_CountGeki = replayReader.read_type< uint16_t >( );
	m_CountKatu = replayReader.read_type< uint16_t >( );
	m_CountMiss = replayReader.read_type< uint16_t >( );
	m_TotalScore = replayReader.read_type< uint32_t >( );
	m_MaxCombo = replayReader.read_type< uint16_t >( );
	m_bIsPerfect = replayReader.read_type< bool >( );
	m_Mods = OsuMods_t( replayReader.read_int32( ) );
	headerLoaded = true;
	m_GameMode_String = VNAME( GameMode );
}

void CReplay::Load( ) {
	if ( !headerLoaded )
		LoadHeader( );
	if ( fullload_done )
		return;

	std::string lifeData = replayReader.read_string( );

	//life
	if ( !( lifeData.empty( ) ) ) {
		std::vector< std::string > vec_Life_block = split( lifeData, ',', false );

		for ( unsigned int i = 0; i < vec_Life_block.size( ); ++i ) {

			std::vector< std::string > vec_Split = split( vec_Life_block.at( i ), '|', false );
			if ( vec_Split.size( ) < 2 )
				continue;

			LifeFrame_t frame;
			frame.Time = std::stoi( vec_Split.at( 0 ) );
			frame.Percentage = std::stof( vec_Split.at( 1 ) );
			LifeFrames.emplace_back( frame );
		}

	}

	// timestamp https://msdn.microsoft.com/en-us/library/system.datetime.ticks%28v=vs.110%29.aspx
	long long ticks = replayReader.read_type< long long >( );

	// length is correct
	ReplayLength = replayReader.read_int32( );
	// Compressed replay data
	if ( ReplayLength > 0 ) {
		int lastTime = 0;
		std::vector<unsigned char> replay_data;
		for ( int i = 0; i < ReplayLength; ++i ) {
			replay_data.push_back( replayReader.read_byte( ) );
		}

		// Changed it to just the entire vector as the parameter
		auto uncompressed = lzma_decompress( replay_data );
		std::string result { uncompressed.begin( ), uncompressed.end( ) };		
		std::vector< std::string > replayDataFrames = split( result, ',', false );
		int lastFrameTime = 0;
		for ( const std::string& frame : replayDataFrames ) {
			std::vector< std::string > frameElements = split( frame, '|', false );

			// documented is only size of 4 https://osu.ppy.sh/wiki/Osr_(file_format)
			if ( frameElements.size( ) < 4 ) 
				continue;
			else if ( frameElements.size( ) != 4 )
				Logs::g_Console.Error( "frameElements.size() was higher than 4, unexpected error!\n" );

			ReplayFrame_t ThisFrame;
			{
				ThisFrame.TimeDiff = std::stoi( frameElements.at( 0 ) );
				ThisFrame.Time = std::stoi( frameElements.at( 0 ) ) + lastFrameTime;
				ThisFrame.X = std::stof( frameElements.at( 1 ) );
				ThisFrame.Y = std::stof( frameElements.at( 2 ) );
				ThisFrame.Keys = OsuKeys_t( std::stoi( frameElements.at( 3 ) ) );
			}
			ReplayFrames.push_back( ThisFrame );
			lastFrameTime = ReplayFrames.at( ReplayFrames.size( ) - 1 ).Time;
		}

	}
	fullload_done = true;
}

void CReplay::DumpInfo( ) {
	printf( "%dx300, %dx100, %dx50, %d misses\n", m_Count300, m_Count100, m_Count50, m_CountMiss );
	printf( "m_TotalScore: %i with combo %d", m_TotalScore, m_MaxCombo );
	if ( m_bIsPerfect )
		printf( "and you fc'd it\n" );
	else
		printf( ", well, you should try more to fc it, %s.\n", m_PlayerName.c_str( ) );

}

CReplay::CReplay( CReplay &&other )
	: replayReader( std::move( other.replayReader ) ),
	m_MapHash( std::move( other.m_MapHash ) ),
	m_PlayerName( std::move( other.m_PlayerName ) ),
	m_ReplayHash( std::move( other.m_ReplayHash ) ),
	m_GameMode_String( std::move( other.m_GameMode_String ) ),
	m_ReplayFile( std::move( other.m_ReplayFile ) ),
	m_Count300( other.m_Count300 ),
	m_Count100( other.m_Count100 ),
	m_Count50( other.m_Count50 ),
	m_CountGeki( other.m_CountGeki ),
	m_CountKatu( other.m_CountKatu ),
	m_CountMiss( other.m_CountMiss ),
	m_MaxCombo( other.m_MaxCombo ),
	m_TotalScore( other.m_TotalScore ),
	m_FileFormat( other.m_FileFormat ),
	m_bIsPerfect( other.m_bIsPerfect ),
	m_bAxisFlip( other.m_bAxisFlip ),
	m_Mods( other.m_Mods ),
	m_GameMode( other.m_GameMode ),
	headerLoaded( other.headerLoaded ),
	fullload_done( other.fullload_done ),
	LifeFrames( std::move( other.LifeFrames ) ),
	ReplayLength( other.ReplayLength ),
	ReplayFrames( std::move( other.ReplayFrames ) ),
	Seed( other.Seed )
{}


CReplay &CReplay::operator=( CReplay &&other ) {
	if ( this == &other )
		return *this;
	replayReader = std::move( other.replayReader );
	m_MapHash = std::move( other.m_MapHash );
	m_PlayerName = std::move( other.m_PlayerName );
	m_ReplayHash = std::move( other.m_ReplayHash );
	m_GameMode_String = std::move( other.m_GameMode_String );
	m_ReplayFile = std::move( other.m_ReplayFile );
	m_Count300 = other.m_Count300;
	m_Count100 = other.m_Count100;
	m_Count50 = other.m_Count50;
	m_CountGeki = other.m_CountGeki;
	m_CountKatu = other.m_CountKatu;
	m_CountMiss = other.m_CountMiss;
	m_MaxCombo = other.m_MaxCombo;
	m_TotalScore = other.m_TotalScore;
	m_FileFormat = other.m_FileFormat;
	m_bIsPerfect = other.m_bIsPerfect;
	m_bAxisFlip = other.m_bAxisFlip;
	m_Mods = other.m_Mods;
	m_GameMode = other.m_GameMode;
	headerLoaded = other.headerLoaded;
	fullload_done = other.fullload_done;
	LifeFrames = std::move( other.LifeFrames );
	ReplayLength = other.ReplayLength;
	ReplayFrames = std::move( other.ReplayFrames );
	Seed = other.Seed;
	return *this;
}