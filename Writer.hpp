//
//  Writer.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef Writer_hpp
#define Writer_hpp

#include <fstream>

#endif /* Writer_hpp */

class Writer {
    FILE* file;
    
public:
    Writer();
    void writeToken(int token);
    void writeValue(double value);
};