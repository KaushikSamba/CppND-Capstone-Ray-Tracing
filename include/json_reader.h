#ifndef JSON_READER_H
#define JSON_READER_H

#include "nlohmann/json.hpp"
#include <fstream>
#include <string>

class JSONReader {
  public:
    JSONReader();
    JSONReader(std::string);
    ~JSONReader();
    void openFile(std::string);
    nlohmann::json getJSON();

  private:
    std::ifstream istream;
};

#endif