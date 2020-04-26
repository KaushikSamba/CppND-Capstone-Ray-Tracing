#include "json_reader.h"
#include <iostream>

JSONReader::~JSONReader() { istream.close(); }

JSONReader::JSONReader() {}
nlohmann::json JSONReader::getJSON() {
    nlohmann::json j;
    istream >> j;
    return j;
}

void JSONReader::openFile(std::string filename) {
    istream.open(filename);
    if (!istream.is_open()) {
        std::cout << "Could not open file " << filename << "\n";
        exit(1);
    }
}

JSONReader::JSONReader(std::string filename) { openFile(filename); }

// int main() {
//     auto options = getImageConfigs("../configs/image_options.json");
//     std::cout << "Aspect ratio: " << options->getAspectRatio() << "\n";
//     return 0;
// }