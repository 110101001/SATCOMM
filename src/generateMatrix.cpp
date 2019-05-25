/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 16:41
#
# Last modified: 2019-03-12 19:38
#
# Filename:	generateMatrix.cpp
#
# Description:generate class graphMatrix 
#
=============================================================================*/
#include<iostream>
#include<fstream>
#include<malloc.h>
#include"graphMatrix.h"
#include"iridiumDefines.h"

#define satellite_map(i) ((i/100!=0)?GATE_COUNT-SATELLITE_PER_PLANE:0)+SATELLITE_PER_PLANE*(i/100)+(i%100-1)

using namespace std;

const float rate[]={
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6.4,0,0,0,0,16,0,0,0,0,0,6.4,16,0,0,0,0,0,0,0,0,191,2,0,0,6.4,191,16,6.4,0,0,0,16,64,6.4,0,0,0,0,0,0,0,0,95,95,32,0,0,6.4,32,95,0,0,0,0,32,32,191,0,0,0,0,0,0,0,0,16,95,16,0,0,16,95,16,32,6.4,1.6,32,191,190,0,0,0,0,0,0,1.6,0,16,95,16,1.6,0,0,191,191,191,239,239,239,239,430,1.6,0,0,1.6,0,1.6,16,239,95,32,6.4,3.2,1.6,318,318,318,32,239,191,430,239,190,3.2,16,6.4,32,95,190,101.4,3.2,191,239,95,190,64,0,0,32,32,32,16,3.2,3.2,64,44.8,71.4,0,0,0
};
class graphMatrix *getMatrix(const char* snapName,const char* flowName){
    int startNode;
    int endNode;
    float delay;
    float delayMatrix[NODE_COUNT][NODE_COUNT];
    float relMatrix[NODE_COUNT][NODE_COUNT];
    float traffic[NODE_COUNT];
    int accessCount[GRID_COUNT]; 
    int gates[GATE_COUNT];
    for(int i=0;i<GATE_COUNT;i++){
        gates[i]=i;
    }

    for(int i=0;i<GATE_COUNT;i++){
        traffic[i]=0;
    }
    ifstream fin(flowName);
    int satellite,region;
    fin>>satellite>>region;
    while(!fin.eof()){
        int tempa,tempb;
        int count=0;
        tempa=satellite;
        tempb=region;
        while(!fin.eof()&&tempb==region){
            fin>>tempa>>tempb;
            count++;
        }
        accessCount[region]=count; 
        region=tempb;
    }
    fin.close(); 
    fin.open(flowName);
    while(!fin.eof()){
        fin>>satellite>>region;
        traffic[satellite_map(satellite)]=rate[region]/accessCount[region];
    }
    fin.close();
    {
        float totalFlow=0;
        for(int i=0;i<NODE_COUNT;i++){
            totalFlow+=traffic[i];
        }
        for(int i=0;i<NODE_COUNT;i++){
            traffic[i]/=totalFlow;
        }
    }

    for(int i=0;i<GATE_COUNT;i++){
        for(int j=GATE_COUNT;j<NODE_COUNT;j++){
           relMatrix[i][j]=S2G_REL; 
        }
    }
    for(int i=GATE_COUNT;i<NODE_COUNT;i++){
        for(int j=0;j<GATE_COUNT;j++){
           relMatrix[i][j]=S2G_REL; 
        }
        for(int j=GATE_COUNT;j<NODE_COUNT;j++){
           relMatrix[i][j]=S2S_REL; 
        }
    }

    for(int i=0;i<NODE_COUNT;i++){
        for(int j=0;j<NODE_COUNT;j++){
           delayMatrix[i][j]=0; 
        }
    }

    fin.open(snapName);
    while(!fin.eof()){
        fin>>startNode>>endNode>>delay;
        if(startNode-endNode==100||endNode-startNode==100||
            startNode-endNode==1||endNode-startNode==1||
            startNode<=GATE_COUNT||endNode<=GATE_COUNT){
            delayMatrix[satellite_map(startNode)][satellite_map(endNode)]=delay;
        }
    } 

    for(int i=0;i<NODE_COUNT;i++){//make a full graph matrix
        for(int j=0;j<NODE_COUNT;j++){
           delayMatrix[i][j]+=delayMatrix[j][i]; 
        }
    }

/*
    for(int i=0;i<NODE_COUNT;i++){//display matrix
        for(int j=0;j<NODE_COUNT;j++){
           cout<<delayMatrix[i][j]<<" "; 
        }
        cout<<endl;
    }
*/
    return new class graphMatrix(delayMatrix,relMatrix,traffic,gates);
}
