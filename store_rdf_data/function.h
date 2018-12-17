#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED
#include "common.h"
//����map Rdf element ��index��ӳ��
int getSubject(string sub)
{
    if(subDict.find(sub)==subDict.end())
    {
        subDict[sub]=subCount++;
    }
    return subDict[sub];
}
int getPredicate(string pre)
{
    if(preDict.find(pre)==preDict.end())
    {
        preDict[pre]=preCount++;
    }
    return preDict[pre];
}
//����map���
void split_rdfData_space(string rdfData,string& sub,string& predicate,string& object)
{
    string temp="";
    int flag=1;
    for(unsigned int i=0;i<rdfData.length();i++)
    {
        if(rdfData[i]!=' ')
        {
            temp+=rdfData[i];
        }
        else{
            if(flag==1)
            {
                sub=temp;
                temp="";
                flag++;
            }
            else if(flag==2)
            {
                predicate=temp;
                temp="";
                flag++;
            }
        }
    }
    object=temp;
}

#endif // FUNCTION_H_INCLUDED
