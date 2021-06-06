#include "data.h"
#include <string.h>
#include <stdlib.h>
extern int compare_s(Jval j1, Jval j2)
{
	return strcmp(j1.s, j2.s);
}

//jtarget la bien can gan gia tri
//jsource la noi copy gia tri
extern void copy_s(Jval* jtarget, const Jval* jsource)
{
	if((jtarget->s)!=NULL) // neu da duoc gan gia tri
		free(jtarget->s);//giai phong bo nho
		
	// cap phat lai vung nho moi
	jtarget->s = (char*)malloc((strlen(jsource->s)+1)*sizeof(char));
	strcpy(jtarget->s, jsource->s);
}