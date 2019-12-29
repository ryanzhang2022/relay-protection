#include <stdio.h>

#define ROWSIZE 2400
#define COLSIZE 11

extern void line_1_p(double* time, double* input, double* brk, double* tripSignal);


void readData(char* filename, double data[][COLSIZE], int row, int col) {
    if (filename == NULL) return;

    FILE *fw = fopen(filename, "r");
    int i, j; 

    if (fw != NULL)
    {
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < col; j++)
            {
                fscanf(fw, "%lf", &data[i][j]); //读取文件中的数据，遇到空格和换行停止读。
            }
        }
        fclose(fw);
    }
}


void main()
{
    double rawdata[ROWSIZE][COLSIZE];
    double time[ROWSIZE];
	double input[ROWSIZE][12];  
	double brk[ROWSIZE][3];
	double tripSignal[ROWSIZE][3];
    int i;

    readData("./testdata.txt", rawdata, ROWSIZE, COLSIZE);
    
	
    for (i = 0; i < ROWSIZE; i++) {
        // 时间
		time[i] = rawdata[i][0];
		
		// 电压
        input[i][0] = rawdata[i][4];
        input[i][1] = rawdata[i][5];
        input[i][2] = rawdata[i][6];

        // 电流
        input[i][3] = rawdata[i][1];
        input[i][4] = rawdata[i][2];
        input[i][5] = rawdata[i][3];

        // 对侧电量
        input[i][6] = 0;
        input[i][7] = 0;
        input[i][8] = 0;
        input[i][9] = 0;
        input[i][10] = 0;
        input[i][11] = 0;
		
		// 断路器状态
		brk[i][0] = 0;
		brk[i][1] = 0;
		brk[i][2] = 0;
		
		tripSignal[i][0] = 0;
		tripSignal[i][1] = 0;
		tripSignal[i][2] = 0;
    }

    for (i = 0; i < ROWSIZE; i++) {
        line_1_p(&time[i], input[i], brk[i], tripSignal[i]);
    }



}
