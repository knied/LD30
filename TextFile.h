//
//  TextFile.h
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 22.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#ifndef __LD30Xcode__TextFile__
#define __LD30Xcode__TextFile__

#include <iostream>
#include <fstream>
#include <streambuf>

class TextFile {
    std::ifstream _file;
    
public:
    TextFile(std::string const& filename);
    ~TextFile();
    
    std::string next_line();
    std::string content();
    void jump_to_top();
    bool end_of_file();
    
    bool is_open() const;
};

#endif /* defined(__LD30Xcode__TextFile__) */
