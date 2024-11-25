#include <iostream>
#include <fstream>

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
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);
            
            outputFile << ir << ' ' << ig << ' ' << ib;
            outputFile << endl;
        }
    }
    clog << "Image Progress Complete" << endl;
    outputFile.close();
    

    
}
