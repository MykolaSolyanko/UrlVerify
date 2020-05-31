#include <array>
#include <iostream>
#include <fstream> 
#include <exception>

enum class Level { // unscouped
    DEBUG,
    INFO,
    ERROR,
    WARNING
};

static const char* getDebugLevel(Level level) {
  switch (level)
  {
  case Level::DEBUG:
    return "[DEBUG]";
  case Level::INFO:
    return "[INFO]";
  case Level::ERROR:
    return "[ERROR]";
  case Level::WARNING:
    return "[WARNING]";
  default:
     return "[UNDEFINED]";
  }
}

template <typename T>
class Logger;

template <>
class Logger<std::ostream> {
  Logger() = delete;
  Logger(const Logger&) = delete;
  Logger& operator =(const Logger&) = delete;

  public:
  template<typename ...Args>
  constexpr void print(Level level, Args&& ...args) {
    std::cout << getDebugLevel(level) << " ";
    print(std::forward<Args>(args)...);
  }

  private:
    template<typename T, typename ...Args>
    constexpr void print(T value, Args&& ...args) {
      std::cout << value << " ";
      print(std::forward<Args>(args)...);
    }

    template<typename T>
    constexpr void print(T&& value) {
      std::cout << value << "\n";
    }
};

template <>
class Logger<std::ofstream> {
  Logger(Logger&&) = delete;
  public:
    template<typename ...Args>
    constexpr void print(Level level, Args&& ...args) {
      file << getDebugLevel(level) << " ";
      print(std::forward<Args>(args)...);
    }
  private:
    Logger(const char *file_path = "log") : file{file_path} {
      if (!file.is_open()) {
        throw std::runtime_error{"Can not open logger file"};
      }
    }
    template<typename T, typename ...Args>
    constexpr void print(T value, Args&& ...args) {
      file << value << " ";
      print(std::forward<Args>(args)...);
    }

    template<typename T>
    constexpr void print(T&& value) {
      file << value << "\n";
    }
    friend inline Logger<std::ofstream>& CreateLoggerObject();
    std::ofstream file; // RAII 
};

// ODR
inline Logger<std::ofstream>& CreateLoggerObject() {
  static Logger<std::ofstream> logger{"/usr/share/url_project"};
  return logger;
}
