#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 100
#define INCREMENTAL_SIZE 10

typedef struct {
    void *key;
    void *value;
} Entry;
typedef struct {
    Entry *entries;
    int size, total;
    Entry (*makeNode)(void*,void*);
    int (*compare)(void*,void*);
} SymbolTable;

SymbolTable createSymbolTable(Entry(*makeNode)(void*,void*),int(*compare)(void*,void*));
SymbolTable update(SymbolTable);
void addEntry(void*,void*,SymbolTable*);
Entry *getEntryValue(void*,const SymbolTable*);
void dropSymbolTable (SymbolTable*);
Entry makePhoneBook(void *phone,void *name);
int comparePhone(void*,void*);

void printAllPhoneBook(const SymbolTable* book)
{
    int i;
    printf("Danh ba hien tai co %d phan tu, kich thuoc toi da %d\n",book->total, book->size);
    for( i=0; i<book->total; i++)
        printf("%20s\t%15s\n", (char*)(book->entries[i]).key, (char*)(book->entries[i]).value);
    
    printf("==================================\n");
}

int main(){
    SymbolTable phoneBook = createSymbolTable(makePhoneBook,comparePhone);
    char name[50];
    char number1[] = "09872511";
    char name1[] = "Anh A";
    char number2[] = "01937253";
    char name2[] = "Chi B";
    addEntry(name1,number1,&phoneBook);
    addEntry(name2,number2,&phoneBook);
    printAllPhoneBook(&phoneBook);
    printf ("Enter key name: "); gets(name);
    Entry *result = getEntryValue(name,&phoneBook);
    if (result == NULL)
        printf ("Not found!\n");
    else printf ("%20s\t%15s\n",(char*)result->key,(char*)result->value);
    dropSymbolTable(&phoneBook);
}

SymbolTable createSymbolTable(Entry (*makeNode)(void*,void*),int (*compare)(void*,void*)){
    SymbolTable temp ;
    temp.size = INITIAL_SIZE;
    temp.total = 0;
    temp.makeNode = makeNode;
    temp.compare = compare;
    temp.entries = (Entry*) malloc (sizeof(Entry)*INITIAL_SIZE);
    return temp;
}

void addEntry(void *key,void *value,SymbolTable *book){
    int i;
    Entry *newEntries;
    if (book->size == book->total){
        book->size += INCREMENTAL_SIZE;
        newEntries = (Entry*) malloc (sizeof(Entry)*(book->size));
        for (i=0;i<book->total;i++)
            newEntries[i] = book->entries[i];
        for (i=0;i<book->total;i++){
            free(book->entries[i].key);
            free(book->entries[i].value);
        }
        free(book);
        book->entries = newEntries;
        book->entries[book->total] = book->makeNode(key,value);
        book->total++;
    } else {
        book->entries[book->total] = book->makeNode(key,value);
        book->total++;
    }
}

Entry makePhoneBook(void *name,void *phone){
    Entry res;
    res.key = strdup((char*)name);
    res.value = strdup( (char*)phone );
    return res;
}

int comparePhone(void *key1,void* key2){
    return strcmp((char*)key1,(char*)key2);
}

Entry *getEntryValue(void* key,const SymbolTable* book){
    int i;
    for (i=0;i<book->total;i++){
        if (book->compare(key,book->entries[i].key) == 0)
            return &book->entries[i];
    }
    return NULL;
}

void dropSymbolTable (SymbolTable* book){
    int i;
    for (i=0;i<book->total;i++){
        free(book->entries[i].key);
        free(book->entries[i].value);
    }
    free(book->entries);
    book->total = 0;
    book->size = INITIAL_SIZE;
}
