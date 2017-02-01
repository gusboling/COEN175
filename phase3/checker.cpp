#include <iostream>
#include "checker.h"

static void printOpen(){
    cout << "Open scope" << endl;
}

static void printClose(){
    cout << "Close scope" << endl;
}

static void printArrayDec(string name, unsigned ind, int spec){
    cout << "Declare array " << name << " with ind " << ind << " and spec " << spec << endl;
}

static void printScalarDec(string name, unsigned ind, int spec){
    cout << "Declare scalar " << name << " with ind " << ind << " and spec " << spec << endl;
}

static void printVarDec(string name, unsigned ind, int spec){
    cout << "Declare variable " << name << " with ind " << ind << " and spec " << spec << endl;
}

static void printFunDec(string name, unsigned ind, int spec){
    cout << "Declare function " << name << " with ind " << ind << "and spec " << spec << endl;
}

static void printSymUse(){
    cout << "Used symbol" << endl; //TODO: get this to say what symbol was used.
}
