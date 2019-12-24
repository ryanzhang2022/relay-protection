#include "..\\code\\dataStruct.h"
#include "..\\code\\common.h"

/**
 * 工频变化量距离继电器
 * 由line.c按相调用，对于相间故障phase=0，代表AB相间，以此类推
 * 
 * 编写说明：
 * 具体原理见说明书P7，不要除了该文件外不要修改其他代码（该函数已经在line.c中被调用；
 * 需要的数据从device中取出后，先赋值给局部变量再使用（提高代码可读性）；
 * 如果需要的整定值没有在dataStruct中定义，暂时直接在本文件中直接给出；
 * 在使用记忆量时，思考时间点对应相减，如果不理解与我讨论；
 * 编写完成测试无误后提交
 */
void deltaDistanceRelay(Device* device, int phase) {
    writeLog(device, "工频变化量距离保护测试");
    //1. 计算delta

    //2. 接地变化距离

    //3. 相间接地距离
}