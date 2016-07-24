#include "stdafx.h"
#include "file_stream.hpp"


file_stream::file_stream(): valid{ false } {}

file_stream::~file_stream()
{
}

Byte file_stream::ReadByte()
{
	if(!valid)
		throw std::runtime_error{ "Error!" };

	Byte b;
	if (!m_file.read(&b, 1))
		valid = false;

	return b;
}

std::vector<Byte> file_stream::ReadBytes(const int size)
{
	//if (!valid)
	//	throw std::runtime_error{ "Error!" };

	//std::vector<Byte> data(size);
	//if(!m_file.read(data.data(), size))
	//	valid = false;

	std::vector<Byte> data;
	for (int i = 0; i < size; ++i)
		data.push_back(ReadByte());

	return data;
}
