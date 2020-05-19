#include <opencv>
#include <iostream>
#include <vector>
#include <utility>
#include <bitset>
#include <fstream>

using namespace cv;

int main(int argv, char** argc) {

    std::ofstream mask;
    mask.open("12_bit_mask.ppm", std::ios::out | std::ios::binary);
    mask << "P6" << std::endl << "320 240" << std::endl << "255" << std::endl;
    std::vector<unsigned char> image (); 

    unsigned char pixels [6]; 

    for (int y = 0; y < 240; y++) {
        for (int x = 0; x < 320; x++) {
            // if (x > std::floor(320/4) && x < std::floor(320*3/4) && y > std::floor(240/4) && y < std::floor(240*3/4)) {
                mask << 0b11111111; 
            // }
            // else {
            //     mask << 0b11111111;
            //     // std::cout << "test" << std::endl;
            // }

        }
    }

    mask.close();







    
}