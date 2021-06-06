#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "avl.h"

node * insert(node *T,Jval x){
	if(T==NULL) // cay rong
	{
		T=(node*)malloc(sizeof(node));
		(T->key).s = NULL;
		copy_s(&(T->key),&x);
		T->left=NULL;
		T->right=NULL;
	}
	else
		if(compare_s(x,T->key)>0)		// insert in right subtree
		{
			T->right=insert(T->right,x);
			if(BF(T)==-2)
				if(compare_s(x,T->right->key)>0)
					T=RR(T);
				else
					T=RL(T);
		}
		else
			if(compare_s(x,T->key)<0)
			{
				T->left=insert(T->left,x);
				if(BF(T)==2)
					if(compare_s(x,T->left->key)<0)
						T=LL(T);
					else
						T=LR(T);
			}
		
		T->ht=height(T);
		
		return(T);
}
 
node * Delete(node *T,Jval x){
	node *p;
	
	if(T==NULL)
	{
		return NULL;
	}
	else
		if(compare_s(x,T->key)>0)		// insert in right subtree
		{
			T->right=Delete(T->right,x);
			if(BF(T)==2)
				if(BF(T->left)>=0)
					T=LL(T);
				else
					T=LR(T);
		}
		else
			if(compare_s(x,T->key)<0)
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
					
					copy_s(&T->key,&p->key);
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
		printf("%20s(Bf=%d)",(T->key).s,BF(T));
		preorder(T->left);
		preorder(T->right);
	}
}

// kiem tra xem tu do co trong tu dien khong
int containKey(node *T,Jval x){
	if(T==NULL) return 0;//khong ton tai khoa tren cay
	if(compare_s(T->key,x)==0) return 1;
	if(compare_s(T->key,x)>0) return containKey(T->left,x);
	else return containKey(T->right,x);
}

node *loadDict(){
	node * root=NULL;
	FILE* filePointer;
	int bufferLength = 255;
	char buffer[bufferLength];
	
	filePointer = fopen("words", "r");
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