/*
 * This file is storaged by UTF-8 encoding, if you cannot load it normally, try to transform it to ANSI.
 * GPSLIB.H v1.0 
 * 作者: 吉吉(JiJi)
 * https://github.com/mmdjiji
 * 
 * 解析GPS芯片的经纬度
 * 用法: gps2data(char* str)
 * 参数: str是一个字符串 例如 char str[] = "3954.43158,N,11623.48816,E";
 * 返回: 一个double类型的数组 数组下标0是转换后的纬度 数组下标1是转换后的经度 一般取6位小数
 * 
 * 通过经纬度获取梅登黑德格网编号
 * 用法: getCode(double lat, double lon)
 * 参数: lat是纬度 lon是经度
 * 返回: 6个字节的字符数组 表示该位置的梅登海格网编号 
 */
#ifndef _GPSLIB_H_
#define  _GPSLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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
	double lat,lon;
	char oflat,oflon;
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
	if(lon<0)lon+=360;if(lat<0)lat+=180;
	static char code[6];
	code[0] = (char)((int)((180 + lon) / 20)+(int)'A');
	code[1] = (char)((int)((90 + lat) / 10)+(int)'A');
	code[2] = (char)((int)((int)(lon + 180) % 20 / 2)+(int)'0');
	code[3] = (char)((int)(lat + 90) % 10+(int)'0');
	code[4] = (char)((int)((lon - (int)(lon / 2) * 2) * 60 / 5)+(int)'A');
	code[5] = (char)((int)((lat - (int)(lat)) * 60 / 2.5)+(int)'A');
	return code;
}
#endif