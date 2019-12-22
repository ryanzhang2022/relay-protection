#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

extern lineStarter(Device* device, int phase);
extern deltaDistanceRelay(Device* device, int phase);
extern distanceRelay(Device* device, int phase);
extern overCurrentRelay(Device* device, int phase);


void line(Device* device) {

    int phase = 0;

    // 将采样值存入瞬时值数组
    sample2inst(device);
    
    // 瞬时值滤波后存入并更新滤波后数组
    dataFilter(device);
    
    // 利用滤波后数据计算12通道相量,存入phasor数组
    toPhasor(device);

    /**
     * 启动判据
     * 只有保护没有启动才进入判别, 只要有一种启动判据动作置位,
     * 就不再进行启动判别.
     */

    for (phase = 0; phase < 3; phase++) {
        if (device->startFlag[phase] == 0) {
            lineStarter(device, phase);
        }
    }
    
    // 保护主判据, 使用计算得到的相量进行相关保护逻辑的实现
    // code...
    
    // 工频变化量距离保护 三相
    for (phase = 0; phase < 3; phase++) {
        if (device->startFlag[phase] == 1) {
            deltaDistanceRelay(device, phase);
        }
    }

    // 距离保护 三相
    for (phase = 0; phase < 3; phase++) {
        if (device->startFlag[phase] == 1) {
            distanceRelay(device, phase);
        }
    }

    // 过电流保护 三相
    for (phase = 0; phase < 3; phase++) {
        if (device->startFlag[phase] == 1) {
            overCurrentRelay(device, phase);
        }
    }

    // 综合各保护动作情况,对tripFlag置位
    for (phase = 0; phase < 3; phase++) {
        if (device->overCurrentTripFlag[phase] == 1 || device->distanceTripFlag[phase] == 1) {
            device->tripFlag[phase] = 1;
        }
    }


    
    
}