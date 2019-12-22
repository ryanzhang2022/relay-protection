// 每周波采样点数
#define POINTS 48

// 数据窗总长(包括记忆量) 4个周波
#define WINDOW 192 

#define PI 3.1415926

#define MAXSIZE 655350



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
    char deviceName[40];
    double time;
    double sample[12];
    // 断路器状态采样,合位为1,断开为0
    int brkSample[3];
    int sampleCount;
    
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

    // 记忆量
    Phasor memVma[POINTS], memVmb[POINTS], memVmc[POINTS];
    Phasor memIma[POINTS], memImb[POINTS], memImc[POINTS];
    Phasor memVna[POINTS], memVnb[POINTS], memVnc[POINTS];
    Phasor memIna[POINTS], memInb[POINTS], memInc[POINTS];

    // 线路参数
    Phasor lineZs; // 自阻抗
    Phasor lineZm; // 互阻抗
    
    // 保护启动标志
    int startFlag[3];
    // 保护启动时间
    double startTime;

    // 相量实时计算值
    Phasor phasor[12];

    // 线路启动元件整定值: 0:电流突变量整定值  1:零序电流整定值  ...
    double lineStartSetValue[10];

    
    // 工频变化量距离
    double deltaDistanceSetValue[10];
    double deltaDistanceTimeSetValue[10];

    // 过电流保护
    double overCurrentSetValue[10];
    double overCurrentTimeSetValue[10];
    int overCurrentTripFlag[3];

    // 距离保护
    double distanceSetValue[10];
    double distanceTimeSetValue[10];
    int distanceTripFlag[3];
    
    // 电流差动保护
    double currentDiffSetValue[10];
    double currentDiffTimeSetValue[10];
    int currentDiffTripFlag[3];

    // 零序电流保护
    double zeroSequenceSetValue[10];
    double zeroSequenceTimeSetValue[10];
    int zeroSequenceTripCount[3];    
    

    // 跳闸动作标志
    int tripFlag[3];

    // 唯一执行语句标志位
    int notYetFlag[MAXSIZE];
   
} Device;

