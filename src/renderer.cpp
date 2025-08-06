#include <GLFW/glfw3.h>
#include "renderer.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

int main() {

    // World
    HittableList world;

    shared_ptr<Material> material_ground = make_shared<Lambertian>(Vector3(0.8, 0.8, 0.0));
    shared_ptr<Material> material_center = make_shared<Lambertian>(Vector3(0.1, 0.2, 0.5));
    shared_ptr<Material> material_left = make_shared<Metal>(Vector3(0.8, 0.8, 0.8));
    shared_ptr<Material> material_right = make_shared<Metal>(Vector3(0.8, 0.6, 0.2));

    world.add(make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Vector3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<Sphere>(Vector3(1.0, 0.0, -1.0), 0.5, material_right));

    Camera cam;
    cam.setAspectRatio(16.0 / 9.0);
    cam.setImageWidth(800);
    cam.setSamplesPerPixel(10);
    cam.setMaxDepth(10);

    cam.render(world);
}