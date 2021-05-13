#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine() {
	char* inp = NULL;
	char c;
	int size = 0;
	while ((c = getchar()) != '\n') {
		size++;
		inp = realloc(inp, sizeof(char) * (size + 1));
		if (!inp) {
			printf("MEM_GRESKA\n");
			exit(-1);
		}
		inp[size - 1] = c;
		inp[size] = NULL;
	}
	return inp;
}

char** readLines(int* n) {
	char** code = 0;
	char* p;
	while ((p = readLine()) != NULL) {
		(*n)++;
		code = realloc(code, sizeof(char*) * ((*n) + 1));
		if (!code) {
			printf("MEM_GRESKA\n");
			exit(-1);
		}
		code[(*n) - 1] = p;
		code[(*n)] = NULL;
	}
	return code;
}

int isSpace(char* s) {
	while (*s != '\0') {
		if (!isspace((unsigned char)*s))
			return 0;
		s++;
	}
	return 1;
}

void removeComments(char* beginComment, char* endComment, char** code, int n) {
	char* firstOcurrance, * secondOcurrance, *s = malloc(sizeof(char)* 50);
	int comments = 0;
	int first = strlen(beginComment);
	int second = strlen(endComment);

	for (int i = 0; i < n; i++) {
		firstOcurrance = strstr(code[i], beginComment);
		secondOcurrance = strstr(code[i], endComment);
		//slucajevi
		//ima i pocetak i kraj brisemo tu liniju, povecavamo brojac da ima komentara, ako je taj brojac 0 onda GRESKA
		//ima pocetak onda for petlja za dalje da se nadje prvi kraj i brise deo izmedju oznaka za komentar
		//ako ni kraja nema GRESKA?? ako nije potpun komentar?
		if (firstOcurrance == NULL && secondOcurrance == NULL)continue; //tu nema komentara
		else if ((firstOcurrance && secondOcurrance) || (secondOcurrance == NULL)) {
			comments++;
			int len = strlen(firstOcurrance);
			int temp = firstOcurrance - code[i];
			code[i][temp] = '\0';
			if ((strlen(code[i]) == 0) || isSpace(code[i])) {
				for (int j = i; j < n; j++) {
					code[j] = code[j + 1];
				}
				n--;//proveri ovu promenu n i i
				i--;
			}
		}
		else if (firstOcurrance == NULL) {
			int len = strlen(secondOcurrance);
			int temp = secondOcurrance - code[i];
			char* tmp = malloc(sizeof(char) * (strlen(code[i]) - len + 1));
			int iterate = strlen(code[i]) - temp + 1;
			for (int j = temp;j < iterate; j++) {
				tmp[j] = code[i][j];
			}
			code[i] = temp;
			if (code[i] == NULL) {
				for (int j = i; j < n; j++) {
					code[j] = code[j + 1];
				}
				n--;//proveri ovu promenu n i i
				i--;
			}
		}
	}
	if(comments){
		for (int i = 0; i < n; printf("%s\n", code[i++]));
	}
	
}


int main() {
	char* comment_begin, *comment_end;
	comment_begin = readLine();
	comment_end = readLine();
	int n = 0, *p = &n;
	char** str = readLines(p);

	printf("%s\n", comment_begin);
	printf("%s\n", comment_end);
	removeComments(comment_begin, comment_end, str, n);
	
	return 0;
}
