//
//  TopDownSintacticAnalizer.hpp
//  LexicalAnalizerForÑ
//
//  Created by Laura del Pino Díaz on 14/5/16.
//  Copyright © 2016 Laura del Pino Díaz. All rights reserved.
//

#ifndef TopDownSintacticAnalizer_hpp
#define TopDownSintacticAnalizer_hpp


#include <stack>
#include "TokenChooser.hpp"
#include <vector>

#endif /* TopDownSintacticAnalizer_hpp */

using namespace std;


class Relation {
public:
    int nt_token;
    int t_token;
    vector<Symbol> rule;

    Relation(int t, int t2){
        this->nt_token = t;
        this->t_token = t2;
    };
    
    void addToNoTerminal(Symbol d){
        this->rule.push_back(d);
    }
};


class Table {
    vector<Relation> v;
    
public:
    
    Table(){
        this->v = *new vector<Relation>();
    }
    
    
    vector<Symbol> getRule(int topStack, int entry){
        for (int i = 0; i < v.size(); i++) {
            if(v[i].nt_token == topStack && v[i].t_token == entry)
                return v[i].rule;
        }
        return *new vector<Symbol>();
    }
    
    bool ExistsARule(int topStack, int entry){
        for (int i = 0; i < v.size(); i++) {
            if(v[i].nt_token == topStack && v[i].t_token == entry)
                return true;
        }
        return false;
    }
    
    void insertARelation(Relation r){
        this->v.push_back(r);
    }
};


/*---------------------TOPDOWN-----------------*/


class TopDownSintacticAnalizer{
private:
    stack<Symbol> pila;
    TokenChooser lang;
    Table table;
    
    
    Symbol ENDOFSTACK = *new Symbol('$', '$');
    Symbol root = *new Symbol(-1);
    Symbol espacios = *new Symbol(-2);
    Symbol globalVar = *new Symbol(-3);
    Symbol declaration = *new Symbol(-4);
    Symbol declaracionReal = *new Symbol (-5);
    Symbol declaracionVector = *new Symbol (-6);
    Symbol funcion = *new Symbol(-7);
    Symbol deffuncion = *new Symbol(-8);
    Symbol funcionDevuelve = * new Symbol(-9);
    Symbol funcionInicio = * new Symbol(-10);
    Symbol funcionVoid = *new Symbol(-11);
    Symbol bloque = *new Symbol(-12);
    Symbol defineParametros = *new Symbol(-13);
    Symbol devuelve = *new Symbol(-14);
    Symbol linea = *new Symbol(-15);
    Symbol content = *new Symbol(-16);
    Symbol bloqueSi = *new Symbol(-17);
    Symbol bloqueMientras = *new Symbol(-18);
    Symbol asignaReal = *new Symbol(-19);
    Symbol asignaVector = *new Symbol(-20);
    Symbol modificaVariable = *new Symbol(-21);
    Symbol llamadaFuncion = *new Symbol(-22);
    Symbol salidaPantalla = *new Symbol(-23);
    Symbol rupturaBucle = *new Symbol(-24);
    Symbol creacionReal = *new Symbol(-25);
    Symbol expresion = *new Symbol(-26);
    Symbol auxExpresion = *new Symbol(-27);
    Symbol creacionVector = *new Symbol(-28);
    Symbol vectorNT = *new Symbol(-29);
    Symbol elementos = *new Symbol(-30);
    Symbol completion = *new Symbol(-31);
    Symbol asignacion = *new Symbol(-32);
    Symbol modificacion = *new Symbol(-33);
    Symbol desplazamiento = *new Symbol(-34);
    Symbol variable = *new Symbol(-35);
    Symbol termino = *new Symbol(-36);
    Symbol posicionVector = *new Symbol(-37);
    Symbol operacion = *new Symbol(-38);
    Symbol parametros = *new Symbol(-39);
    Symbol imprimible = *new Symbol(-40);
    Symbol devolucion = *new Symbol(-41);
    
