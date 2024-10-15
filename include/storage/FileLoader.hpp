
#ifndef FILELOADER_HPP
#define FILELOADER_HPP
#include <string>

#endif //FILELOADER_HPP

#include <fstream>
#include <vector>

namespace storage {

  class FileLoader {
    private:
    const std::string& path;
    constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
    std::fstream data;
    std::vector<std::string> lines;

    void readLines() {
      //TODO: Check for error codes
      while (!data.eof) {
        std::getline(data, lines.back(), '\n');
      }
    };

    public:
      FileLoader() = delete;
      explicit FileLoader(const std::string& path) : path(path) {
        data.open(path, mode);
        readLines();
      };
  };

}