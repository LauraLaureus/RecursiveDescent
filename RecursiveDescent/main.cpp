#include "TokenChooser.hpp"

TokenChooser* tc;
Symbol nextToken;


void root();
void espacios();
void global();
void definicion();
void defineReal();
void defineVector();
void identificador();
void definicionFuncion();

void error(std::string s){
    printf(s.c_str());
    exit(1);
}

int main(int argc, const char * argv[]) {
    
    
    tc = new TokenChooser("/Users/lala/RecursiveDescent/test.ng");
    nextToken = tc->nextToken();
    root();
    printf("Parse completed.\n");
}

void root(){

    
    switch (nextToken.token) {
        case GLOBAL:
            espacios();
            root();
            break;
        case FUNC:
            espacios();
            root();
            break;
        case EOF:
            break;
        default:
            error("Undefined space. Expected function or global");
            break;
    }
}

void espacios(){
    switch (nextToken.token) {
        case GLOBAL:
            global();
            break;
            
        case FUNC:
            
            definicionFuncion();
            break;
            
        default:
            error("Space not defined properly. Expected function or global");
            break;
    }
    
}


void global(){

    if(nextToken.token == GLOBAL){
        nextToken = tc->nextToken();
        definicion();
        if(nextToken.token != PUNTOYCOMA){
            error("Expecting ;.");
        }
        else{
            nextToken = tc->nextToken();
        }
    }
}

void definicion(){
    
    switch (nextToken.token) {
        case REAL:
            defineReal();
            break;
        case VECTOR:
            defineVector();
            break;
        default:
            error("Expecting a data type ;.");
            break;
    }
}

void defineReal(){
    switch (nextToken.token) {
        case REAL:
            nextToken = tc->nextToken();
            identificador();
            break;
            
        default:
            error("Expecting a data type ;.");
            break;

    }

}

void defineVector(){

    switch (nextToken.token) {
        case VECTOR:
            nextToken = tc->nextToken();
            identificador();
            break;
            
        default:
            error("Expecting a data type ;.");
            break;
            
    }
}

void identificador(){
    switch (nextToken.token) {
        case VARIABLE:
            nextToken = tc->nextToken();
            break;
            
        default:
            error("Expecting a identifier ;.");
            break;
    }
    
}


void funcionInicio();
void funcionVoid();
void funcionDevuelve();

void definicionFuncion(){
    if(nextToken.token == FUNC){
        nextToken = tc->nextToken();
        switch (nextToken.token) {
            case INICIO:
                funcionInicio();
                break;
            case VARIABLE:
                funcionVoid();
                break;
            case REAL:
                funcionDevuelve();
                break;
            
            default:
               break;
        }
    }
}

void bloque();

void funcionInicio(){

    switch (nextToken.token) {
        case INICIO:
            nextToken = tc->nextToken();

            if(nextToken.token == ABRELLAVES){
                nextToken = tc->nextToken();
                //bloque();
                if(nextToken.token == CIERRALLAVES){
                    nextToken = tc->nextToken();
                }
            }
            else{
                error("Corrupted function definition.");
            }
            
            break;
            
        default:
            error("Unknow error");
            break;
    }
}

void defineParametros();

void funcionVoid(){
    switch (nextToken.token) {
        case VARIABLE:
            nextToken = tc->nextToken();
            defineParametros();
            if(nextToken.token == ABRELLAVES){
                nextToken = tc->nextToken();
                //bloque();
                if(nextToken.token == CIERRALLAVES){
                    nextToken = tc->nextToken();
                }
            }
            else{
                error("Corrupted function definition.");
            }
            
            break;
            
        default:
            error("Unknow error");
            break;
    }

}

void funcionDevuelve(){
    switch (nextToken.token) {
        case REAL:
            nextToken = tc->nextToken();
            identificador();
            defineParametros();
            if(nextToken.token == ABRELLAVES){
                nextToken = tc->nextToken();
                //bloque();
                if(nextToken.token == CIERRALLAVES){
                    nextToken = tc->nextToken();
                }
            }
            else{
                error("Corrupted function definition.");
            }
            
            break;
            
        default:
            error("Unknow error");
            break;
    }

}

void defineParametros(){



}
