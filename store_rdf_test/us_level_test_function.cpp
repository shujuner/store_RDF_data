#include<iostream>
#include <windows.h>
using namespace std;
int main()
{
    double run_time;
	_LARGE_INTEGER time_start;
	_LARGE_INTEGER time_over;
	double dqFreq;
	LARGE_INTEGER f;
	QueryPerformanceFrequency(&f);
    dqFreq=(double)f.QuadPart;
    QueryPerformanceCounter(&time_start);

    //function start

    cout<<"1"<<endl;
    cout<<"1"<<endl;

    //function end

    QueryPerformanceCounter(&time_over);
    run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
    printf("\nrun_time %fus\n",run_time);
}
