/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 19:57
#
# Last modified: 2019-03-13 20:07
#
# Filename:	graph.cpp
#
# Description: 
#
=============================================================================*/
#include"graphMatrix.h"
#include<iostream>

using namespace std;

graphMatrix::graphMatrix(float edgeDelay[][NODE_COUNT],float edgeRel[][NODE_COUNT],float nodeTraffic[],int gate[]){
    for(int i=0;i<NODE_COUNT;i++){
        for(int j=0;j<NODE_COUNT;j++){
            _edgeDelay[i][j]=edgeDelay[i][j];
            _edgeRel[i][j]=edgeRel[i][j];
        }
    }   
    for(int i=0;i<NODE_COUNT;i++){
        _nodeTraffic[i]=nodeTraffic[i];
    }
    for(int i=0;i<GATE_COUNT;i++){
        _gate[i]=gate[i];
    }
    for(int i=0;i<NODE_COUNT;i++){
        ninfo[i].flowSum=nodeTraffic[i];
        ninfo[i].flowLoss=0;
    }
     
}

void graphMatrix::importControler(int controlers[],int controlerCount){
    for(int i=GATE_COUNT;i<NODE_COUNT;i++){
        bool selfControler=false;
        for(int j=0;j<controlerCount;j++){
            if(i==controlers[j]){
                selfControler=true;
            }
        }
        if(selfControler){
            ninfo[i].controler=i;
            ninfo[i].controlerDelay=0;
            ninfo[i].controlerRel=1;
            continue;
        }
        bool S[NODE_COUNT];
        float dis[NODE_COUNT];
        int prev[NODE_COUNT];
        for(int j=0;j<NODE_COUNT;j++){
            S[j]=false;
        } 
        S[i]=true;
        dis[i]=0;
        while(1){
            int nearest=0;
            int prevNode=0;
            bool ctrlFlag=false;
            float minDistance=10;//Should be large enough
            for(int j=0;j<NODE_COUNT;j++){
                if(S[j]){
                    for(int k=0;k<NODE_COUNT;k++){
                        if(_edgeDelay[j][k]==0||S[k]) continue;
                        float tmpDis;
                        tmpDis=dis[j]+_edgeDelay[j][k];
                        if(tmpDis<minDistance){
                            nearest=k;
                            minDistance=tmpDis;
                            prevNode=j;
                        }
                    }
                }
            }
            for(int j=0;j<controlerCount;j++){
                if(nearest==controlers[j]){
                    ninfo[i].controler=nearest;
                    ninfo[i].controlerDelay=minDistance;
                    ctrlFlag=true;
                    break;
                }
            }
            prev[nearest]=prevNode;
            if(ctrlFlag==true){
                break;
            }
            S[nearest]=true;
            dis[nearest]=minDistance;
        }
        float rel=1;
        int present=ninfo[i].controler;
        while(present!=i){
            rel*=_edgeRel[present][prev[present]];
            present=prev[present];
        }
        ninfo[i].controlerRel=rel;
    }
    for(int i=0;i<NODE_COUNT;i++){
        cout<<"index:"<<i<<" ctrler:"<<ninfo[i].controler<<" delay:"<<ninfo[i].controlerDelay<<" rel:"<<ninfo[i].controlerRel<<endl;
    }
}