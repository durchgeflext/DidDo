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
      static void info(const std::string_view& origin, const std::string& message) {
        std::cout << "INFO: " << "[" << origin << "]" << " " << message << std::endl;
      }

      /**
      * Prints a warning message to the console.
      */
      static void warning(const std::string_view& origin, const std::string& message) {
        std::cout << "WARNING: " << "[" << origin << "]" << " " << message << std::endl;
      }

      /**
      * Prints an error message to the console.
      */
      static void error(const std::string_view& origin, const std::string& errorMessage) {
        std::cerr << "[" << origin << "]" << " " << errorMessage << std::endl;
      }
  };
}