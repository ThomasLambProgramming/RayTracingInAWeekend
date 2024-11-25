#include <iostream>
#include <fstream>
#include "Vector3.h"
#include "Color.h"

using namespace std;
int main()
{
    int image_width = 256;
    int image_height = 256;

    ofstream outputFile("outputFile.ppm");
    outputFile << "P3" << endl << image_width << ' ' << image_height << endl << "255" << endl;
    cout << "Started Image Processing" << endl;
    for (int j = 0; j < image_height; j++) {
        clog << "Image Progress " << ((float)j / (float)image_height * 100) << endl;
        
        for (int i = 0; i < image_width; i++) {
            Color pixelColor = Color(double(i) / (image_width-1), double(j) / (image_height-1), 0.0);
            WriteColor(outputFile ,pixelColor);
        }
    }
    clog << "Image Progress Complete" << endl;
    outputFile.close();
}
