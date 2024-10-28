#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <storage/FileLoader.hpp>

namespace diddo::storage {
  class DiaryLoader {
    private:
      static constexpr std::string_view className = "DiaryLoader";
      const std::string path;
      std::filesystem::directory_iterator fileIt;

    public:
      DiaryLoader() = delete;
      explicit DiaryLoader(const std::string& path) : path(path), fileIt(path){};

      ~DiaryLoader()= default;

      //TODO: Take crae of warnings and exceptions
      [[nodiscard("Did you want to ignore all the data?")]] std::vector<std::unique_ptr<std::vector<std::string>>> loadDiary(const size_t fileNumber) const {
        std::vector<std::unique_ptr<std::vector<std::string>>> result;
        for (size_t fileIndex = 0; fileIndex < fileNumber; fileIndex++) {
          const std::string& filePath = fileIt->path().string();
          FileLoader loader(filePath);
          result.emplace_back(loader.getLines());
        }
        return result;
      }
  };
};