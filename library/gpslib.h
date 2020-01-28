/*
 * This file is storaged by UTF-8 encoding, if you cannot load it normally, try to transform it to ANSI.
 * GPSLIB.H v1.1
 * 作者: 吉吉(JiJi)
 * https://github.com/mmdjiji
 *
 * 度分经纬度格式转换
 * 定义: double degree2format(double value)
 * 参数: 一个double类型的变量 表示度分经纬度
 * 返回: 一个double类型的变量 表示普通经纬度
 *
 * 解析GPS芯片的经纬度
 * 定义: double* gps2data(char* str)
 * 参数: 一个字符串 例如 char str[] = "3954.43158,N,11623.48816,E";
 * 返回: 一个double类型的数组 数组下标0是转换后的纬度 数组下标1是转换后的经度 一般取6位小数
 *
 * 通过经纬度获取梅登黑德格网编号
 * 定义: char* getCode(double lat, double lon)
 * 参数: lat是纬度 lon是经度
 * 返回: 6个字节的字符数组 表示该位置的梅登海格网编号
 *
 * 解析RMC信息
 * 定义: RMC rmc2data(char* str)
 * 参数: 一个包含RMC信息的字符串 例如 char str[] = "RMC,083000.00,A,3954.43158,N,11623.48816,E,0.000,,010120,,,D*6E";
 * 返回: 一个RMC结构体 定义如下
 * 注意: 目前并不使用校验码内部校验
 */
#ifndef _GPSLIB_H_
#define  _GPSLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct RMC {
	char valid; 				//定位状态 'A'为有效定位 'V'为无效定位
	char UTC_TIME[7]; 	//UTC时间 hhmmss
	char UTC_DATE[7]; 	//UTC日期 ddmmyy
	double lat; 				//纬度 有符号
	double lon;					//经度 有符号
	double speed;				//地面速率
	double direction;		//地面航向
} RMC;
double degree2format(double value) {
	int negative = 0;
	if(value < 0) {
		negative = 1;
		value = -value;
	}
	int du = floor(value / 100);
	double fen = value - du*100;
	if(negative)du=-du;
	return du + (fen/60);
}
double* gps2data(char* str) {
	static double ret[2];
	char *tokenPtr=strtok(str,",");
	ret[0] = atof(tokenPtr);
	tokenPtr=strtok(NULL,",");
	if(tokenPtr[0] == 'S')ret[0] = -ret[0];
	tokenPtr=strtok(NULL,",");
	ret[1] = atof(tokenPtr);
	tokenPtr=strtok(NULL,",");
	if(tokenPtr[0] == 'W')ret[1] = -ret[1];
	ret[0] = degree2format(ret[0]);
	ret[1] = degree2format(ret[1]);
	return ret;
}
char* getCode(double lat, double lon) {
	if(lon<0)lon+=360;
	if(lat<0)lat+=180;
	static char code[6];
	code[0] = (char)((int)((180 + lon) / 20)+(int)'A');
	code[1] = (char)((int)((90 + lat) / 10)+(int)'A');
	code[2] = (char)((int)((int)(lon + 180) % 20 / 2)+(int)'0');
	code[3] = (char)((int)(lat + 90) % 10+(int)'0');
	code[4] = (char)((int)((lon - (int)(lon / 2) * 2) * 60 / 5)+(int)'A');
	code[5] = (char)((int)((lat - (int)(lat)) * 60 / 2.5)+(int)'A');
	return code;
}
RMC rmc2data(char* str) {
	static RMC output;
	char buff[20] = {0};
	int i, j, count = 0, buffs = 0;
	for(i=0; i<strlen(str); i++) {
		if(str[i] != ',') {
			buff[count++] = str[i];
			buff[count] = '\0';
		} else {
			if(str[i-1] == ',' && i>=1) buff[0] = '\0';
			count = 0;
			switch(buffs++) {
				case 1:
					for(j=0; j<6; j++) output.UTC_TIME[j] = buff[j];
					break;
				case 2:
					output.valid = buff[0];
					break;
				case 3:
					output.lat = degree2format(atof(buff));
					break;
				case 4:
					if(buff[0] == 'S') output.lat = -output.lat;
					break;
				case 5:
					output.lon = degree2format(atof(buff));
					break;
				case 6:
					if(buff[0] == 'W') output.lon = -output.lon;
					break;
				case 7:
					output.speed = atof(buff);
					break;
				case 8:
					output.direction = atof(buff);
					break;
				case 9:
					for(j=0; j<6; j++) output.UTC_DATE[j] = buff[j];
					break;
			}

		}
	}
	output.UTC_TIME[6] = '\0';
	output.UTC_DATE[6] = '\0';
	return output;
}
#endif