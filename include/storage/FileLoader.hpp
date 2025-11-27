#pragma once

#include <filesystem>
#include <fstream>
#include <string>

#include <UI/UIHandler.hpp>


namespace diddo::storage {
#define IGNORED_STATUS "Did you want to ignore the return status?"

    /**
     *This class handles loading files, as well as deleting and saving them.
     */
    class FileLoader {
        static constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
        const std::string &path;
        std::shared_ptr<std::fstream> data;

        public:
        FileLoader() = delete;

        FileLoader(FileLoader &file) = delete;

        FileLoader(FileLoader &&file) = delete;

        /**
        * Constructor for the FileLoader class.
        *
        * @param path Reference to the path, where the file is located
        */
        explicit FileLoader(const std::string &path) : path(path) {
        }

        ~FileLoader() = default;

        /**
        * Returns the contents of the file.
        *
        * @return shared pointer to the file stream, which is both readable and writable
        */
        [[nodiscard(IGNORED_STATUS)]]
        bool getContent(std::shared_ptr<std::fstream> &data) const {
            if (!this->data->is_open()) {
                ui::UIHandler::error<FileLoader>("The file " + path + " is not open");
                return false;
            }
            data = this->data;
            return true;
        }

        /**
        * Closes and deletes the file.
        *
        * @return Returns true, if operation was successful and false otherwise
        */
        [[nodiscard(IGNORED_STATUS)]]
        bool deleteFile() const {
            data->close();
            if (data->rdstate() == std::fstream::failbit) {
                ui::UIHandler::warning<FileLoader>("The file " + path + " could not be closed correctly");
                return false;
            }

            std::error_code ec;
            if (std::filesystem::remove(path, ec)) {
                ui::UIHandler::info<FileLoader>("The file " + path + " has been deleted");
                return true;
            }

            if (0 == ec.value()) {
                ui::UIHandler::warning<FileLoader>(
                    "The file " + path + "could not be deleted, but didn't produce an error");
                return false;
            }
            ui::UIHandler::error<FileLoader>("An error occurred while deleting the file " + path + ": " + ec.message());
            return false;
        }

        /**
         * Renames the file
         *
         * @param newPath The new name of the file
         * @return True, if successful, false otherwise
         */
        bool renameFile(std::string &newPath) {
            //TODO: Implement renaming of files
            ui::UIHandler::warning<FileLoader>("File renaming is not yet implemented");
            return false;
        }

        /**
         * Opens the file
         *
         * @return True, if the file was opened successfully, false otherwise
         */
        [[nodiscard(IGNORED_STATUS)]]
        bool openFile() const {
            data->open(path, mode);
            if (data->rdstate() == std::fstream::failbit) {
                ui::UIHandler::error<FileLoader>("The file " + path + " could not be opened");
                return false;
            }
            ui::UIHandler::info<FileLoader>("The file " + path + " has been opened");
            return true;
        }

        [[nodiscard]] bool closeFile() const {
            if (!data->is_open()) {
                ui::UIHandler::warning<FileLoader>("The file " + path + " has already been closed");
                return true;
            }
            data->close();
            if (data->rdstate() == std::fstream::failbit) {
                ui::UIHandler::error<FileLoader>("The file " + path + " could not be closed");
                return false;
            }
            return true;
        }
    };
}
