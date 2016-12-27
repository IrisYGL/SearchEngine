#ifndef INVERTEDDOC
#define INVERTEDDOC
#include "AVLTree.h"
#include "data structure.h"

int getDocID(CharString filename);		//����ļ�����Ӧ��ID
AVLTree* divide(AVLTree* tree, CharString s, CharStringLink * dic, CharString rootPath, CharString filename, int * maxWordLength);	
//���ķִʲ������ֵĴʹ���ƽ���������ͬʱ���������ĵ�


#endif