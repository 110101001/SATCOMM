/*=============================================================================
#
# Author: WuPeicong - 161180138@smail.nju.edu.cn
#
# Create Time : 2019-03-14 12:52
#
# Last modified: 2019-03-14 12:52
#
# Filename: simulateAnneal.h
#
# Description: 
#
=============================================================================*/
#ifndef _SIMULATEANNEAL_H_
#define _SIMULATEANNEAL_H_

#include"graphMatrix.h"
#include"../iridiumDefines.h"

void generateNewSet(int *ctrlers,int count);
int *anneal(float initTemp,float endTemp,float k,int setSize);

#endif
