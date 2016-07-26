#include "stdafx.h"

void CBeatmap::ReadFile( std::string beatmapfile ) {
	m_strBeatmapFile = beatmapfile;
	m_vecHitObjects.clear( );
	m_vecTimingObjects.clear( );
	m_fBeatLength = 1.f;

	std::string strLine;
	int fCoordX;
	int fCoordY;
	int iStartTime;
	int iCircleType;
	int iEndTime;
	float fBeatLength;
	float fSingle;

	bool bHitObjects = false;
	bool bTimingPoints = false;
	bool bDifficulty = false;
	bool bGeneral = false;
	bool bFileFormat = false;

	// read all lines of program
	std::basic_ifstream< char > ioFile( m_strBeatmapFile );
	std::string strTemp_line;

	if ( ioFile.is_open( ) ) {
		while ( getline( ioFile, strTemp_line ) ) {
			m_vec_strLines.push_back( strTemp_line );
		}
	}
	// start the actual parsing.
	for ( unsigned int i = 0; i < m_vec_strLines.size( ); i++ ) {

		std::string strFileLine = m_vec_strLines [ i ];
		if ( !bFileFormat ) {
			if ( strFileLine.find( "file format" ) != std::string::npos ) {
				m_iFileFormat = stoi( split( strFileLine, 'v', false ) [ 1 ] );
			}
		}
		else if ( strFileLine == "[General]" ) {
			bGeneral = true;
		}
		else if ( bGeneral ) {
			if ( !( strFileLine != "" ) ) {
				bGeneral = false;
			}
			else if ( ( strFileLine.find( "Mode" ) != std::string::npos ) ) {
				//todo: error handling
				strLine = strFileLine.substr( strFileLine.length( ) - 1 );
				m_Mode = OsuGameModes_t( stoi( strLine ) );
			}

		}
		if ( strFileLine == "[Difficulty]" ) {
			bDifficulty = true;
		}
		else if ( bDifficulty ) {
			if ( !( strFileLine != "" ) ) {
				bDifficulty = false;
			}
			else if ( strFileLine.find( "HPDrainRate:" ) != std::string::npos ) {
				strLine = strFileLine.substr( strFileLine.length( ) - 1 );
				m_fHealthDrain = stof( strLine );
			}
			else if ( strFileLine.find( "ApproachRate:" ) != std::string::npos ) {
				strLine = strFileLine.substr( strFileLine.length( ) - 1 );
				m_fApproachRate = stof( strLine );
			}
			else if ( strFileLine.find( "CircleSize:" ) != std::string::npos ) {
				strLine = strFileLine.substr( 11 );
				m_fCircleSize = stof( strLine );
			}
			else if ( strFileLine.find( "OverallDifficulty:" ) != std::string::npos ) {
				strLine = strFileLine.substr( 18 );
				m_fOverallDifficulty = stof( strLine );
			}
			else if ( strFileLine.find( "SliderMultiplier" ) != std::string::npos ) {
				strLine = strFileLine.substr( 17 );
				m_fSliderMultiplier = stof( strLine );
			}
		}
		else if ( strFileLine == "[TimingPoints]" ) {
			bTimingPoints = true;
		}
		else if ( bTimingPoints ) {
			if ( !( strFileLine != "" ) ) {
				bTimingPoints = false;
				m_vecTimingObjects.push_back( m_vecTimingObjects [ m_vecTimingObjects.size( ) - 1 ] );
			}
			else {
				float single1 = stof( split( strFileLine, ',', false ) [ 1 ] );

				iStartTime = stoi( split( strFileLine, ',', false ) [ 0 ] );
				TimingPoint_t timingPoint;
				timingPoint.Time = iStartTime;
				timingPoint.BeatLength = single1;
				m_vecTimingObjects.push_back( timingPoint );
			}
		}
		else if ( strFileLine == "[HitObjects]" ) {
			bHitObjects = true;
		}
		else if ( bHitObjects ) {
			fCoordX = stoi( split( strFileLine, ',', false ) [ 0 ] );
			fCoordY = stoi( split( strFileLine, ',', false ) [ 1 ] );
			iStartTime = stoi( split( strFileLine, ',', false ) [ 2 ] );
			iCircleType = stoi( split( strFileLine, ',', false ) [ 3 ] );
			if ( ( iCircleType & 1 ) > 0 ) {

				HitObject_t hitObject;
				vector2f_t p;
				p.x = float( fCoordX );
				p.y = float( fCoordY );
				hitObject.StartTime = iStartTime,
					hitObject.StartPoint = p,
					hitObject.Type = NOTE_NORMAL;
				m_vecHitObjects.push_back( hitObject );
			}
			else if ( ( iCircleType & 2 ) <= 0 ) {
				iEndTime = stoi( split( strFileLine, ',', false ) [ 5 ] );
				if ( iEndTime < 1 ) {
					std::string line = split( strFileLine, ',', false ) [ 5 ];
					iEndTime = stoi( split( line, ':', false ) [ 0 ] );
				}
				HitObject_t hitObject1;
				vector2f_t p;
				p.x = float( fCoordX );
				p.y = float( fCoordY );
				hitObject1.StartTime = iStartTime,
					hitObject1.EndTime = iEndTime,
					hitObject1.StartPoint = p,
					hitObject1.Type = NOTE_SPINNER,
					hitObject1.IsSpiner = true;
				m_vecHitObjects.push_back( hitObject1 );
			}
			else {
				float single2 = stof( split( strFileLine, ',', false ) [ 7 ] );
				float single3 = stof( split( strFileLine, ',', false ) [ 6 ] );
				unsigned int iCount = 0;
				while ( iStartTime >= m_vecTimingObjects [ iCount ].Time ) {
					if ( iCount > m_vecTimingObjects.size( ) - 2 ) {
						break;
					}

					if ( m_vecTimingObjects [ iCount ].BeatLength > 0.f ) {
						m_fBeatLengthBase = m_vecTimingObjects [ iCount ].BeatLength;
					}
					iCount++;

				}
				m_fBeatLength = ( iCount == 0
								  ? m_vecTimingObjects [ iCount ].BeatLength
								  : m_vecTimingObjects [ iCount - 1 ].BeatLength );
				if ( m_fBeatLength >= 0.f ) {
					fBeatLength = m_fBeatLength * ( single2 / m_fSliderMultiplier ) / 100.f;
					fSingle = fBeatLength * single3;
					HitObject_t hitObject2;
					vector2f_t p;
					p.x = float( fCoordX );
					p.y = float( fCoordY );
					hitObject2.StartTime = iStartTime,
						hitObject2.EndTime = int( fSingle ) + iStartTime,
						hitObject2.StartPoint = p,
						hitObject2.Type = NOTE_SLIDER,
						hitObject2.IsSlider = true;

					m_vecHitObjects.push_back( hitObject2 );
					m_fBeatLengthBase = m_fBeatLength;
				}
				else {
					float beatLength1 = float( int( m_fBeatLength ) ) / -100.f;
					m_fBeatLength = m_fBeatLengthBase * beatLength1;
					fBeatLength = m_fBeatLength * ( single2 / m_fSliderMultiplier ) / 100.f;
					fSingle = fBeatLength * single3;
					HitObject_t hitObject3;
					vector2f_t p;
					p.x = float( fCoordX );
					p.y = float( fCoordY );
					hitObject3.StartTime = iStartTime,
						hitObject3.EndTime = int( fSingle ) + iStartTime,
						hitObject3.StartPoint = p,
						hitObject3.Type = NOTE_SLIDER,
						hitObject3.IsSlider = true;

					m_vecHitObjects.push_back( hitObject3 );
				}
			}
		}
	}
}