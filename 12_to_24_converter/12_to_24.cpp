#include <opencv>
#include <iostream>
#include <vector>
#include <utility>
#include <bitset>
#include <fstream>

using namespace cv;

int main() {

    std::ifstream image_12_bit;
    image_12_bit.open("../24_to_12_converter/12bitoutput", std::ios::in | std::ios::binary);

    std::ofstream image_24_bit;
    image_24_bit.open("24bitoutput.ppm", std::ios::out | std::ios::binary);

    image_24_bit << "P6" << std::endl << "1200 1200" << std::endl << "255" << std::endl;
    
    std::vector<unsigned char> image (); 

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
}