//
//  TextFile.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 22.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "TextFile.h"

TextFile::TextFile(std::string const& filename) {
    _file.open(filename.c_str());
}
TextFile::~TextFile() {
    _file.close();
}

std::string TextFile::next_line() {
    std::string line;
    std::getline(_file, line);
    return line;
}
std::string TextFile::content() {
    std::string content;
    content.assign((std::istreambuf_iterator<char>(_file)),
                   std::istreambuf_iterator<char>());
    return content;
}
void TextFile::jump_to_top() {
    _file.seekg(0, std::ios::beg);
}

bool TextFile::end_of_file() {
    return _file.eof();
}

bool TextFile::is_open() const {
    return _file.is_open();
}