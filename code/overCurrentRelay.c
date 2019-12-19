#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void overCurretRelay(Device* device, int phase) {
    int* timeCount;
    int* tripFlag;
    int* tripTime;
    
    // 整定值
    double I1set = device->overCurrentSetValue[1];
    double I2set = device->overCurrentSetValue[2];
    double I3set = device->overCurrentSetValue[3];

    int t1set = device->overCurrentTimeSetValue[1];
    int t2set = device->overCurrentTimeSetValue[2];
    int t3set = device->overCurrentTimeSetValue[3];
    int tBackset = device->overCurrentTimeSetValue[4];

    Phasor I;


    timeCount = &device->overCurrentTimeCount[phase];
    tripFlag = &device->overCurrentTripFlag[phase];
    tripTime = &device->overCurrentTimeCount[4];
    I = device->phasor[3+phase];

    // 启动后延时计数
    (*timeCount)++;


    // I段

    if (*timeCount > t1set && (absPhasor(I) > I1set)) {
        *tripFlag = 1;
    }

 
    // II段

    if (*timeCount > t2set && (absPhasor(I) > I2set)) {
        *tripFlag = 1;
    }


    // III段

    if (*timeCount > t3set && (absPhasor(I) > I3set)) {
        *tripFlag = 1;
    }


    // 复归

    if (*tripFlag == 1){
        (*tripTime)++;
    }

    if (*tripTime > tBackset) {
        *tripFlag = 0;
        *tripTime = 0;
        *timeCount = 0;
    }
    
}
