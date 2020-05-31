#include <curl/curl.h>
#include "url_content.h"
#include <iostream>

bool get_url_content(const std::string& url) {
  CURL* curl_handler = curl_easy_init();
  if (curl_handler == nullptr) {
    return false;
  }
  std::string url_content;

  auto callback = [](char *ext_data, size_t size, size_t nmemb, std::string* out_data) -> size_t {
    if (ext_data != nullptr && out_data != nullptr) {
        out_data->append(ext_data, size * nmemb);

        return size * nmemb; // size_t 
    }
    return 0; // int
  };

  curl_easy_setopt(curl_handler, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl_handler, CURLOPT_WRITEFUNCTION, +callback);
  curl_easy_setopt(curl_handler, CURLOPT_WRITEDATA, &url_content);
  auto res = curl_easy_perform(curl_handler);

  if (res != CURLE_OK) {
    std::cout << curl_easy_strerror(res) << std::endl;
    return false;
  }
  // std::cout << url_content << std::endl;
  return true;
}