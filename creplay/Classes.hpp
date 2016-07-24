#pragma once
#include "stdafx.h"

class KeyCounter {
public:
	int M1 = 0;
	int M2 = 0;
	int K1 = 0;
	int K2 = 0;

	KeyCounter( ) {

	}

	KeyCounter( KeyCounter &other ) {
		M1 = other.M1;
		M2 = other.M1;
		K1 = other.K1;
		K2 = other.K2;
	}

	void Update( OsuKeys_t last, OsuKeys_t current ) {
		int diff = current - last;

		if ( diff > 0 ) {
			int u = 0;
		}

		// 		M1 += ( !last.HasFlag( Keys.M1 ) && current.HasFlag( Keys.M1 ) && !current.HasFlag( Keys.K1 ) ) ? 1 : 0;
		// 		M2 += ( !last.HasFlag( Keys.M2 ) && current.HasFlag( Keys.M2 ) && !current.HasFlag( Keys.K2 ) ) ? 1 : 0;
		// 		K1 += ( !last.HasFlag( Keys.K1 ) && current.HasFlag( Keys.K1 ) ) ? 1 : 0;
		// 		K2 += ( !last.HasFlag( Keys.K2 ) && current.HasFlag( Keys.K2 ) ) ? 1 : 0;

	}


	std::string ToString( ) {
		//TODO: .ToString
		return "NOT DONE";
		//return K1 + "|" + K2 + "|" + M1 + "|" + M2;
	}

};

struct ReplayFrame_t {
	// TODO: In documentation it says this is 64bit integer, do tests.
	int TimeDiff;
	int Time;
	float TimeInSeconds = Time / 1000.f;
	float X;
	float Y;
	OsuKeys_t Keys;
	//KeyCounter keyCounter;
};

//Life bar graph: comma separated pairs u|v, where u is the time in milliseconds into the song 
//and v is a floating point value from 0 - 1 that represents the amount of life you have at the given time (0 = life bar is empty, 1= life bar is full).
struct LifeFrame_t {
	int Time;
	float Percentage;
};

