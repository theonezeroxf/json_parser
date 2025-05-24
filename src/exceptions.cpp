#include "json/exceptions.hpp"

ParseException::ParseException(const std::string& message)
    : std::runtime_error("Parse error: " + message) {}

InvalidValueException::InvalidValueException(const std::string& message)
    : std::runtime_error("Invalid value: " + message) {}