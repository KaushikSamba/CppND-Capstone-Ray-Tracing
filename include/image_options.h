#ifndef IMAGE_OPTIONS_H
#define IMAGE_OPTIONS_H

#include "nlohmann/json.hpp"
#include <string>

struct ImageOptions {
    ImageOptions(const nlohmann::json &);
    ImageOptions(int height, int width);
    ImageOptions(int height, int width, float degrees, std::string filename);
    float getAspectRatio() const;
    float getFoVMultiplier() const;

    const int height, width;
    const float alpha;
    const std::string filename;
};

#endif