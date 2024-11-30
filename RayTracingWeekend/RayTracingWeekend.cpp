#include "BaseClasses/Camera.h"
#include "BaseClasses/RayTraceWeekendConstants.h"
#include "BaseClasses/HittableList.h"
#include "BaseClasses/Sphere.h"

using namespace std;

int main()
{
    HittableList world;
    world.AddObject(make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.AddObject(make_shared<Sphere>(Point3(0,-100.5,-1), 100));

    Camera camera;
    camera.aspectRatio = 16.0/9.0;
    camera.imageWidth = 400;
    camera.Render(world);
}
