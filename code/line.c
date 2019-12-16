#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"


void line(Device* device) {
    // 将采样值存入瞬时值数组
    sample2inst(device);
    
    // 瞬时值滤波后存入并更新滤波后数组
    dataFilter(device);
    
    // 利用滤波后数据计算12通道相量,存入phasor数组
    toPhasor(device);
    
    // 保护主判据, 使用计算得到的相量进行相关保护逻辑的实现
    // code...
    device->relayFlag[0] = 12;
    
}