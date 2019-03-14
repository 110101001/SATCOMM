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

int main(){
    class graphMatrix *graph= getMatrix("0400.snp");
    int ctrls[]={8,21,34,47,60};
    graph->importControler(ctrls,5);
    graph->caculate();
    return 0;
}
