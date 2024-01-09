#include "decoder.h"
#include <iostream>
#include <map>
#include <stdexcept>
#include "file_reader.h"
#include "huffman.h"
#include "fft.h"
#include "jpeg_decoder.h"

Image Decode(std::istream& input) {
	FileReader reader(input);
	JpegDecoder decoder(reader);
	if (!decoder.CheckStart()) {
		throw std::invalid_argument("Incorrect file start");
	}

	uint8_t next_sec;
	bool changed = false;
	while (true) {
		uint8_t section_id = changed ? next_sec : decoder.GetSectionId();
		changed = false;
		if (section_id == 217) {
			break;
		}
		size_t len = decoder.GetLen();

		size_t was_readen = reader.GetReaden();
		if (section_id == 254) {
			decoder.HandleCOM(len);
		} else if (224 <= section_id && section_id <= 239) {
			decoder.HandleAPPn(len);
		} else if (section_id == 218) {
			decoder.HandleSOS(len, next_sec);
			if (next_sec == 217) {
				break;
			}
			changed = true;
		} else if (section_id == 219) {
			decoder.HandleDQT(len);
		} else if (section_id == 192) {
			decoder.HandleSOF0(len);
		} else if (section_id == 196) {
			decoder.HandleDHT(len);
		} else {
			throw std::invalid_argument("Unknown marker");
		}
		decoder.CheckFileEnded();
		size_t cur_readen = reader.GetReaden();
		if (section_id != 218 && cur_readen - was_readen != len * 8) {
			throw std::invalid_argument("Len of a section is incorrect");
		}
	}

	return decoder.img;
}
