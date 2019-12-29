#include "..\\code\\dataStruct.h"
#include "..\\code\common.h"

/**
 * RelayMain.c
 * 所有保护装置的入口函数
 */


// 定义全局变量
Device line1P;

// 声明各类保护函数
extern double line(Device*); // 线路保护


// 注意采用GFORTRAN,C函数名需要多一个下划线
void line_1_p_(double* time, double* input, double* brk, double* tripSignal) {
    linkSimulation(&line1P, "线路1-P", *time, input, brk, tripSignal);
}












