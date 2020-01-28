#include <stdio.h>
#include "gpslib.h" 
int main(){
	char str[] = "RMC,083000.00,A,3954.43158,N,11623.48816,E,0.000,,010120,,,D*6E"; //从GPS芯片接收到的位置数据
	RMC result = rmc2data(str); //解析GPS数据 并将结果以指针形式存入数组gps 
	char *code = getCode(result.lat,result.lon); //解析梅登海格区块 并将结果以指针形式存入数组code 
	
	//输出解析到的信息 
	printf("UTC日期：%s\n", result.UTC_DATE);
	printf("UTC时间：%s\n", result.UTC_TIME);
	printf("定位状态：%c (%s)\n", result.valid,(result.valid=='A')?"有效":"无效");
	printf("纬度：%lf\n", result.lat);
	printf("经度：%lf\n", result.lon);
	printf("地面速率：%lf\n", result.speed);
	printf("地面航向：%lf\n", result.direction);
	printf("梅登海格区块：%s\n",code);
	return 0;
}