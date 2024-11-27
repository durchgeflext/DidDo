#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include <UI/UIHandler.hpp>


namespace diddo::storage {

  /**
   *This class handles loading files, as well as deleting and saving them.
   */
  class FileLoader {
    static constexpr std::string_view className = "FileLoader";
    static constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
    const std::string& path;
    std::shared_ptr<std::fstream> data;

    public:
    FileLoader() = delete;

    /**
    * Constructor for the FileLoader class.
    *
    * @param path: Reference to the path, where the file is located
    */
    explicit FileLoader(const std::string& path) : path(path) {
      data->open(path, mode);
      ui::UIHandler::info(className, "The file " + path + " has been opened");
    }

    /**
    * Destructor for the FileLoader class. Closes and saves the file.
    */
    ~FileLoader() {
      if(!data->is_open()) {
        ui::UIHandler::warning(className,  "The file " + path + " has already been closed");
        return;
      }
      data->close();
      if (data->rdstate() == std::fstream::failbit) {
        ui::UIHandler::error(className, "The file " + path + " could not be closed");
      }
    }

    /**
    * Returns the contents of the file.
    *
    * @return: shared pointer to the file stream, which is both readable and writable
    */
    [[nodiscard("Did you want to ignore all the data?")]] std::shared_ptr<std::fstream> getContent() const {
      if(!data->is_open()) {
        ui::UIHandler::error(className, "The file " + path + " is not open");
      }
      return data;
    }

    /**
    * Closes and deletes the file.
    */
    void deleteFile() {
      data->close();
      if (data->rdstate() == std::fstream::failbit) {
        ui::UIHandler::warning(className, "The file " + path + " could not be closed correctly before deletion");
      }

      std::error_code ec;
      if (std::filesystem::remove(path, ec)) {
        ui::UIHandler::info(className, "The file " + path + " has been deleted");
        return;
      }

      if (0 == ec.value()) {
        ui::UIHandler::warning(className, "The file " + path + "could not be deleted, but didn't produce an error");
        return;
      }

      if (ec.value() != 0) {
        ui::UIHandler::error(className, "An error occurred while deleting the file " + path + ": " + ec.message());
      }
    }

    void renameFile(std::string& newPath) {
      //TODO: Implement renaming of files
      ui::UIHandler::warning(className, "File renaming is not yet implemented");

    }

  };

}