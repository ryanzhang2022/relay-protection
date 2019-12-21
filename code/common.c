#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

void initSetValue(Device* device, char* deviceName){
    // 后期应该为根据装置名查找配置文件

    // 设置装置名
    if (notYet(device, "设置保护装置名及保护定值")) {
        strcpy(device->deviceName, deviceName);
        
        device->lineStartSetValue[0] = 1.0; // 电流突变量启动
        device->lineStartSetValue[1] = 0.1; // 零序电流启动

        device->overCurrentSetValue[0] = 3.0;  // I段
        device->overCurrentSetValue[1] = 2.5;  // II段
        device->overCurrentSetValue[2] = 1.5;  // III段

        device->overCurrentTimeSetValue[0] = 0.1; // I段延时20ms
        device->overCurrentTimeSetValue[1] = 0.5; // II段
        device->overCurrentTimeSetValue[2] = 1.0; // III段
        device->overCurrentTimeSetValue[3] = 4.0; // 返回

        device->distanceSetValue[0] = 40;
        device->distanceSetValue[1] = 300;
        device->distanceSetValue[2] = 500;

        device->distanceTimeSetValue[0] = 10e-3;        
        device->distanceTimeSetValue[1] = 0.1;        
        device->distanceTimeSetValue[2] = 0.4;        
        device->distanceTimeSetValue[3] = 4.0; 

        // 初始化完毕,记录日志
        writeLog(device, "装置初始化");       

    }
}

int upTo10(Device* device) {
    device->sampleCount++;
    if (device->sampleCount == 10) {
        device->sampleCount = 0;
        return 1;
    } else {
        return 0;
    }
}


// 仿真采样
void sample(Device* device, double vma, double vmb, double vmc, double ima, double imb, double imc, double vna, double vnb, double vnc, double ina, double inb, double inc, double ka, double kb, double kc, double time) {
    
    // 更新装置时间
    device->time = time;
    
    device->sample[0] = vma;
    device->sample[1] = vmb;
    device->sample[2] = vmc;
    device->sample[3] = ima;
    device->sample[4] = imb;
    device->sample[5] = imc;
    device->sample[6] = vna;
    device->sample[7] = vnb;
    device->sample[8] = vnc;
    device->sample[9] = ina;
    device->sample[10] = inb;
    device->sample[11] = inc;

    // 采样值合位为0, 开位为2 --转换为--> 合位状态为1,开位状态为0
    device->brkSample[0] = (int)((2-ka)/2);
    device->brkSample[1] = (int)((2-kb)/2);
    device->brkSample[2] = (int)((2-kc)/2);
    
}

void sample2inst(Device* device) {
    int i = 0;
    
    // 更新数据    
    for (i = 9; i >= 1; i--) {
        device->instVma[i] = device->instVma[i-1];
        device->instVmb[i] = device->instVmb[i-1];
        device->instVmc[i] = device->instVmc[i-1];
        device->instIma[i] = device->instIma[i-1];
        device->instImb[i] = device->instImb[i-1];
        device->instImc[i] = device->instImc[i-1];

        device->instVna[i] = device->instVna[i-1];
        device->instVnb[i] = device->instVnb[i-1];
        device->instVnc[i] = device->instVnc[i-1];
        device->instIna[i] = device->instIna[i-1];
        device->instInb[i] = device->instInb[i-1];
        device->instInc[i] = device->instInc[i-1];
    }

    device->instVma[0] = device->sample[0];
    device->instVmb[0] = device->sample[1];
    device->instVmc[0] = device->sample[2];
    device->instIma[0] = device->sample[3];
    device->instImb[0] = device->sample[4];
    device->instImc[0] = device->sample[5];

    device->instVna[0] = device->sample[6];
    device->instVnb[0] = device->sample[7];
    device->instVnc[0] = device->sample[8];
    device->instIna[0] = device->sample[9];
    device->instInb[0] = device->sample[10];
    device->instInc[0] = device->sample[11];
    
}

