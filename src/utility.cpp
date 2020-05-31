#include "utility.h"
#include "cxxopts.hpp"
#include <iostream>
#include <regex>
#include "logger.hpp"

constexpr size_t kDeps{4};
static bool IsUrl(const std::string& url) {
  std::regex reg{R"(https://(?:www\.|(?!www))[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|www\.[a-zA-Z0-9][a-zA-Z0-9-]+[a-zA-Z0-9]\.[^\s]{2,}|
https://(?:www\.|(?!www))[a-zA-Z0-9]+\.[^\s]{2,}|www\.[a-zA-Z0-9]+\.[^\s]{2,})"};
  std::cmatch match;
  return std::regex_match(url.c_str(), match, reg); // url == pattern
}

UrlParseData parse_comand_line(int argc, char** argv) { // url deps 
  cxxopts::Options options{argv[0], "Parse url content"};
  options.add_options()
  ("u, url", "Https url", cxxopts::value<std::string>())
  ("d, deps", "Deps url search", cxxopts::value<int>()->default_value("4"))
  ("h, help", "How to use");

  auto parse_result = options.parse(argc, argv);
  if (parse_result.count("help")) {
     std::cout << options.help() << std::endl;
     return std::nullopt;
  }

  if (parse_result.count("url") == 0) {
    std::cerr << "url must be set\n";
    CreateLoggerObject().print(Level::ERROR, "url must be set");
    return std::nullopt;
  }

  auto url = parse_result["url"].as<std::string>();

  if (!IsUrl(url)) {
    std::cerr << "incorrect url\n";
    CreateLoggerObject().print(Level::ERROR, "incorrect url");
    return std::nullopt;
  }

  return std::make_optional<UrlPair>(url, kDeps); // RVO
}