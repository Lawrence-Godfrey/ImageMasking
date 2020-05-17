#include <opencv>
#include <iostream>
#include <vector>
#include <utility>
#include <bitset>
#include <fstream>

using namespace cv;

int main(int argv, char** argc) {
    Mat img = imread(argc[1], IMREAD_COLOR);     // read in image
    
    std::vector<Mat> three_channels;             
    split(img, three_channels);                  // seperate rgb into seperate channels 

    std::ofstream myfile;
    myfile.open("12bitoutput", std::ios::out | std::ios::binary);

    for(int i=0; i<img.rows; i++){                          // loop through y axis
        for(int j=0; j<img.cols; j++)                       // loop through x axis
        {
            for(int k = 0; k < 3; k++) {                    // loop through RGB values
                unsigned char first_half = std::floor(three_channels.at(k).at<uchar>(i,j)/16);       // first 4 bits of char, ie, kth part of 12 bit pixel
                first_half <<= 4;
                // the next section of code allows for the last 4 bits of the 8 bit char to be the start of another 12 bit pixel 
                k++;                            
                if(k>2) {                       
                    if(j<img.cols-1) {
                        j++;
                    }
                    else if(i<img.rows-1) {
                        i++;
                        j = 0;
                    }
                    k=0;
                }

                unsigned char second_half = std::floor(three_channels.at(k).at<uchar>(i,j)/16);            // last 4 bits of char, ie, kth part of 12 bit pixel
                
                myfile << (unsigned char)(first_half | second_half) ;                                               // output 8 bit char 
                if(i>1000 && j > 1000 && i < 1100 && j < 1100) {
                    std::cout << std::bitset<8>( first_half | second_half ) << std::endl;
                }
            }

        }    
    }

    myfile.close();
    
    unsigned char first_half = std::floor(three_channels.at(0).at<uchar>(600,300)/16);
    
    std::cout << "first half:  " << std::bitset<8>(first_half) << std::endl;

    first_half <<= 4;
    
    std::cout << "first half shifted: " << std::bitset<8>(first_half) << std::endl;

    unsigned char second_half = std::floor(three_channels.at(1).at<uchar>(600,300)/16);
    
    std::cout << "second half: " << std::bitset<8>(second_half) << std::endl;

    std::cout << "ORed: " << std::bitset<8>( first_half | second_half ) ;

    
    // imshow("Colour", img);

    // imwrite("OutputGray.jpg", img);

    // waitKey(); 
}