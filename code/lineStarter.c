#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

double* chooseCurrentPhase(Device* device, int phase);
double* chooseVoltagePhase(Device* device, int phase);
void overCurrentStart(Device* device, int phase);
int singlePhaseStart(Device* device, double* inst);
void zeroSequenceCurrentStart(Device* device,int phase);


// 线路启动判据
void lineStarter(Device* device, int phase) {
    overCurrentStart(device, phase);
    zeroSequenceCurrentStart(device, phase);
}



/**
 * 过电流启动判据
 * 突变量整定值为0.5kA
 */
void overCurrentStart(Device* device, int phase) {
    double* instIm;
    instIm = chooseCurrentPhase(device, phase);
    
    if (singlePhaseStart(device, instIm) == 1) {
        device->startFlag[phase] = 1;
        device->startTime = device->time;

        writeLogWithPhase(device, "%c相电流突变量启动元件动作", phase);
    } 
 
}

int singlePhaseStart(Device* device, double* inst) {
    Phasor phasorNow, phasorBefore, phasorDelta;
    double amp;

    inst2phasor(inst, 0, &phasorNow);
    inst2phasor(inst, 1*POINTS, &phasorBefore);
    
    phasorDelta = phasorSub(phasorNow, phasorBefore);

    amp = phasorAbs(phasorDelta);

    // 突变量整定值为0.5kA
    if (amp > device->lineStartSetValue[0]) {
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

/**
 * 零序过电流起动判据
 * 整定值为0.1kA
 */
void zeroSequenceCurrentStart(Device* device,int phase){

    Phasor I0, temp;
    double abs;

    temp = phasorAdd(device->phasor[3], device->phasor[4]);
    I0 = phasorAdd(temp, device->phasor[5]);
    abs = phasorAbs(I0)/3;

    if (abs > device->lineStartSetValue[1]){
        device->startFlag[0] = 1;
        device->startFlag[1] = 1;
        device->startFlag[2] = 1;
        
        device->startTime = device->time;

        writeLog(device, "零序过电流启动元件动作");
    }

}