#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#endif //UIHANDLER_HPP

#include <string>

namespace diddo::ui {
    /**
    * This class handles the user interface.
    */
    class UIHandler {
        private:

        public:
        /**
        * Prints an info message to the console.
        */
        template<typename T>
        static void info(const std::string &message) {
            std::cout << "INFO: " << "[" << typeid(T).name() << "]" << " " << message << std::endl;
        }

        /**
        * Prints a warning message to the console.
        */
        template<typename T>
        static void warning(const std::string &message) {
            std::cout << "WARNING: " << "[" << typeid(T).name() << "]" << " " << message << std::endl;
        }

        /**
        * Prints an error message to the console.
        */
        template<typename T>
        static void error(const std::string &errorMessage) {
            std::cerr << "[" << typeid(T).name() << "]" << " " << errorMessage << std::endl;
        }
    };
}
