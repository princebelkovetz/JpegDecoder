# Jpeg Decoder 
Implementation of JPEG Decoding algorithm. 

Implemented:
* Huffman trees
* Inverse discrete cosine transform (using FFTW3 lib)
* Special class for reading bits from a jpeg
* The main algorithm itself, that decodes JPEG section by section


Example of usage is provided in main.cpp. The main function returns an Image class, that stores matrix of pixels.


