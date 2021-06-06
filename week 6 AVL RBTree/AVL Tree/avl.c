#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "avl.h"

//Ham them mot node co gia tri x vao cay AVL
node * insert(node *T,Jval x)
{
	if(T==NULL) // cay rong
	{
		T=(node*)malloc(sizeof(node));
		(T->key).s = NULL;
		copy_s(&(T->key),&x);
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(compare_s(x,T->key)>0)	
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)//can bang lai cay
				if(compare_s(x,T->right->key)>0)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(compare_s(x,T->key)<0)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)//can bang lai cay
					if(compare_s(x,T->left->key)<0)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}

//Xoa mot node trong cay AVL
node * Delete(node *T,Jval x)
{
	node *p; // khai bao node the mang de xoa trong truong hop node can xoa co ca right node va left node
            // Phan tu the mang co 2 cach chon:
            //1. Lon nhat ben nhanh trai
            //2. Nho nhat ben nhanh phai
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(compare_s(x,T->key)>0)// gia tri node can xoa lon hon node hien tai thi duyet sang phai
		{
			T->right=Delete(T->right,x);//de quy
			if(BF(T)==2)//can bang lai cay
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else//// gia tri node can xoa nho hon node hien tai thi duyet sang trai
			if(compare_s(x,T->key)<0)
			{
				T->left=Delete(T->left,x);
				if(BF(T)==-2)	//Sau khi xoa neu cay dang mat can bang nen can bang lai cay
					if(BF(T->right)<=0)// neu cay mat can bang phai-phai
						T=RR(T);//
					else//neu cay mat can bang phai-trai
						T=RL(T);
			}
			else//neu gia tri node can xoa bang T->key
			{
				
				if(T->right!=NULL)//neu T co right node
				{	
					p=T->right;
					
					while(p->left!= NULL)
						p=p->left;
					
					copy_s(&T->key,&p->key);//da thay xong gia tri node p cho T
					T->right=Delete(T->right,p->key);//Tien hanh xoa node p
					
					if(BF(T)==2)//Sau khi xoa can bang lai cay AVL
						if(BF(T->left)>=0)
							T=LL(T);
						else
							T=LR(T);
				}
				else//neu T ko co right node thi suy ra T co leftnode (la node la) hoac khong (do cay AVL)
					return(T->left);
			}
	T->ht=height(T);
	return(T);
}
 
int height(node *T)//ham tim chieu cao cua node T
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
 
node * rotateright(node *x)//ham quay phai node x
{
	node *y;
	y=x->left;
	x->left=y->right;
	y->right=x;
	x->ht=height(x);
	y->ht=height(y);
	return(y);
}
 
node * rotateleft(node *x)//Ham quay trai node x
{
	node *y;
	y=x->right;
	x->right=y->left;
	y->left=x;
	x->ht=height(x);
	y->ht=height(y);
	
	return(y);
}
 
node * RR(node *T)//can bang cay lech phai-phai
{
	T=rotateleft(T);//quay trai node T
	return(T);
}
 
node * LL(node *T)//can bang cay lech trai-trai
{
	T=rotateright(T);//quay phai node T
	return(T);
}
 
node * LR(node *T)//can bang cay lech trai-phai
{
	T->left=rotateleft(T->left);//quay trai node con trai cua T
	T=rotateright(T);//Quay phai node T
	
	return(T);
}
 
node * RL(node *T)//can bang cay lech phai-trai
{
	T->right=rotateright(T->right);//quay phai node con phai
	T=rotateleft(T);//quay trai node T
	return(T);
}

// cap nhat trang thai can bang sau khi dieu chinh
int BF(node *T)
{
	int lh,rh;//chieu cao node trai, node phai
	if(T==NULL)
		return(0);
    
    // kiem tra xem T co node con trai khong, neu co thi tang lh them +1
	if(T->left==NULL)
		lh=0;
	else 
		lh=1+T->left->ht;
    
    // kiem tra xem T co node con phai, neu co thi tang lh them +1
	if(T->right==NULL)
		rh=0;
	else
		rh=1+T->right->ht;
 
	return(lh-rh);// tra ve trang thai can bang cua cay 
}
 
void preorder(node *T)
{
	if(T!=NULL)
	{
		printf("%20s(Bf=%d)",(T->key).s,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}

// kiem tra xem tu do co trong tu dien khong
int containKey(node *T,Jval x)
{
	if(T==NULL) return 0;//khong ton tai khoa tren cay
	if(compare_s(T->key,x)==0) return 1;
	if(compare_s(T->key,x)>0) return containKey(T->left,x);
	else return containKey(T->right,x);
}

//tao cay moi va nap tu dien tu file
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
		
		Jval newData;
		newData.s = buffer;
	    root=insert(root,newData);
	}
	
	fclose(filePointer);

	return root;
}