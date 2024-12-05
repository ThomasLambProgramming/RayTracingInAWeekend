#ifndef CAMERA_H
#define CAMERA_H
#include "Hittable.h"
#include <fstream>

#include "Material.h"

class Camera
{
public:
    double aspectRatio = 1.0;  // Ratio of image width over height
    int imageWidth  = 100;  // Rendered image width in pixel count
    int samplesPerPixel = 1;
    int maxLightBounces = 10;

    Point3 lookFrom = Point3(0,0,0); //where camera is looking from
    Point3 lookAt = Point3(0,0,0); //what the camera is looking at.
    Vector3 cameraUp = Vector3(0,1,0); 
    double vFov = 90; //Vertical field of view in degrees.
    
    double defocusAngle = 0; // ray angle variation through each pixel
    double focusDistance = 10; //distance from camera look location to plane of perfect focus
    
    void Render(const Hittable& world)
    {
        Initialize();
        
        std::ofstream outputFile("outputFile.ppm");
        outputFile << "P3" << '\n' << imageWidth << ' ' << imageHeight << "\n" << "255" << "\n";
        std::clog << "Started Image Processing" << "\n";
        for (int j = 0; j < imageHeight; j++)
        {
            std::clog << "Image Progress " << (int)((float)j / imageHeight * 100) << "\n";
            for (int i = 0; i < imageWidth; i++)
            {
                Color pixelColor(0,0,0);
                for (int sample = 0; sample < samplesPerPixel; sample++)
                {
                    Ray ray = GetRay(i, j);
                    pixelColor += RayColor(ray, world, 0);
                }
                WriteColor(outputFile, pixelSamplesScale * pixelColor);
            }
        }
        std::clog << "Image Progress Complete" << "\n";
        outputFile.close();
    }
    
private:
    double pixelSamplesScale; //Color scale factor for a sum of pixels. 
    Point3 cameraCenter = Point3(0,0,0);
    int imageHeight;
    Vector3 pixel00Location;
    Vector3 pixelDeltaU;
    Vector3 pixelDeltaV;
    Vector3 u,v,w; //camera frame basis vectors.

    Vector3 defocusDiskU; //horiztonal radius of defocus disk
    Vector3 defocusDiskV; //vertical radius of defocus disk
    
    void Initialize()
    {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        cameraCenter = lookFrom;
        
        double theta = DegreeToRadian(vFov);
        double h = std::tan(theta/2);
        double viewportHeight = 2.0 * h * focusDistance;
        double viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);
        
        pixelSamplesScale = 1.0 / samplesPerPixel;

        w = UnitVector(lookFrom - lookAt);
        u = UnitVector(CrossProduct(cameraUp, w));
        v = CrossProduct(w, u);

        //Calculate the vectors across the horizontal and vertical viewport edges.
        Vector3 viewportU = viewportWidth * u;
        Vector3 viewportV = viewportHeight * -v;

        //Calculate the amount to move in each direction for each pixel in the x and y coords
        pixelDeltaU = viewportU / imageWidth;
        pixelDeltaV = viewportV / imageHeight;

        //RHS coord system -z is forward so -z focal length (im 99% focal length is also the near plane for frustum), assuming cameracenter we want to move it half the screen left and up.
        Vector3 viewportUpperLeft = cameraCenter - (focusDistance * w) - viewportU / 2 - viewportV / 2;
        //We inset by half a pixel on either side so each pixel position is the middle of the pixel it is meant to ray from.
        pixel00Location = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);

        double defocusRadius = focusDistance * std::tan(DegreeToRadian(defocusAngle / 2));
        defocusDiskU = u * defocusRadius;
        defocusDiskV = v * defocusRadius;
    }

    Ray GetRay(int i, int j) const
    {
        //Create a ray based on the x,y position + random offset for multisampling / antialiasing
        Vector3 offset = SampleSquare();
        Vector3 pixelSample = pixel00Location +
            ((i + offset.x()) * pixelDeltaU) + 
            ((j + offset.y()) * pixelDeltaV);

        Vector3 rayOrigin = (defocusAngle <= 0) ? cameraCenter : DefocusDiscSample();
        Vector3 rayDirection = pixelSample - rayOrigin;
        return Ray(rayOrigin, rayDirection);
    }

    Vector3 SampleSquare() const
    {
        //Return a vector in ([-0.5,-0.5], [0.5,0.5])
        return Vector3(RandomDouble() - 0.5, RandomDouble() -0.5, 0);
    }
    
    Color RayColor(const Ray& ray, const Hittable& world, int bounceDepth) const
    {
        if (bounceDepth >= maxLightBounces)
            return Color(0,0,0);
        
        HitRecord record;
        if (world.Hit(ray, Interval(0.001, infinity), record))
        {
            Ray scatteredRay;
            Color attenuation;
            if (record.material->Scatter(ray, record, attenuation, scatteredRay))
                return attenuation * RayColor(scatteredRay, world, bounceDepth+1);
            return Color(0,0,0);
        }

        //Background gradient from white to blue (this is the sky color)
        Vector3 direction = UnitVector(ray.Direction());
        double a = 0.5 * (direction.y() + 1.0);
        return (1.0 - a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
        //When logging direction.y is -0.7 -> 0.57 in range so a's range is 0.15->0.785
    }

    Point3 DefocusDiscSample() const
    {
        Vector3 point = RandomInsideUnitDisc();
        return cameraCenter + (point[0] * defocusDiskU) + (point[1] * defocusDiskV);
    }
};

#endif
