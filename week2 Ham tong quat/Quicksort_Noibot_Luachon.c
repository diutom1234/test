#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// n là s? lu?ng ph?n t? c?n sinh
// Hàm sinh và tr? v? m?ng c?p phát d?ng ch?a n ph?n t?
	

int* generateArray(int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n;i++)
        list[i] = rand();
    return list;
}


// hàm t?o ra 1 m?ng copy c?a m?ng ban d?u (c?p phát d?ng)
int* copyArray(int* source, int n)
{
    int* list = (int*)malloc(n*sizeof(int));
    for(int i=0; i<n;i++)
        list[i] = source[i];
    return list;
}

int int_compare(void const* x, void const *y) {
	int m, n;
	m = *((int*)x); // ep ve kieu so nguyen
	n = *((int*)y); 
	if ( m == n ) return 0;
	return m > n? 1: -1;
}

int double_compare(void const* x, void const *y) {
	int m, n;
	m = *((double*)x); // ep ve kieu so nguyen
	n = *((double*)y); 
	if ( m == n ) return 0;
	return m > n? 1: -1;
}

void swap(void* a, void *b, int size)
{
    void *tmp = malloc(size);
    memcpy(tmp,a, size) ;
    memcpy(a,b, size) ;
    memcpy(b,tmp, size) ;
}

// m?ng d?u vào number
// kích thu?c 1 ph?n t? t_size
// hàm so sánh compare
void quicksort(void *number,int first,int last, int (*compare)(void const *,void const *), int t_size)
{
   int i, j, pivot;
   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(compare((char*)number + i*t_size,(char*)number +pivot*t_size)==-1&&i<last)
            i++;
         while(compare((char*)number + j*t_size,(char*)number +pivot*t_size)==1)
            j--;
        // swap phan tu
         if(i<j){
             swap((char*)number + i*t_size,(char*)number + j*t_size, t_size);
         }
      }
      swap((char*)number + j*t_size,(char*)number + pivot*t_size, t_size);

      quicksort(number,first,j-1, compare, t_size);
      quicksort(number,j+1,last,compare, t_size);
   }
}

void printArr(int *list, int n)
{
    for (int i=0; i<n ;i++)
        printf("%d, ",list[i]);
    
    printf("\n");
}

//hàm s?p x?p n?i b?t
void bubblesort(void *number, int n, int (*compare)(void const *,void const *), int t_size)
{
    for(int i=n; i>1; i--)
        for(int j=1;j<i; j++)
        {
            if(compare((char*)number + (j-1)*t_size,(char*)number +j*t_size)==1)//number[j-1]> number[j]
                swap((char*)number + (j-1)*t_size,(char*)number + j*t_size, t_size);
        }
}

// hàm s?p x?p l?a ch?n
void selectionsort(void *number, int n, int (*compare)(void const *,void const *), int t_size)
{
    for(int i=n; i>1; i--)
    {
        int vtmax = 0;
        for(int j=1; j<i; j++)
            if(compare((char*)number + j*t_size,(char*)number +vtmax*t_size)==1)//list[j]>list[vtmax]
                vtmax = j; 
        swap((char*)number + (i-1)*t_size,(char*)number + vtmax*t_size, t_size);
    }
}
int main()
{
    const int n=10; 
    double time_spent = 0.0;
    
    printf("So luong phan tu n=%d\n",n);
    clock_t begin = clock();
    int *source = generateArray(n);
    clock_t end = clock();
    // calculate elapsed time by finding difference (end - begin) and
	// divide by CLOCKS_PER_SEC to convert to seconds
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Sinh mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
	
	
    int *copy1, *copy2, *copy3;
    
    begin = clock();
    copy1 = copyArray(source, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Copy mang mat thoi gian la %f micro seconds\n", time_spent*1e6);
    copy2 = copyArray(source, n);
    copy3 = copyArray(source, n);
    
    printf("Sap xep noi bot: \n");
    printArr(copy1,n);
    begin = clock();
    bubblesort(copy1,n,int_compare,sizeof(int));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep noi bot mat thoi gian la %f micro seconds\n", time_spent*1e6);
    printArr(copy1,n);
    
    printf("Sap xep lua chon: \n");
    printArr(copy2,n);
    begin = clock();
    bubblesort(copy2,n,int_compare,sizeof(int));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep lua chon mat thoi gian la %f micro seconds\n", time_spent*1e6);
    printArr(copy2,n);
    
    printf("Sap xep QuickSort: \n");
    printArr(copy3,n);
    begin = clock();
    quicksort(copy3,0,n-1, int_compare,sizeof(int));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort mat thoi gian la %f micro seconds\n", time_spent*1e6);
	printArr(copy3,n);

    // testing
    printf("\n");
    printf("%d %d\n",copy3[0],copy3[1]);
    swap(copy3, copy3 + 1, sizeof(copy3[0]));
    printf("%d %d\n",copy3[0],copy3[1]);
    // giai phong bo nho dong
    free(copy3);
    free(source);
    
    return 0;
}
