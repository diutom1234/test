#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
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


//hàm s?p x?p n?i b?t
void bubblesort(int *list, int n)
{
    for(int i=n; i>1; i--)
        for(int j=1;j<i; j++)
        {
            if(list[j-1]> list[j])
            {
                int tmp = list[j];
                list[j] = list[j-1];
                list[j-1] = tmp;
            }
        }
}

// hàm s?p x?p l?a ch?n
void selectionsort(int *list, int n)
{
    for(int i=n; i>1; i--)
    {
        int vtmax = 0;
        for(int j=1; j<i; j++)
            if(list[j]>list[vtmax]) vtmax = j;
        
        int tmp = list[i-1];
        list[i-1] = list[vtmax];
        list[vtmax] = tmp;
    }
}
void quicksort(int *number,int first,int last)
{
   int i, j, pivot, temp;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
        // swap phan tu
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;
      quicksort(number,first,j-1);
      quicksort(number,j+1,last);
   }
}

int main()
{
    const int n=10000; 
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
    
    begin = clock();
    bubblesort(copy1,n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep noi bot mat thoi gian la %f micro seconds\n", time_spent*1e6);
    
    begin = clock();
    selectionsort(copy2,n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep lua chon mat thoi gian la %f micro seconds\n", time_spent*1e6);
    

    begin = clock();
    quicksort(copy3,0,n-1);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Sap xep QuickSort mat thoi gian la %f micro seconds\n", time_spent*1e6);
	

    // giai phong bo nho dong
    free(copy1);
    free(copy2);
    free(copy3);
    free(source);
    return 0;
}
