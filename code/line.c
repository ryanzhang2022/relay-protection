#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

extern distanceRelay(Device* device, int phase);


void line(Device* device) {
    // 将采样值存入瞬时值数组
    sample2inst(device);
    
    // 瞬时值滤波后存入并更新滤波后数组
    dataFilter(device);
    
    // 利用滤波后数据计算12通道相量,存入phasor数组
    toPhasor(device);

    // 过电流启动判据
    // 只有满足启动判据,才执行判别逻辑
    overCurrentStart(device);
    
    // 保护主判据, 使用计算得到的相量进行相关保护逻辑的实现
    // code...
    

    // 距离保护 A相


    if (device->startFlag[0] == 1) {
        distanceRelay(device, 0);
    }


    // 根据各保护动作情况,打印日志信息


    // 综合各保护动作情况,对overallTripFlag置位


    
    
}