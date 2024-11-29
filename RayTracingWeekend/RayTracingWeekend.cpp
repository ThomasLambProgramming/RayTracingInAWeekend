#include <fstream>
#include "BaseClasses/RayTraceWeekendConstants.h"
#include "BaseClasses/Hittable.h"
#include "BaseClasses/HittableList.h"
#include "BaseClasses/Sphere.h"

using namespace std;

Color RayColor(const Ray& ray, const Hittable& world)
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

    HittableList world;
    world.AddObject(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.AddObject(make_shared<Sphere>(Point3(0,-100.5,-1), 100));

    
    ofstream outputFile("outputFile.ppm");
    outputFile << "P3" << '\n' << imageWidth << ' ' << imageHeight << "\n" << "255" << "\n";
    cout << "Started Image Processing" << "\n";
    for (int j = 0; j < imageHeight; j++)
    {
        clog << "Image Progress " << (int)((float)j / imageHeight * 100) << "\n";
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
    
    clog << "Image Progress Complete" << "\n";
    outputFile.close();
}
