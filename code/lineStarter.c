#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

double* chooseCurrentPhase(Device* device, int phase);
double* chooseVoltagePhase(Device* device, int phase);
int overCurrentStart(Device* device, int phase);
int singlePhaseStart(Device* device, double* inst);
int zeroSequenceCurrentStart(Device* device,int phase);
void recordMemoryUI(Device* device); // 未实现
void ratedParam(Device* device);


// 线路启动判据
void lineStarter(Device* device, int phase) {
    int flag1 = overCurrentStart(device, phase);
    int flag2 = zeroSequenceCurrentStart(device, phase);

    if (flag1 == 1 || flag2 == 1) {
        device->startTime = device->time; // 虽然与各自的置位操作重复，但暂时还是保留。
        // 存储记忆量
        recordMemoryUI(device);

        // 计算额定参数, 电压电流..
        ratedParam(device);
    }
}



/**
 * 过电流启动判据
 * 突变量整定值为0.5kA
 */
int overCurrentStart(Device* device, int phase) {
    double* instIm;
    instIm = chooseCurrentPhase(device, phase);
    
    if (singlePhaseStart(device, instIm) == 1) {
        device->startFlag[phase] = 1;
        device->startTime = device->time;

        writeLogWithPhase(device, "%c相电流突变量启动元件动作", phase);
        return 1;
    } 
    return 0;
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
int zeroSequenceCurrentStart(Device* device,int phase){

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
        return 1;
    }
    return 0;
}


/**
 * 启动后对进行记忆
 * 由总启动元件lineStarter调用
 * 每个电气量（比如Vma）计算一个周波48个相量，思考这是为什么？
 * 为什么不是记忆启动时刻一个时间点？
 */
void recordMemoryUI(Device* device) {
    // 记录当前时刻
}


/**
 * 计算额定参数
 */
void ratedParam(Device* device) {
    device->ratedVoltage = phasorAbs(device->memVma[0]) / 1.4142;
    device->ratedCurrent = phasorAbs(device->memIma[0]) / 1.4142;
    device->ratedBetweenVoltage = phasorAbs(phasorSub(device->memVmb[0], device->memVma[0])) / 1.4142;
    device->ratedBetweenCurrent = phasorAbs(phasorSub(device->memImb[0], device->memIma[0])) / 1.4142;
}
