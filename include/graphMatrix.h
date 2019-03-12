/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-12 18:26
#
# Last modified: 2019-03-12 18:26
#
# Filename: graphMatrix.h
#
# Description: 
#
=============================================================================*/
#ifndef _GRAPHMATRIX_H_
#define _GRAPHMATRIX_H_

#include"../iridiumDefines.h"

class graphMatrix{
    private:
        float _edgeDelay[NODE_COUNT][NODE_COUNT];
        float _edgeRel[NODE_COUNT][NODE_COUNT];
        float _nodeTraffic[SATELLITE_COUNT];

        int _gate[GATE_COUNT];
    public:
        graphMatrix():
            _edgeDelay(),_edgeRel(),_nodeTraffic(),_gate()
            {}
};

#endif
