#include "stdafx.h"
#include "Replay.hpp"

Logs::CConsole g_Console( "Replay Analyser" );

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
// 		std::vector< char > vec_CodedStream = lzma_decompress( replayReader.read_bytes( ReplayLength ) );
//		std::string replayDataString { vec_CodedStream.begin( ), vec_CodedStream.end( ) };

//		std::cout << replayDataString << '\n';


		std::vector<char> replay_data; 
		for ( int i = 0; i < ReplayLength; ++i ) {
			replay_data.push_back( replayReader.read_byte( ) );
		}

		auto uncompressed = lzma_decompress( { replay_data.begin( ), replay_data.end( ) } );
		g_Console.Write( "result", std::string( replay_data.begin( ), replay_data.end( ) ), CONSOLE_WARNING );
		//TODO: bug
		std::string result { uncompressed.begin( ), uncompressed.end( ) };
		g_Console.Write( "result", result, CONSOLE_WARNING );


		std::vector< std::string > replayDataFrames = split( result, ',', false );
		int lastFrameTime = 0;
		std::cout << replayDataFrames.size( ) << '\n';
		for ( const std::string &frame : replayDataFrames ) {
			std::vector< std::string > frameElements = split( frame, '|', false );

			// docummented is only size of 4
			if ( frameElements.size( ) < 4 )
				continue;
			else if ( frameElements.size( ) != 4 )
				g_Console.Error( "frameElements.size() was higher than 4, unexpected error!\n" );

			//ReplayFrames.push_back( ReplayFrame_t { std::stoi( frameElements.at( 0 ) ), std::stoi( frameElements.at( 0 ) ) + lastFrameTime, ( std::stoi( frameElements.at( 0 ) ) + lastFrameTime ) / 1000.0f, std::stof( frameElements.at( 1 ) ), std::stof( frameElements.at( 2 ) ), static_cast< Keys_t >( std::stoi( frameElements.at( 3 ) ) ) } );
			//b_ReplayFrames.emplace_back( ReplayFrame { std::stoi( frameElements.at( 0 ) ), std::stoi( frameElements.at( 0 ) ) + lastFrameTime, ( std::stoi( frameElements.at( 0 ) ) + lastFrameTime ) / 1000.0f, std::stof( frameElements.at( 1 ) ), std::stof( frameElements.at( 2 ) ), static_cast< Keys >( std::stoi( frameElements.at( 3 ) ) ) } );
			//lastFrameTime = b_ReplayFrames.at( b_ReplayFrames.size( ) - 1 ).Time;

			ReplayFrame_t ThisFrame;
			{
				ThisFrame.TimeDiff = std::stoi( frameElements.at( 0 ) );
				ThisFrame.Time = std::stoi( frameElements.at( 0 ) ) + lastFrameTime;
				ThisFrame.X = std::stof( frameElements.at( 1 ) );
				ThisFrame.Y = std::stof( frameElements.at( 2 ) );
				ThisFrame.Keys = OsuKeys_t( std::stoi( frameElements.at( 3 ) ) );
			}
			g_Console.Error( std::to_string( ThisFrame.Time ) );
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

