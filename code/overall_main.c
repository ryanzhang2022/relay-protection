#include "..\\code\\dataStruct.h"
#include "..\\code\common.h"
#include <math.h>

// 定义全局变量
Device lineDevice01;
Device lineDevice02;



// 声明采样函数(主函数中只保留这一个子函数!)
void sample(Device* device, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);

// 声明各类保护函数
extern double line(Device*); // 线路保护


void line_1_p(double* vma, double* vmb, double* vmc, double* ima, double* imb, double* imc, double* vna, double* vnb, double* vnc, double* ina, double* inb, double* inc, double* ka, double* kb, double* kc, double* time, double* p1, double* p2, double* p3) {
    // 设置装置名
    if (lineDevice01.temp == 0) {
        lineDevice01.temp = 1;
        lineDevice01.deviceName = "线路1-P";
    }
    
    // 初始化日志
    writeLog(&lineDevice01, "装置初始化");


    
    // 仿真程序跑10次, 进行一次采样
    lineDevice01.sampleCount++;
    if (lineDevice01.sampleCount == 10) {
        lineDevice01.sampleCount = 0;
         sample(&lineDevice01, *vma, *vmb, *vmc, *ima, *imb, *imc, *vna, *vnb, *vnc, *ina, *inb, *inc, *ka, *kb, *kc, *time);
         line(&lineDevice01);
    }
    
    
    // 以下代码块为测试代码
    {
        double x;
        double y;
        double res;
        
        x = lineDevice01.phasor[3].real;
        y = lineDevice01.phasor[3].img;
        res = sqrt(x*x + y*y);
        
        *p1 = lineDevice01.distanceTripFlag[0]; 
        *p2 = lineDevice01.brkSample[0];   
        *p3 = lineDevice01.time;

    }
}




void line_1_q(double* vma, double* vmb, double* vmc, double* ima, double* imb, double* imc, double* vna, double* vnb, double* vnc, double* ina, double* inb, double* inc, double* ka, double* kb, double* kc, double* time, double* p1, double* p2, double* p3) {
    

}


// ----------------采样函数----------------------
void sample(Device* device, double vma, double vmb, double vmc, double ima, double imb, double imc, double vna, double vnb, double vnc, double ina, double inb, double inc, double ka, double kb, double kc, double time) {
    // 更新装置时间
    device->time = time;
    
    device->sample[0] = vma;
    device->sample[1] = vmb;
    device->sample[2] = vmc;
    device->sample[3] = ima;
    device->sample[4] = imb;
    device->sample[5] = imc;
    device->sample[6] = vna;
    device->sample[7] = vnb;
    device->sample[8] = vnc;
    device->sample[9] = ina;
    device->sample[10] = inb;
    device->sample[11] = inc;

    // 采样值合位为0, 开位为2 --转换为--> 合位状态为1,开位状态为0
    device->brkSample[0] = (int)((2-ka)/2);
    device->brkSample[1] = (int)((2-kb)/2);
    device->brkSample[2] = (int)((2-kc)/2);

    
}









