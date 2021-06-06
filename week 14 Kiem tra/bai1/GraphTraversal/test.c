/*Nhập vào danh sách những người bạn của từng người trong file

===================
An: Hoa, Hong, Dung, Tien, Tung, Toan
Hong: Hoa, An, Dung, Tien
Dung: Tien, An, Hoa, Minh
Tien: An, Minh
Tung: Hung, Dung, An
Toan: Linh, An, Dung
Ly: Minh, Lam, Linh
Linh: Hoan, Hai
========================
Mỗi dòng là 1 người và những người bạn thân của người đó
Giả sử không có tên bị trùng

Với file trên, 
1.nhập vào tên 2 người, hỏi xem hai người đó có phải là bạn thân hay không
2.Nếu hai người là bạn thân, hãy liệt kê bạn chung của cả 2 người này 

*/
#include<stdio.h>
#include<string.h>
#include"jrbgraph.h"
char * chuan_hoa(char * s) { 
    int l = strlen(s); 
    if (s[l-1]<97||s[l-1]>122) { 
        s[l-1]='\0'; 
    }
    return s; 
}
int main(){
    char output1[10][10];
    char output2[10][10];
    int i,j,m,n;
    int check=0;
    Graph g = createGraph();
    FILE *f1;
    f1= fopen("friend.txt","r");
    // char s1[100];
    // char s2[100];
    // while (!feof(f1))
    // {
    //     fscanf(f1,"%s%s",s1,s2);
    //     addEdge_str(g,s1,s2);
    // }
    while (!feof(f1)) { 
        char  s[50]; 
        fgets(s,50, f1);
        char * split = strtok(s," "); 
        //int len= strlen(split) ; 
        char luu[10][10]; 
        int k=0 ; 
        while (split!=NULL) { 
            strcpy(luu[k],chuan_hoa(split)) ; 
            // printf("%s ",luu[k]) ; 
            k++; 
            split = strtok(NULL," "); 
        }
        for(int i=1; i<k; i++) { 
            addEdge_str(g, luu[0], luu[i]); 
        }
    }
    fclose(f1);
    char name1[10];
    char name2[10];
    printf("\nnhap ten ban thu nhat:"); scanf("%s",name1);
    getchar();
    printf("\nnhap ten ban thu hai:"); scanf("%s",name2);
    m=getAdjacentVertices_str(g,name1,output1);
    n=getAdjacentVertices_str(g,name2,output2);
    if (m==0 || n==0) printf("No adjacent vertices of node \n");
    else{
        for ( i = 0; i < m; i++)
        {
           if(strcmp(output1[i],name2)==0) {
               printf("2 nguoi la ban than\n");
            check=1;
        }
    } 
    }
    if(check==1){
            printf("ban chung cua 2 ban la:");
           for (i=0; i<m; i++){
           for ( j = 0; j < n; j++)
           {
               if(strcmp(output1[i],output2[j])==0) printf("%5s",output1[i]);
           }
           
           }
    }
    else printf("2 nguoi ko phai la ban than");
    return 0;
}