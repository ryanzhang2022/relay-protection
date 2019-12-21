#include "..\\code\\dataStruct.h"
#include "..\\code\common.h"

// 定义全局变量
Device line1Q;


// 声明各类保护函数
extern double line(Device*); // 线路保护


void line_1_q_(double* vm, double* im, double* vn, double* in, double* time, double* brk, double* p1, double* p2, double* p3) {
    *p1 = vm[0];
}
