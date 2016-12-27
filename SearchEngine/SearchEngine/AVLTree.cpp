#include "AVLTree.h"


docWord::docWord()
{
	this->DF = 0;
	this->termID = -1;
	this->occur = 0;
	this->docLink = NULL;   //��������ĵ������ʼ��Ϊ��
}

docWord::~docWord()
{
	docLinkNode *p, *q;
	p = q = this->docLink;	//ɾ��������������ĵ�����
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q;
	}
}

docLinkNode::docLinkNode()
{
	this->docID = -1;
	this->times = 0;
	this->next = NULL;
}

void docWord::addLinkInfo(int ID) //���������ĵ������£�1�������ĵ��ͣ�2������µ��ĵ���Ϣ
{
	docLinkNode *p, *q;
	p = this->docLink;
	if (p == NULL)
	{
		this->docLink = new docLinkNode();
		this->docLink->docID = ID;
		this->docLink->times++;
		this->DF++;
		return;
	}
	while (p->next != NULL)
	{
		if (p->docID == ID)
		{
			p->times++;
			int tempID, tempTimes;
			p = this->docLink;
			while (p->next != NULL)
			{
				q = p->next;
				if (q->times > p->times)
				{
					tempTimes = q->times;
					tempID = q->docID;
					q->times = p->times;
					q->docID = p->docID;
					p->times = tempTimes;
					p->docID = tempID;
				}
				p = p->next;
			}
			return;
		}
		p = p->next;
	}
	if (p->docID == ID)
	{
		p->times++;
		int tempID, tempTimes;
		p = this->docLink;
		while (p->next != NULL)
		{
			q = p->next;
			if (q->times > p->times)
			{
				tempTimes = q->times;
				tempID = q->docID;
				q->times = p->times;
				q->docID = p->docID;
				p->times = tempTimes;
				p->docID = tempID;
			}
			p = p->next;
		}
		return;
	}
	q = new docLinkNode();
	q->docID = ID;
	q->times++;
	p->next = q;
	this->DF++;
	return;
}

void docWord::LinkByTimes() //�����ִ�������
{
	for (docLinkNode *p = docLink; p->next != nullptr; p = p->next)
	{
		for (docLinkNode *q = p->next; q != nullptr; q = q->next)
		{
			if (p->times < q->times)
			{
				int temp;
				temp = q->times;
				q->times = p->times;
				p->times = temp;
				temp = q->docID;
				q->docID = p->docID;
				p->docID = temp;
			}
		}
	}
}
int docWord::getTimes(int ID)
{
	docLinkNode *p;
	p = this->docLink;
	while (p != NULL)
	{
		if (p->docID == ID)
		{
			return p->times;
		}
		p = p->next;
	}
	return -1;
}

void docWord::modifyInfo(int ID, int times)
{
	docLinkNode *p;
	p = this->docLink;
	while (p != NULL)
	{
		if (p->docID == ID)
		{
			p->times = times;
		}
		p = p->next;
	}
	return;
}

void docWord::removeLinkNode(int ID)
{
	docLinkNode *p, *q;
	p = this->docLink;
	q = p;
	while (p != NULL)
	{
		if (p->docID == ID)
		{
			if(p->next == nullptr)
			{
				q->next = nullptr;
			}
			else
			{
				q->next = p->next;
			}
		}
		q = p;
		p = p->next;
	}
	return;
}

node::node()
{
	lchild = nullptr;
	rchild = nullptr;
}

AVLTree::AVLTree()
	: root(nullptr)
{
}

//��ƽ����ת�������
void AVLTree::LeftAdjust(AVLNode *&p, int &taller)
{
	AVLNode *p1, *p2;
	if (p->bf == 0)                                //�����������ȸ�ʱ����ʹ���߶�����
	{
		p->bf = 1;
		taller = 1;								   //����ƽ��������Ϊ1���߶�Ϊ1
	}
	else if (p->bf == -1)						   //�����������������ߣ���������������ȸ�
	{
		p->bf = 0;
		taller = 0;                                //����ƽ��������Ϊ0���߶�Ϊ0
	}
	else                                           //������������������ʱ������������ƽ�⴦��
	{
		p1 = p->lchild;
		if (p1->bf == 1)                           //�����뵽���ӵ���������ʱ����LL����
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = p1->bf = 0;
			p = p1;
		}
		else if (p1->bf == -1)                     //�����뵽���ӵ���������ʱ����LR����
		{
			p2 = p1->rchild;
			p1->rchild = p2->lchild;
			p2->lchild = p1;
			p->lchild = p2->rchild;
			p2->rchild = p;
			p = p2;								   //��pָ���µĸ��ڵ㣬����bf��ֵΪ0
			p->bf = 0;
		}
		taller = 0;
	}
}

//��ƽ����ת�������,������ƽ����ת����
void AVLTree::RightAdjust(AVLNode *&p, int &taller)
{
	AVLNode *p1, *p2;
	if (p->bf == 0)
	{
		p->bf = -1;
		taller = 1;
	}
	else if (p->bf == 1)
	{
		p->bf = 0;
		taller = 0;
	}
	else
	{
		p1 = p->rchild;
		if (p1->bf == -1)
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p->bf = p1->bf = 0;
			p = p1;
		}
		else if (p1->bf == 1)
		{
			p2 = p1->lchild;
			p1->lchild = p2->rchild;
			p2->rchild = p1;
			p->rchild = p2->lchild;
			p2->lchild = p;
			p = p2;
			p->bf = 0;
		}
		taller = 0;
	}
}

