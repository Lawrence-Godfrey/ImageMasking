#include <iostream>
#include <fstream>
#include <chrono>
#include <bitset>
#include <thread>
#include <vector>

using namespace std::chrono;
int main(int argv, char** argc) {

    if(argv < 5) {
        std::cout << "Run with arguments: <path_to_image1> <path_to_image2> <path_to_mask> <path_to_output>";
        return 0;
    }

    const auto begin = high_resolution_clock::now();

    std::ifstream image1;
    image1.open(argc[1], std::ios::in | std::ios::binary);
    
    std::ifstream image2;
    image2.open(argc[2], std::ios::in | std::ios::binary);

    std::ifstream mask;
    mask.open(argc[3], std::ios::in | std::ios::binary);

    std::ofstream masked_image;
    masked_image.open(argc[4], std::ios::out | std::ios::binary);
    
    
    uint32_t length = 115200;

    unsigned char * image_buffer1 = new unsigned char [length];
    image1.read((char *)image_buffer1, length);

    unsigned char * image_buffer2 = new unsigned char [length];
    image2.read((char *)image_buffer2, length);

    unsigned char * mask_buffer = new unsigned char [length];
    mask.read((char *)mask_buffer, length);

    unsigned char * masked_image_buffer = new unsigned char [length];

    
    

    auto time = high_resolution_clock::now() - begin;

    std::cout << "Time taken to read in images: " << duration<double, std::milli>(time).count() << ".\n";

    const auto begin2 = high_resolution_clock::now();


    for(uint32_t i = 0; i < length; i++) {
        masked_image_buffer[i] = (image_buffer1[i] & ~mask_buffer[i]) ^ (image_buffer2[i] & mask_buffer[i]) ;
    }
  

    time = high_resolution_clock::now() - begin2;
    std::cout << "Time taken to mask image without and gates: " << duration<double, std::milli>(time).count() << ".\n";
   
   
    
    masked_image.write((char *)masked_image_buffer, length);

    
    image1.close();
    image2.close();
    mask.close();
    masked_image.close();
}
