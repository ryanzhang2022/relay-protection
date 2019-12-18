#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void distanceRelay(Device* device, int phase) {
    int* timeCount;
    int* tripFlag;
    // 整定值
    
    double Z1set = 20.0, Z2set = 70, Z3set = 300.0; 

    Phasor U, I;
    Phasor x, y;


    timeCount = &device->distanceTimeCount[phase];
    tripFlag = &device->distanceTripFlag[phase];
    U = device->phasor[0+phase];
    I = device->phasor[3+phase];

    // 启动后延时计数
    (*timeCount)++;


    // I段
    x = phasorSub(U, phasorMulti(0.5*Z1set, I));
    y = phasorMulti(0.5*Z1set, I);

    
    if (*timeCount > 2 && (absPhasor(x) - absPhasor(y)) < 0 ) {
        *tripFlag = 1;
    }

 
    // II段
    x = phasorSub(U, phasorMulti(0.5*Z2set, I));
    y = phasorMulti(0.5*Z2set, I);


    if (*timeCount > 48 && (absPhasor(x) - absPhasor(y)) < 0 ) {
        *tripFlag = 1;
    }


    // III段
    x = phasorSub(U, phasorMulti(0.5*Z3set, I));
    y = phasorMulti(0.5*Z3set, I);



    if (*timeCount > 150 && (absPhasor(x) - absPhasor(y)) < 0 ) {
        *tripFlag = 1;
    }

    
}