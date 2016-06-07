//
//  RegularExpressionAutomataManager.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 11/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//
#pragma once
#include <string>



class RegularExpressionAutomata{
public:
    virtual int check(std::string str,bool write) = 0;
};


class RegularExpressionAutomataIdentificador : public RegularExpressionAutomata{
    
private:
    int initialState(std::string chain,bool write);
    int State1(std::string chain,int index,bool write);
    std::string identifier;
    int lastIndex = 0;
    
public:
    int check(std::string str,bool write){
        return initialState(str,false);
    };
    
    std::string getIdentifier();
    int getLastIndex();
};



class RegularExpressionAutomataDigit: public RegularExpressionAutomata{
private:
    double value;
    int lastIndex = 0;
    int initialState(std::string chain, bool write);
    int State1(std::string chain,int index, bool write);
    int State2(std::string chain,int index, bool write);

public:
    int check(std::string str, bool write){
        return initialState(str,false);
    };
    double getValue();
    int getLastIndex();
};

/* ---------------FOCUS -----------------*/


class RegularExpressionAutomataString: public RegularExpressionAutomata{

    std::string value;
    int lastIndex = 0;
    int initialState(std::string chain, bool write);
    int State1(std::string chain,int index, bool write);
    int State2(std::string chain,int index, bool write);

public:
    int check(std::string str, bool write){
        return initialState(str,false);
    };
    
    std::string getValue();
    int getLastIndex();

};



class RegularExpressionAutomataManager{

    int lastActive;
    RegularExpressionAutomataIdentificador id;
    RegularExpressionAutomataDigit dig;
    RegularExpressionAutomataString str;
    /*For Automatas*/
    
public:
    RegularExpressionAutomataManager();
    int anyRegularExpresionInRightOrPartialState(std::string,bool);
    int getLastIndexFromLastActive();
};


