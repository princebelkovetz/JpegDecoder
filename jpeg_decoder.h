#include <iostream>
#include <map>
#include <stdexcept>
#include "file_reader.h"
#include "huffman.h"
#include "fft.h"
#include "image.h"

using HuffmanForest = std::vector<std::vector<HuffmanTree>>;
using QuantTables = std::vector<std::vector<int>>;

struct MetaInfo {
	int precision;
	int height;
	int width;
	int channels;
	bool was = false;
};

struct ChannelInfo {
	int h, v, id;
};

class JpegDecoder {
public:
	JpegDecoder(FileReader& reader);

	void CheckFileEnded();

	bool CheckStart();

	uint8_t GetSectionId();

	size_t GetLen();

	void HandleCOM(size_t len);

	void HandleAPPn(size_t len);

	void ZigZagDecompress(std::vector<int>& arr, std::vector<std::vector<int>>& mat, int mat_x,
						  int mat_y);

	void HandleDQT(size_t len);

	void HandleSOF0(size_t len);

	std::vector<double> IDCT(const std::vector<std::vector<int>>& data, int x, int y);

	std::vector<int> ReadEncoded(size_t& cur, int ch_id, int& old_coef);

	void HandleDHT(size_t len);

	void HandleSOS(size_t len, uint8_t& next_sec);

	FileReader& reader;
	Image img;
	QuantTables q_tables;
	MetaInfo meta_info;
	std::vector<ChannelInfo> ch_info;
	HuffmanForest trees;
	std::vector<bool> bits;
	int mcu_h;
	int mcu_w;
	std::vector<double> input;
	std::vector<double> output;
	DctCalculator calculator;
};
