#include "BaseClasses/Camera.h"
#include "BaseClasses/RayTraceWeekendConstants.h"
#include "BaseClasses/HittableList.h"
#include "BaseClasses/Sphere.h"
#include "BaseClasses/Material.h"

using namespace std;

int main()
{
    HittableList world;
    
    shared_ptr<Material> materialGround = make_shared<Lambertian>(Color(0.8,0.8,0.0));
    shared_ptr<Material> materialCenter = make_shared<Lambertian>(Color(0.1,0.2,0.5));
    shared_ptr<Material> materialLeft = make_shared<Dielectric>(1.5);
    shared_ptr<Material> materialBubble = make_shared<Dielectric>(1.0 / 1.5);
    shared_ptr<Material> materialRight = make_shared<Metal>(Color(0.8,0.6,0.2), 0.0);
    
    world.AddObject(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, materialGround));
    world.AddObject(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, materialCenter));
    world.AddObject(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, materialLeft));
    world.AddObject(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.4, materialBubble));
    world.AddObject(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, materialRight));
    
    //auto R = std::cos(pi/4);
    //
    //auto material_left  = make_shared<Lambertian>(Color(0,0,1));
    //auto material_right = make_shared<Lambertian>(Color(1,0,0));
    //
    //world.AddObject(make_shared<Sphere>(Point3(-R, 0, -1), R, material_left));
    //world.AddObject(make_shared<Sphere>(Point3( R, 0, -1), R, material_right));
    
    Camera camera;
    camera.lookFrom = Point3(-2,2,1);
    camera.lookAt= Point3(0,0,-1);
    camera.cameraUp = Vector3(0,1,0);
    camera.aspectRatio = 16.0 / 9.0;
    camera.vFov = 20;
    camera.imageWidth = 400;
    camera.samplesPerPixel = 10;
    camera.maxLightBounces = 15;
    camera.defocusAngle = 10.0;
    camera.focusDistance = 3.4;
    camera.Render(world);
}