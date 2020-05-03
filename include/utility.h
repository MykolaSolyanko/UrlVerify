#pragma once

#include <string>
#include <utility>
#include <optional>

using UrlPair = std::pair<std::string, size_t>;

using UrlParseData = std::optional<UrlPair>;

UrlParseData parse_comand_line(int argc, char** argv);