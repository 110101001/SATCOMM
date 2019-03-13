/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 18:26
#
# Last modified: 2019-03-13 18:46
#
# Filename:	graphMatrix.h
#
# Description: 
#
=============================================================================*/
#ifndef _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_

#include"../iridiumDefines.h"

typedef struct{
    float avgDelay;
    float flowLoss;
}result;

typedef struct{
    int controler;
    float controlerDelay;
    float controlerRel;
    float flowSum;
    float flowLoss;
}nodeInfo;

class graphMatrix{
    private:
        float _edgeDelay[NODE_COUNT][NODE_COUNT];
        float _edgeRel[NODE_COUNT][NODE_COUNT];
        float _nodeTraffic[NODE_COUNT];

        int _gate[GATE_COUNT];
        nodeInfo ninfo[NODE_COUNT];
    public:
        graphMatrix():
            _edgeDelay(),_edgeRel(),_nodeTraffic(),_gate()
            {}
        graphMatrix(float edgeDelay[][NODE_COUNT],float edgeRel[][NODE_COUNT],float _nodeTraffic[],int gate[]);
        void importControler(int controlers[],int controlerCount);
        result caculate();
};

#endif
