#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

int string_compare_case(void const *str1, void const *str2)
{
    char *s1, *s2;
	s1 = (char*)str1; // ep ve kieu xau
	s2 = (char*)str2; 
	return strcmp(s1,s2);
}

int string_compare_nocase(void const *str1, void const *str2)
{
	int d;
    char *s1, *s2;
	s1 = (char*)str1; // ep ve kieu xau
	s2 = (char*)str2; 
	for (;; s1++, s2++) {
        d = tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        if (d != 0 || !*s1)
            return d>0?1:(d<0?-1:0);
    }
}
void doicho(void *buff,int first,int last, int t_size){
    char* temp1 = (char*)buff+(t_size*first);
    char* temp2 = (char*)buff+(t_size*last);
    void *s = malloc(t_size) ;
    memcpy(s,temp1,t_size);
    memcpy(temp1,temp2,t_size);
    memcpy(temp2,s,t_size);
    free(s);
}
//
void quicksort(void *buff,int first,int last, int (*compare)(void const *,void const *), int t_size)
{
    int i, j, pivot;
    if(first<last){
		pivot=first;
        i=first;
        j=last;
        while(i<j){
			while((compare((char*)buff + i*t_size,(char*)buff +pivot*t_size))<=0 && i<last)
				i++;
			while((compare((char*)buff + j*t_size,(char*)buff +pivot*t_size))>0)
				j--;
			// swap phan tu
			if(i<j) doicho(buff,i,j,t_size);
		}
    doicho(buff,pivot,j,t_size);
    quicksort(buff,first,j-1, compare, t_size);
    quicksort(buff,j+1,last,compare, t_size);
    }
}
int main(){
    char namelist[][30] = {"iPhone","Apple","apple","Samsung","Google","Facebook","Xiaomi","Huwei"};
    printf ("\nCo phan biet hoa/thuong:\n");
    quicksort(namelist,0,7,string_compare_case,sizeof(namelist[0]));
    for (int i=0;i<8;i++)
        printf ("%s\t",namelist[i]);
	
	printf ("\nKhong phan biet hoa/thuong:\n");
    quicksort(namelist,0,7,string_compare_nocase,sizeof(namelist[0]));
    for (int i=0;i<8;i++)   
        printf ("%s\t",namelist[i]);
	return 0;
}

