

#ifndef EXECUTOR_H
#define EXECUTOR_H


#include "parser.h"

int executeCreateTable(CreateTableNode *node);
int executeInsert(InsertNode *node);
int executeSelect(SelectNode *node);
#endif
