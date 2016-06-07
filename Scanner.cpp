//
//  Scanner.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "Scanner.hpp"

Scanner::Scanner(const char* path){
    
    this->file.open(path);
}

char Scanner::nextChar(){
    this->file.get(this->current);
    return this->current;
}

bool Scanner::hasNext(){
    return this->file.good();
}