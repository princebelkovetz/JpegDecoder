#pragma once

#include <fstream>
#include <vector>

class FileReader {
public:
	explicit FileReader(std::istream& stream);

	bool ReadBit();

	std::vector<bool> ReadBits(size_t n);

	uint8_t ReadByte();

	uint8_t ReadHalfByte();

	uint16_t Read2Bytes();

	bool Ended() const;

	size_t GetReaden() const;

private:
	std::istream& stream_;
	uint8_t last_byte_;
	size_t bits_left_;
	size_t readen_;
	bool ended_;
};