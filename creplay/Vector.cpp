#include "stdafx.h"
#include "Vector.hpp"

// Vector2i
vector2i_t vector2i_t::operator + ( const vector2i_t &v ){
	return vector2i_t { x + v.x, y + v.y };
}

vector2i_t vector2i_t::operator + ( const int &i ){
	return vector2i_t { x + i, y + i };
}

vector2i_t vector2i_t::operator - ( const vector2i_t &v ){
	return vector2i_t { x - v.x, y - v.y };
}

vector2i_t vector2i_t::operator - ( const int &i ){
	return vector2i_t { x - i, y - i };
}

// Vector2f
vector2f_t vector2f_t::operator + ( const vector2f_t &v ){
	return vector2f_t { x + v.x, y + v.y };
}

vector2f_t vector2f_t::operator + ( const float &i ){
	return vector2f_t { x + i, y + i };
}

vector2f_t vector2f_t::operator - ( const vector2f_t &v ){
	return vector2f_t { x - v.x, y - v.y };
}

vector2f_t vector2f_t::operator - ( const float &i ){
	return vector2f_t { x - i, y - i };
}

// Vector3i
vector3i_t vector3i_t::operator + ( const vector3i_t &v ){
	return vector3i_t { x + v.x, y + v.y, z + v.z };
}

vector3i_t vector3i_t::operator + ( const int &i ){
	return vector3i_t { x + i, y + i, z + i };
}

vector3i_t vector3i_t::operator - ( const vector3i_t &v ){
	return vector3i_t { x - v.x, y - v.y, z - v.z };
}

vector3i_t vector3i_t::operator - ( const int &i ){
	return vector3i_t { x - i, y - i, z - i };
}

// Vector3f
vector3f_t vector3f_t::operator + ( const vector3f_t &v ){
	return vector3f_t { x + v.x, y + v.y, z + v.z };
}

vector3f_t vector3f_t::operator + ( const float &i ){
	return vector3f_t { x + i, y + i, z + i };
}

vector3f_t vector3f_t::operator - ( const vector3f_t &v ){
	return vector3f_t { x - v.x, y - v.y, z - v.z };
}

vector3f_t vector3f_t::operator - ( const float &i ){
	return vector3f_t { x - i, y - i, z - i };
}

vector3f_t vector3f_t::operator -= ( const vector3f_t &v ){
	return vector3f_t { x -= v.x,y -= v.y, z -= v.z };
}

vector3f_t vector3f_t::operator -= ( const float &i ){
	return vector3f_t { x -= i,y -= i, z -= i };
}

vector3f_t vector3f_t::operator += ( const vector3f_t &v ){
	return vector3f_t { x += v.x,y += v.y, z += v.z };
}

vector3f_t vector3f_t::operator += ( const float &i ){
	return vector3f_t { x += i,y += i, z += i };
}

vector3f_t vector3f_t::operator * ( const vector3f_t &v ){
	return vector3f_t { x * v.x, y * v.y, z * v.z };
}

vector3f_t vector3f_t::operator * ( const float &i ){
	return vector3f_t { x * i, y * i, z * i };
}

vector3f_t vector3f_t::operator / ( const vector3f_t &v ){
	return vector3f_t { x / v.x, y / v.y, z / v.z };
}

vector3f_t vector3f_t::operator / ( const float &i ){
	return vector3f_t { x / i, y / i, z / i };
}

vector3f_t vector3f_t::operator *= ( const vector3f_t &v ){
	return vector3f_t { x *= v.x, y *= v.y, z *= v.z };
}

vector3f_t vector3f_t::operator *= ( const float &i ){
	return vector3f_t { x *= i, y *= i, z *= i };
}

vector3f_t vector3f_t::operator /= ( const vector3f_t &v ){
	return vector3f_t { x /= v.x, y /= v.y, z /= v.z };
}

vector3f_t vector3f_t::operator /= ( const float &i ){
	return vector3f_t { x /= i, y /= i, z /= i };
}

bool vector3f_t::operator==( vector3f_t const &v1 ) {
	return v1.x == x 
		&& v1.y == y 
		&& v1.z == z;
}

bool vector3f_t::operator==( vector3f_t const &v1 )const {
	return v1.x == x 
		&& v1.y == y 
		&& v1.z == z;
}

bool vector3f_t::operator!=( vector3f_t const &v1 ) {
	return !( v1 == *this );
}

bool vector3f_t::operator!=( vector3f_t const &v1 )const {
	return !( v1 == *this );
}
