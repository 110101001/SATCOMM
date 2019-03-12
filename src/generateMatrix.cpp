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

class graphMatrix *getMatrix(const char* snapName){
    int startNode;
    int endNode;
    float delay;
    float delayMatrix[NODE_COUNT][NODE_COUNT];
    float relMatrix[NODE_COUNT][NODE_COUNT];

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

    ifstream fin(snapName);
    while(!fin.eof()){
        fin>>startNode>>endNode>>delay;
        delayMatrix[satellite_map(startNode)][satellite_map(endNode)]=delay;
    } 

    float planeDelay=delayMatrix[GATE_COUNT][GATE_COUNT+1];

    for(int i=0;i<PLANE;i++){//delay between sat in the same plane
            delayMatrix[GATE_COUNT+i*SATELLITE_PER_PLANE][GATE_COUNT+i*SATELLITE_PER_PLANE+SATELLITE_PER_PLANE-1]=planeDelay;
        for(int j=0;j<SATELLITE_PER_PLANE-1;j++){
            delayMatrix[GATE_COUNT+i*SATELLITE_PER_PLANE+j][GATE_COUNT+i*SATELLITE_PER_PLANE+j+1]=planeDelay;
        }
    }

    for(int j=0;j<SATELLITE_PER_PLANE;j++){//interplane delay
        for(int i=0;i<PLANE-1;i++){
            delayMatrix[GATE_COUNT+i*SATELLITE_PER_PLANE+j][GATE_COUNT+(i+1)*SATELLITE_PER_PLANE+j]=delayMatrix[GATE_COUNT+j][GATE_COUNT+SATELLITE_PER_PLANE+j];
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
           cout<<relMatrix[i][j]<<" "; 
        }
        cout<<endl;
    }
*/
    return new class graphMatrix();
}
