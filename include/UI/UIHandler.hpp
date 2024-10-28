#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#endif //UIHANDLER_HPP

#include <string>

namespace diddo::ui {
  class UIHandler {
    private:

    public:
      static void warning(const std::string_view& origin, const std::string& message) {
        std::cout << "WARNING:" << "[" << origin << "]" << " " << message << std::endl;
      }

      static void error(const std::string_view& origin, const std::string& errorMessage) {
        std::cerr << "[" << origin << "]" << " " << errorMessage << std::endl;
      }
  };
}