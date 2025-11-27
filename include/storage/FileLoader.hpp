#pragma once

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <UI/UIHandler.hpp>


namespace diddo::storage {
#define IGNORED_STATUS "Did you want to ignore the return status?"

    /**
     *This class handles loading files, as well as deleting and saving them.
     */
    class FileLoader {
        static constexpr std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out;
        const std::string &path;
        std::fstream data;

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
        * @return a vector of strings representing each line
        */
        [[nodiscard(IGNORED_STATUS)]]
        bool getContent(std::vector<std::string>& strv) {
            if (!strv.empty()) {
                ui::UIHandler::error<FileLoader>("The input vector is not empty");
                return false;
            }

            if (!data.is_open()) {
                ui::UIHandler::error<FileLoader>("The file " + path + " is not open");
                return false;
            }

            std::string tmp;
            while (std::getline(data, tmp)) {
                strv.push_back(tmp);
            }
            return true;
        }

        /**
        * Returns the contents of the file.
        *
        * @return string with file contents
        */
        [[nodiscard(IGNORED_STATUS)]]
        bool getContent(std::string& str) {
            if (!str.empty()) {
                ui::UIHandler::error<FileLoader>("The input string is not empty");
                return false;
            }

            if (!data.is_open()) {
                ui::UIHandler::error<FileLoader>("The file " + path + " is not open");
                return false;
            }

            std::stringstream buf;
            buf << data.rdbuf();
            str = buf.str();
            return true;
        }

        /**
         * Writes data back to the file
         *
         * @param strv The vector containing the lines
         * @return True, if everything succeeded, false otherwise
         */
        [[nodiscard(IGNORED_STATUS)]]
        bool writeContent(const std::vector<std::string>& strv) {
            if (strv.empty()) {
                ui::UIHandler::warning<FileLoader>("Writing nothing to file, as the input is empty");
                return true;
            }

            if (!data.is_open()) {
                ui::UIHandler::error<FileLoader>("The file " + path + " is not open");
                return false;
            }

            for (const auto& line : strv) { // NOLINT(readability-use-anyofallof)
                data << line << "\n";
                if (data.rdstate() == std::fstream::failbit) {
                    ui::UIHandler::error<FileLoader>("Encountered Error when attempting to write \""
                                                        + line + "\" to file " + path);
                    return false;
                }
            }
            return true;
        }

        /**
         * Writes data back to the file
         *
         * @param str The string with the input data
         * @return True, if everything succeeded, false otherwise
         */
        [[nodiscard(IGNORED_STATUS)]]
        bool writeContent(const std::string& str) {
            if (str.empty()) {
                ui::UIHandler::warning<FileLoader>("Writing nothing to file, as the input is empty");
                return true;
            }

            if (!data.is_open()) {
                ui::UIHandler::error<FileLoader>("The file " + path + " is not open");
                return false;
            }

            data << str;
            if (data.rdstate() == std::fstream::failbit) {
                ui::UIHandler::error<FileLoader>("Encountered error when attempting to write to file " + path);
                return false;
            }
            return true;
        }

        /**
        * Closes and deletes the file.
        *
        * @return Returns true, if operation was successful and false otherwise
        */
        [[nodiscard(IGNORED_STATUS)]]
        bool deleteFile() {
            data.close();
            if (data.rdstate() == std::fstream::failbit) {
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
        bool openFile() {
            data.open(path, mode);
            if (data.rdstate() == std::fstream::failbit) {
                ui::UIHandler::error<FileLoader>("The file " + path + " could not be opened");
                return false;
            }
            ui::UIHandler::info<FileLoader>("The file " + path + " has been opened");
            return true;
        }

        [[nodiscard(IGNORED_STATUS)]]
        bool closeFile() {
            if (!data.is_open()) {
                ui::UIHandler::warning<FileLoader>("The file " + path + " has already been closed");
                return true;
            }
            data.close();
            if (data.rdstate() == std::fstream::failbit) {
                ui::UIHandler::error<FileLoader>("The file " + path + " could not be closed");
                return false;
            }
            return true;
        }
    };
}
