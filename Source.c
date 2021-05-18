#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* readLine() {
    char* inp = NULL;
    char c;
    int size = 0;
    while ((c = getchar()) != '\n') {
        size++;
        inp = realloc(inp, sizeof(char) * (size + 1));
        if (!inp) {
            printf("MEM_GRESKA\n");
            exit(0);
        }
        inp[size - 1] = c;
        inp[size] = '\0';
    }
    return inp;
}

char** readLines(int* n) {
    char** code = NULL;
    char* p;
    while ((p = readLine()) != NULL) {
        (*n)++;
        code = realloc(code, sizeof(char*) * (*n));
        if (!code) {
            printf("MEM_GRESKA\n");
            exit(0);
        }
        code[(*n) - 1] = p;
    }
    return code;
}

void removeSubstr(char* string, char* sub) {
    char* match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match + len);
    }
}

void removeComments(char* beginComment, char* endComment, char** code, int *n) {
    char* firstOcurrance, * secondOcurrance;
    int comments = 0;

    for (int i = 0; i < (*n); i++) {
        while (1) {
            firstOcurrance = strstr(code[i], beginComment);
            if (firstOcurrance) {
                int len = firstOcurrance - code[i];
                char* hel = code[i];
                int start = len + strlen(beginComment);
                for (int s = 0; s <= start; s++) {
                    hel++;
                }
                secondOcurrance = strstr(hel, endComment);
            }
            else {
                secondOcurrance = strstr(code[i], endComment);
            }
            if (firstOcurrance == NULL && secondOcurrance == NULL)break; //tu nema komentara
            else if (secondOcurrance == NULL) {
                comments++;
                int temp = firstOcurrance - code[i];
                code[i][temp] = '\0';
                if ((strlen(code[i]) == 0)) {//pogledaj sta ce ovo isspace
                    char* del = code[i];
                    for (int j = i; j < (*n); j++) {
                        code[j] = code[j + 1];
                    }free(del);
                    (*n)--;
                    i--;
                }
            }
            else if (firstOcurrance && secondOcurrance) {
                
                comments++;
                int temp = firstOcurrance - code[i];
                int temp1 = secondOcurrance - code[i] + strlen(endComment) - 1;
                char* one = malloc(sizeof(char) * (temp1 - temp + 2));
                if (!one) {
                    printf("MEM_GRESKA\n");
                    exit(0);
                }
                int s = 0;
                for (int k = temp; k <= temp1; k++) {
                    one[s++] = code[i][k];
                }

                one[temp1 - temp + 1] = 0;
                removeSubstr(code[i], one);
                free(one);
                if (strlen(code[i]) == 0) {
                    char* del = code[i];
                    for (int j = i; j < (*n); j++) {
                        code[j] = code[j + 1];
                    }free(del);
                    (*n)--;

                }
                
            }
            else if (firstOcurrance == NULL) {
                int temp = secondOcurrance - code[i];
                char* tmp = malloc(sizeof(char) * (strlen(code[i]) - strlen(endComment) - temp + 1));
                if (!tmp) {
                    printf("MEM_GRESKA\n");
                    exit(0);
                }
                temp = temp + strlen(endComment);
                int iterate = strlen(code[i]) + 1, k = 0;
                for (int j = temp; j <= iterate; j++) {
                    tmp[k++] = code[i][j];
                }

                memcpy(code[i], tmp, sizeof(char) * (strlen(tmp) + 1));
                free(tmp);
                if (strlen(code[i]) == 0) {
                    char* del = code[i];
                    for (int j = i; j < (*n); j++) {
                        code[j] = code[j + 1];
                    }free(del);
                    (*n)--;
                    i--;
                }
                
            }
        }
    }
    if (comments) {
        for (int i = 0; i < (*n); i++) {
            printf("%s\n", code[i]);
        }
    }

}

int isSpace(char* s) {
    while (*s != '\0') {
        if (!isspace((unsigned char)*s))
            return 0;
        s++;
    }
    return 1;
}


int main() {
    char* comment_begin, * comment_end;
    comment_begin = readLine();
    comment_end = readLine();
    if (comment_begin == NULL || comment_begin == NULL) {
        printf("GRESKA\n");
    }
    int n = 0;
    char** str = readLines(&n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == '\n') {
            s++;
        }
    }if (s == n) {
        printf("GRESKA\n");
    }
    removeComments(comment_begin, comment_end, str, &n);
    free(comment_begin);
    free(comment_end);
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }free(str);
    return 0;
}
