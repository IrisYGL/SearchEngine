#ifndef AVLTREE
#define AVLTREE
#include"data structure.h"
#include<iostream>
using namespace std;


//�ĵ�����ڵ�
class docLinkNode
{
public:
	docLinkNode();
public:
	int docID;				//���ָõ��ʵ��ĵ���ID
	int times;				//�õ����ڸ��ĵ��г��ֵĴ���
	docLinkNode *next;
};

//���ʽڵ�
class docWord
{
public:
	docWord();
	~docWord();
public:
	CharString term;		//����
	int termID;				//����ID
	int DF;					//���ʳ����ڶ���������
	int occur;				//�����ܵĳ��ִ���
	docLinkNode* docLink;	//���ʹ������ĵ������ͷ�ڵ�
	
	void addLinkInfo(int docID);			//���������ĵ������£�1�������ĵ��ͣ�2������µ��ĵ���Ϣ
	void LinkByTimes();						//�˹ؼ��ʺ���ĵ����ĵ������ִ����Ӵ�С����
	int getTimes(int docID);				//��øõ�����ĳ���ĵ��г��ֵĴ���
	void modifyInfo(int docID, int times);	//�޸ĸýڵ��Ӧ��ĳ�ĵ�����Ϣ
	void removeLinkNode(int docID);			 //ɾ��ĳ�ĵ�
};

//�������ƽ�����ڵ�����
typedef struct node
{
    docWord a;								//ƽ�����ڵ��д���ĵ�����Ϣ
    int bf;									//���ӵ�ƽ������
    struct node *lchild;				    //����ָ��
    struct node *rchild;                    //�Һ���ָ��
    node();
}AVLNode;

//ƽ��������ඨ��
class AVLTree
{
public:
    AVLNode * root;
public:
	AVLTree();
public:
    //��ƽ����ת�������
    void LeftAdjust(AVLNode *&p, int &taller);
    //��ƽ����ת�������
    void RightAdjust(AVLNode *&p, int &taller);
    //��ǰƽ�����������һ��Ԫ��
    int InsertNode(AVLNode *&b, CharString e, int &taller, AVLNode *&present);
	//�ڽ���ɾ��ƽ��������Ľڵ�ʱ����Ҫ����Ӧ����ƽ����ת����
	void LeftAdjust1(AVLNode *&p, int &taller);
	//�ڽ���ɾ��ƽ��������Ľڵ�ʱ����Ҫ����Ӧ����ƽ����ת����
	void RightAdjust1(AVLNode *&p, int &taller);
	 //���ڱ�ɾ���ڵ�������������Ϊ��
	void Remove2(AVLNode *q, AVLNode *&r, int &taller);                           
	//ɾ��ƽ��������Ľڵ�
	int RemoveNode(AVLNode *&p, int x, int &taller);
	//�ݹ����ʵ������
    AVLNode* SearchAVLNode(AVLNode *&b, CharString n);
};

#endif