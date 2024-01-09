#include "jpeg_decoder.h"
#include <cassert>
#include <exception>
#include <stdexcept>
#include <vector>
#include "fft.h"

JpegDecoder::JpegDecoder(FileReader& reader)
		: reader(reader),
		  img(),
		  q_tables(2),
		  mcu_h(8),
		  mcu_w(8),
		  input(64),
		  output(64),
		  calculator(8, &input, &output) {
	trees.emplace_back(std::vector<HuffmanTree>(2));
	trees.emplace_back(std::vector<HuffmanTree>(2));
}

void JpegDecoder::CheckFileEnded() {
	if (reader.Ended()) {
		throw std::invalid_argument("File unexpectedly ended");
	}
}

bool JpegDecoder::CheckStart() {
	uint8_t first = reader.ReadByte();
	uint8_t second = reader.ReadByte();
	return first == 255 && second == 216;
}

uint8_t JpegDecoder::GetSectionId() {
	uint8_t first = reader.ReadByte();
	uint8_t second = reader.ReadByte();
	if (first != 255) {
		throw std::invalid_argument("Incorrect section begin");
	}
	return second;
}

size_t JpegDecoder::GetLen() {
	size_t len = 0;
	for (int i = 0; i < 2; ++i) {
		len = (len << 8) ^ reader.ReadByte();
	}
	if (len < 2) {
		throw std::invalid_argument("Len of a section cannot be less than 2");
	}
	len -= 2;
	return len;
}

void JpegDecoder::HandleCOM(size_t len) {
	std::string res;
	res.reserve(len);
	for (size_t i = 0; i < len; ++i) {
		res += static_cast<char>(reader.ReadByte());
	}
	img.SetComment(res);
}

void JpegDecoder::HandleAPPn(size_t len) {
	for (size_t i = 0; i < len; ++i) {
		reader.ReadByte();
	}
}

void JpegDecoder::ZigZagDecompress(std::vector<int>& arr, std::vector<std::vector<int>>& mat,
								   int mat_x = 0, int mat_y = 0) {
	static const std::vector<std::vector<int>> kOrder = {
			{0, 1, 5, 6, 14, 15, 27, 28},     {2, 4, 7, 13, 16, 26, 29, 42},
			{3, 8, 12, 17, 25, 30, 41, 43},   {9, 11, 18, 24, 31, 40, 44, 53},
			{10, 19, 23, 32, 39, 45, 52, 54}, {20, 22, 33, 38, 46, 51, 55, 60},
			{21, 34, 37, 47, 50, 56, 59, 61}, {35, 36, 48, 49, 57, 58, 62, 63},
	};
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			mat[mat_x + i][mat_y + j] = arr[kOrder[i][j]];
		}
	}
}

void JpegDecoder::HandleDQT(size_t len) {
	if (len != 65 && len != 130) {
		throw std::invalid_argument("Incorrect len of section wit quant tables");
	}
	uint8_t data_byte = reader.ReadByte();
	uint8_t data_len = (data_byte >> 4) ? 2 : 1;
	uint8_t table_id = data_byte & 15;
	if (table_id > 1) {
		throw std::invalid_argument("Table id in quant table cannot be greater than 1");
	}
	std::vector<int> res;
	for (size_t i = 0; i < 64; ++i) {
		if (data_len == 2) {
			uint8_t first = reader.ReadByte();
			uint8_t second = reader.ReadByte();
			res.push_back((first << 8) ^ second);
		} else if (data_len == 1) {
			res.push_back(reader.ReadByte());
		}
	}
	q_tables[table_id] = res;
	if (len == 130) {
		HandleDQT(65);
	}
}

void JpegDecoder::HandleSOF0(size_t len) {
	meta_info.precision = reader.ReadByte();
	meta_info.height = reader.Read2Bytes();
	meta_info.width = reader.Read2Bytes();
	meta_info.channels = reader.ReadByte();
	meta_info.was = true;
	ch_info.resize(meta_info.channels);
	if (!meta_info.height || !meta_info.width || !meta_info.channels) {
		throw std::invalid_argument("Invalid paramters of picture in meta data");
	}
	if (static_cast<unsigned long long>(meta_info.height) * meta_info.width > 100'000'000) {
		throw std::invalid_argument("Picture is too big");
	}
	uint8_t last_id = 0;
	for (int i = 0; i < meta_info.channels; ++i) {
		uint8_t id = reader.ReadByte();
		if (++last_id != id) {
			throw std::invalid_argument("Wrong id order");
		}
		ch_info[i].h = reader.ReadHalfByte();
		ch_info[i].v = reader.ReadHalfByte();
		ch_info[i].id = reader.ReadByte();
	}
	mcu_h *= ch_info[0].v;
	mcu_w *= ch_info[0].h;
	if (ch_info[0].v != 1 && ch_info[0].v != 2) {
		throw std::invalid_argument("Invalid scaling values");
	}
	if (ch_info[0].h != 1 && ch_info[0].h != 2) {
		throw std::invalid_argument("Invalid scaling values");
	}
	if (static_cast<int>(len) != 6 + 3 * meta_info.channels) {
		throw std::invalid_argument("Incorrect len in meta info section");
	}
}

