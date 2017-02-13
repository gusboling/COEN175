//Libraries
#include <string>
#include <iostream>

//Program Headers
#include "type.h"
#include "symbol.h"
#include "lexer.h"

#ifndef ERROR_H
#define ERROR_H

void conf_types(string name);
void redef(string name);
void redec(string name);
void undec(string name);
void void_type(string name);

#endif /* ERROR_H */
