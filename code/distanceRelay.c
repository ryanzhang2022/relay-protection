#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void distanceRelay(Device* device, int phase) {
    int* tripFlag;
    double startTime = device->startTime;
    double time = device->time;
    // 整定值
    double Z1set = device->distanceSetValue[0];
    double Z2set = device->distanceSetValue[1];
    double Z3set = device->distanceSetValue[2];

    double t1set = device->distanceTimeSetValue[0];
    double t2set = device->distanceTimeSetValue[1];
    double t3set = device->distanceTimeSetValue[2];

    double returnTimeSet = device->distanceTimeSetValue[3];


    Phasor U, I;
    Phasor x, y;

    tripFlag = &device->distanceTripFlag[phase];
    U = device->phasor[0+phase];
    I = device->phasor[3+phase];


    // I段
    x = phasorSub(U, phasorMulti(0.5*Z1set, I));
    y = phasorMulti(0.5*Z1set, I);

    
    if ((time-startTime) > t1set && (phasorAbs(x) - phasorAbs(y)) < 0 ) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相距离保护I段动作", phase);
    }

 
    // II段
    x = phasorSub(U, phasorMulti(0.5*Z2set, I));
    y = phasorMulti(0.5*Z2set, I);


    if ((time-startTime) > t2set && (phasorAbs(x) - phasorAbs(y)) < 0 ) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相距离保护II段动作", phase);
    }


    // III段
    x = phasorSub(U, phasorMulti(0.5*Z3set, I));
    y = phasorMulti(0.5*Z3set, I);


    if ((time-startTime) > t3set && (phasorAbs(x) - phasorAbs(y)) < 0 ) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相距离保护III段动作", phase);
    }


/*
    // 保护返回
    if ((time-startTime) > returnTimeSet) {
        device->startFlag[phase] = 0;
        *tripFlag = 0;
        writeLog(device, "距离保护返回");
    }
    */
   
}