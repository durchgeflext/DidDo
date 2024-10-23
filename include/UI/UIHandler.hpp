#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#endif //UIHANDLER_HPP

#include <string>

namespace diddo::ui {
  class UIHandler {
    private:

    public:
      static void error(const std::string& origin, const std::string& errorMessage) {
        std::cerr << "[" << origin << "]" << " " << errorMessage << std::endl;
      }
  };
}