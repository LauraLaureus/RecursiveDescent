//
//  main.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 14/3/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "TopDownSintacticAnalizer.hpp"

int main(int argc, const char * argv[]) {
    
    TopDownSintacticAnalizer sang = *new TopDownSintacticAnalizer("/Users/lala/ManualNG/AnalizadorLexicoManual/LexicalAnalizerForÑ/LexicalAnalizerForÑ/test.ng");
    sang.analice();
       
    return 0;
}
