#ifndef FUNCTION_H
#define FUNCTION_H

#include "data structure.h"

void ReadHtml(CharString filename, CharString & s);														//读取html文件
CharString AnalyseHtml(CharString & fs, CharString & rootPath, CharString & filename);				//网页解析
unsigned int hash_func(CharString s);															//用哈希函数生成字符串对应的哈希表中的位置
CharStringLink * ReadDic(CharString & filename, int * maxWordLength);													//词库的读入
bool hash_find(CharString & s, CharStringLink * dic);												//在词库中查找单词是否存在
CharStringLink ReadQuery(CharString & filename);

#endif