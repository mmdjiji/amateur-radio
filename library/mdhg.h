/*
 * 通过经纬度获取梅登黑德格网编号
 * 用法: getCode(double lon, double lat)
 * 参数: lon是经度 lat是纬度 
 * 返回: 6个字节的字符数组 表示该位置的梅登海格网编号 
 * 作者: 吉吉(JiJi)
 * https://github.com/mmdjiji
 */
#ifndef _MDHG_H_
#define  _MDHG_H_
char* getCode(double lon, double lat) {
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
