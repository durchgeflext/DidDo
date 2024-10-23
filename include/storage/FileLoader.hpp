
#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#endif //FILELOADER_HPP

#include <string>
#include <fstream>
#include <vector>

#include <UI/UIHandler.hpp>


namespace diddo::storage {

  class FileLoader {
    private:
    constexpr std::string className = "FileLoader";
    constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
    const std::string& path;
    std::fstream data;
    std::vector<std::string> lines;

    void readLines() {
      while (!data.eof) {
        std::getline(data, lines.back(), '\n');
        if (data.rdstate() == std::ios_base::badbit) {
          ui::UIHandler::error(className, "irrecoverable stream error when reading \"" + path + "\".");
        }
        if (data.rdstate() == std::ios_base::failbit) {}
          ui::UIHandler::error(className, "reading \"" + path + "\" did not work, formatting or extraction error.");
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