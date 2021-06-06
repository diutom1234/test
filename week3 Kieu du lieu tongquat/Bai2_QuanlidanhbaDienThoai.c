#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITAL_SIZE 10
#define INCREMENTAL_SIZE 5

typedef struct {
    char number[15];
    char name[50];
} PhoneEntry;
typedef struct {
    PhoneEntry *entries;
    int total;//tong so ban ghi hien tai
    int size;//kich thuoc mang hien tai, size >= total
} PhoneBook;

PhoneEntry* recallocArray(PhoneEntry* ,int);
PhoneBook createPhoneBook();
void addPhoneNumber(char*,char*,PhoneBook *);
PhoneEntry* getPhoneNumber(char*,PhoneBook);
void dropPhoneBook(PhoneBook*);

int main(){
    char name[50];
    char number[15];
    scanf ("%s%s",name,number);
    PhoneBook book = createPhoneBook();
    addPhoneNumber(number,name,&book);
    // addPhoneNumber(number,name,&book);
    printf ("%d\n", book.total);
    scanf ("%s%s",name,number);
    addPhoneNumber(number,name,&book);
    printf ("%s\t%d\n", book.entries[0].name,book.total);
    strcpy(name,"anh");
    PhoneEntry* res = getPhoneNumber(name,book);
    if (res != NULL)
        printf("%s",res->number);
    dropPhoneBook(&book);

}

//Cap phat dong
PhoneEntry* recallocArray(PhoneEntry* book,int total){
    int i;
    PhoneEntry *temp = (PhoneEntry*) malloc (sizeof(PhoneEntry)*(total+INCREMENTAL_SIZE));
    for (i=0;i<total;i++){
        temp[i] = book[i];
    }
    free(book);
    return temp;
}

//Ham khoi tao danh ba voi kich thuoc ban dau 10 phan tu
PhoneBook createPhoneBook(){
    PhoneBook temp;
    temp.total=0;
    temp.size = INITAL_SIZE;
    temp.entries = (PhoneEntry*) malloc (sizeof(PhoneEntry)*temp.size);
    return temp;
}

//Ham them mot ban ghi moi vao danh ba
//Neu can phai chinh sua se thuc hien trong ham nay
void addPhoneNumber(char* number,char* name,PhoneBook* book){
    int i;
    PhoneEntry* res = getPhoneNumber(name,*book);
    if(res != NULL){
        for (i=0;i<book->total;i++){
            if (strcmp(book->entries[i].name,name)==0){
                strcpy(book->entries[i].number,number);
                break;
            }
        }
    } else if(book->total == book->size){
        book->entries = recallocArray(book->entries,book->size);
        book->size += INCREMENTAL_SIZE;
        strcpy(book->entries[book->total].name,name);
        strcpy(book->entries[book->total].number,number);
        book->total++;
    } else {
        strcpy(book->entries[book->total].name,name);
        strcpy(book->entries[book->total].number ,number);
        book->total++;
    }
}

//Ham tra SDT theo ten
PhoneEntry* getPhoneNumber(char* name,PhoneBook book){
    int i;
    for (i=0;i<book.total;i++){
        if (strcmp(book.entries[i].name,name) == 0)
            return book.entries+i;
    }
    return NULL;
}


//HAm xoa danh ba
void dropPhoneBook(PhoneBook* book){
    free(book->entries);
    book->entries = NULL;
    book->total = 0;
    book->size = INITAL_SIZE;
}