//��ǰƽ�����������һ��Ԫ��
int AVLTree::InsertNode(AVLNode *&b, CharString e, int &taller, AVLNode *&present)
{
	if (b == NULL)                                               //��bΪ����ʱ���ж�̬����ȴ�������Ԫ��
	{
		b = new(AVLNode);
		b->a.term = e;
		b->lchild = b->rchild = NULL;
		b->bf = 0;                                                //��ƽ��������Ϊ 0
		taller = 1;                                               //���ýڵ�ĸ߶���Ϊ 1
		present = b;
	}
	else
	{
		if (e == b->a.term)                                       //��������Ѿ����ڸõ㣬���������
		{
			taller = 0;
			present = b;
			return 0;
		}
		if (e < b->a.term)                                         //������������С�ڸýڵ㣬���������Ӳ���
		{
			if ((InsertNode(b->lchild, e, taller, present)) == 0)
			{
				return 0;
			}
			if (taller == 1)									   //���ýڵ�ĸ߶�Ϊ1���������1������ƻ�ƽ��
				LeftAdjust(b, taller);							   //�ƻ��������ƽ����ת�������´ﵽƽ��
		}
		else                                                        //���������Һ��Ӳ���
		{
			if ((InsertNode(b->rchild, e, taller, present)) == 0)
			{
				return 0;
			}
			if (taller == 1)										//���ýڵ�ĸ߶�Ϊ1���������1������ƻ�ƽ��
				RightAdjust(b, taller);							//�ƻ��������ƽ����ת�������´ﵽƽ��
		}
	}
	return 1;
}

//�ڽ���ɾ��ƽ��������Ľڵ�ʱ����Ҫ����Ӧ����ƽ����ת����
void AVLTree::LeftAdjust1(AVLNode *&p, int &taller)
{
	AVLNode *p1, *p2;
	if (p->bf == 1)
	{
		p->bf = 0;
		taller = 1;
	}
	else if (p->bf == 0)
	{
		p->bf = -1;
		taller = 0;
	}
	else
	{
		p1 = p->rchild;										//RR����
		if (p1->bf == 0)
		{
			p->rchild = p1->lchild;
			p1->rchild = p;
			p1->bf = 1;
			p->bf = -1;
			p = p1;
			taller = 0;
		}
		else if (p1->bf == -1)							  //RR����
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p->bf = p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else											   //RL����
		{
			p2 = p1->lchild;
			p1->lchild = p2->rchild;
			p2->rchild = p1;
			p->rchild = p2->lchild;
			p2->lchild = p;
			p2->bf = 0;
			p = p2;
			taller = 1;
		}
	}
}

//�ڽ���ɾ��ƽ��������Ľڵ�ʱ����Ҫ����Ӧ����ƽ����ת����
void AVLTree::RightAdjust1(AVLNode *&p, int &taller)
{
	AVLNode *p1, *p2;
	if (p->bf == -1)
	{
		p->bf = 0;
		taller = -1;
	}
	else if (p->bf == 0)
	{
		p->bf = 1;
		taller = 0;
	}
	else													 //LL����
	{
		p1 = p->lchild;
		if (p1->bf == 0)
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = -1;
			p1->bf = 1;
			p = p1;
			taller = 0;
		}
		else if (p1->bf == 1)						    //LL����
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else                                             //LR����
		{
			p2 = p1->rchild = p2->lchild;
			p2->lchild = p1;
			p->lchild = p2->rchild;
			p2->rchild = p;
			p2->bf = 0;
			p = p2;
			taller = 1;
		}
	}
}

void AVLTree::Remove2(AVLNode *q, AVLNode *&r, int &taller)     //���ڱ�ɾ���ڵ�������������Ϊ��
{
	if (r->rchild == NULL)
	{
		q->a.termID = r->a.termID;
		q = r;
		r = r->lchild;
		free(q);
		taller = 1;
	}
	else
	{
		Remove2(q, r->rchild, taller);
		if (taller == 1)
			RightAdjust(r, taller);
	}
}

//ɾ��ƽ��������Ľڵ�
int AVLTree::RemoveNode(AVLNode *&p, int x, int &taller)
{
	int k;
	AVLNode *q;
	if (p == NULL)                                                //���Ϊ�������������˳�
		return 0;
	else if (x < p->a.termID)                                     //�����ɾ���Ľڵ�С�ڸýڵ㣬����������Ѱ��
	{
		k = RemoveNode(p->lchild, x, taller);
		if (taller == 1)
			LeftAdjust(p, taller);
		return k;
	}
	else if (x > p->a.termID)
	{
		k = RemoveNode(p->rchild, x, taller);
		if (taller == 1)
			RightAdjust1(p, taller);
		return k;
	}
	else
	{
		q = p;
		if (p->rchild == NULL)                                //��ɾ�ڵ�������Ϊ��
		{
			p = p->lchild;
			free(q);
			taller = 1;
		}
		else if (p->rchild == NULL)                            //��ɾ�ڵ�������Ϊ��
		{
			p = p->lchild;
			free(q);
			taller = 1;
		}
		else                                                    //��ɾ�ڵ�������������Ϊ��,����Remove2
		{
			Remove2(q, q->lchild, taller);
			if (taller == 1)
				LeftAdjust1(q, taller);
			p = q;
		}
		return 1;
	}
}

//�ݹ����ʵ������
AVLNode* AVLTree::SearchAVLNode(AVLNode *&b, CharString n)
{
	if (!b)
		return nullptr;
	else if (n == b->a.term)
		return b;													//�ҵ��˾ͷ��ش˽ڵ�
	else if (n < b->a.term)
		return SearchAVLNode(b->lchild, n);						    //���С����������������в���
	else
		return SearchAVLNode(b->rchild, n);                         //����͵��Һ����в���
}