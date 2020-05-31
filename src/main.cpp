#include "utility.h"
#include "url_content.h"
#include "logger.hpp"
#include <iostream>

int main(int argc, char** argv) {
  try {
    auto url_data = parse_comand_line(argc, argv);

    if (url_data == std::nullopt) {
      return -1;
    }
    auto[url, deps] = url_data.value();

    CreateLoggerObject().print(Level::DEBUG, "URL:", url, "deps:", deps);

    if (!get_url_content(url)) {
      return -1;
    }
  } catch(const std::exception& e) {
     std::cerr << "Throw exception\n";
  }
  return 0;
}
