#ifndef CAMERA_H
#define CAMERA_H
#include "Hittable.h"
#include <fstream>

class Camera
{
public:
    double aspectRatio = 1.0;  // Ratio of image width over height
    int imageWidth  = 100;  // Rendered image width in pixel count
    
    void Render(const Hittable& world)
    {
        Initialize();
        
        std::ofstream outputFile("outputFile.ppm");
        outputFile << "P3" << '\n' << imageWidth << ' ' << imageHeight << "\n" << "255" << "\n";
        std::cout << "Started Image Processing" << "\n";
        for (int j = 0; j < imageHeight; j++)
        {
            std::clog << "Image Progress " << (int)((float)j / imageHeight * 100) << "\n";
            for (int i = 0; i < imageWidth; i++)
            {
                Point3 pixelCenter = pixel00Location + (i * pixelDeltaU) + (j * pixelDeltaV);
                //direction from camera to the viewport pixel center
                Vector3 rayDirection = pixelCenter - cameraCenter;
                Ray ray(cameraCenter, rayDirection);

                //Previous green to red uv basic.
                //Color(double(i) / (imageWidth-1), double(j) / (imageHeight-1), 0.0);
                Color pixelColor = RayColor(ray, world);
                WriteColor(outputFile ,pixelColor);
            }
        }
        std::clog << "Image Progress Complete" << "\n";
        outputFile.close();
    }
    
private:
    //Camera
    Point3 cameraCenter = Point3(0,0,0);
    int imageHeight;
    Vector3 pixel00Location;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    
    void Initialize()
    {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;
        
        double focalLength = 1.0;
        double viewportHeight = 2.0;
        double viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
        
        //Calculate the vectors across the horizontal and vertical viewport edges.
        Vector3 viewportU = Vector3(viewportWidth,0,0);
        Vector3 viewportV = Vector3(0,-viewportHeight,0);

        //Calculate the amount to move in each direction for each pixel in the x and y coords
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        //RHS coord system -z is forward so -z focal length (im 99% focal length is also the near plane for frustum), assuming cameracenter we want to move it half the screen left and up.
        Vector3 viewportUpperLeft = cameraCenter - Vector3(0,0,focalLength) - viewportU / 2 - viewportV / 2;
        //We inset by half a pixel on either side so each pixel position is the middle of the pixel it is meant to ray from.
        pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
    }
    
    Color RayColor(const Ray& ray, const Hittable& world) const
    {
        HitRecord record;
        if (world.Hit(ray, Interval(0, infinity), record))
        {
            return 0.5 * (record.normal + Color(1,1,1));
        }

        //Background gradient from white to blue
        Vector3 direction = UnitVector(ray.Direction());
        double a = 0.5 * (direction.y() + 1.0);
        return (1.0 - a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
        //When logging direction.y is -0.7 -> 0.57 in range so a's range is 0.15->0.785
    }
};

#endif
