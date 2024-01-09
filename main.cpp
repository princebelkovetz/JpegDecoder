#include <iostream>
#include <fstream>
#include "decoder.h"

int main() {
	std::cerr << "Checking RGB of " << "colors.jpg" << "\n";
    std::ifstream fin("colors.jpg");
    if (!fin.is_open()) {
        throw std::invalid_argument("Cannot open a file");
    }
    auto image = Decode(fin);
    fin.close();
	
	for (int i = 0; i < image.Height(); ++i) {
		for (int j = 0; j < image.Width(); ++j) {
			std::cerr << "pixel " << i << ' ' << j << '\n' << "rgb: ";
			auto pixel = image.GetPixel(i, j); 
			std::cerr << pixel.r << ' ' << pixel.g << ' ' << pixel.b << '\n';
		}
	}

	return 0;
}
