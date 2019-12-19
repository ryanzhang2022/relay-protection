#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void overCurrentRelay(Device* device, int phase) {
    int* timeCount;
    int* tripFlag;


    // 整定值
    double I1set = device->overCurrentSetValue[1];
    double I2set = device->overCurrentSetValue[2];
    double I3set = device->overCurrentSetValue[3];

    int t1set = device->overCurrentTimeSetValue[1];
    int t2set = device->overCurrentTimeSetValue[2];
    int t3set = device->overCurrentTimeSetValue[3];

    int returnTimeSet = device->overCurrentTimeSetValue[4];


    Phasor I;

    timeCount = &device->overCurrentTimeCount[phase];
    tripFlag = &device->overCurrentTripFlag[phase];
    I = device->phasor[3+phase];

    // 启动后延时计数
    (*timeCount)++;


    // I段
    if (*timeCount > t1set && (phasorAbs(I) > I1set)) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相过电流保护I段动作", phase);
    }


    // II段
    if (*timeCount > t2set && (phasorAbs(I) > I2set)) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相过电流保护II段动作", phase);
    }


    // III段
    if (*timeCount > t3set && (phasorAbs(I) > I3set)) {
        *tripFlag = 1;
        writeLogWithPhase(device, "%c相过电流保护III段动作", phase);
    }

    // 保护返回
    if (*timeCount > returnTimeSet) {
        // 逻辑待定
        // 清理启动标记?
        // 计时器归零?
    }
}
