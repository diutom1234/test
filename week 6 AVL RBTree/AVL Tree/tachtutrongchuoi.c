#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void split(char *s, char res[100][20], int* size);// tach chuoi dau vao ra mang cac tu
void sort(char s[100][20], int size);// dua tren tap tu da tach duoc, sap xep lai theo thu tu abc
void display(char s[100][20], int size);//in ra man hinh ket qua

void split(char *s, char res[100][20], int* size) {
	int i = 0;
	const char* delim = " .,?!-\t\n";//cac dau hieu tach khi gap thi se tach tu ra
	char *p;//
	for(p = strtok(s, delim); p != NULL; p = strtok(NULL, delim)) {
		strcpy(res[i++], p);//gan tu duoc tach vao mang res
	}
	*size = i;//cap nhat so luong tu
}

void sort(char s[100][20], int size) {
	int i, j;
	for(i = 0; i < size-1; i++) {
		for(j = size-1; j > i; j--) {
			if(strcmp(s[j-1], s[j]) > 0) {//so sanh 2 tu va tien hanh doi vi tri
				char *p = (char*) malloc(20);
				strcpy(p, s[j]);
				strcpy(s[j], s[j-1]);
				strcpy(s[j-1], p);
			}
		}
	}
}

void display(char s[100][20], int size) {
	int i;
	for(i = 0; i <  size; i++) {
		printf("%s ", s[i]);
	}
}

int main(){
	char input[1000];
	fgets(input, 999, stdin);
	int len = strlen(input);
	if(len > 0) {
		input[len-1] = '\0';
	}
	char res[100][20];
	int numOfWords = 0;
	split(input, res, &numOfWords);
	sort(res, numOfWords);
	display(res, numOfWords);
	
	return 0;
}
