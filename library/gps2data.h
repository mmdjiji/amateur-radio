/*
 * 解析GPS芯片的经纬度 
 * 用法: gps2data(char* str)
 * 参数: str是一个字符串 例如 char str[] = "3940.46761,N,11602.48621S,E"; 
 * 返回: 一个double类型的数组 数组下标0是转换后的纬度 数组下标1是转换后的经度 一般取6位小数 
 * 作者: 吉吉(JiJi)
 * https://github.com/mmdjiji
 */
#ifndef _GPS2DATA_H_
#define _GPS2DATA_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
double degree2format(double value){
	int negative = 0;
	if(value < 0){
		negative = 1;
		value = -value;
	}
	int du = floor(value / 100);
	double fen = value - du*100;
	if(negative)du=-du;
	return du + (fen/60);
}
double* gps2data(char* str){
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
#endif
