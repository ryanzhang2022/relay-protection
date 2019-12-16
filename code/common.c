#include <math.h>
#include "..\\code\\dataStruct.h"

void lowPassFilter(double* aft, double* bef);
void inst2phasor(double* inst, int start, Phasor* phasor);

void sample2inst(Device* device) {
    int i = 0;

    for (i = 9; i >= 1; i--) {
        device->instVma[i] = device->instVma[i-1];
        device->instVmb[i] = device->instVmb[i-1];
        device->instVmc[i] = device->instVmc[i-1];
        device->instIma[i] = device->instIma[i-1];
        device->instImb[i] = device->instImb[i-1];
        device->instImc[i] = device->instImc[i-1];

        device->instVna[i] = device->instVna[i-1];
        device->instVnb[i] = device->instVnb[i-1];
        device->instVnc[i] = device->instVnc[i-1];
        device->instIna[i] = device->instIna[i-1];
        device->instInb[i] = device->instInb[i-1];
        device->instInc[i] = device->instInc[i-1];
    }

    device->instVma[0] = device->sample[0];
    device->instVmb[0] = device->sample[1];
    device->instVmc[0] = device->sample[2];
    device->instIma[0] = device->sample[3];
    device->instImb[0] = device->sample[4];
    device->instImc[0] = device->sample[5];

    device->instVna[0] = device->sample[6];
    device->instVnb[0] = device->sample[7];
    device->instVnc[0] = device->sample[8];
    device->instIna[0] = device->sample[9];
    device->instInb[0] = device->sample[10];
    device->instInc[0] = device->sample[11];
        
}

void dataFilter(Device* device) {
    
    int i = 0;
    // 滤波后数据后移
    for (i = WINDOW-1; i >= 1; i--) {
        device->filterVma[i] = device->filterVma[i-1];
        device->filterVmb[i] = device->filterVmb[i-1];
        device->filterVmc[i] = device->filterVmc[i-1];
        device->filterIma[i] = device->filterIma[i-1];
        device->filterImb[i] = device->filterImb[i-1];
        device->filterImc[i] = device->filterImc[i-1];

        device->filterVna[i] = device->filterVna[i-1];
        device->filterVnb[i] = device->filterVnb[i-1];
        device->filterVnc[i] = device->filterVnc[i-1];
        device->filterIna[i] = device->filterIna[i-1];
        device->filterInb[i] = device->filterInb[i-1];
        device->filterInc[i] = device->filterInc[i-1];
    }

    // 更新新的滤波后数据点
    lowPassFilter(device->filterVma, device->instVma);
    lowPassFilter(device->filterVmb, device->instVmb);
    lowPassFilter(device->filterVmc, device->instVmc);

    lowPassFilter(device->filterIma, device->instIma);
    lowPassFilter(device->filterImb, device->instImb);
    lowPassFilter(device->filterImc, device->instImc);

    lowPassFilter(device->filterVna, device->instVna);
    lowPassFilter(device->filterVnb, device->instVnb);
    lowPassFilter(device->filterVnc, device->instVnc);

    lowPassFilter(device->filterIna, device->instIna);
    lowPassFilter(device->filterInb, device->instInb);
    lowPassFilter(device->filterInc, device->instInc);
  
}

void toPhasor(Device* device) {
    inst2phasor(device->filterVma, 0, &device->phasor[0]);
    inst2phasor(device->filterVmb, 0, &device->phasor[1]);
    inst2phasor(device->filterVmc, 0, &device->phasor[2]);

    inst2phasor(device->filterIma, 0, &device->phasor[3]);
    inst2phasor(device->filterImb, 0, &device->phasor[4]);
    inst2phasor(device->filterImc, 0, &device->phasor[5]);

    inst2phasor(device->filterVna, 0, &device->phasor[6]);
    inst2phasor(device->filterVnb, 0, &device->phasor[7]);
    inst2phasor(device->filterVnc, 0, &device->phasor[8]);

    inst2phasor(device->filterIna, 0, &device->phasor[9]);
    inst2phasor(device->filterInb, 0, &device->phasor[10]);
    inst2phasor(device->filterInc, 0, &device->phasor[11]);

    
}


/**
 * 低通滤波函数
 * 参数分别为滤波后数组和滤波前数组
 */
void lowPassFilter(double* aft, double* bef) {
    // 滤波参数直接给出,使用bufferFilter.m计算得到
    double at = 5.3717e-04;
    double bt = -1.9334;
    double ct = 0.93553;

    aft[0] = at*bef[0] + 2*at*bef[1] + at*bef[2] - bt*aft[1] - ct*aft[2];
}

/**
 * 全周傅式算法
 */
void inst2phasor(double* inst, int start, Phasor* phasor) {
    int i = start;
    // 因为定义的全局变量, 需要先把上次计算值清掉
    phasor->real = 0;
    phasor->img = 0;
    

    for (i = start; i < start + POINTS; i++) {
        phasor->real += inst[i]*sin(2*PI*i/POINTS);
        phasor->img  += inst[i]*cos(2*PI*i/POINTS);
    }
    
    // C语言语法规则: 2/400等于零!
    phasor->real = phasor->real * (2/POINTS);
    phasor->img =  phasor->img * (2/POINTS);

    
}