#include "utility.h"
#include "url_content.h"

#include <iostream>

int main(int argc, char** argv) {
  auto url_data = parse_comand_line(argc, argv);

  if (url_data == std::nullopt) {
    std::cout << "incorrect input data\n";
    return -1;
  }
  auto[url, deps] = url_data.value();

  if (!parse_url_content(url)) {
    return -1;
  }
  return 0;
}
