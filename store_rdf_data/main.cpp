#include "common.h"
#include "triple.h"
#include "variables.h"
#include "function.h"
#include <windows.h>
using namespace std;
int main()
{
    string fileName="watdiv10M.txt";
    ifstream input;
    string line;
    input.open(fileName,ios::in);
    if(!input)
    {
        cout<<"打开文件:"<<fileName<<"失败!"<<endl;
    }
    cout<<"开始读取文件"<<endl;
    while(!input.eof())
    {
        int s,p,o;
        string sub,pre,object,endP;
        input>>sub>>pre>>object>>endP;
        if(sub=="")
            break;
        s=getSubject(sub);
        p=getPredicate(pre);
        o=getSubject(object);
        subDict[sub]=s;
        preDict[pre]=p;
        subDict[object]=o;
        revSubDict[s]=sub;
        revPreDict[p]=pre;
        revSubDict[o]=object;
        if(subExist[s]==1)
        {
            map<int,int>::iterator iter=subSet[sPosition[s]].pPosition.find(p);
            if(iter==subSet[sPosition[s]].pPosition.end())
            {
                predicate pTemp;
                pTemp.pre=p;
                pTemp.obj.push_back(o);
                pTemp.objExist[o]=1;
                subSet[sPosition[s]].p.push_back(pTemp);
                subSet[sPosition[s]].pPosition[p]=subSet[sPosition[s]].pPosition.size()-1;
            }
            else
            {
                subSet[sPosition[s]].p[subSet[sPosition[s]].pPosition[p]].obj.push_back(o);
                subSet[sPosition[s]].p[subSet[sPosition[s]].pPosition[p]].objExist[o]=1;
            }
        }
        else
        {
            subExist[s]=1;
            subject tempS;
            predicate tempP;
            tempP.pre=p;
            tempS.pPosition[p]=0;
            tempP.obj.push_back(o);
            tempP.objExist[o]=1;
            tempS.sub=s;
            tempS.p.push_back(tempP);
            subSet.push_back(tempS);
            sPosition[s]=subSet.size()-1;
            cout<<subSet.size()<<endl;
        }
    }
    input.close();
    vector<subject>::iterator it=subSet.begin();
    /*for(;it!=subSet.end();it++)
    {
        cout<<"主语是: "<<revSubDict[it->sub]<<" 谓语有: ";
        vector<predicate>::iterator pIt=it->p.begin();
        for(;pIt!=it->p.end();pIt++)
        {
            cout<<revPreDict[pIt->pre]<<" ";
        }
        cout<<"宾语有: ";
        pIt=it->p.begin();
        for(;pIt!=it->p.end();pIt++)
        {
            vector<int>::iterator oIt=pIt->obj.begin();
            for(;oIt!=pIt->obj.end();oIt++)
                cout<<revSubDict[*oIt]<<" ";
        }

        cout<<endl;
    }*/

    double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);

	//-----------------------------------------------------------------s p ?o查询---------------------------------------------------------------------------------//
   // int pp=subSet[sPosition[subDict["<http://db.uwaterloo.ca/~galuc/wsdbm/User44234>"]]].pPosition[preDict["<http://db.uwaterloo.ca/~galuc/wsdbm/friendOf>"]];
  //  int objIndex=subSet[sPosition[subDict["_:c"]]].p[pp].obj[0];
    //-----------------------------------------------------------------s ?p o查询---------------------------------------------------------------------------------//

    subject selectP=subSet[sPosition[subDict["<http://db.uwaterloo.ca/~galuc/wsdbm/User44234>"]]];
    vector<predicate> preInSelectData=selectP.p;
    for(auto iter: preInSelectData)
    {
        if(iter.objExist[objDict["<http://db.uwaterloo.ca/~galuc/wsdbm/User57186>"]]==1)
        {
            cout<<iter.pre<<endl;
        }
    }

    QueryPerformanceCounter(&time_over);
	run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	printf("\nrun_time：%fus\n",run_time);
    return 0;
}
