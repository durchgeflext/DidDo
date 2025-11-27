#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <storage/FileLoader.hpp>

namespace diddo::storage {
    class DiaryLoader {
        const std::string path;
        std::filesystem::directory_iterator fileIt;
        std::vector<std::shared_ptr<std::fstream> > diary;

        public:
        DiaryLoader() = delete;

        DiaryLoader(DiaryLoader &diary) = delete;

        DiaryLoader(DiaryLoader &&diary) = delete;

        explicit DiaryLoader(const std::string &path) : path(path), fileIt(path) {
            diary = std::vector<std::shared_ptr<std::fstream> >(10);
            for (const std::filesystem::directory_entry &file: fileIt) {
                if (file.is_directory()) {
                    ui::UIHandler::warning<DiaryLoader>(
                        "There is a directory where there should only be files");
                }
                const std::string &filePath = file.path().string();
                FileLoader loader(filePath);
                diary.emplace_back(loader.getContent());
            }
        };

        ~DiaryLoader() = default;

        [[nodiscard("Did you want to ignore all the data?")]]
        std::vector<std::unique_ptr<std::vector<std::string> > > &getDiary() {
            return diary;
        }

        void addEntry(const std::vector<std::string> &entry) {
            diary.emplace_back(std::make_unique<std::vector<std::string> >(entry));
        }
    };
};
