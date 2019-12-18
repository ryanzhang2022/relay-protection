// common

void sample2inst(Device*);

void dataFilter(Device*);

void toPhasor(Device*);

void overCurrentStart(Device* device);

double absPhasor(Phasor p);
Phasor phasorAdd(Phasor pa, Phasor pb);
Phasor phasorSub(Phasor, Phasor);
Phasor phasorMulti(double a, Phasor p);

void lowPassFilter(double* aft, double* bef);

void inst2phasor(double* inst, int start, Phasor* phasor);
int singlePhaseStart(double* inst);

void writeLog(Device* device, char* content);
void writePhaseLog(Device* device, char* content, int phase);

unsigned int SDBMHash(char *str, int arrLength); 



