#ifndef TRIPLE_H_INCLUDED
#define TRIPLE_H_INCLUDED

#include "common.h"
using namespace std;

class predicate
{
public:
    int pre;
    vector<int> obj;
    map<int,int> objExist;
    bool operator ==(const int&);

};
bool predicate::operator ==(const int &x){
    return(this->pre==x);
}
class subject
{
public:
    int sub;
    vector<predicate> p;
    map<int,int> pPosition;
    bool operator== (const int&);
};
bool subject::operator ==(const int &x){
    return(this->sub==x);
}

#endif // TRIPLE_H_INCLUDED
