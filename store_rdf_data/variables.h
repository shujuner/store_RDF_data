#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include "common.h"
#include "triple.h"
int subCount=1,preCount=1;
map<string,int> subDict,preDict,objDict;
map<int,string> revSubDict,revPreDict,revObjDict;

vector<subject> subSet; //�洢subject����ṹ��

map<int,int> sPosition;

map<int,int> subExist;
#endif // VARIABLES_H_INCLUDED
