#include <iostream>
#include <fstream>
#include "BaseClasses/Vector3.h"
#include "BaseClasses/Color.h"
#include "BaseClasses/Ray.h"

using namespace std;

Color RayColor(const Ray& r)
{
    Vector3 direction = UnitVector(r.Direction());
    double a = 0.5 * (direction.y() + 1.0);
    return (1.0 - a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
    //When logging direction.y is -0.7 -> 0.57 in range so a's range is 0.15->0.785
}

int main()
{
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;
    //scale image height based on width to maintain aspect ratio and double check it is non 0/negative.
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    //Camera
    double focalLength = 1.0;
    double viewportHeight = 2.0;
    double viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
    Point3 cameraCenter = Point3(0,0,0);

    //Calculate the vectors across the horizontal and vertical viewport edges.
    Vector3 viewportU = Vector3(viewportWidth,0,0);
    Vector3 viewportV = Vector3(0,-viewportHeight,0);

    //Calculate the amount to move in each direction for each pixel in the x and y coords
    Vector3 pixelDeltaU = viewportU / imageWidth;
    Vector3 pixelDeltaV = viewportV / imageHeight;

    //RHS coord system -z is forward so -z focal length (im 99% focal length is also the near plane for frustum), assuming cameracenter we want to move it half the screen left and up.
    Vector3 viewportUpperLeft = cameraCenter - Vector3(0,0,focalLength) - viewportU / 2 - viewportV / 2;
    //We inset by half a pixel on either side so each pixel position is the middle of the pixel it is meant to ray from.
    Vector3 pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

    ofstream outputFile("outputFile.ppm");
    outputFile << "P3" << endl << imageWidth << ' ' << imageHeight << endl << "255" << endl;
    cout << "Started Image Processing" << endl;
    for (int j = 0; j < imageHeight; j++) {
        clog << "Image Progress " << ((float)j / (float)imageHeight * 100) << endl;
        for (int i = 0; i < imageWidth; i++) {
            Point3 pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
            //direction from camera to the viewport pixel center
            Vector3 rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            //Previous green to red uv basic.
            //Color(double(i) / (imageWidth-1), double(j) / (imageHeight-1), 0.0);
            Color pixelColor = RayColor(ray);
            WriteColor(outputFile ,pixelColor);
        }
    }
    clog << "Image Progress Complete" << endl;
    outputFile.close();
}
