#pragma once
#include <string>

#define toRadian(x) x*3.1415926/180.0f

bool ReadFile(const char* FileName, std::string& outFile);