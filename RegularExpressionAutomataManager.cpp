//
//  RegularExpressionAutomataManager.cpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 11/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#include "RegularExpressionAutomataManager.hpp"

RegularExpressionAutomataManager::RegularExpressionAutomataManager(){
    this->id = *new RegularExpressionAutomataIdentificador();
    this->dig = *new RegularExpressionAutomataDigit();
    this->str = *new RegularExpressionAutomataString();
}

int RegularExpressionAutomataManager::anyRegularExpresionInRightOrPartialState(std::string chain,bool write){
    /*
     TODO: 
        lanzar todos los automatas y desde que uno de 0 o 1 devolver true en otro caso devolver false.
     */
    int n;
    
    
    n = id.check(chain,write);
    if(n  > -1){
        lastActive = 1;
        return n;
    }
    
    n = dig.check(chain, write);
    if(n  > -1){
        lastActive = 2;
        return n;
    }
    
    n = str.check(chain, write);
    if(n  > -1){
        lastActive = 3;
        return n;
    }
    
    return -1;
}

int RegularExpressionAutomataManager::getLastIndexFromLastActive(){

    switch (lastActive) {
        case 1:
            return id.getLastIndex();
            break;
        case 2:
            return dig.getLastIndex();
            break;
        case 3:
            return str.getLastIndex();
            break;

    }
    
    return 0;
}


///////////////////ID_ Automata

int RegularExpressionAutomataIdentificador::initialState(std::string chain,bool write){

    if (std::isalpha(chain[0])) {
        return State1(chain,1,write);
    }
    return -1;
}

int RegularExpressionAutomataIdentificador::State1(std::string chain,int index,bool write){
    
    //Continue processing chain
    if (std::isalnum(chain[index])) {
        if(chain.size()-1 == index && write){
            this->identifier = chain;
            return 0;
        }
        else if (chain.size()-1 == index) return 1;
        return State1(chain,index+1,write);
    }
    else if(index < chain.size()){
        this->identifier = chain;
        this->lastIndex = index;
        return 2;
    }
    
    return -1;
    
}


std::string RegularExpressionAutomataIdentificador::getIdentifier(){
    if (lastIndex != 0) {
        std::string id (this->identifier.begin(),this->identifier.begin()+lastIndex);
        return id;
    }
    return this->identifier;
}

int RegularExpressionAutomataIdentificador::getLastIndex(){
    return this->lastIndex;
}



////////////////Real_ Automata

int RegularExpressionAutomataDigit::initialState(std::string chain, bool write){
    if(std::isdigit(chain[0])){
        return State1(chain,1, write);
    }
    return -1;
}

int RegularExpressionAutomataDigit::State1(std::string chain,int index, bool write){

    if (std::isdigit(chain[index])) {
        if(chain.size()-1 == index && write){
            this->value = std::stof(chain);
            return 0;
        }
        else if (chain.size()-1 == index) return 1;
        return State1(chain, index+1, write);
    } else if (chain[index] == '.') {
        //this->value = std::stof(chain);
        return State2(chain, index+1, write);
    }
    else if(index < chain.size()){
        this->value = std::stof(chain);
        this->lastIndex = index;
        return 2;
    }
    return -1;

}


int RegularExpressionAutomataDigit::State2(std::string chain,int index, bool write){
    
    if (std::isdigit(chain[index])) {
        if(chain.size()-1 == index && write){
            this->value = std::stof(chain);
            return 0;
        }
        else if (chain.size()-1 == index) return 1;
        return State2(chain, index+1, write);
    } else if(index < chain.size()){
        this->value = std::stof(chain);
        this->lastIndex = index;
        return 2;
    }
    return -1;
}




double RegularExpressionAutomataDigit::getValue(){
    return this->value;
}

int RegularExpressionAutomataDigit::getLastIndex(){
    return this->lastIndex;
}


//TODO State1

int RegularExpressionAutomataString::initialState(std::string chain, bool write){
    if(chain[0] == '\"'){
        return State1(chain, 1, write);
    }
    return -1;
}

int RegularExpressionAutomataString::State1(std::string chain, int index, bool write){
    if(chain[index] == '\"'){
        this->value = chain;
        return 3;
    }else if(index == chain.size()-1) return 1;
    else {
        return State1(chain, index+1, write);
    }
}


std::string RegularExpressionAutomataString::getValue(){
    return this->value;
}

int RegularExpressionAutomataString::getLastIndex(){
    return this->getLastIndex();
}


