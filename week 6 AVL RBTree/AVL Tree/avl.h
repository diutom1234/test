#include "data.h"

typedef struct AVLNODE
{	Jval key; // dung truong con tro *s trong jVal
	struct AVLNODE *left,*right;
	int ht;
}node;


int containKey(node *,Jval); // kiem tra xem key co ton tai
node *insert(node *,Jval); //them mot node vao cay AVL
node *Delete(node *,Jval); // xoa mot node cua cay AVL
void preorder(node *);
void inorder(node *);
int height( node *);
node *loadDict(); // tao cay moi va nap tu dien tu file

node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);

int BF(node *); // cap nhat trang thai can bang sau khi dieu chinh