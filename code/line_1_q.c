#include "..\\code\\dataStruct.h"
#include "..\\code\common.h"

// 定义全局变量
Device line1Q;


// 声明各类保护函数
extern double line(Device*); // 线路保护


void line_1_q_(double* vm, double* im, double* vn, double* in, double* time, double* brk, double* p1, double* p2, double* p3) {
    // 设置整定值
    initSetValue(&line1Q, "线路1-Q"); 
 
    // 仿真程序跑10次, 进行一次采样和保护计算
    if (upTo10(&line1Q) == 1) {
        sample(&line1Q, vm[0], vm[1], vm[2], im[0], im[1], im[2], vn[0], vn[1], vn[2], in[0], in[1], in[2], brk[0], brk[1], brk[2], *time);
         line(&line1Q);
    }
  
    // 结果输出
    *p1 = line1Q.tripFlag[0]; 
    *p2 = line1Q.tripFlag[1]; 
    *p3 = line1Q.tripFlag[2]; 

}
