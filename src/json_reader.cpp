#include "json_reader.h"
#include <iostream>

JSONReader::~JSONReader() { _istream.close(); }

JSONReader::JSONReader() {}
void JSONReader::getJSON() { _istream >> _json; }

void JSONReader::openFile(std::string filename) {
    _istream.open(filename);
    if (!_istream.is_open()) {
        std::cout << "Could not open file " << filename << "\n";
        exit(1);
    }
}

JSONReader::JSONReader(std::string filename) { openFile(filename); }

void JSONReader::parse_options(std::shared_ptr<ImageOptions> &configs) {
    configs = std::make_shared<ImageOptions>(_json["image_options"]);
}

void JSONReader::parse_objects(
    std::vector<std::unique_ptr<Sphere<float>>> &spheres) {
    for (auto &object_json : _json["objects"]) {
        if (object_json["type"].get<std::string>() == "sphere") {
            spheres.emplace_back(std::make_unique<Sphere<float>>(object_json));
            spheres.back()->print();
        }
    }
}