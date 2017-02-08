#include <iostream>
#include <string>

#include "checker.h"
#include "type.h"
#include "symbol.h"

using namespace std;

void printOpen(){
    cout << "Open scope" << endl;
}

void printClose(){
    cout << "Close scope" << endl;
}

void printArrayDec(string name, unsigned ind, int spec){
    cout << "Declare array " << name << " with ind " << ind << " and spec " << spec << endl;
}

void printScalarDec(string name, unsigned ind, int spec){
    cout << "Declare scalar " << name << " with ind " << ind << " and spec " << spec << endl;
}

void printVarDec(string name, unsigned ind, int spec){
    cout << "Declare variable " << name << " with ind " << ind << " and spec " << spec << endl;
}

void printFunDec(string name, unsigned ind, int spec){
    cout << "Declare function " << name << " with ind " << ind << "and spec " << spec << endl;
}

void printSymUse(){
    cout << "Used symbol" << endl; //TODO: get this to say what symbol was used.
}

void declareArray(string name, int spec, unsigned ind, unsigned length){
    Type t(ARRAY, spec, ind);
    t.length = length;
    Symbol sym(name, t);
    //TODO: Is there supposed to be more here?
}
