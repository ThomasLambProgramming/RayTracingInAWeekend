#include "BaseClasses/Camera.h"
#include "BaseClasses/RayTraceWeekendConstants.h"
#include "BaseClasses/HittableList.h"
#include "BaseClasses/Sphere.h"
#include "BaseClasses/Material.h"

using namespace std;

int main()
{
    HittableList world;

    shared_ptr<Material> groundMaterial = make_shared<Lambertian>(Color(0.5,0.5,0.5));
    shared_ptr<Material> glass1 = make_shared<Dielectric>(1.5);
    shared_ptr<Material> lambert1 = make_shared<Lambertian>(Color(0.4,0.2,0.1));
    shared_ptr<Material> metal1 = make_shared<Metal>(Color(0.7,0.6,0.5), 0.0);

    //Ground sphere that is enlarged to look like a surface.
    world.AddObject(make_shared<Sphere>(Point3(0,-1000,0), 1000, groundMaterial));

    //Large spheres to showcase each material
    world.AddObject(make_shared<Sphere>(Point3(0,1,0), 1.0, glass1));
    world.AddObject(make_shared<Sphere>(Point3(-4,1,0), 1.0, lambert1));
    world.AddObject(make_shared<Sphere>(Point3(4,1,0), 1.0, metal1));
    

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double ChooseMat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4,0.2,8)).Length() > 0.9)
            {
                shared_ptr<Material> sphereMaterial;
                //Diffuse Material
                if (ChooseMat < 0.8)
                {
                    Color albedo = Color::Random() * Color::Random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.AddObject(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                //Metal Material
                else if (ChooseMat < 0.95)
                {
                    Color albedo = Color::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.4);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                }
                //Glass Material
                else
                {
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.AddObject(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }
    
    Camera camera;
    camera.aspectRatio = 16.0 / 9.0;
    camera.imageWidth = 1200;
    camera.samplesPerPixel = 500;
    camera.maxLightBounces = 50;
    
    camera.vFov = 20;
    camera.lookFrom = Point3(13,2,3);
    camera.lookAt= Point3(0,0,0);
    camera.cameraUp = Vector3(0,1,0);
    
    camera.defocusAngle = 0.6;
    camera.focusDistance = 10;
    camera.Render(world);
}