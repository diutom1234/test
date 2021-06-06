#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct node
{	char key[20];
	struct node *left,*right;
	int ht;
}node;

int containKey(node *,char*); // kiem tra xem key co ton tai
node *insert(node *,char*);
node *Delete(node *,char*);
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
 
int main()
{
	
	node *root=NULL;
	int n,i,op;
	char x[20];
	
	root = loadDict();
	do
	{
		printf("\nEnter a key:");
		fflush(stdin);
		gets(x);
		if(containKey(root,x)==0)
			printf("%s KHONG co trong tu dien!\n",x);
		else
			printf("%s la tu dung!\n",x);
	}
	while(1);
	
	return 0;
}
 
node * insert(node *T,char* x)
{
	if(T==NULL) // cay rong
	{
		T=(node*)malloc(sizeof(node));
		strcpy(T->key,x);
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(strcmp(x,T->key)>0)		// insert in right subtree
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)
				if(strcmp(x,T->right->key)>0)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(strcmp(x,T->key)<0)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)
					if(strcmp(x,T->left->key)<0)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}
 
node * Delete(node *T,char* x)
{
	node *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(strcmp(x,T->key)>0)		// insert in right subtree
		{
			T->right=Delete(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(strcmp(x,T->key)<0)
			{
				T->left=Delete(T->left,x);
				if(BF(T)==-2)	//Rebalance during windup
					if(BF(T->right)<=0)
						T=RR(T);
					else
						T=RL(T);
			}
			else
			{
				//data to be deleted is found
				if(T->right!=NULL)
				{	//delete its inorder succesor
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					strcpy(T->key,p->key);
					T->right=Delete(T->right,p->key);
					
					if(BF(T)==2)//Rebalance during windup
						if(BF(T->left)>=0)
							T=LL(T);
						else
							T=LR(T);
				}
				else
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
 
int height(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
	
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
		
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
	
	if(lh>rh)
		return(lh);
	
	return(rh);
}
 
node * rotateright(node *x)
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
 
node * rotateleft(node *x)
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	
	return(y);
}
 
node * RR(node *T)
{
	T=rotateleft(T);
	return(T);
}
 
node * LL(node *T)
{
	T=rotateright(T);
	return(T);
}
 
node * LR(node *T)
{
	T->left=rotateleft(T->left);
	T=rotateright(T);
	
	return(T);
}
 
node * RL(node *T)
{
	T->right=rotateright(T->right);
	T=rotateleft(T);
	return(T);
}
 
int BF(node *T)
{
	int lh,rh;
	if(T==NULL)
		return(0);
 
	if(T->left==NULL)
		lh=0;
	else
		lh=1+T->left->ht;
 
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);
}
 
void preorder(node *T)
{
	if(T!=NULL)
	{
		printf("%20s(Bf=%d)",T->key,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}
 
void inorder(node *T)
{
	if(T!=NULL)
	{
		inorder(T->left);
		printf("%20s(Bf=%d)",T->key,BF(T));
		inorder(T->right);
	}
}

// kiem tra xem tu do co trong tu dien khong
int containKey(node *T,char* x)
{
	if(T==NULL) return 0;//khong ton tai khoa tren cay
	if(strcmp(T->key,x)==0) return 1;
	if(strcmp(T->key,x)>0) return containKey(T->left,x);
	else return containKey(T->right,x);
}

node *loadDict()
{
	node * root=NULL;
	FILE* filePointer;
	int bufferLength = 255;
	char buffer[bufferLength];
	
	filePointer = fopen("words.txt", "r");
	while(fgets(buffer, bufferLength, filePointer)) 
	{		
		buffer[strlen(buffer)-1] = '\0';
	    //printf("%s\n", buffer);
	    for(int i = 0; buffer[i]; i++){
		  buffer[i] = tolower(buffer[i]);
		}
	    root=insert(root,buffer);
	}
	
	fclose(filePointer);

	return root;
}