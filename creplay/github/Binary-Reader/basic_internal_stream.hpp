#pragma once
#include "types.hpp"
#include <vector>

class basic_internal_stream {
public:
	virtual ~basic_internal_stream() {}

	virtual Byte ReadByte() = 0;
	virtual std::vector<Byte> ReadBytes(const int size) = 0;
};
