#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void overCurrentRelay(Device* device, int phase) {
    int* tripFlag;
    double startTime = device->startTime;
    double time = device->time;

    // 整定值
    double I1set = device->overCurrentSetValue[0];
    double I2set = device->overCurrentSetValue[1];
    double I3set = device->overCurrentSetValue[2];

    double t1set = device->overCurrentTimeSetValue[0];
    double t2set = device->overCurrentTimeSetValue[1];
    double t3set = device->overCurrentTimeSetValue[2];

    int returnTimeSet = device->overCurrentTimeSetValue[3];


    Phasor I;

    tripFlag = &device->overCurrentTripFlag[phase];
    I = device->phasor[3+phase];


    // I段
    if ((time-startTime) > t1set && (phasorAbs(I) > I1set)) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相过电流保护I段动作", phase);
    }


    // II段
    if ((time-startTime) > t2set && (phasorAbs(I) > I2set)) {
        
        *tripFlag = 1;

        writeLogWithPhase(device, "%c相过电流保护II段动作", phase);
    }


    // III段
    if ((time-startTime) > t3set && (phasorAbs(I) > I3set)) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相过电流保护III段动作", phase);
    }


/*
    // 保护返回
    if ((time-startTime) > returnTimeSet) {
        device->startFlag[phase] = 0;
        *tripFlag = 0;
        writeLogWithPhase(device, "c%相过电流保护返回", phase);
    }
    */
}