void JpegDecoder::HandleDHT(size_t len) {
	uint8_t cls = reader.ReadHalfByte();
	uint8_t id = reader.ReadHalfByte();
	if (cls > 1 || id > 1) {
		throw std::invalid_argument("Invalid class or id in section with building Huffman Tree");
	}
	std::vector<uint8_t> code_lenghts;
	std::vector<uint8_t> values;
	code_lenghts.reserve(16);
	size_t sum = 0;
	size_t cnt = 1;
	for (size_t i = 0; i < 16; ++i) {
		code_lenghts.push_back(reader.ReadByte());
		sum += code_lenghts.back();
		++cnt;
	}

	values.reserve(sum);
	for (size_t i = 0; i < sum; ++i) {
		values.push_back(reader.ReadByte());
		++cnt;
	}

	assert(values.size() == sum);

	trees[cls][id].Build(code_lenghts, values);
	if (cnt < len) {
		HandleDHT(len - cnt);
	}
}

std::vector<int> JpegDecoder::ReadEncoded(size_t& cur, int ch_id, int& old_coef) {
	if (ch_id > 1) {
		throw std::invalid_argument("Incorrect huffman tree id");
	}
	int cls = 0;
	std::vector<int> arr;
	arr.reserve(64);
	while (arr.size() < 64) {
		int value = 0;
		if (cur == bits.size()) {
			throw std::invalid_argument("Incorrect decoded section, not enough bits to decode");
		}
		while (!trees[cls][ch_id].Move(bits[cur++], value)) {
			if (cur == bits.size()) {
				throw std::invalid_argument("Incorrect decoded section, not enough bits to decode");
			}
		}

		if (value == 0 && cls) {
			break;
		}

		if (cur + (value & 15) > bits.size()) {
			throw std::invalid_argument("Incorrect decoded section, not enough bits to decode");
		}

		int res = 0, mlt = 0;
		if (bits[cur] == 0) {
			mlt = 1;
		}
		for (size_t i = cur; i < cur + (value & 15); ++i) {
			res <<= 1;
			res ^= bits[i] ^ mlt;
		}
		for (int i = 0; i < (value >> 4); ++i) {
			arr.push_back(0);
		}
		if (mlt) {
			res = -res;
		}
		if (!cls) {
			if ((value >> 4) != 0) {
				throw std::invalid_argument("Invalid decoded data");
			}
			res += old_coef;
			old_coef = res;
		}
		arr.push_back(res);
		cur += value & 15;
		cls = 1;
	}
	arr.resize(64);
	return arr;
}

std::vector<double> JpegDecoder::IDCT(const std::vector<std::vector<int>>& data, int x = 0,
									  int y = 0) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			input[i * 8 + j] = data[i + x][j + y];
		}
	}
	calculator.Inverse();
	return output;
}

int Normalization(double col) {
	return std::min(std::max(col + 128, 0.0), 255.0);
}

RGB ColorConversion(double y, double cb = 0, double cr = 0) {
	double r = cr * (2 - 2 * 0.299) + y;
	double b = cb * (2 - 2 * 0.114) + y;
	double g = (y - 0.114 * b - 0.299 * r) / .587;
	return RGB{Normalization(r), Normalization(g), Normalization(b)};
}

void Rescale(std::vector<std::vector<double>>& mat, int mcu_h, int mcu_w) {
	std::vector<std::vector<double>> new_mat = mat;
	int mlt_h = mcu_h / 8;
	int mlt_w = mcu_w / 8;
	for (size_t i = 0; i < new_mat.size(); ++i) {
		for (size_t j = 0; j < new_mat[0].size(); ++j) {
			new_mat[i][j] = mat[i / mlt_h][j / mlt_w];
		}
	}
	mat = new_mat;
}

