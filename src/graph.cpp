/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 19:57
#
# Last modified: 2019-03-14 12:43
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
        ninfo[i].flowLoss=0;
    }
     
}
//First task is to assign a controler to every node(minimum delay), and caculate delay and reliability between controler and node accordingly. Then controlers[] is no longer needed.
void graphMatrix::importControler(int controlers[],int controlerCount){
    for(int i=0;i<NODE_COUNT;i++){
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
                    ninfo[i].controlerDelay=minDistance*2;
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
        ninfo[i].controlerRel=rel*rel;
    }
    /*for(int i=0;i<NODE_COUNT;i++){
        cout<<"index:"<<i<<" ctrler:"<<ninfo[i].controler<<" delay:"<<ninfo[i].controlerDelay<<" rel:"<<ninfo[i].controlerRel<<endl;
    }*/
}

//Second task is to caculate results
result graphMatrix::caculate(){
    result res={0,0};
    for(int i=0;i<GATE_COUNT;i++){
        bool S[NODE_COUNT];
        float dis[NODE_COUNT];
        int prev[NODE_COUNT];
        int order[NODE_COUNT];
        int index=1;
        for(int j=0;j<NODE_COUNT;j++){
            S[j]=false;
        } 

        S[i]=true;
        dis[i]=0;
        order[0]=i;

        for(int j=0;j<NODE_COUNT;j++){
            ninfo[j].flowSum=_nodeTraffic[j]/GATE_COUNT;
            ninfo[j].flowLoss=0;
        }

        while(index<NODE_COUNT){
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
            prev[nearest]=prevNode;
            S[nearest]=true;
            dis[nearest]=minDistance; 
            order[index++]=nearest;
        }

        for(int j=0;j<NODE_COUNT;j++){
            float flowPass=ninfo[j].flowSum*ninfo[j].controlerRel;
            res.avgDelay+=flowPass*ninfo[j].controlerDelay;
            res.flowLoss+=ninfo[j].flowSum-flowPass;
            ninfo[j].flowSum=flowPass;
        }

        for(int j=NODE_COUNT-1;j>0;j--){
            int k=order[j];
            float flowPass=ninfo[k].flowSum*_edgeRel[k][prev[k]];
            //cout<<k<<" to "<<prev[k]<<":"<<flowPass<<endl;
            if(ninfo[k].controler!=ninfo[prev[k]].controler){
                flowPass*=ninfo[prev[k]].controlerRel;
                res.avgDelay+=flowPass*ninfo[prev[k]].controlerDelay;
                //cout<<"switch ctrler, add "<<flowPass<<"*"<<ninfo[prev[k]].controlerDelay*2<<endl;
            }
            res.avgDelay+=flowPass*_edgeDelay[k][prev[k]]; 
            ninfo[prev[k]].flowSum+=ninfo[k].flowSum*_edgeRel[k][prev[k]];
            ninfo[k].flowLoss=ninfo[k].flowSum-flowPass;
            res.flowLoss+=ninfo[k].flowLoss;
        }
    }
    res.avgDelay/=1-res.flowLoss;
    //cout<<res.avgDelay<<" "<<res.flowLoss<<endl;
    return res;
}
