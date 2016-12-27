#include "AVLTree.h"


docWord::docWord()
{
	this->DF = 0;
	this->termID = -1;
	this->occur = 0;
	this->docLink = NULL;   //其关联的文档链表初始化为空
}

docWord::~docWord()
{
	docLinkNode *p, *q;
	p = q = this->docLink;	//删除其关联的整条文档链表
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

void docWord::addLinkInfo(int ID) //建立倒排文档并更新（1）搜索文档和（2）添加新的文档信息
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

void docWord::LinkByTimes() //按出现次数排序
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

//左平衡旋转情况处理
void AVLTree::LeftAdjust(AVLNode *&p, int &taller)
{
	AVLNode *p1, *p2;
	if (p->bf == 0)                                //当左右子树等高时插入使树高度增加
	{
		p->bf = 1;
		taller = 1;								   //所以平衡因子置为1，高度为1
	}
	else if (p->bf == -1)						   //当右子树比左子树高，插入后左右子树等高
	{
		p->bf = 0;
		taller = 0;                                //所以平衡因子置为0，高度为0
	}
	else                                           //当左子树比右子树高时插入则需做左平衡处理
	{
		p1 = p->lchild;
		if (p1->bf == 1)                           //当插入到左孩子的左子树上时需做LL处理
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = p1->bf = 0;
			p = p1;
		}
		else if (p1->bf == -1)                     //当插入到左孩子的右子树上时需做LR处理
		{
			p2 = p1->rchild;
			p1->rchild = p2->lchild;
			p2->lchild = p1;
			p->lchild = p2->rchild;
			p2->rchild = p;
			p = p2;								   //将p指向新的根节点，并置bf的值为0
			p->bf = 0;
		}
		taller = 0;
	}
}

//右平衡旋转情况处理,类似左平衡旋转处理
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

//向当前平衡二叉树插入一个元素
int AVLTree::InsertNode(AVLNode *&b, CharString e, int &taller, AVLNode *&present)
{
	if (b == NULL)                                               //当b为空树时进行动态分配等待插入新元素
	{
		b = new(AVLNode);
		b->a.term = e;
		b->lchild = b->rchild = NULL;
		b->bf = 0;                                                //将平衡因子置为 0
		taller = 1;                                               //将该节点的高度置为 1
		present = b;
	}
	else
	{
		if (e == b->a.term)                                       //如果树中已经存在该点，则无需插入
		{
			taller = 0;
			present = b;
			return 0;
		}
		if (e < b->a.term)                                         //如果待插入的数小于该节点，则往它左孩子插入
		{
			if ((InsertNode(b->lchild, e, taller, present)) == 0)
			{
				return 0;
			}
			if (taller == 1)									   //若该节点的高度为1，插入后增1，则会破坏平衡
				LeftAdjust(b, taller);							   //破坏后进行左平衡旋转处理重新达到平衡
		}
		else                                                        //否则往它右孩子插入
		{
			if ((InsertNode(b->rchild, e, taller, present)) == 0)
			{
				return 0;
			}
			if (taller == 1)										//若该节点的高度为1，插入后增1，则会破坏平衡
				RightAdjust(b, taller);							//破坏后进行右平衡旋转处理重新达到平衡
		}
	}
	return 1;
}

//在进行删除平衡二叉树的节点时候需要做相应的左平衡旋转处理
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
		p1 = p->rchild;										//RR处理
		if (p1->bf == 0)
		{
			p->rchild = p1->lchild;
			p1->rchild = p;
			p1->bf = 1;
			p->bf = -1;
			p = p1;
			taller = 0;
		}
		else if (p1->bf == -1)							  //RR处理
		{
			p->rchild = p1->lchild;
			p1->lchild = p;
			p->bf = p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else											   //RL处理
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

//在进行删除平衡二叉树的节点时候需要做相应的右平衡旋转处理
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
	else													 //LL处理
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
		else if (p1->bf == 1)						    //LL处理
		{
			p->lchild = p1->rchild;
			p1->rchild = p;
			p->bf = p1->bf = 0;
			p = p1;
			taller = 1;
		}
		else                                             //LR处理
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

void AVLTree::Remove2(AVLNode *q, AVLNode *&r, int &taller)     //用于被删除节点左右子树均不为空
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

//删除平衡二叉树的节点
int AVLTree::RemoveNode(AVLNode *&p, int x, int &taller)
{
	int k;
	AVLNode *q;
	if (p == NULL)                                                //如果为空树，则正常退出
		return 0;
	else if (x < p->a.termID)                                     //如果待删除的节点小于该节点，则往它左孩子寻找
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
		if (p->rchild == NULL)                                //被删节点右子树为空
		{
			p = p->lchild;
			free(q);
			taller = 1;
		}
		else if (p->rchild == NULL)                            //被删节点左子树为空
		{
			p = p->lchild;
			free(q);
			taller = 1;
		}
		else                                                    //被删节点左右子树均不为空,调用Remove2
		{
			Remove2(q, q->lchild, taller);
			if (taller == 1)
				LeftAdjust1(q, taller);
			p = q;
		}
		return 1;
	}
}

//递归查找实现搜索
AVLNode* AVLTree::SearchAVLNode(AVLNode *&b, CharString n)
{
	if (!b)
		return nullptr;
	else if (n == b->a.term)
		return b;													//找到了就返回此节点
	else if (n < b->a.term)
		return SearchAVLNode(b->lchild, n);						    //如果小于则继续在其左孩子中查找
	else
		return SearchAVLNode(b->rchild, n);                         //否则就到右孩子中查找
}