void JpegDecoder::HandleSOS(size_t len, uint8_t& next_sec) {
	if (!meta_info.was) {
		throw std::invalid_argument("Section with encoded data cannot go without meta data =(");
	}
	int channels = reader.ReadByte();
	if (channels != meta_info.channels) {
		throw std::invalid_argument("Conflict info about number of channels");
	}
	if (static_cast<int>(len) != 1 + 3 + 2 * channels) {
		throw std::invalid_argument("Invalid len of SOS section");
	}
	uint8_t last_id = 0;
	for (int i = 0; i < channels; ++i) {
		uint8_t id = reader.ReadByte();
		if (++last_id != id) {
			throw std::invalid_argument("Incorrect order of channel ids in SOS section");
		}
		uint8_t huffman_dc_id = reader.ReadHalfByte();
		uint8_t huffman_ac_id = reader.ReadHalfByte();
		if (huffman_ac_id > 1 || huffman_dc_id > 1) {
			throw std::invalid_argument("Incorrect data in SOS section about huffman tables id");
		}
	}
	if (reader.ReadByte() != 0) {
		throw std::invalid_argument("Invalid progressive regime bits");
	}
	if (reader.ReadByte() != 63) {
		throw std::invalid_argument("Invalid progressive regime bits");
	}
	if (reader.ReadByte() != 0) {
		throw std::invalid_argument("Invalid progressive regime bits");
	}
	uint8_t first = reader.ReadByte();
	uint8_t second = reader.ReadByte();
	while (first != 255 || second == 0) {
		if (bits.size() > 100'000'000) {
			throw std::invalid_argument("Expected end of sos section a bit earlier");
		}
		for (int i = 7; i >= 0; --i) {
			bits.push_back((first >> i) & 1);
		}
		if (first == 255) {
			first = reader.ReadByte();
			second = reader.ReadByte();
		} else {
			first = second;
			second = reader.ReadByte();
		}
	}
	next_sec = second;
	size_t cur = 0;
	std::vector<int> olds(3);
	int ceil_width = (meta_info.width + mcu_w - 1) / mcu_w;
	int ceil_height = (meta_info.height + mcu_h - 1) / mcu_h;
	img.SetSize(meta_info.width, meta_info.height);

	std::vector<std::vector<std::vector<int>>> mats(
			channels, std::vector<std::vector<int>>(mcu_h, std::vector<int>(mcu_w)));
	std::vector<std::vector<int>> got(channels);
	std::vector<std::vector<std::vector<double>>> dct(
			channels, std::vector<std::vector<double>>(mcu_h, std::vector<double>(mcu_w)));
	for (int y = 0; y < ceil_height; ++y) {
		for (int x = 0; x < ceil_width; ++x) {
			for (int i = 0; i < channels; ++i) {
				if (i == 0) {
					for (int ix = 0; ix < mcu_h / 8; ++ix) {
						for (int iy = 0; iy < mcu_w / 8; ++iy) {
							got[i] = ReadEncoded(cur, ch_info[i].id, olds[i]);
							assert(got[i].size() == 64);
							for (size_t j = 0; j < 64; ++j) {
								if (static_cast<size_t>(ch_info[i].id) >= q_tables.size() ||
									j >= q_tables[ch_info[i].id].size()) {
									throw std::invalid_argument("Not enough DQT tables were given");
								}
								got[i][j] *= q_tables[ch_info[i].id][j];
							}
							ZigZagDecompress(got[i], mats[i], 8 * ix, 8 * iy);
							auto res = IDCT(mats[i], 8 * ix, 8 * iy);
							for (int dx = 0; dx < 8; ++dx) {
								for (int dy = 0; dy < 8; ++dy) {
									dct[i][8 * ix + dx][8 * iy + dy] = res[dx * 8 + dy];
								}
							}
						}
					}
				} else {
					got[i] = ReadEncoded(cur, ch_info[i].id, olds[i]);
					assert(got[i].size() == 64);
					for (size_t j = 0; j < 64; ++j) {
						if (static_cast<size_t>(ch_info[i].id) >= q_tables.size() ||
							j >= q_tables[ch_info[i].id].size()) {
							throw std::invalid_argument("Not enough DQT tables were given");
						}
						got[i][j] *= q_tables[ch_info[i].id][j];
					}
					ZigZagDecompress(got[i], mats[i]);
					auto res = IDCT(mats[i]);
					for (int dx = 0; dx < 8; ++dx) {
						for (int dy = 0; dy < 8; ++dy) {
							dct[i][dx][dy] = res[dx * 8 + dy];
						}
					}
					Rescale(dct[i], mcu_h, mcu_w);
				}
			}

			for (int i = 0; i < mcu_h; ++i) {
				for (int j = 0; j < mcu_w; ++j) {
					RGB pixel = channels > 1
								? ColorConversion(dct[0][i][j], dct[1][i][j], dct[2][i][j])
								: ColorConversion(dct[0][i][j]);
					size_t yy = y * mcu_h + i, xx = x * mcu_w + j;
					if (yy >= img.Height() || xx >= img.Width()) {
						continue;
					}
					img.SetPixel(yy, xx, pixel);
				}
			}
		}
	}
}
