#include "image_options.h"
#include <cmath>

ImageOptions::ImageOptions(int height, int width)
    : height(height), width(width), alpha(M_PI_2), filename("out.ppm") {}

ImageOptions::ImageOptions(int height, int width, float degrees,
                           std::string filename)
    : height(height), width(width), alpha(degrees * M_PI / 180),
      filename(filename) {}

ImageOptions::ImageOptions(const nlohmann::json &j)
    : height(j["dimensions"]["height"].get<int>()),
      width(j["dimensions"]["width"].get<int>()),
      alpha(j["angle"].get<float>()),
      filename(j["save_filename"].get<std::string>()), 
      backgroundColor(static_cast<std::vector<float>>(j["background_color"])) {}

float ImageOptions::getAspectRatio() const { return width / (float)height; }

float ImageOptions::getFoVMultiplier() const { return tan(alpha / 2); }