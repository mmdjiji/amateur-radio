#include <stdio.h>
#include "gpslib.h" 
int main(){
	char str[] = "3954.43158,N,11623.48816,E"; //从GPS芯片接收到的位置数据 
	double *gps = gps2data(str); //解析GPS数据 并将结果以指针形式存入数组gps 
	char *code = getCode(gps[0],gps[1]); //解析梅登海格区块 并将结果以指针形式存入数组code 
	printf("纬度：%.8lf\n经度：%.8lf\n",gps[0],gps[1]);
	printf("梅登海格区块：%s",code);
	return 0;
}