    void fullfillAnalysisTable(){
        Relation root_global = *new Relation(root.token,GLOBAL);
        root_global.addToNoTerminal(espacios);
        root_global.addToNoTerminal(root);
        this->table.insertARelation(root_global);
        
        Relation root_func = *new Relation(root.token,FUNC);
        root_func.addToNoTerminal(espacios);
        root_func.addToNoTerminal(root);
        this->table.insertARelation(root_func);
        
        Relation root_eof = *new Relation(root.token,EOF);
        root_eof.addToNoTerminal(*new Symbol(EOF));
        this->table.insertARelation(root_eof);
        
        Relation espacios_global = *new Relation(espacios.token,GLOBAL);
        espacios_global.addToNoTerminal(globalVar);
        this->table.insertARelation(espacios_global);
        
        Relation espacios_funcion = *new Relation(espacios.token,FUNC);
        espacios_funcion.addToNoTerminal(funcion);
        this->table.insertARelation(espacios_funcion);
        
        
        Relation globalVar_global = *new Relation(globalVar.token,GLOBAL);
        globalVar_global.addToNoTerminal(* new Symbol(GLOBAL,GLOBAL));
        globalVar_global.addToNoTerminal(declaration);
        globalVar_global.addToNoTerminal(*new Symbol(PUNTOYCOMA,PUNTOYCOMA));
        this->table.insertARelation(globalVar_global);
        
        Relation declaration_real = *new Relation(declaration.token,REAL);
        declaration_real.addToNoTerminal(declaracionReal);
        this->table.insertARelation(declaration_real);
        
        Relation declaracionReal_real = *new Relation(declaracionReal.token,REAL);
        declaracionReal_real.addToNoTerminal(*new Symbol(REAL,REAL));
        declaracionReal_real.addToNoTerminal(*new Symbol(VARIABLE));
        this->table.insertARelation(declaracionReal_real);
        
        Relation declaracion_vector = *new Relation(declaration.token,VECTOR);
        declaracion_vector.addToNoTerminal(declaracionVector);
        this->table.insertARelation(declaracion_vector);
        
        Relation declaracion_vector_hijo = *new Relation(declaracionVector.token,VECTOR);
        declaracion_vector_hijo.addToNoTerminal(*new Symbol(VECTOR));
        declaracion_vector_hijo.addToNoTerminal(*new Symbol(VARIABLE));
        this->table.insertARelation(declaracion_vector_hijo);
        
        Relation defineFuncion_init = *new Relation(funcion.token, INICIO);
        defineFuncion_init.addToNoTerminal(funcionVoid);
        this->table.insertARelation(defineFuncion_init);
        
        Relation funcionInicio_rel = *new Relation(funcionInicio.token,INICIO);
        funcionInicio_rel.addToNoTerminal(*new Symbol(INICIO));
        funcionInicio_rel.addToNoTerminal(*new Symbol(VARIABLE));
        funcionInicio_rel.addToNoTerminal(*new Symbol(ABRELLAVES));
        funcionInicio_rel.addToNoTerminal(*new Symbol(INICIO));
        funcionInicio_rel.addToNoTerminal(bloque);
        funcionInicio_rel.addToNoTerminal(*new Symbol(CIERRALLAVES));
        this->table.insertARelation(funcionInicio_rel);
        
        Relation defineFuncion_devuelve = *new Relation(funcion.token, REAL);
        defineFuncion_devuelve.addToNoTerminal(funcionDevuelve);
        this->table.insertARelation(defineFuncion_devuelve);
        
        Relation defineFuncion_void = *new Relation(funcion.token, INICIO);
        defineFuncion_void.addToNoTerminal(funcionVoid);
        this->table.insertARelation(defineFuncion_void);
        
        Relation funcionVoid_rel = *new Relation(funcionVoid.token,VARIABLE);
        funcionInicio_rel.addToNoTerminal(*new Symbol(VARIABLE));
        funcionInicio_rel.addToNoTerminal(defineParametros);
        funcionInicio_rel.addToNoTerminal(*new Symbol(ABRELLAVES));
        funcionInicio_rel.addToNoTerminal(bloque);
        funcionInicio_rel.addToNoTerminal(*new Symbol(CIERRALLAVES));
        this->table.insertARelation(funcionVoid_rel);
        
        
        Relation funcionDevuelve_rel = *new Relation(funcionDevuelve.token,REAL);
        funcionInicio_rel.addToNoTerminal(*new Symbol(REAL));
        funcionInicio_rel.addToNoTerminal(defineParametros);
        funcionInicio_rel.addToNoTerminal(*new Symbol(ABRELLAVES));
        funcionInicio_rel.addToNoTerminal(bloque);
        funcionInicio_rel.addToNoTerminal(devuelve);
        funcionInicio_rel.addToNoTerminal(*new Symbol(CIERRALLAVES));
        this->table.insertARelation(funcionDevuelve_rel);
        

        Relation bloque_real = *new Relation(bloque.token,REAL);
        bloque_real.addToNoTerminal(linea);
        bloque_real.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_real);
        
        
        Relation bloque_vector = *new Relation(bloque.token,VECTOR);
        bloque_vector.addToNoTerminal(linea);
        bloque_vector.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_vector);
        
        
        Relation bloque_var = *new Relation(bloque.token,VARIABLE);
        bloque_var.addToNoTerminal(linea);
        bloque_var.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_var);
        
        
        Relation bloque_if = *new Relation(bloque.token,SI);
        bloque_if.addToNoTerminal(linea);
        bloque_if.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_if);

        
        Relation bloque_call = *new Relation(bloque.token,CALL);
        bloque_call.addToNoTerminal(linea);
        bloque_call.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_call);

        
        Relation bloque_while = *new Relation(bloque.token,MIENTRAS);
        bloque_while.addToNoTerminal(linea);
        bloque_while.addToNoTerminal(bloque);
        this->table.insertARelation(bloque_while);
        
        
        Relation bloque_empty = *new Relation(bloque.token,CIERRALLAVES);
        this->table.insertARelation(bloque_empty);
        
        Relation bloque_empty2 = *new Relation(bloque.token,DEVUELVE);
        this->table.insertARelation(bloque_empty2);

        
        Relation line_content = *new Relation(linea.token,REAL);
        line_content.addToNoTerminal(content);
        line_content.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_content);
        
        Relation line_contentV = *new Relation(linea.token,VECTOR);
        line_contentV.addToNoTerminal(content);
        line_contentV.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_contentV);
        
        Relation line_contentVar = *new Relation(linea.token,VARIABLE);
        line_contentVar.addToNoTerminal(content);
        line_contentVar.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_contentVar);
        
        Relation line_contentC = *new Relation(linea.token,CALL);
        line_contentC.addToNoTerminal(content);
        line_contentC.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_contentC);
        
        Relation line_contentE = *new Relation(linea.token,ESCRIBIR);
        line_contentE.addToNoTerminal(content);
        line_contentE.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_contentE);
        
        Relation line_contentB = *new Relation(linea.token,BREAK);
        line_contentB.addToNoTerminal(content);
        line_contentB.addToNoTerminal(*new Symbol(PUNTOYCOMA));
        this->table.insertARelation(line_contentB);

        
        Relation line_contentS = *new Relation(linea.token,SI);
        line_contentS.addToNoTerminal(bloqueSi);
        this->table.insertARelation(line_contentS);
        
        Relation line_contentM = *new Relation(linea.token,MIENTRAS);
        line_contentM.addToNoTerminal(bloqueMientras);
        this->table.insertARelation(line_contentM);
        
        Relation content_a = *new Relation(content.token,REAL);
        content_a.addToNoTerminal(*new Symbol(REAL));
        content_a.addToNoTerminal(*new Symbol(VARIABLE));
        content_a.addToNoTerminal(asignaReal);
        this->table.insertARelation(content_a);

        Relation content_av = *new Relation(content.token,VECTOR);
        content_av.addToNoTerminal(*new Symbol(VECTOR));
        content_av.addToNoTerminal(*new Symbol(VARIABLE));
        content_av.addToNoTerminal(asignaVector);
        this->table.insertARelation(content_av);
        
        Relation content_avar = *new Relation(content.token,VARIABLE);
        content_avar.addToNoTerminal(modificaVariable);
        this->table.insertARelation(content_avar);
        
        Relation content_call = *new Relation(content.token,CALL);
        content_call.addToNoTerminal(llamadaFuncion);
        this->table.insertARelation(content_call);
        
        Relation content_output = *new Relation(content.token,ESCRIBIR);
        content_output.addToNoTerminal(llamadaFuncion);
        this->table.insertARelation(content_output);
        
        Relation content_break = *new Relation(content.token,BREAK);
        content_break.addToNoTerminal(rupturaBucle);
        this->table.insertARelation(content_break);
        
        Relation asigna_real = *new Relation(content.token,ASIGNACION);
        asigna_real.addToNoTerminal(*new Symbol(ASIGNACION));
        asigna_real.addToNoTerminal(creacionReal);
        this->table.insertARelation(asigna_real);
        
        
        Relation declara_real = *new Relation(content.token,PUNTOYCOMA);
        this->table.insertARelation(declara_real);
        
        
        Relation creacion_real = *new Relation(creacionReal.token,VALORREAL);
        creacion_real.addToNoTerminal(*new Symbol(VALORREAL));
        creacion_real.addToNoTerminal(auxExpresion);
        this->table.insertARelation(creacion_real);
        
        Relation creacion_real2 = *new Relation(creacionReal.token,VARIABLE);
        creacion_real2.addToNoTerminal(expresion);
        this->table.insertARelation(creacion_real2);
        
        
        Relation asigna_vector = *new Relation(asignaVector.token,ASIGNACION);
        asigna_vector.addToNoTerminal(*new Symbol(ASIGNACION));
        asigna_vector.addToNoTerminal(creacionVector);
        this->table.insertARelation(asigna_vector);
        
        
        Relation declara_vector = *new Relation(asignaVector.token,PUNTOYCOMA);
        this->table.insertARelation(declara_vector);
        
        Relation creacion_vector = *new Relation(creacionVector.token,ABRECORCHETES);
        creacion_vector.addToNoTerminal(*new Symbol(VALORREAL));
        creacion_vector.addToNoTerminal(vectorNT);
        this->table.insertARelation(creacion_vector);
        
        Relation creacion_vector2 = *new Relation(creacionVector.token,RESERVAESPACIOVECTOR);
        creacion_vector2.addToNoTerminal(*new Symbol(RESERVAESPACIOVECTOR));
        creacion_vector2.addToNoTerminal(*new Symbol(ABRECORCHETES));
        creacion_vector2.addToNoTerminal(*new Symbol(VALORREAL));
        creacion_vector2.addToNoTerminal(*new Symbol(CIERRACORCHETES));
        this->table.insertARelation(creacion_vector);
        
        Relation vectorNt = *new Relation(vectorNT.token,ABRECORCHETES);
        vectorNt.addToNoTerminal(*new Symbol(ABRECORCHETES));
        vectorNt.addToNoTerminal(elementos);
        vectorNt.addToNoTerminal(*new Symbol(CIERRACORCHETES));
        this->table.insertARelation(vectorNt);
        
        Relation elementos_r = *new Relation(elementos.token,VALORREAL);
        elementos_r.addToNoTerminal(*new Symbol(VALORREAL));
        elementos_r.addToNoTerminal(completion);
        this->table.insertARelation(elementos_r);
        
        Relation completion_full = *new Relation(completion.token,COMA);
        completion_full.addToNoTerminal(*new Symbol(COMA));
        completion_full.addToNoTerminal(elementos);
        this->table.insertARelation(completion_full);
        
        Relation completion_lambda = *new Relation(completion.token,PUNTOYCOMA);
        this->table.insertARelation(completion_lambda);
        
        
        Relation modificaVariable_r = *new Relation(modificaVariable.token,VARIABLE);
        modificaVariable_r.addToNoTerminal(asignacion);
        modificaVariable_r.addToNoTerminal(modificacion);
        this->table.insertARelation(modificaVariable_r);
        
        Relation asignacion_rel = *new Relation(modificacion.token,VARIABLE);
        asignacion_rel.addToNoTerminal(*new Symbol(VARIABLE));
        asignacion_rel.addToNoTerminal(desplazamiento);
        asignacion_rel.addToNoTerminal(*new Symbol(ASIGNACION));
        this->table.insertARelation(asignacion_rel);
        
        Relation modificacion_r = *new Relation(modificacion.token,VALORREAL);
        modificacion_r.addToNoTerminal(*new Symbol(VALORREAL));
        modificacion_r.addToNoTerminal(auxExpresion);
        this->table.insertARelation(modificacion_r);
        
        Relation modificacion_r2 = *new Relation(modificacion.token,VARIABLE);
        modificacion_r2.addToNoTerminal(variable);
        modificacion_r2.addToNoTerminal(auxExpresion);
        this->table.insertARelation(modificacion_r2);
        
        Relation modificacion_r3 = *new Relation(modificacion.token,LEER);
        modificacion_r.addToNoTerminal(*new Symbol(LEER));
        this->table.insertARelation(modificacion_r3);
        
        Relation modificacion_r4 = *new Relation(modificacion.token,CALL);
        modificacion_r.addToNoTerminal(llamadaFuncion);
        this->table.insertARelation(modificacion_r4);
        
        Relation variable_r = *new Relation(variable.token,VARIABLE);
        variable_r.addToNoTerminal(*new Symbol(VARIABLE));
        variable_r.addToNoTerminal(desplazamiento);
        this->table.insertARelation(variable_r);
        
        Relation desplazamiento_r = *new Relation(desplazamiento.token,ABRECORCHETES);
        desplazamiento_r.addToNoTerminal(posicionVector);
        this->table.insertARelation(desplazamiento_r);
        
        Relation desplazamiento_r2 = *new Relation(desplazamiento.token,PUNTOYCOMA);
        
        this->table.insertARelation(desplazamiento_r2);
        
        
        Relation posicion_vector = *new Relation(posicionVector.token,ABRECORCHETES);
        posicion_vector.addToNoTerminal(*new Symbol(ABRECORCHETES));
        posicion_vector.addToNoTerminal(termino);
        posicion_vector.addToNoTerminal(*new Symbol(CIERRACORCHETES));
        this->table.insertARelation(posicion_vector);
        
        Relation expresion_r = *new Relation(expresion.token,VALORREAL);
        expresion_r.addToNoTerminal(termino);
        expresion_r.addToNoTerminal(operacion);
        expresion_r.addToNoTerminal(termino);
        this->table.insertARelation(expresion_r);
        
        Relation expresion_r2 = *new Relation(expresion.token,VARIABLE);
        expresion_r2.addToNoTerminal(termino);
        expresion_r2.addToNoTerminal(operacion);
        expresion_r2.addToNoTerminal(termino);
        this->table.insertARelation(expresion_r2);
        
        
        Relation termino_r = *new Relation(termino.token,VALORREAL);
        termino_r.addToNoTerminal(*new Symbol(VALORREAL));
        this->table.insertARelation(termino_r);
        
        
        Relation termino_r2 = *new Relation(termino.token,VARIABLE);
        termino_r2.addToNoTerminal(*new Symbol(VARIABLE));
        this->table.insertARelation(termino_r2);
        
        Relation operacion_r = *new Relation(operacion.token,SUMA);
        operacion_r.addToNoTerminal(*new Symbol(SUMA));
        this->table.insertARelation(operacion_r);
        
        
        Relation operacion_r2 = *new Relation(operacion.token,RESTA);
        operacion_r2.addToNoTerminal(*new Symbol(RESTA));
        this->table.insertARelation(operacion_r2);
        
        
        Relation operacion_r3 = *new Relation(operacion.token,DIVISION);
        operacion_r3.addToNoTerminal(*new Symbol(DIVISION));
        this->table.insertARelation(operacion_r3);

        
        Relation operacion_r4 = *new Relation(operacion.token,MULTIPLICACION);
        operacion_r4.addToNoTerminal(*new Symbol(MULTIPLICACION));
        this->table.insertARelation(operacion_r4);

        
        Relation operacion_r5 = *new Relation(operacion.token,OR);
        operacion_r5.addToNoTerminal(*new Symbol(OR));
        this->table.insertARelation(operacion_r5);
        
        
        Relation operacion_r6 = *new Relation(operacion.token,AND);
        operacion_r.addToNoTerminal(*new Symbol(AND));
        this->table.insertARelation(operacion_r6);
        
        
        Relation operacion_r7 = *new Relation(operacion.token,NOT);
        operacion_r7.addToNoTerminal(*new Symbol(NOT));
        this->table.insertARelation(operacion_r7);

        
        Relation operacion_r8 = *new Relation(operacion.token,IGUAL_QUE);
        operacion_r8.addToNoTerminal(*new Symbol(IGUAL_QUE));
        this->table.insertARelation(operacion_r8);

        
        Relation operacion_r9 = *new Relation(operacion.token,DISTINTO_QUE);
        operacion_r9.addToNoTerminal(*new Symbol(DISTINTO_QUE));
        this->table.insertARelation(operacion_r);
        
        
        Relation operacion_r10 = *new Relation(operacion.token,MAYOR_QUE);
        operacion_r10.addToNoTerminal(*new Symbol(MAYOR_QUE));
        this->table.insertARelation(operacion_r10);
        
        Relation operacion_r11 = *new Relation(operacion.token,MAYOR_O_IGUAL_QUE);
        operacion_r11.addToNoTerminal(*new Symbol(MAYOR_O_IGUAL_QUE));
        this->table.insertARelation(operacion_r11);

        
        Relation operacion_r12 = *new Relation(operacion.token,MENOR_QUE);
        operacion_r12.addToNoTerminal(*new Symbol(MENOR_QUE));
        this->table.insertARelation(operacion_r12);

        
        Relation operacion_r13 = *new Relation(operacion.token,MENOR_O_IGUAL_QUE);
        operacion_r13.addToNoTerminal(*new Symbol(MENOR_O_IGUAL_QUE));
        this->table.insertARelation(operacion_r13);

        Relation bloque_Si = *new Relation(bloqueSi.token,SI);
        bloque_Si.addToNoTerminal(*new Symbol(SI));
        bloque_Si.addToNoTerminal(expresion);
        bloque_Si.addToNoTerminal(*new Symbol(ABRELLAVES));
        bloque_Si.addToNoTerminal(bloque);
        bloque_Si.addToNoTerminal(*new Symbol(CIERRALLAVES));
        this->table.insertARelation(bloque_Si);
        
        
        Relation bloque_Mientras = *new Relation(bloqueMientras.token,MIENTRAS);
        bloque_Mientras.addToNoTerminal(*new Symbol(MIENTRAS));
        bloque_Mientras.addToNoTerminal(expresion);
        bloque_Mientras.addToNoTerminal(*new Symbol(ABRELLAVES));
        bloque_Mientras.addToNoTerminal(bloque);
        bloque_Mientras.addToNoTerminal(*new Symbol(CIERRALLAVES));
        this->table.insertARelation(bloque_Mientras);
        
        Relation llamada_Funcion = *new Relation(llamadaFuncion.token, CALL);
        llamada_Funcion.addToNoTerminal(*new Symbol(CALL));
        llamada_Funcion.addToNoTerminal(*new Symbol(VARIABLE));
        llamada_Funcion.addToNoTerminal(defineParametros);
        this->table.insertARelation(llamada_Funcion);
        
        
        this->table.insertARelation(*new Relation (parametros.token,CIERRAPARENTESIS));
        
        Relation parametros_r = *new Relation (parametros.token,REAL);
        parametros_r.addToNoTerminal(*new Symbol(REAL));
        this->table.insertARelation(parametros_r);
        
        Relation parametros_r2 = *new Relation (parametros.token,VECTOR);
        parametros_r2.addToNoTerminal(*new Symbol(VECTOR));
        this->table.insertARelation(parametros_r2);
        
        Relation parametros_r3 = *new Relation (parametros.token,COMA);
        parametros_r3.addToNoTerminal(*new Symbol(COMA));
        parametros_r3.addToNoTerminal(parametros);
        this->table.insertARelation(parametros_r3);
        
        Relation define_parametros = *new Relation(defineParametros.token,ABREPARENTESIS);
        define_parametros.addToNoTerminal(*new Symbol(ABREPARENTESIS));
        define_parametros.addToNoTerminal(parametros);
        define_parametros.addToNoTerminal(*new Symbol(CIERRAPARENTESIS));
        this->table.insertARelation(define_parametros);
        
        Relation imprimible_r = *new Relation(imprimible.token, VARIABLE);
        imprimible_r.addToNoTerminal(*new Symbol(VARIABLE));
        this->table.insertARelation(imprimible_r);
        
        Relation imprimible_r2 = *new Relation(imprimible.token, VALORREAL);
        imprimible_r2.addToNoTerminal(*new Symbol(VALORREAL));
        this->table.insertARelation(imprimible_r2);
        
        Relation rupturaBucle_r = *new Relation(rupturaBucle.token,BREAK);
        rupturaBucle_r.addToNoTerminal(*new Symbol(BREAK));
        this->table.insertARelation(rupturaBucle_r);
        
        Relation devuelve_r = *new Relation(devuelve.token, DEVUELVE);
        devuelve_r.addToNoTerminal(*new Symbol(DEVUELVE));
        devuelve_r.addToNoTerminal(devolucion);
        this->table.insertARelation(devuelve_r);
        
        Relation devolucion_r = *new Relation(devolucion.token,VALORREAL);
        devolucion_r.addToNoTerminal(*new Symbol(VALORREAL));
        this->table.insertARelation(devolucion_r);
        
        Relation devolucion_r2 = *new Relation(devolucion.token,VARIABLE);
        devolucion_r2.addToNoTerminal(*new Symbol(VARIABLE));
        this->table.insertARelation(devolucion_r2);

        
    }
    
    
    bool isTerminal(Symbol d){
        return d.token > 255;
    }
    
public:
    
    TopDownSintacticAnalizer(std::string path){
        this->lang = *new TokenChooser(path);
        this->table = *new Table();
        fullfillAnalysisTable();
        
    }
    
    
    
    
    void analice(){
       
        pila.push(ENDOFSTACK);
        pila.push(root);
        Symbol token = lang.nextToken();
        Symbol topStack = pila.top();
        
        while (topStack.token != ENDOFSTACK.token) {
            
            
            if(isTerminal(topStack)|| topStack.token == ENDOFSTACK.token){
                
                if(topStack.token == token.token){
                    pila.pop();
                    token = lang.nextToken();
                }else{
                    printf("ERROR");
                }
            }else{
                if(table.ExistsARule(topStack.token,token.token)){
                    vector<Symbol> rule = table.getRule(topStack.token,token.token);
                    pila.pop();
                    for(int i = rule.size()-1; i >= 0; i--){
                        pila.push(rule[i]);
                    }
                }else{
                    printf("ERROR");
                }
            }
            
            topStack = pila.top();
            //token = lang.nextToken();
        }
        
    }
};