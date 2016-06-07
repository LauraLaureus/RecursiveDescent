//
//  Writer.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 16/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "Writer.hpp"

Writer::Writer(){

    this->file = fopen("lang_output.ngi", "w");
}

void Writer::writeToken(int token){
    fwrite(&token, sizeof(int), 1, this->file);
}

void Writer::writeValue(double value){
    fwrite(&value, sizeof(double), 1, this->file);
}