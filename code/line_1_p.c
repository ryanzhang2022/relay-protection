#include "..\\code\\dataStruct.h"
#include "..\\code\common.h"

// 定义全局变量
Device line1P;


// 声明各类保护函数
extern double line(Device*); // 线路保护


void line_1_p(double* vma, double* vmb, double* vmc, double* ima, double* imb, double* imc, double* vna, double* vnb, double* vnc, double* ina, double* inb, double* inc, double* ka, double* kb, double* kc, double* time, double* p1, double* p2, double* p3) {
    // 设置整定值
    initSetValue(&line1P, "线路1-P"); 
 
    // 仿真程序跑10次, 进行一次采样和保护计算
    if (upTo10(&line1P) == 1) {
        sample(&line1P, *vma, *vmb, *vmc, *ima, *imb, *imc, *vna, *vnb, *vnc, *ina, *inb, *inc, *ka, *kb, *kc, *time);
         line(&line1P);
    }
  
    // 结果输出
    *p1 = line1P.tripFlag[0]; 
    *p2 = line1P.tripFlag[1]; 
    *p3 = line1P.tripFlag[2]; 

}












