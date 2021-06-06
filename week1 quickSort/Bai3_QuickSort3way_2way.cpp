#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double t;
int* generateArray(int n){
    int i;
    srand((int)time(NULL));
    int *arr = (int*) malloc(n*sizeof(int));
    for (i=0;i<n;i++){
        arr[i] = rand();
    }
    return arr;
}

int* generateArrayDuplicate(int n){
    int i,j;
    int* list = (int*)malloc(n*sizeof(int));
    srand((int)time(NULL));
    for(i=0; i<n;i++)
    {
        list[i] = rand();
        int m = rand()%10;
        // t?o ra m l?n l?p c?a ph?n t? th? i
        for(j=1; j<=m; j++)
        {
            list[i+j] = list[i];
        }
        i = i + m;
    }
    return list;
}

int* copyArray(int *list,int n){
    int i;
    int *arr = (int*) malloc (n*sizeof(int));
    for (i=0;i<n;i++){
        arr[i] = list[i];
    }
    return arr;
}

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort_2way(int *number,int first,int last)
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
        if(i<j){
            swap(&number[i],&number[j]);
         }
      }

      swap(&number[pivot],&number[j]);
      quickSort_2way(number,first,j-1);
      quickSort_2way(number,j+1,last);
      
   }
}

void quickSort_3way(int a[], int l, int r) {
    int k;
	if (r <= l) return;
	int i = l-1, j = r;
	int p = l-1, q = r;
	while(1)	{
		while (a[++i] < a[r]);
		while (a[r] < a[--j]) if (j == l) break;
		if (i >= j) break;
		swap(&a[i],&a[j]);
		if (a[i]==a[r]) swap(&a[++p],&a[i]);
		if (a[j]==a[r]) swap(&a[--q],&a[j]);
	}
	swap(&a[i],&a[r]);
	j = i - 1;
	i = i + 1;
	for (k = l ; k <= p; k++) swap(&a[k],&a[j--]);
	for (k = r-1; k >= q; k--) swap(&a[k],&a[i++]);
	quickSort_3way(a, l, j);
	quickSort_3way(a, i, r);
}

int main(){
    int n = 1000;
    double time;
    int *source1 = generateArray(n);
    int *source2 = generateArrayDuplicate(n);
    printf ("Truong hop sinh mang ngau nhien:\n");
    int *copy1 = copyArray(source1,n);
    int *copy2 = copyArray(source1,n);
    clock_t begin = clock();
    quickSort_2way(copy1,0,n-1);
    clock_t end = clock();
    time = (double) (end-begin)/CLOCKS_PER_SEC;
    printf ("Thoi gian chay quicksort chia hai phan la: %lf\n",time);

    begin = clock();
    quickSort_3way(copy2,0,n-1);
    end = clock();
    time = (double) (end-begin)/CLOCKS_PER_SEC;
    printf ("Thoi gian chay quicksort chia ba phan la: %lf\n",time);

    printf ("Truong hop cac phan tu bi trung lap:\n");
    copy1 = copyArray(source2,n);
    copy2 = copyArray(source2,n);
    begin = clock();
    quickSort_2way(copy1,0,n-1);
    end = clock();
    time = (double) (end-begin)/CLOCKS_PER_SEC;
    printf ("Thoi gian chay quicksort chia hai phan la: %lf\n",time);

    begin = clock();
    quickSort_3way(copy2,0,n-1);
    end = clock();
    time = (double) (end-begin)/CLOCKS_PER_SEC;
    printf ("Thoi gian chay quicksort chia ba phan la: %lf\n",time);

}