void dataFilter(Device* device) {
    
    int i = 0;
    // 滤波后数据后移
    for (i = WINDOW-1; i >= 1; i--) {
        device->filterVma[i] = device->filterVma[i-1];
        device->filterVmb[i] = device->filterVmb[i-1];
        device->filterVmc[i] = device->filterVmc[i-1];
        device->filterIma[i] = device->filterIma[i-1];
        device->filterImb[i] = device->filterImb[i-1];
        device->filterImc[i] = device->filterImc[i-1];

        device->filterVna[i] = device->filterVna[i-1];
        device->filterVnb[i] = device->filterVnb[i-1];
        device->filterVnc[i] = device->filterVnc[i-1];
        device->filterIna[i] = device->filterIna[i-1];
        device->filterInb[i] = device->filterInb[i-1];
        device->filterInc[i] = device->filterInc[i-1];
    }

    // 更新新的滤波后数据点
    lowPassFilter(device->filterVma, device->instVma);
    lowPassFilter(device->filterVmb, device->instVmb);
    lowPassFilter(device->filterVmc, device->instVmc);

    lowPassFilter(device->filterIma, device->instIma);
    lowPassFilter(device->filterImb, device->instImb);
    lowPassFilter(device->filterImc, device->instImc);

    lowPassFilter(device->filterVna, device->instVna);
    lowPassFilter(device->filterVnb, device->instVnb);
    lowPassFilter(device->filterVnc, device->instVnc);

    lowPassFilter(device->filterIna, device->instIna);
    lowPassFilter(device->filterInb, device->instInb);
    lowPassFilter(device->filterInc, device->instInc);
  
}

void toPhasor(Device* device) {
    inst2phasor(device->filterVma, 0, &device->phasor[0]);
    inst2phasor(device->filterVmb, 0, &device->phasor[1]);
    inst2phasor(device->filterVmc, 0, &device->phasor[2]);

    inst2phasor(device->filterIma, 0, &device->phasor[3]);
    inst2phasor(device->filterImb, 0, &device->phasor[4]);
    inst2phasor(device->filterImc, 0, &device->phasor[5]);

    inst2phasor(device->filterVna, 0, &device->phasor[6]);
    inst2phasor(device->filterVnb, 0, &device->phasor[7]);
    inst2phasor(device->filterVnc, 0, &device->phasor[8]);

    inst2phasor(device->filterIna, 0, &device->phasor[9]);
    inst2phasor(device->filterInb, 0, &device->phasor[10]);
    inst2phasor(device->filterInc, 0, &device->phasor[11]);

    
}


/**
 * 低通滤波函数
 * 参数分别为滤波后数组和滤波前数组
 */
void lowPassFilter(double* aft, double* bef) {
    // 滤波参数直接给出,使用bufferFilter.m计算得到 此处为48点采样,100hz截止频率
    double at = 0.014401;
    double bt = -1.632993;
    double ct = 0.690599;

    aft[0] = at*bef[0] + 2*at*bef[1] + at*bef[2] - bt*aft[1] - ct*aft[2];
}

/**
 * 全周傅式算法
 */
void inst2phasor(double* inst, int start, Phasor* phasor) {
    int i = start;
    // 因为定义的全局变量, 需要先把上次计算值清掉
    phasor->real = 0;
    phasor->img = 0;
    

    for (i = start; i < start + POINTS; i++) {
        phasor->real += inst[i]*sin(2*PI*i/(double)POINTS);
        phasor->img  += inst[i]*cos(2*PI*i/(double)POINTS);
    }
    
    // C语言语法规则: 2/400等于零!
    phasor->real = phasor->real * (2/(double)POINTS);
    phasor->img =  phasor->img * (2/(double)POINTS);  
}


double phasorAbs(Phasor p) {
    return sqrt(p.real*p.real + p.img*p.img);
}

