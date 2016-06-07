//
//  Scanner.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef Scanner_hpp
#define Scanner_hpp

#include <fstream>
//#include <iterator>
#include "global.h"

#endif /* Scanner_hpp */

using namespace std;

class Scanner {
    std::ifstream file;
    char current;
    
public:
    Scanner(const char* path);
    char nextChar();
    bool hasNext ();
};
