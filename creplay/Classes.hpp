#pragma once
#include "stdafx.h"

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
