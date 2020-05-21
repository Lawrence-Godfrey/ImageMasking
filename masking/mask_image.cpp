#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>

using namespace std::chrono;
int main(int argv, char** argc) {

    if(argv < 4) {
        std::cout << "Run with arguments: <path_to_image> <path_to_mask> <path_to_output> <i (optional)>";
        return 0;
    }

    bool inverse = false;
    bool xor_only = false;

    if(argv == 5) {
        if(argc[4][0] == 'i') {
            inverse = true;
        }
        else if(argc[4][0] == 'x'){
            xor_only = true;
        }
    }

    const auto begin = high_resolution_clock::now();

    std::ifstream image;
    image.open(argc[1], std::ios::in | std::ios::binary);

    std::ifstream mask;
    mask.open(argc[2], std::ios::in | std::ios::binary);

    std::ofstream masked_image;
    masked_image.open(argc[3], std::ios::out | std::ios::binary);
    
    
    int length = 115200;

    unsigned char * image_buffer = new unsigned char [length];
    image.read((char *)image_buffer, length);

    unsigned char * mask_buffer = new unsigned char [length];
    mask.read((char *)mask_buffer, length);

    unsigned char * masked_image_buffer = new unsigned char [length];

    auto time = high_resolution_clock::now() - begin;
    std::cout << "Time taken to read in images: " << duration<double, std::milli>(time).count() << ".\n";
    

    const auto begin2 = high_resolution_clock::now();
    if(xor_only) {
        for(int i = 0; i < length; i++) {
            masked_image_buffer[i] = (image_buffer[i] ^ mask_buffer[i]) ;
        }
    }
    else {
        for(int i = 0; i < length; i++) {
            masked_image_buffer[i] = (image_buffer[i] ^ mask_buffer[i]) & (image_buffer[i]);
        }

    }
    
    masked_image.write((char *)masked_image_buffer, length);

    time = high_resolution_clock::now() - begin2;
    std::cout << "Time taken to mask image: " << duration<double, std::milli>(time).count() << ".\n";
    
    image.close();
    mask.close();
    masked_image.close();
}
