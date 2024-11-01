#pragma once

#include <string>
#include <fstream>
#include <vector>

#include <UI/UIHandler.hpp>


namespace diddo::storage {

  ///This class handles loading files, as well as deleting and saving them
  class FileLoader {
    static constexpr std::string_view className = "FileLoader";
    static constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
    const std::string& path;
    std::fstream data;
    std::vector<std::string> lines;

    void readLines() {
      while (!data.eof()) {
        std::getline(data, lines.back(), '\n');
        if (data.rdstate() == std::ios_base::badbit) {
          ui::UIHandler::error(className.data(), "irrecoverable stream error when reading \"" + path + "\".");
        }
        if (data.rdstate() == std::ios_base::failbit) {}
          ui::UIHandler::error(
            className.data(), "reading \"" + path + "\" did not work, formatting or extraction error.");
      }
    };

    public:
      FileLoader() = delete;
      explicit FileLoader(const std::string& path) : path(path) {
        data.open(path, mode);
        readLines();
      };

      ~FileLoader() {
        if(!data.is_open()) {
          ui::UIHandler::error(className,  "The file " + path + " has already been closed");
          return;
        }
        data.close();
      }

      std::unique_ptr<std::vector<std::string>> getLines() {
        return std::make_unique<std::vector<std::string>>(lines);
      }
  };

}