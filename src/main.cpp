#include "image_options.h"
#include "image_saver.h"
#include "json_reader.h"
#include "ray.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "sphere.h"
#include <iostream>
#include <memory>
#include <random>
#include <vector>

void get_world_coordinates(float &world_x, float &world_y, const int &x,
                           const int &y,
                           const std::shared_ptr<ImageOptions> &options,
                           const float &aspect_ratio, const float &fov_scale) {
    world_x =
        (2 * (x + 0.5) / (float)options->width - 1) * aspect_ratio * fov_scale;
    world_y = (1 - 2 * (y + 0.5) / (float)options->height) * fov_scale;
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
                    logger->debug("Pixel: ({}, {})", x, y);
                    logger->debug("Intersected sphere {} at distance {}", i,
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
                image[y * options->width + x] =
                    spheres[which_sphere]->getSurfaceProperties(minIntersection,
                                                                ray);
            } else {
                image[y * options->width + x] = options->backgroundColor;
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
    reader.parse_options(options);
    // reader.parse_objects(spheres);
}

int main() {
    auto logger = spdlog::basic_logger_mt("raytracing_logger",
                                          "../logs/raytracing_logs.txt");
    logger->set_level(spdlog::level::warn);
    std::shared_ptr<ImageOptions> options;
    std::vector<std::unique_ptr<Sphere<float>>> spheres;

    getJSONData("../configs/config.json", options, spheres);

    // Generate random spheres
    size_t numSpheres = 32;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, 1);

    gen.seed(10);
    for (size_t i = 0; i < numSpheres; ++i) {
        Vector3D<float> center((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10,
                               -1 * (1 + dis(gen) * 10));
        float radius = (0.5 + dis(gen) * 2);
        Vector3D<float> color(dis(gen), dis(gen), dis(gen));
        spheres.emplace_back(
            std::make_unique<Sphere<float>>(center, radius, color));
        spheres.back()->log();
    }

    render_image(std::move(options), std::move(spheres));
    return 0;
}