#ifndef IMAGE_SAVER_H
#define IMAGE_SAVER_H

#include "image_options.h"
#include "vector3d.h"
#include <fstream>
#include <memory>

class ImageSaver {
  public:
    ImageSaver(std::shared_ptr<ImageOptions>);
    ~ImageSaver();
    void save(const std::unique_ptr<Vector3D<float>[]> &);

  private:
    std::ofstream _outstream;
    std::shared_ptr<ImageOptions> _options;
};

#endif