#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>

using namespace std::chrono;
int main(int argv, char** argc) {

    if(argv < 3) {
        std::cout << "Run with arguments: <path_to_image> <path_to_mask>";
    }

    const auto begin = high_resolution_clock::now();

    std::ifstream image;
    image.open(argc[1], std::ios::in | std::ios::binary);

    std::ifstream mask;
    mask.open(argc[2], std::ios::in | std::ios::binary);

    std::ofstream masked_image;
    masked_image.open("mask_output", std::ios::out | std::ios::binary);
    
    
    int length = 115200;

    unsigned char * image_buffer = new unsigned char [length];
    image.read((char *)image_buffer, length);

    unsigned char * mask_buffer = new unsigned char [length];
    mask.read((char *)mask_buffer, length);

    auto time = high_resolution_clock::now() - begin;
    std::cout << "Elapsed time: " << duration<double, std::milli>(time).count() << ".\n";
    
    // for(int i = 0; i < length; i++) {
    //     std::cout << std::bitset<8>((unsigned char)mask_buffer[i]);
    // }

    // for(int i = 0; i < length; i++) {
    //     image_buffer[i] = image_buffer[i] ^ 0b11111111;                          // turns 
    // }

    for(int i = 0; i < length; i++) {
        masked_image << (unsigned char)(((unsigned char)image_buffer[i] ^ (unsigned char)mask_buffer[i]) & (image_buffer[i]));
    }
    
    
    image.close();
    mask.close();
    masked_image.close();
}
