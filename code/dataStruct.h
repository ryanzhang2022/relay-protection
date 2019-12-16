// 数据窗总长(包括记忆量)
#define WINDOW 1600
// 每周波采样点数
#define POINTS 400.0
#define PI 3.1415926

/*
* 相量
*/
typedef struct Phasor {
    double real;
    double img;
} Phasor;


/* 保护装置通用的数据结构--全局变量
* sample, 本次12通道采样值
* instVma, instVmb等数组: 瞬时值数组
* phasor 本次相量计算结果
* setValue数组: 通用整定值数组,具体每一个元素所代表的的整定值含义见各个保护的说明
* relayTime数组, 通用延时数组 
* relayFlag数组, 通用跳闸标记
*/
typedef struct Device {
    double sample[12];
    
    // 只需要保留少量历史数据用于滤波即可
    double instVma[10];
    double instVmb[10];
    double instVmc[10];
    double instIma[10];
    double instImb[10];
    double instImc[10];
    double instVna[10];
    double instVnb[10];
    double instVnc[10];
    double instIna[10];
    double instInb[10];
    double instInc[10];
    
    double filterVma[WINDOW];
    double filterVmb[WINDOW];
    double filterVmc[WINDOW];
    double filterIma[WINDOW];
    double filterImb[WINDOW];
    double filterImc[WINDOW];
    double filterVna[WINDOW];
    double filterVnb[WINDOW];
    double filterVnc[WINDOW];
    double filterIna[WINDOW];
    double filterInb[WINDOW];
    double filterInc[WINDOW];
    
    Phasor phasor[12];
    double setValue[20];
    double relayTime[20];
    int relayFlag[20];
    
} Device;

