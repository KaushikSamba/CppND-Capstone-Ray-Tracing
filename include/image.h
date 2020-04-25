#ifndef IMAGE_H
#define IMAGE_H

#include <cmath>
#include <string>
#include "geometry.h"
#include <memory>
#include <fstream>

struct ImageOptions {
  public:
    ImageOptions(int height, int width)
        : height(height), width(width), alpha(M_PI_2), filename("out.ppm") {}
    ImageOptions(int height, int width, float degrees)
        : height(height), width(width), alpha(degrees * M_PI / 180),
          filename("out.ppm") {}
    ImageOptions(int height, int width, float degrees, std::string filename)
        : height(height), width(width), alpha(degrees * M_PI / 180),
          filename(filename) {}
    float getAspectRatio() const { return width / (float)height; }
    float getFoVMultiplier() const { return tan(alpha / 2); }
    const int height, width;
    const float alpha;
    const std::string filename;
};

class ImageSaver {
  public:
    ImageSaver(std::shared_ptr<ImageOptions> options) : _options(options) {
        _outstream.open(_options->filename, std::ios::out | std::ios::binary);
        if (!_outstream) {
            std::cerr << "Unable to open file!";
            exit(1);
        }
    }
    // template <typename T> std::ostream &operator<<(T &data) {
    //     return outstream << data;
    // }
    ~ImageSaver() { _outstream.close(); }
    void save(const std::unique_ptr<Vector3D<float>[]> &);

  private:
    std::ofstream _outstream;
    std::shared_ptr<ImageOptions> _options;
};

void ImageSaver::save(const std::unique_ptr<Vector3D<float>[]> &image) {
    // ImageSaver saver(options.filename);
    _outstream << "P6\n"
               << _options->width << " " << _options->height << "\n255\n";
    for (size_t y = 0; y < _options->height; y++) {
        for (size_t x = 0; x < _options->width; x++) {
            char r = (char)(255 * image[y * _options->height + x].X());
            char g = (char)(255 * image[y * _options->height + x].Y());
            char b = (char)(255 * image[y * _options->height + x].Z());
            _outstream << r << g << b;
        }
    }
}

#endif