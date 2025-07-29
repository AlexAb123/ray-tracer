#include <GLFW/glfw3.h>
#include "renderer.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main() {
    // World
    HittableList world;
    world.add(make_shared<Sphere>(Vector3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(Vector3(0, -100.5, -1), 100));

    Camera cam;
    cam.setAspectRatio(16.0 / 9.0);
    cam.setImageWidth(800);

    cam.render(world);
}