#pragma once
#include "stdafx.h"
struct vector2i_t{
	int x, y;

	vector2i_t operator + ( const vector2i_t & );
	vector2i_t operator + ( const int & );
	vector2i_t operator - ( const vector2i_t & );
	vector2i_t operator - ( const int & );
};

struct vector2f_t{
	float x, y;

	vector2f_t operator + ( const vector2f_t & );
	vector2f_t operator + ( const float & );
	vector2f_t operator - ( const vector2f_t & );
	vector2f_t operator - ( const float & );
};

struct vector3i_t{
	int x, y, z;

	vector3i_t operator + ( const vector3i_t & );
	vector3i_t operator + ( const int & );
	vector3i_t operator - ( const vector3i_t & );
	vector3i_t operator - ( const int & );
};

struct vector3f_t{
	float x, y, z;

	vector3f_t operator + ( const vector3f_t & );
	vector3f_t operator + ( const float & );
	vector3f_t operator - ( const vector3f_t & );
	vector3f_t operator - ( const float & );
	vector3f_t operator += ( const vector3f_t & );
	vector3f_t operator += ( const float & );
	vector3f_t operator -= ( const vector3f_t & );
	vector3f_t operator -= ( const float & );
	vector3f_t operator * ( const vector3f_t & );
	vector3f_t operator * ( const float & );
	vector3f_t operator / ( const vector3f_t & );
	vector3f_t operator / ( const float & );
	vector3f_t operator *= ( const vector3f_t & );
	vector3f_t operator *= ( const float & );
	vector3f_t operator /= ( const vector3f_t & );
	vector3f_t operator /= ( const float & );

	bool vector3f_t::operator == ( vector3f_t const & );
	bool vector3f_t::operator == ( vector3f_t const & ) const;
	bool vector3f_t::operator != ( vector3f_t const & );
	bool vector3f_t::operator != ( vector3f_t const & ) const;
};
