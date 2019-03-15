/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 18:26
#
# Last modified: 2019-03-12 18:26
#
# Filename: main.cpp
#
# Description: 
#
=============================================================================*/
#include<iostream>
#include"include/generateMatrix.h"
#include"graphMatrix.h"
#include"simulateAnneal.h"

using namespace std;

class graphMatrix *graph;

int main(int argc,char **argv){
    if(argc<5) return 1;

    float initTemp;
    float endTemp;
    float k;
    int ctrlerCount;
    float *delays;
    delays=(float *)malloc(sizeof(float)*(argc-5));
    sscanf(argv[1],"%f",&initTemp);
    sscanf(argv[2],"%f",&endTemp);
    sscanf(argv[3],"%f",&k);
    sscanf(argv[4],"%d",&ctrlerCount);
    for(int s=5;s<argc;s++){
        cout<<"Caculating "<<argv[s]<<":";
        graph = getMatrix(argv[s]);
        int *res=anneal(initTemp,endTemp,k,ctrlerCount);

        cout<<"Best placement: ";
        for(int i=0;i<ctrlerCount;i++){
            if((res[i]-GATE_COUNT)%SATELLITE_PER_PLANE<9){
                cout<<"LEO"<<(res[i]-GATE_COUNT)/SATELLITE_PER_PLANE+1<<"0"<<(res[i]-GATE_COUNT)%SATELLITE_PER_PLANE+1<<" ";
            }
            else{
                cout<<"LEO"<<(res[i]-GATE_COUNT)/SATELLITE_PER_PLANE+1<<(res[i]-GATE_COUNT)%SATELLITE_PER_PLANE+1<<" ";
            }
        }
        cout<<endl;
        graph->importControler(res,ctrlerCount);
        result score=graph->caculate();
        cout<<"Average flow setup time: "<<score.avgDelay<<endl;

        delays[s-5]=score.avgDelay;
    }
    for(int i=0;i<argc-5;i++){
        cout<<delays[i]<<" ";
    }
    cout<<endl;
    return 0;

}
