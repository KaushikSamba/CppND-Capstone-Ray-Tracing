#include "image_saver.h"
#include "png++-0.2.9/png.hpp"
#include <iostream>

ImageSaver::~ImageSaver() {
    if (_ext == Extensions::ppm)
        _outstream.close();
}
ImageSaver::ImageSaver(std::shared_ptr<ImageOptions> options)
    : _options(options) {
    findExtension();
    if (_ext == Extensions::ppm) {
        _outstream.open(_options->filename, std::ios::out | std::ios::binary);
        if (!_outstream) {
            std::cerr << "Unable to open file!";
            exit(1);
        }
    }
}

void ImageSaver::findExtension() {
    size_t i = _options->filename.rfind('.', _options->filename.length());
    if (i != std::string::npos) {
        if (_options->filename.substr(i + 1) == "ppm") {
            _ext = Extensions::ppm;
            return;
        } else if (_options->filename.substr(i + 1) == "png") {
            _ext = Extensions::png;
            return;
        }
    }
    std::cerr << "Unsupported file extension. Exiting... \n";
    exit(1);
}

void ImageSaver::save_png(const std::unique_ptr<Vector3D<float>[]> &image) {
    png::image<png::rgb_pixel> png_image(_options->width, _options->height);
    for (size_t y = 0; y < _options->height; y++) {
        for (size_t x = 0; x < _options->width; x++) {
            char r =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].X()));
            char g =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].Y()));
            char b =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].Z()));
            png_image.set_pixel(x, y, png::rgb_pixel(r, g, b));
        }
    }
    png_image.write(_options->filename);
}

void ImageSaver::save_ppm(const std::unique_ptr<Vector3D<float>[]> &image) {
    _outstream << "P6\n"
               << _options->width << " " << _options->height << "\n255\n";
    for (size_t y = 0; y < _options->height; y++) {
        for (size_t x = 0; x < _options->width; x++) {
            char r =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].X()));
            char g =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].Y()));
            char b =
                (char)(255 *
                       std::min(1.0f, image[y * _options->width + x].Z()));
            _outstream << r << g << b;
        }
    }
}

void ImageSaver::save(const std::unique_ptr<Vector3D<float>[]> &image) {
    if (_ext == Extensions::png)
        save_png(image);
    if (_ext == Extensions::ppm)
        save_ppm(image);
    std::cout << "Completed writing to file " << _options->filename << "\n";
}