Phasor phasorAdd(Phasor pa, Phasor pb) {
    Phasor p;

    p.real = pa.real + pb.real;
    p.img = pa.img + pb.img;

    return p;
}

Phasor phasorSub(Phasor pa, Phasor pb) {
    Phasor p;

    p.real = pa.real - pb.real;
    p.img = pa.img - pb.img;

    return p;
}


/**
 * 计算常数与相量乘积
 */
Phasor phasorMulti(double a, Phasor p) {
    p.real *= a;
    p.img *= a;

    return p;
}

/**
 * 日志模块 
 * 参考 C语言实现写入日志文件 https://blog.csdn.net/sunlion81/article/details/8647028
 */

/*

/*
写入日志文件
@param filename [in]: 日志文件名
@param buffer [in]: 日志内容
@param buf_size [in]: 日志内容大小
@return 空
*/
void writeLog(Device* device, char* content) {
    // 获取当前时间作为日志文件名
    // 每隔5分钟更新文件名

    time_t rawtime;
    struct tm* timeinfo;
    char filename[40];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(filename, "..\\\\log\\\\%04d-%02d-%02d_%02d-%02d.txt",
        (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
        timeinfo->tm_hour, ((int)(timeinfo->tm_min)/5)*5);

    if (content != NULL && notYet(device, content)) {
        // 写日志
        {
            FILE *fp;
            fp = fopen(filename, "at+");
            if (fp != NULL)
            { 
                fprintf(fp, "[LOG-INFO] Simulation Time: %fs [%s]: ", device->time, device->deviceName);
        
                fprintf(fp, content);
                fprintf(fp, "...OK\n");
                fclose(fp);
                fp = NULL;  
            }
        }
    }
}


/**
 * 上面日志函数的重载形式, 主要用于相别信息
*/
void writeLogWithPhase(Device* device, char* content, int phase) {
    // 获取当前时间作为日志文件名
    // 每隔5分钟更新文件名

    time_t rawtime;
    struct tm* timeinfo;
    char filename[40];
    char formatContent[128];
    char charPhase;

    // 将相别数字转换为字母
    charPhase = (char)('A'+phase);

    // 格式化字符串
    sprintf(formatContent, content, charPhase);

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(filename, "..\\\\log\\\\%04d-%02d-%02d_%02d-%02d.txt",
        (timeinfo->tm_year+1900), timeinfo->tm_mon, timeinfo->tm_mday,
        timeinfo->tm_hour, ((int)(timeinfo->tm_min)/5)*5);


    
    if (formatContent != NULL && notYet(device, formatContent)) {
        // 写日志
        {
            FILE *fp;
            fp = fopen(filename, "at+");
            if (fp != NULL)
            { 
                fprintf(fp, "[LOG-INFO] Simulation Time: %fs [%s]: ",device->time, device->deviceName);
        
                fprintf(fp, formatContent);
                fprintf(fp, "...OK\n");
                fclose(fp);
                fp = NULL;

            }
        }
    }
}


/**
 * hash算法
 * @param:需要求hash值的字符串
 * @param:数组长度
 */
unsigned int SDBMHash(char *str, int arrLength) {
    unsigned int hash = 0; 
    while (*str)
    {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
 
    return (hash & 0x7FFFFFFF)%arrLength;
}


/**
 * notYet函数
 * 功能:将该函数的返回值作为判别条件,可以保证条件语句内的
 * 语句仅执行一次, 使用方法如下:
 * if (notYet(device, "描述代码段的作用")) {
 *     // 执行语句...
 * }
 * 原理:利用"描述代码段的作用"作为该代码段的标识,通过hash计算基本确保唯一性
 */
int notYet(Device* device, char* str) {
    unsigned int hashCode;

    hashCode = SDBMHash(str, MAXSIZE);
    if (device->notYetFlag[hashCode] == 0) {
        device->notYetFlag[hashCode] = 1;
        return 1;
    } 
    return 0;    
}


