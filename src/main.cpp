#include "image_options.h"
#include "image_saver.h"
#include "json_reader.h"
#include "ray.h"
#include "sphere.h"
#include <iostream>
#include <memory>
#include <vector>

void get_world_coordinates(float &world_x, float &world_y, const int &x,
                           const int &y,
                           const std::shared_ptr<ImageOptions> &options,
                           const float &aspect_ratio, const float &fov_scale) {
    world_x =
        (aspect_ratio * (2 * ((x + 0.5) / options->width) - 1)) * fov_scale;
    world_y = (1 - 2 * ((y + 0.5) / options->height)) * fov_scale;
}

void render_image(const std::shared_ptr<ImageOptions> options,
                  const std::vector<std::unique_ptr<Sphere<float>>> &&spheres) {
    // Sphere<float> sphere(Vector3D<float>(5, 3, -10), 3);
    // sphere.print();

    // Vector3D<float> image[options.height][options.width];
    std::unique_ptr<Vector3D<float>[]> image =
        std::make_unique<Vector3D<float>[]>(options->height * options->width);

    float fov_scale = options->getFoVMultiplier();
    float aspect_ratio = options->getAspectRatio();
    Vector3D<float> origin(0, 0, 0);
    float world_x, world_y;
    for (int y = 0; y < options->height; y++) {
        for (int x = 0; x < options->width; x++) {
            get_world_coordinates(world_x, world_y, x, y, options, aspect_ratio,
                                  fov_scale);
            // std::cout << "FoV pixels: (" << cam_fov_x << ", " <<
            // cam_fov_y
            //           << ")\n";

            Vector3D<float> dir =
                Vector3D<float>(world_x, world_y, -1) - origin;
            // dir.print();
            dir.normalize();

            Ray<float> ray(origin, dir);
            Vector3D<float> intersection;
            if (spheres[0]->intersects(ray, intersection)) {
                // std::cout << "Pixels: (" << x << ", " << y
                //   << ")\tIntersection at: ";
                // intersection.print('\t');
                // Assigning each pixel a color value based on the facing ratio.
                Vector3D<float> normal;
                spheres[0]->normalAtPoint(normal, intersection);
                // std::cout << "Normal: ";
                // normal.print('\t');

                float facingRatio =
                    std::max(normal.dot(ray.direction * -1), 0.0f);
                // std::cout << "Facing ratio = " << facingRatio << "\t";
                image[y * options->height + x] = {0, 0, facingRatio};
                // image[y * options.height + x].print('\n');
            }

            // Assigning each pixel a color value based on the direction vector
            // dir.absolute();
            // image[y][x] = dir;
            // dir.print();
            // image[y][x].print();
        }
    }
    std::cout << "Saving PPM image to file.\n";
    // Saving the PPM image
    // save_image(options, image);
    ImageSaver saver(options);
    std::cout << "Ref count: " << options.use_count() << "\n";
    saver.save(image);
}

std::shared_ptr<ImageOptions> getImageConfigs(std::string filename) {
    JSONReader reader(filename);
    nlohmann::json j = reader.getJSON();
    std::shared_ptr<ImageOptions> options = std::make_shared<ImageOptions>(
        j["dimensions"]["height"], j["dimensions"]["width"], j["angle"],
        j["filename"]);
    return options;
}

int main() {
    std::shared_ptr<ImageOptions> options =
        getImageConfigs("../configs/image_options.json");
    ;
    // ImageOptions options(201, 201, 90);
    std::vector<std::unique_ptr<Sphere<float>>> spheres;
    spheres.emplace_back(std::make_unique<Sphere<float>>(0, 0, -10, 3));
    spheres[0]->print();
    render_image(std::move(options), std::move(spheres));
    std::cout << "Ref count: " << options.use_count() << "\n";
    // std::cout << "Aspect ratio: " << options->getAspectRatio() << "\n";
    return 0;
}