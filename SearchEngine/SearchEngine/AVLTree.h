#ifndef AVLTREE
#define AVLTREE
#include"data structure.h"
#include<iostream>
using namespace std;


//文档链表节点
class docLinkNode
{
public:
	docLinkNode();
public:
	int docID;				//出现该单词的文档的ID
	int times;				//该单词在该文档中出现的次数
	docLinkNode *next;
};

//单词节点
class docWord
{
public:
	docWord();
	~docWord();
public:
	CharString term;		//单词
	int termID;				//单词ID
	int DF;					//单词出现在多少文章中
	int occur;				//单词总的出现次数
	docLinkNode* docLink;	//单词关联的文档链表的头节点
	
	void addLinkInfo(int docID);			//建立倒排文档并更新（1）搜索文档和（2）添加新的文档信息
	void LinkByTimes();						//此关键词后面的倒排文档按出现次数从大到小排序
	int getTimes(int docID);				//获得该单词在某个文档中出现的次数
	void modifyInfo(int docID, int times);	//修改该节点对应的某文档的信息
	void removeLinkNode(int docID);			 //删除某文档
};

//定义二叉平衡树节点类型
typedef struct node
{
    docWord a;								//平衡树节点中储存的单词信息
    int bf;									//增加的平衡因子
    struct node *lchild;				    //左孩子指针
    struct node *rchild;                    //右孩子指针
    node();
}AVLNode;

//平衡二叉树类定义
class AVLTree
{
public:
    AVLNode * root;
public:
	AVLTree();
public:
    //左平衡旋转情况处理
    void LeftAdjust(AVLNode *&p, int &taller);
    //右平衡旋转情况处理
    void RightAdjust(AVLNode *&p, int &taller);
    //向当前平衡二叉树插入一个元素
    int InsertNode(AVLNode *&b, CharString e, int &taller, AVLNode *&present);
	//在进行删除平衡二叉树的节点时候需要做相应的左平衡旋转处理
	void LeftAdjust1(AVLNode *&p, int &taller);
	//在进行删除平衡二叉树的节点时候需要做相应的右平衡旋转处理
	void RightAdjust1(AVLNode *&p, int &taller);
	 //用于被删除节点左右子树均不为空
	void Remove2(AVLNode *q, AVLNode *&r, int &taller);                           
	//删除平衡二叉树的节点
	int RemoveNode(AVLNode *&p, int x, int &taller);
	//递归查找实现搜索
    AVLNode* SearchAVLNode(AVLNode *&b, CharString n);
};

#endif