/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-14 12:52
#
# Last modified: 2019-03-14 12:52
#
# Filename: simulateAnneal.cpp
#
# Description: 
#
=============================================================================*/
#include"simulateAnneal.h"
#include"graphMatrix.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<malloc.h>

#define TERMINAL_WIDTH 80

using namespace std;
extern class graphMatrix *graph;

void generateNewSet(int *ctrlers,int count){
    int chgPos=rand()%count;
    int chgRes;
    bool repeatFlag=true;
    while(repeatFlag==true){
        repeatFlag=false;
        chgRes=rand()%SATELLITE_COUNT+GATE_COUNT;
        for(int i=0;i<count;i++){
            if(chgRes==ctrlers[i]){
                repeatFlag=true;
                break;
            }
        }
    }
    ctrlers[chgPos]=chgRes;
    return;
}

int* anneal(float initTemp,float endTemp,float k,int setSize){
    int iterDiv=ceil(-log(initTemp/endTemp)/(log(k)*TERMINAL_WIDTH));
    result res;
    float temp=initTemp;
    float tempRes=10;//should be large enough
    float lastRes=10;
    float deltaRes=0;
    int iter=0;
    int *set=(int*)malloc(sizeof(int)*setSize);
    int *tempSet=(int*)malloc(sizeof(int)*setSize);
    for(int i=0;i<setSize;i++){
        set[i]=GATE_COUNT+i;
        tempSet[i]=set[i];
    }
    while(temp>endTemp){
        generateNewSet(tempSet,setSize);
        graph->importControler(tempSet,setSize);
        res=graph->caculate();
        tempRes=res.avgDelay;
        deltaRes=tempRes-lastRes;
        float lambda=(rand()%1000)/1000;
        if(deltaRes<0||lambda<exp(-deltaRes/temp)){
            lastRes=tempRes;
            for(int i=0;i<setSize;i++){
                set[i]=tempSet[i];
            }
        }
        else{
            for(int i=0;i<setSize;i++){
                tempSet[i]=set[i];
            }
        }
        //cout<<"temp: "<<temp<<" delay:"<<tempRes<<endl;
        temp=temp*k;
        iter++;
        if(iter%iterDiv==0){
            cout<<"#"<<flush;
        }
    }
    cout<<endl;
    free(tempSet);
    return set;
}
