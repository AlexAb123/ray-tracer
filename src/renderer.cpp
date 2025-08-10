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

    shared_ptr<Material> groundMaterial = make_shared<Lambertian>(Vector3(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMaterial = make_shared<Lambertian>(Vector3(0.1, 0.2, 0.5));
    shared_ptr<Material> leftMaterial = make_shared<Dielectric>(1.5);
    shared_ptr<Material> bubbleMaterial = make_shared<Dielectric>(1.0 / 1.5);
    shared_ptr<Material> rightMaterial = make_shared<Metal>(Vector3(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), 100.0, groundMaterial));
    world.add(make_shared<Sphere>(Vector3(0.0, 0.0, -1.2), 0.5, centerMaterial));
    world.add(make_shared<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.5, leftMaterial));
    world.add(make_shared<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.4, bubbleMaterial));
    world.add(make_shared<Sphere>(Vector3(1.0, 0.0, -1.0), 0.5, rightMaterial));

    Camera cam;
    cam.setAspectRatio(16.0 / 9.0);
    cam.setImageWidth(800);
    cam.setSamplesPerPixel(10);
    cam.setMaxBounces(10);

    cam.setVFov(90);

    cam.setLookFrom(Vector3(-2, 2, 1));
    cam.setLookAt(Vector3(0, 0, -1));
    cam.setUp(Vector3(0, 1, 0));

    cam.render(world);
}