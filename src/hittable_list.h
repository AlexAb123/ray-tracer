#pragma once

#include <memory>
#include <vector>
#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) {
        objects.push_back(object);
    }

    bool hit(const Ray& r, double rayTMin, double rayTmax, HitRecord& rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        double closestSoFar = rayTmax;

        for (const shared_ptr<Hittable>& object : objects) {
            if (object->hit(r, rayTMin, closestSoFar, tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.t();
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};