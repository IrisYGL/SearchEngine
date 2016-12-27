#ifndef FUNCTION_H
#define FUNCTION_H

#include "data structure.h"

void ReadHtml(CharString filename, CharString & s);														//��ȡhtml�ļ�
CharString AnalyseHtml(CharString & fs, CharString & rootPath, CharString & filename);				//��ҳ����
unsigned int hash_func(CharString s);															//�ù�ϣ���������ַ�����Ӧ�Ĺ�ϣ���е�λ��
CharStringLink * ReadDic(CharString & filename, int * maxWordLength);													//�ʿ�Ķ���
bool hash_find(CharString & s, CharStringLink * dic);												//�ڴʿ��в��ҵ����Ƿ����
CharStringLink ReadQuery(CharString & filename);

#endif