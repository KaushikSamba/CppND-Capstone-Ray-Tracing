#include "image_saver.h"
#include <iostream>

ImageSaver::~ImageSaver() { _outstream.close(); }
ImageSaver::ImageSaver(std::shared_ptr<ImageOptions> options)
    : _options(options) {
    _outstream.open(_options->filename, std::ios::out | std::ios::binary);
    if (!_outstream) {
        std::cerr << "Unable to open file!";
        exit(1);
    }
}

void ImageSaver::save(const std::unique_ptr<Vector3D<float>[]> &image) {
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
    std::cout << "Completed writing to file " << _options->filename << "\n"; 
}