#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

double* chooseCurrentPhase(Device* device, int phase);
double* chooseVoltagePhase(Device* device, int phase);
void overCurrentStart(Device* device, int phase);
int singlePhaseStart(double* inst);


// 线路启动判据
void lineStarter(Device* device, int phase) {
    overCurrentStart(device, phase);
    //其他启动判据...
}





/**
 * 过电流启动判据
 * 突变量整定值为0.5kA
 */
void overCurrentStart(Device* device, int phase) {
    double* instIm;
    instIm = chooseCurrentPhase(device, phase);
    
    if (singlePhaseStart(instIm) == 1) {
        device->startFlag[phase] = 1;
        writeLogWithPhase(device, "%c相过电流启动元件动作", phase);
    } 
 
}

int singlePhaseStart(double* inst) {
    Phasor phasorNow, phasorBefore, phasorDelta;
    double amp;

    inst2phasor(inst, 0, &phasorNow);
    inst2phasor(inst, 3*POINTS, &phasorBefore);
    
    phasorDelta = phasorSub(phasorNow, phasorBefore);

    amp = phasorAbs(phasorDelta);

    // 突变量整定值为0.5kA
    if (amp > 0.5) {
        return 1;
    } else {
        return 0;
    }   
}

double* chooseCurrentPhase(Device* device, int phase) {
    double* instIm;
    switch (phase) {
        case 0:
            /* code */
            instIm = device->filterIma;
            break;
        case 1:
            instIm = device->filterImb;
            break;
        case 2:
            instIm = device->filterImc;
            break;
    }
    return instIm;
}

double* chooseVoltagePhase(Device* device, int phase) {
    double* instVm;
    switch (phase) {
        case 0:
            /* code */
            instVm = device->filterVma;
            break;
        case 1:
            instVm = device->filterVmb;
            break;
        case 2:
            instVm = device->filterVmc;
            break;
    }
    return instVm;
}