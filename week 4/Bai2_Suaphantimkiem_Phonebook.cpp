#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITAL_SIZE 1000
#define INCREMENTAL_SIZE 10

typedef struct {
    char number[20];
    char name[80];
} PhoneEntry;
typedef struct {
    PhoneEntry *entries;
    int total;
    int size;
} PhoneBook;

int count;
PhoneEntry* reAllocArray(PhoneEntry* ,int);
PhoneBook createPhoneBook();
void addPhoneNumber(char*,char*,PhoneBook *);
// int getPhoneNumber(char*,const PhoneBook*,int,int);
void printAllPhoneBook(const PhoneBook* book);
PhoneEntry* getPhoneNumber(const PhoneBook*,char*);
void dropPhoneBook(PhoneBook);

int main(){
    char name[80];
    char number[20];
    int i;
    PhoneBook book = createPhoneBook();
    addPhoneNumber("0918477128","Nguyen Van Mau",&book);
    addPhoneNumber("0124568951","Nguyen Tieu Binh",&book);
    addPhoneNumber("0384455469","Tu Thieu Hoa",&book);
    addPhoneNumber("0984685201","Nguyen Duc Hoa",&book);
    addPhoneNumber("0346213334","Luc Tieu Linh Dong",&book);
    addPhoneNumber("0967827352","Diem Hoai Le",&book);
    addPhoneNumber("0918271628","Ly Linh Ngoc",&book);
    printAllPhoneBook(&book);    
    printf ("Enter key name: "); scanf ("%s",name);
    // addPhoneNumber("091",name,&book);
    const PhoneBook *temp = &book;
     PhoneEntry* result = getPhoneNumber(temp,name);
    // printf ("%d\n",sizeof(book.entries)/sizeof(PhoneEntry));
    if (result == NULL)
        printf ("Not found!\n");
    else {
        printf ("Result:\n");
        for(i=0;i<count;i++){
            printf ("%s\t%s\n",result[i].name,result[i].number);
        }
    }
    free(result);
    printAllPhoneBook(&book);    
    

    // if (strstr("Nguyen Van Mau","Anh") == NULL) printf ("1\n");
    dropPhoneBook(book);

}

PhoneEntry* reAllocArray(PhoneEntry* book,int total){
    int i;
    PhoneEntry *temp = (PhoneEntry*) malloc (sizeof(PhoneEntry)*(total+INCREMENTAL_SIZE));
    for (i=0;i<total;i++){
        temp[i] = book[i];
    }
    free(book);
    return temp;
}

PhoneBook createPhoneBook(){
    PhoneBook temp;
    temp.total=0;
    temp.size = INITAL_SIZE;
    temp.entries = (PhoneEntry*) malloc (sizeof(PhoneEntry)*temp.size);
    return temp;
}

void addPhoneNumber(char* number,char* name,PhoneBook* book){
    int i,j,haveAdd = 0;
    if(book->total == book->size){
        book->entries = reAllocArray(book->entries,book->size);
        book->size += INCREMENTAL_SIZE;
        /*
        strcpy(book->entries[book->total].name,name);
        book->entries[book->total].number = number;
        */
        if (book->total == 0){
            strcpy(book->entries[book->total].name,name);
            strcpy(book->entries[book->total].number,number);
            book->total++;
        } else{ 
            for (i=0;i<book->total;i++){
                if (strcmp(book->entries[i].name,name)>0){
                    for (j=book->total;j>i;j--)
                        book->entries[j] = book->entries[j-1];
                    strcpy(book->entries[i].name,name);
                    strcpy(book->entries[i].number,number);
                    haveAdd = 1;
                    break; 
                }
            }
            if (haveAdd == 0){
                strcpy(book->entries[book->total].name,name);
                strcpy(book->entries[book->total].number,number);
            }
            book->total++;
        }
    } else {
        if (book->total == 0){
            strcpy(book->entries[book->total].name,name);
            strcpy(book->entries[book->total].number,number);
            book->total++;
        } else{ 
            for (i=0;i<book->total;i++){
                if (strcmp(book->entries[i].name,name)>0){
                    for (j=book->total;j>i;j--)
                        book->entries[j] = book->entries[j-1];
                    strcpy(book->entries[i].name,name);
                    strcpy(book->entries[i].number,number);
                    haveAdd = 1;
                    break; 
                }
            }
            if (haveAdd == 0){
                strcpy(book->entries[book->total].name,name);
                strcpy(book->entries[book->total].number,number);
            }
            book->total++;
        }
    }

}
/*
int getPhoneNumber(char* name,const PhoneBook* book,int left,int right){
    int mid;
    if (left>right)
        return -1;
    mid = (left+right)/2;
    if (strcmp(book->entries[mid].name,name) == 0)
        return mid;
    else if (strcmp(book->entries[mid].name,name)>0)
        return getPhoneNumber(name,book,0,mid-1);
    else return getPhoneNumber(name,book,mid+1,right); 
}
*/

void printAllPhoneBook(const PhoneBook* book){
    int i;
    printf("Danh ba hien tai co %d phan tu, kich thuoc toi da %d\n",book->total, book->size);
    for(i=0; i<book->total; i++)
        printf("%20s\t%20s\n", (book->entries[i]).name, (book->entries[i]).number);
}

void dropPhoneBook(PhoneBook book){
    free(book.entries);
    book.total = 0;
    book.size = INITAL_SIZE;
}

PhoneEntry* getPhoneNumber(const PhoneBook* book,char* key){
    count=0;
    int i,j=0;
    for (i=0;i<book->total;i++){
        if (strstr(strupr(book->entries[i].name),strupr(key)) != NULL)
            count++;
    }
    if (count == 0)
        return NULL;
    PhoneEntry* result = (PhoneEntry*) malloc (sizeof(PhoneEntry)*count);
    for (i=0;i<book->total;i++){
        if (strstr(strlwr(book->entries[i].name),strlwr(key)) != NULL){
            result[j] = book->entries[i];
            j++;
        }
    }
    return result;
}
