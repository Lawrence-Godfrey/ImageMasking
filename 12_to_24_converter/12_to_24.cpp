#include <iostream>
#include <fstream>

int main(int argv, char** argc) {

    if(argv < 3) {
        std::cout << "Run with arguments: <path_to_input> <path_to_output>";
    }

    std::ifstream image_12_bit;
    image_12_bit.open(argc[1], std::ios::in | std::ios::binary);
    if(image_12_bit.is_open()) {
        std::cout << "12 bit input image read..." << std::endl;
    }

    std::ofstream image_24_bit;
    image_24_bit.open(std::string(argc[2]) + ".ppm", std::ios::out | std::ios::binary);
    
    if(image_24_bit.is_open()) {
        std::cout << "24 bit .ppm input output image created..." << std::endl;
    }

    image_24_bit << "P6" << std::endl << "320 240" << std::endl << "255" << std::endl;
    

    unsigned char ch;
    while(image_12_bit.get((char &)ch)) {                     // loop through x axis
        
        unsigned char first_half = ch >> 4;
        first_half &= 0b00001111;
        first_half *= 16;

        image_24_bit << (unsigned char)first_half;

        unsigned char second_half = ch &= 0b00001111;
        second_half *= 16;

        image_24_bit << (unsigned char)second_half;

    }    
    
    image_12_bit.close();
    image_24_bit.close();
    std::cout << "Finished." << std::endl;
}