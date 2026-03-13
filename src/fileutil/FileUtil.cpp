//
// Created by leonw on 13.03.2026.
//
#include "../fileutil/FileUtil.hpp"
#include <iterator>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

std::string FileUtil::read_file(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Failed to open file: " + path);
    return std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
}
