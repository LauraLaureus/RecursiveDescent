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
void funcionInicio();
void funcionVoid();
void funcionDevuelve();
void bloque();
void defineParametros();
void parametros();

void linea();
void devuelve();
void devolucion();

void rupturaBucle();

void content();
void bloqueSi();
void bloqueMientras();


void termino();
void operacion();

void imprimible();
void salidaPantalla();
void llamadaFuncion();

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



void funcionVoid(){
    switch (nextToken.token) {
        case VARIABLE:
            nextToken = tc->nextToken();
            defineParametros();
            if(nextToken.token == ABRELLAVES){
                nextToken = tc->nextToken();
                bloque();
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
                bloque();
                devuelve();
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

    switch (nextToken.token) {
        case ABREPARENTESIS:
            nextToken = tc->nextToken();
            parametros();
            if(nextToken.token == CIERRAPARENTESIS){
                nextToken = tc->nextToken();
            }else{
                error("Error. Missed )");
            }
            break;
        
        default:
            error("Error. Maybe an extra space before parameters?");
            break;
    }


}

void parametros(){

    switch (nextToken.token) {
        case REAL:
        case VECTOR:
            definicion();
            parametros();
            break;
        case COMA:
            nextToken = tc->nextToken();
            parametros();
            break;
        case CIERRAPARENTESIS:
            return;
        default:
            break;
    }
}



void devuelve(){
    if (nextToken.token == DEVUELVE) {
        nextToken = tc->nextToken();
        devolucion();
    }
    else{
        error("Missed devuelve keyworkd ");

    }
}

void devolucion(){

    if (nextToken.token == VALORREAL || nextToken.token == VARIABLE) {
        nextToken = tc->nextToken();
        if(nextToken.token == PUNTOYCOMA){
            nextToken = tc->nextToken();
        }
        else{
            error("Missed ; ");
        }
    }
    else{
        error("Missed return value");
    }
}

void bloque(){

    switch (nextToken.token) {
        case REAL:
        case VECTOR:
        case VARIABLE:
        case SI:
        case MIENTRAS:
        case CALL:
        case ESCRIBIR:
        case PARAR:
            linea();
            break;
        case CIERRALLAVES: //siguientes
        case DEVUELVE:
            return;
        default:
            error("Unknown sentence");
            break;
    }
}



void linea(){

    switch (nextToken.token) {
        case REAL:
        case VECTOR:
        case VARIABLE:
        case CALL:
        case ESCRIBIR:
         case PARAR:
            content();
            break;
        case SI:
            bloqueSi();
            break;
        case MIENTRAS:
            bloqueMientras();
            break;
        default:
            error("Unknown sentence");
            break;
    }
    bloque();
    //nextToken = tc->nextToken(); //solo para probar.
}

void content(){
    switch (nextToken.token) {
        case PARAR:
            rupturaBucle();
            break;
        case ESCRIBIR:
            salidaPantalla();
            break;
        case CALL:
            llamadaFuncion();
            break;
            
        default:
            error("Unknown content");
            break;
    }
    if (nextToken.token == PUNTOYCOMA) {
        nextToken = tc->nextToken();
    }
}

void expresion();

void bloqueSi(){

    if(nextToken.token == SI){
        nextToken = tc->nextToken();
        if( nextToken.token == ABREPARENTESIS){
            nextToken = tc->nextToken();
            expresion();
            
            if(nextToken.token == CIERRAPARENTESIS){
                nextToken = tc->nextToken();
            }
            else
                error("Missed a )");
                
        }
        else
            error("Missing ( for expresion");
        
        if(nextToken.token == ABRELLAVES){
            nextToken = tc->nextToken();
            bloque();
            if(nextToken.token == CIERRALLAVES){
                nextToken = tc->nextToken();
            }
            else error("Missed a )");
        }
        else
            error("Missed sentences for flow control expression");
        
    }else{
        error("Missed si keyword");
    }

}

void bloqueMientras(){
    
    if(nextToken.token == MIENTRAS){
        nextToken = tc->nextToken();
        if( nextToken.token == ABREPARENTESIS){
            nextToken = tc->nextToken();
            expresion();
            
            if(nextToken.token == CIERRAPARENTESIS){
                nextToken = tc->nextToken();
            }
            else
                error("Missed a )");
            
        }
        else
            error("Missing ( for expresion");
        
        if(nextToken.token == ABRELLAVES){
            nextToken = tc->nextToken();
            bloque();
            if(nextToken.token == CIERRALLAVES){
                nextToken = tc->nextToken();
            }
            else error("Missed a )");
        }
        else
            error("Missed sentences for flow control expression");
        
    }else{
        error("Missed si keyword");
    }
}


void expresion(){
        if(nextToken.token == VARIABLE || nextToken.token== VALORREAL){
        
            termino();
            operacion();
            termino();
        }else
        error("unknown expresion");
     //nextToken = tc->nextToken();
}

void termino(){
    if(nextToken.token == VARIABLE || nextToken.token== VALORREAL){
        nextToken = tc->nextToken();
    }
    else{
        error("unknown terminal");
    }
}

void operacion(){

    switch (nextToken.token) {
        case SUMA:
        case RESTA:
        case DIVISION:
        case MULTIPLICACION:
        case OR:
        case AND:
        case NOT:
        case MAYOR_QUE:
        case MAYOR_O_IGUAL_QUE:
        case MENOR_QUE:
        case MENOR_O_IGUAL_QUE:
            nextToken = tc->nextToken();
            break;
            
        default:
            error("unknown operation");
            break;
    }
}


void rupturaBucle(){
    if(nextToken.token == PARAR ){
        nextToken = tc->nextToken();
    }
    else{
        error("unknown loop break");
    }
}

void salidaPantalla(){
    if(nextToken.token == ESCRIBIR ){
        nextToken = tc->nextToken();
        imprimible();
    }
    else{
        error("unknown how to show in display");
    }

}

void imprimible(){
    if(nextToken.token == CADENA || nextToken.token == VARIABLE ){
        nextToken = tc->nextToken();
    }
    else{
        error("unknown what to print");
    }
}


void llamadaFuncion(){
    if(nextToken.token == CALL ){
        nextToken = tc->nextToken();
        if(nextToken.token == VARIABLE ){
            nextToken = tc->nextToken();
            defineParametros();
        }
        else{
            error("unknown how to show in display");
        }
    }
    else{
        error("unknown how to call the function");
    }
}