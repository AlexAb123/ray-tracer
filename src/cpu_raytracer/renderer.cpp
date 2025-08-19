#include <GLFW/glfw3.h>
#include "renderer.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <glm/glm.hpp>

int main() {


    glm::vec3 v = glm::vec3(1, 0, 2);
    // World
    HittableList world1;

    shared_ptr<Material> groundMaterial1 = make_shared<Lambertian>(Vector3(0.8, 0.8, 0.0));
    shared_ptr<Material> centerMaterial = make_shared<Lambertian>(Vector3(0.1, 0.2, 0.5));
    shared_ptr<Material> leftMaterial = make_shared<Dielectric>(1.5);
    shared_ptr<Material> bubbleMaterial = make_shared<Dielectric>(1.0 / 1.5);
    shared_ptr<Material> rightMaterial = make_shared<Metal>(Vector3(0.8, 0.6, 0.2), 0.0);

    world1.add(make_shared<Sphere>(Vector3(0.0, -100.5, -1.0), 100.0, groundMaterial1));
    world1.add(make_shared<Sphere>(Vector3(0.0, 0.0, -1.2), 0.5, centerMaterial));
    world1.add(make_shared<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.5, leftMaterial));
    world1.add(make_shared<Sphere>(Vector3(-1.0, 0.0, -1.0), 0.4, bubbleMaterial));
    world1.add(make_shared<Sphere>(Vector3(1.0, 0.0, -1.0), 0.5, rightMaterial));

    // World
    HittableList world;

    // Ground
    shared_ptr<Material> groundMaterial = make_shared<Lambertian>(Vector3(0.5, 0.5, 0.5));
    world.add(make_shared<Sphere>(Vector3(0, -1000, 0), 1000.0, groundMaterial));

    // Random small spheres
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto chooseMat = randomDouble();
            Vector3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Vector3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) {
                    // Diffuse
                    auto albedo = Vector3::random() * Vector3::random();
                    sphereMaterial = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) {
                    // Metal
                    auto albedo = Vector3::random(0.5, 1.0);
                    auto fuzz = randomDouble(0.0, 0.5);
                    sphereMaterial = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else {
                    // Glass
                    sphereMaterial = make_shared<Dielectric>(1.5);
                    world.add(make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    // Three main spheres
    shared_ptr<Material> material1 = make_shared<Dielectric>(1.5);
    world.add(make_shared<Sphere>(Vector3(0, 1, 0), 1.0, material1));

    shared_ptr<Material> material2 = make_shared<Lambertian>(Vector3(0.4, 0.2, 0.1));
    world.add(make_shared<Sphere>(Vector3(-4, 1, 0), 1.0, material2));

    shared_ptr<Material> material3 = make_shared<Metal>(Vector3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<Sphere>(Vector3(4, 1, 0), 1.0, material3));

    Camera cam;
    cam.setAspectRatio(16.0 / 9.0);
    cam.setImageWidth(800);
    cam.setSamplesPerPixel(10);
    cam.setMaxBounces(10);

    cam.setVFov(20);

    cam.setLookFrom(Vector3(13, 2, 3));
    cam.setLookAt(Vector3(0, 0, 0));
    cam.setUp(Vector3(0, 1, 0));

    cam.setDefocusAngle(0.6);
    cam.setFocusDist(10.0);

    cam.render(world1);

    return 0;
}