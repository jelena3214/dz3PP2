#define _CRT_SECURE_NO_WARNINGS
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

void removeComments(char* beginComment, char* endComment, char** code, int n) {
	char* firstOcurrance, * secondOcurrance;
	for (int i = 0; i < n; i++) {
		firstOcurrance = strstr(code[i], beginComment);
		secondOcurrance = strrstr(code[i], endComment);
		//slucajevi
		//ima i pocetak i kraj brisemo tu liniju, povecavamo brojac da ima komentara, ako je taj brojac 0 onda GRESKA
		//ima pocetak onda for petlja za dalje da se nadje prvi kraj i brise deo izmedju oznaka za komentar
		//ako ni kraja nema GRESKA?? ako nije potpun komentar?
		if (firstOcurrance == NULL && secondOcurrance == NULL)continue; //tu nema komentara
		else if (secondOcurrance == NULL) {
			char* s = firstOcurrance + strlen(beginComment);
			for (int j = i + 1; j < n; j++) {
				char* find = strstr(code[j], endComment);
				if (find != NULL)break;
			}
		}
	}
}


int main() {
	char* comment_begin, *comment_end;
	comment_begin = readLine();
	comment_end = readLine();
	//printf("%s\n", comment_begin);
	//printf("%s\n", comment_end);

	int n = 0, *p = &n;
	char** str = readLines(p);
	



	return 0;
}
