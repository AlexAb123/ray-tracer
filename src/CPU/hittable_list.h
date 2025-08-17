#pragma once

#include <memory>
#include <vector>
#include "hittable.h"

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
public:
    std::vector<shared_ptr<Hittable>> m_objects;

    HittableList() {}
    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { m_objects.clear(); }

    void add(shared_ptr<Hittable> object) {
        m_objects.push_back(object);
    }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override {
        HitRecord tempRec;
        bool hitAnything = false;
        double closestSoFar = rayT.max();

        for (const shared_ptr<Hittable>& object : m_objects) {
            if (object->hit(r, Interval(rayT.min(), closestSoFar), tempRec)) {
                hitAnything = true;
                closestSoFar = tempRec.t();
                rec = tempRec;
            }
        }

        return hitAnything;
    }
};