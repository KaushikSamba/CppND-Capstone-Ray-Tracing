#include "image_options.h"
#include "image_saver.h"
#include "json_reader.h"
#include "ray.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
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
    auto logger = spdlog::get("raytracing_logger");
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

            Vector3D<float> dir =
                Vector3D<float>(world_x, world_y, -1) - origin;
            dir.normalize();

            Ray<float> ray(origin, dir);
            Vector3D<float> intersection;
            float distance;
            float minDistance = INFINITY;
            Vector3D<float> minIntersection;
            size_t which_sphere;
            for (size_t i = 0; i < spheres.size(); i++) {
                if (spheres[i]->intersects(ray, intersection, distance)) {
                    logger->info("Pixel: ({}, {})", x, y);
                    logger->info("Intersected sphere {} at distance {}", i,
                                 distance);
                    if (distance < minDistance) {
                        minDistance = distance;
                        minIntersection = intersection;
                        which_sphere = i; // Index of this sphere
                    }
                }
            }

            // If minDistance is infinity, no sphere intersected with this ray
            if (!std::isinf(minDistance)) {
                // Get surface info of the nearest sphere.
                image[y * options->height + x] =
                    spheres[which_sphere]->getSurfaceProperties(minIntersection,
                                                                ray);
            }
        }
    }
    std::cout << "Saving image to file.\n";
    ImageSaver saver(options);
    saver.save(image);
}

void getJSONData(const std::string &filename,
                 std::shared_ptr<ImageOptions> &options,
                 std::vector<std::unique_ptr<Sphere<float>>> &spheres) {
    JSONReader reader(filename);
    reader.getJSON();
    reader.parse(options, spheres);
}

int main() {
    auto logger = spdlog::basic_logger_mt("raytracing_logger",
                                          "../logs/raytracing_logs.txt");
    std::shared_ptr<ImageOptions> options;
    std::vector<std::unique_ptr<Sphere<float>>> spheres;

    getJSONData("../configs/config.json", options, spheres);

    render_image(std::move(options), std::move(spheres));
    return 0;
}