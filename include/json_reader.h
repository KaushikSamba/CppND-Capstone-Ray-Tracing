#ifndef JSON_READER_H
#define JSON_READER_H

#include "image_options.h"
#include "nlohmann/json.hpp"
#include "sphere.h"
#include <fstream>
#include <string>

class JSONReader {
  public:
    JSONReader();
    JSONReader(std::string filename);
    ~JSONReader();

    void getJSON();
    void parse_options(std::shared_ptr<ImageOptions> &configs);
    void parse_objects(std::vector<std::unique_ptr<Sphere<float>>> &spheres);

  private:
    void openFile(std::string filename);

    std::ifstream _istream;
    nlohmann::json _json;
};

#endif