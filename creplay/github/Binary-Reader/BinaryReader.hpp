#pragma once
#include "basic_internal_stream.hpp"
#include <memory>
#include <string>
#include <cstdint>

template<typename stream_type>
class BinaryReader
{
public:
	template<typename... stream_param>
	explicit BinaryReader(stream_param... arguments);

	template<typename type>	type read_type();
	Byte read_byte();
	int16_t read_int16();
	int32_t read_int32();
	int64_t read_int64();
	float_t read_float();
	double_t read_double();
	int read_Uleb128();
	std::string read_string();
	std::vector<Byte> read_bytes(const int size);

private:
	std::unique_ptr<basic_internal_stream> m_stream;
};

template<typename stream_type>
template<typename ... stream_param>
::BinaryReader<stream_type>::BinaryReader(stream_param... arguments) : m_stream{ std::make_unique<stream_type>(arguments...) }
{}

template<typename stream_type>
template<typename type>
type BinaryReader<stream_type>::read_type()
{
	Byte buffer[sizeof type];
	for (int i = 0; i < sizeof type; ++i)
		buffer[i] = read_byte();
	return *reinterpret_cast<type*>(buffer);
}

template<typename stream_type>
Byte BinaryReader<stream_type>::read_byte()
{
	return m_stream->ReadByte();
}

template<typename stream_type>
int16_t BinaryReader<stream_type>::read_int16()
{
	return read_type<int16_t>();
}

template<typename stream_type>
int32_t BinaryReader<stream_type>::read_int32()
{
	return read_type<int32_t>();
}

template<typename stream_type>
int64_t BinaryReader<stream_type>::read_int64()
{
	return read_type<int64_t>();
}

template<typename stream_type>
float_t BinaryReader<stream_type>::read_float()
{
	return read_type<float_t>();
}

template<typename stream_type>
double_t BinaryReader<stream_type>::read_double()
{
	return read_type<double_t>();
}

template<typename stream_type>
int BinaryReader<stream_type>::read_Uleb128()
{
	Byte byte = read_byte();
	int value = byte & 0x7f;

	for(int i = 1; byte & 0x80; ++i) {
		byte = read_byte();
		value |= (byte & 0x7f) << 7 * i;
	}
	return value;
}

template<typename stream_type>
std::string BinaryReader<stream_type>::read_string()
{
	// variable length
	// 00 = empty string
	// 0B <length> <char>* = normal string
	// <length> is encoded as an LEB, and is the byte length of the rest.
	// <char>* is encoded as UTF8, and is the string content.
	Byte kind = read_byte();
	if(kind == 0x00)
		return "";
	else if(kind != 0x0B)
		throw std::runtime_error{ "Invalid string!" };

	const int string_length = read_Uleb128();
	if(string_length <= 0)
		return "";

	std::string content;
	content.reserve(string_length);
	for(int i = 0; i < string_length; ++i)
		content.push_back(read_byte());

	return content;
}

template<typename stream_type>
std::vector<Byte> BinaryReader<stream_type>::read_bytes(const int size)
{
	return m_stream->ReadBytes(size);
}
