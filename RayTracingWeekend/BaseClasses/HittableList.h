#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "RayTraceWeekendConstants.h"
#include "Hittable.h"
#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() = default;
    HittableList(shared_ptr<Hittable> object) {AddObject(object);}

    void Clear() {objects.clear();}
    void AddObject(shared_ptr<Hittable> newObject) {objects.push_back(newObject);}

    bool Hit(const Ray& ray, Interval rayT, HitRecord& record) const override
    {
        HitRecord temporaryRecord;
        bool hitAnyObject= false;
        double closestObjectDistance = rayT.max;

        for (const shared_ptr<Hittable>& objectToCheck : objects)
        {
            if (objectToCheck->Hit(ray, Interval(rayT.min, closestObjectDistance), temporaryRecord))
            {
                hitAnyObject = true;
                closestObjectDistance = temporaryRecord.t;
                record = temporaryRecord;
            }
        }
        return hitAnyObject;
    }
protected:
private:
};

#endif
