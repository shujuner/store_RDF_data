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
    //检查数据存储是否正确-------------------------------------------------------------start
    /*cout<<"subSet size="<<subSet.size()<<endl;
    cout<<"第一项的主体是"<<subSet[0].sub<<endl;
    for(auto iter : subSet[0].p)
    {
        cout<<"第一项的谓语为:"<<iter.pre<<endl;
        cout<<"obj"<<endl;
        for(auto i : iter.obj)
        {
            cout<<i<<" ";
        }
    }*/
    //检查数据存储是否正确-------------------------------------------------------------end
    input.close();
    double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
	//-----------------------------------------------------------------s p ?o查询---------------------------------------------------------------------------------//
//    int pp=subSet[sPosition[subDict["<http://db.uwaterloo.ca/~galuc/wsdbm/User44234>"]]].pPosition[preDict["<http://db.uwaterloo.ca/~galuc/wsdbm/friendOf>"]];
//    int objIndex=subSet[sPosition[subDict["_:c"]]].p[pp].obj[0];
    //-----------------------------------------------------------------s ?p o查询---------------------------------------------------------------------------------//
    string cinS,cinP,cinO;
    int choose;
    cout<<"请输入你要执行的查询类型0(s p ?o),1(s ?p o),2(quit):"<<endl;
    while(cin>>choose)
    {
        if(choose==0)
        {
            cout<<"请输入主语和谓语，以空格分割: "<<endl;
            cin>>cinS>>cinP;
            QueryPerformanceFrequency(&f);
            dqFreq=(double)f.QuadPart;
            QueryPerformanceCounter(&time_start);
            int pp=subSet[sPosition[subDict[cinS]]].pPosition[preDict[cinP]];
            int objIndex=subSet[sPosition[subDict[cinS]]].p[pp].obj[0];
            cout<<"object= "<<revSubDict[objIndex]<<endl;
            QueryPerformanceCounter(&time_over);
            run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
            printf("\nrun_time：%fus\n",run_time);
        }
        else if(choose==1)
        {
            cout<<"请输入主语和宾语，以空格分割: "<<endl;
            cin>>cinS>>cinO;
            QueryPerformanceFrequency(&f);
            dqFreq=(double)f.QuadPart;
            QueryPerformanceCounter(&time_start);
            subject selectP=subSet[sPosition[subDict[cinS]]];
            vector<predicate> preInSelectData=selectP.p;
            for(auto iter: preInSelectData)
            {
                cout<<"iter.predicate="<<iter.pre<<endl;
                if(iter.objExist[subDict[cinO]]==1)
                {
                    cout<<revPreDict[iter.pre]<<" "<<endl;
                }
            }
            QueryPerformanceCounter(&time_over);
            run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
            printf("\nrun_time：%fus\n",run_time);
        }
        else{
            break;
        }
        cout<<"请输入你要执行的查询类型0(s p ?o),1(s ?p o),2(quit):"<<endl;
    }
    return 0;
}
