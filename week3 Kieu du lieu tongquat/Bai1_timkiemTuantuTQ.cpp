#include <stdio.h>
#include <stdlib.h>

typedef union {
    int i;
    long l;
    float f;
    double d;
    char c;
    void* v;
} Jval;

void exch(Jval a[],int i,int j);
void sort_gen(Jval a[],int left,int right,int (*compare)(Jval*,Jval*));
int search_gen(Jval a[],int size,Jval item,int (*compare)(Jval*,Jval*));
int binary_search_gen(Jval a[],int left,int right,Jval item,int (*compare)(Jval*,Jval*));
int intCompare(Jval* x,Jval* y);
int floatCompare(Jval* x,Jval* y);
int longCompare(Jval* x,Jval* y);
int doubleCompare(Jval* x,Jval* y);
// int voidCompare(Jval* x,Jval* y);

Jval new_jval_i(int i) { Jval j; j.i = i; return j; }
Jval new_jval_l(long l) { Jval j; j.l = l; return j; }
Jval new_jval_f(float f) { Jval j; j.f = f; return j; }
Jval new_jval_d(double d) { Jval j; j.d = d; return j; }
Jval new_jval_v(void *v) { Jval j; j.v = v; return j; }

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }  

int main(){
    Jval a_i[10],a_f[10],key;
    int n = 6,i;
    printf ("Mang so thuc kieu float, nhap mang:\n ");
    for (i=0;i<n;i++){
        scanf("%f",&a_f[i].f);
    }
    printf ("Nhap key: ");scanf("%f",&key.f);
    printf ("Vi tri phan tu:(khong tim thay -1): %d\n",search_gen(a_f,n,key,floatCompare));

    printf ("Mang so nguyen kieu int, nhap mang:\n ");
    for (i=0;i<n;i++){
        scanf("%d",&a_i[i].i);
    }
    printf ("Nhap key: ");scanf("%d",&key.i);
    printf ("Vi tri phan tu:(khong tim thay -1): %d\n",search_gen(a_i,n,key,intCompare));

}

void exch(Jval a[],int i,int j){
    Jval temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void sort_gen(Jval a[],int left,int right,int (*compare)(Jval*,Jval*)){
    int i, j, pivot, temp;
    int comp;
    if(left<right){
        pivot=left;
        i=left;
        j=right;

        while(i<j){
            while((comp=compare(a+i,a+pivot)) <= 0 && i<right)
                i++;
            while((comp=compare(a+j,a+pivot)) > 0)
                j--;
            if(i<j){
                exch(a,i,j);
            }
        }

        exch(a,pivot,j);
        sort_gen(a,left,j-1,compare);
        sort_gen(a,j+1,right,compare);
    }
}

int search_gen(Jval a[],int size,Jval item,int (*compare)(Jval*,Jval*)){
    int i;
    for (i=0;i<size;i++){
        if (compare(a+i,&item)==0){
            return i;
        }
    }
    return -1;
}

int binary_search_gen(Jval a[],int left,int right,Jval item,int (*compare)(Jval*,Jval*)){
    int comp;
    if (left > right)
        return -1;
    int mid = (left+right)/2;
    if ((comp=compare(a+mid,&item))>0)
        return binary_search_gen(a,left,mid-1,item,compare);
    else if ((comp=compare(a+mid,&item))<0)
        return binary_search_gen(a,mid+1,right,item,compare);
    else return mid;
}

int intCompare(Jval* x,Jval* y){
    return jval_i(*x) - jval_i(*y);
}

int floatCompare(Jval *x,Jval *y){
    return jval_f(*x) - jval_f(*y);
}

int longCompare(Jval* x,Jval* y){
    return jval_l(*x) - jval_l(*y);
}

int doubleCompare(Jval* x,Jval* y){
    return jval_d(*x) - jval_d(*y);
}

// int voidCompare(Jval* x,Jval* y){
//     return jval_v(*x) - jval_v(*y);
// }

