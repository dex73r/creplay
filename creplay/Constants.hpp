#pragma once
enum OsuKeys_t {
	KEYS_NONE				=	0,
	KEYS_M1					=	( 1 << 0 ),
	KEYS_M2					=	( 1 << 1 ),
	KEYS_K1					=	( 1 << 2 ) | ( 1 << 0 ),
	KEYS_K2					=	( 1 << 3 ) | ( 1 << 1 )
};

enum OsuMods_t {
	MODE_NONE				=	0,
	MODE_NOFAIL				=	( 1 << 0 ),
	MODE_EASY				=	( 1 << 1 ),
	MODE_NOVIDEO			=	( 1 << 2 ), //this isn't really a mod anymore.
	MODE_HIDDEN				=	( 1 << 3 ),
	MODE_HARDROCK			=	( 1 << 4 ),
	MODE_SUDDENDED			=	( 1 << 5 ),
	MODE_DOUBLETIME			=	( 1 << 6 ),
	MODE_RELAX				=	( 1 << 7 ),
	MODE_HALFTIME			=	( 1 << 8 ),
	MODE_NIGHTCORE			=	( 1 << 9 ), //always used with DT : 512 + 64 = 576
	MODE_FLASHLIGHT			=	( 1 << 10 ),
	MODE_AUTO				=	( 1 << 11 ),
	MODE_SPUNOUT			=	( 1 << 12 ),
	MODE_AUTOPILOT			=	( 1 << 13 ),
	MODE_PERFECT			=	( 1 << 14 ),
	MODE_MANIA4K			=	( 1 << 15 ),
	MODE_MANIA5K			=	( 1 << 16 ),
	MODE_MANIA6K			=	( 1 << 17 ),
	MODE_MANIA7K			=	( 1 << 18 ),
	MODE_MANIA8K			=	( 1 << 19 ),
	MODE_KEYMOD				=	1015808, // k4+k5+k6+k7+k8
	MODE_FADEIN				=	( 1 << 20 ),
	MODE_RANDOM				=	( 1 << 21 ),
	MODE_LASTMOD			=	( 1 << 22 ), //	Cinema
	MODE_TARGETPRAC			=	( 1 << 23 ), //osu!cuttingedge only
	MODE_KEY9				=	( 1 << 24 ),
	MODE_COOP				=	( 1 << 25 ),
	MODE_KEY1				=	( 1 << 26 ),
	MODE_KEY3				=	( 1 << 27 ),
	MODE_KEY2				=	( 1 << 28 ),
};

enum OsuGameModes_t {
	GAMEMODE_OSU			=	0,
	GAMEMODE_TAIKO			=	1,
	GAMEMODE_CTB			=	2,
	GAMEMODE_MANIA			=	3
};

enum ConsoleLog_t {
	CONSOLE_ERROR			=	( 1 << 0 ),
	CONSOLE_UNDEFINED		=	( 1 << 1 ),
	CONSOLE_WARNING			=	( 1 << 2 ),
	CONSOLE_MESSAGE			=	( 1 << 3 )// default
};

enum ErrorCodes_t {
	ERRORCODE_UNEXPECTED	=	( 1 << 0 ),
	ERRORCODE_UNDEFINED		=	( 1 << 1 ),
	ERRORCODE_WARNING		=	( 1 << 2 ),
	ERRORCODE_MESSAGE		=	( 1 << 3 )
};

enum NoteType_t {
	NOTE_NORMAL = 1,
	NOTE_CIRCLE = 2,
	NOTE_SLIDER = 4,
	NOTE_SPINNER = 8,
	NOTE_COLOURHAX = 112,
	NOTE_HOLD = 128
};


/// BITWISE TEMPLATES PART

template< class T >
inline T operator~( T a ) {
	return reinterpret_cast< T >( ~int( a ) );
}

inline OsuKeys_t operator|( OsuKeys_t a, OsuKeys_t b ){
	return static_cast< OsuKeys_t >( static_cast< int >( a ) | static_cast< int >( b ) );
}

template< class T >
inline T operator&( T a, T b ) {
	return reinterpret_cast< T >( int( a ) & int( b ) );
}

template< class T >
inline T operator^( T a, T b ) {
	return reinterpret_cast< T >( int( a ) ^ int( b ) );
}

template< class T >
inline T &operator|=( T &a, T b ) {
	return reinterpret_cast< T& >( reinterpret_cast< int& >( a ) |= int( b ) );
}

template< class T >
inline T &operator&=( T &a, T b ) {
	return reinterpret_cast< T& >( reinterpret_cast< int& >( a ) &= int( b ) );
}

template< class T >
inline T &operator^=( T &a, T b ) {
	return reinterpret_cast< T& >( reinterpret_cast< int& >( a ) ^= int( b ) );
}
