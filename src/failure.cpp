#include<iostream>
#include"graphMatrix.h"
#include"iridiumDefines.h"

using namespace std;

float graphMatrix::testFailure(){
    int linkCount=0;
    float totalRecover=0;
    for(int i=0;i<NODE_COUNT;i++){
        for(int j=0;j<i;j++){
            if(_edgeDelay[i][j]!=0){
                linkCount++;
                float minResponseA=1;
                float minResponseB=1;
                for(int k=0;k<NODE_COUNT;k++){
                    if(_edgeDelay[i][k]!=0&&k!=j){
                        float delay=_edgeDelay[i][k]+ninfo[k].controlerDelay/2;
                        if(minResponseA>delay){
                            minResponseA=delay;
                        }
                    }
                    if(_edgeDelay[j][k]!=0&&k!=i){
                        float delay=_edgeDelay[j][k]+ninfo[k].controlerDelay/2;
                        if(minResponseB>delay){
                            minResponseB=delay;
                        }
                    }
                }
                if(ninfo[i].controler==ninfo[j].controler){
                    float maxRecover=0;
                    for(int k=0;k<NODE_COUNT;k++){
                        if(ninfo[k].controler==ninfo[i].controler){
                            if(maxRecover<ninfo[k].controlerDelay/2){
                                maxRecover=ninfo[k].controlerDelay/2;            
                            }
                        }
                    }
                    if(minResponseA<minResponseB){
                        totalRecover+=maxRecover+minResponseA;
                    }
                    else{
                        totalRecover+=maxRecover+minResponseB;
                    }
                }
                else{
                    float maxRecoverA=0;
                    float maxRecoverB=0;
                    for(int k=0;k<NODE_COUNT;k++){
                        if(ninfo[k].controler==ninfo[i].controler){
                            if(maxRecoverA<ninfo[k].controlerDelay/2){
                                maxRecoverA=ninfo[k].controlerDelay/2;            
                            }
                        }
                        if(ninfo[k].controler==ninfo[j].controler){
                            if(maxRecoverB<ninfo[k].controlerDelay/2){
                                maxRecoverB=ninfo[k].controlerDelay/2;            
                            }
                        }
                    }
                    if(maxRecoverA+minResponseA<maxRecoverB+minResponseB){
                        totalRecover+=maxRecoverB+minResponseB;
                    }
                    else{
                        totalRecover+=maxRecoverA+minResponseA;
                    }
                }
            }
        }
    }
    return totalRecover/linkCount;
}
