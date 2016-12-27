#ifndef INVERTEDDOC
#define INVERTEDDOC
#include "AVLTree.h"
#include "data structure.h"

int getDocID(CharString filename);		//获得文件名对应的ID
AVLTree* divide(AVLTree* tree, CharString s, CharStringLink * dic, CharString rootPath, CharString filename, int * maxWordLength);	
//中文分词并用所分的词构建平衡二叉树，同时建立倒排文档


#endif