cmake_minimum_required(VERSION 3.21)
project(jpeg_decoder)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 23)
find_package(FFTW)

message(STATUS "Path to FFTW includes: ${FFTW_INCLUDES}")
message(STATUS "Path to FFTW library: ${FFTW_LIBRARIES}")

function(link_decoder_deps TARGET)
    target_include_directories(${TARGET} PUBLIC
            ${FFTW_INCLUDES})

    target_link_libraries(${TARGET} PUBLIC
            ${FFTW_LIBRARIES})

endfunction()
add_executable(jpeg_decoder main.cpp jpeg_decoder.cpp fft.cpp decoder.cpp file_reader.cpp huffman.cpp)

link_decoder_deps(jpeg_decoder)

