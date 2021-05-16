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
            exit(-1);
        }
        inp[size - 1] = c;
        inp[size] = '\0';
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

void removeSubstr(char* string, char* sub) {
    char* match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match + len);
    }
}

void removeComments(char* beginComment, char* endComment, char** code, int n) {
    char* firstOcurrance, * secondOcurrance;
    int comments = 0;

    for (int i = 0; i < n; i++) {
        while (1) {
            //ovo pogledaj kad je komentar '''
            firstOcurrance = strstr(code[i], beginComment);
            if (firstOcurrance) {
                int len = firstOcurrance - code[i];
                char* hel = code[i];
                int start = len + strlen(beginComment);
                for (int s = 0; s <= start; s++) {
                    hel++;
                }
                //printf("hel:%s\n", hel);
                secondOcurrance = strstr(hel, endComment);

                /*printf("CODE%s\n", code[i]);
                printf("sec%s\n", secondOcurrance);
                printf("firs%s\n", firstOcurrance);*/
            }
            else {
                secondOcurrance = strstr(code[i], endComment);
            }
            if (firstOcurrance == NULL && secondOcurrance == NULL)break; //tu nema komentara
            else if (secondOcurrance == NULL) {
                comments++;
                int temp = firstOcurrance - code[i];
                code[i][temp] = '\0';
                if ((strlen(code[i]) == 0) || isSpace(code[i])) {
                    for (int j = i; j < n; j++) {
                        code[j] = code[j + 1];
                    }
                    free(code[n]);
                    n--;//proveri ovu promenu n i i
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
                    exit(-1);
                }
                int s = 0;
                for (int k = temp; k <= temp1; k++) {
                    one[s++] = code[i][k];
                }
                //printf("%d %d\n", temp, temp1);
                one[temp1 - temp + 1] = 0;
                removeSubstr(code[i], one);
                /*if (strlen(code[i]) == 0) {
                    for (int j = i; j < n; j++) {
                        code[j] = code[j + 1];
                    }
                    n--;//proveri ovu promenu n i i
                    i--;*/
                    //printf("%s\n", code[i]);
                free(one);
            }
            else if (firstOcurrance == NULL) {
                int temp = secondOcurrance - code[i];
                char* tmp = malloc(sizeof(char) * (strlen(code[i]) - strlen(endComment) - temp + 1));
                if (!tmp) {
                    printf("MEM_GRESKA\n");
                    exit(-1);
                }
                temp = temp + strlen(endComment);
                int iterate = strlen(code[i]) + 1, k = 0;
                for (int j = temp; j <= iterate; j++) {
                    tmp[k++] = code[i][j];
                }
                code[i] = tmp;

                if (strlen(code[i]) == 0) {
                    for (int j = i; j < n; j++) {
                        code[j] = code[j + 1];
                    }
                    n--;//proveri ovu promenu n i i
                    i--;
                }
                free(tmp);
            }
        }
    }
    if (comments) {
        for (int i = 0; i < n; printf("%s\n", code[i++]));
    }
    else {
        printf("GRESKA\n");
    }

}

int main() {
    char* comment_begin, * comment_end;
    comment_begin = readLine();
    comment_end = readLine();
    int n = 0, * p = &n;
    char** str = readLines(p);
    removeComments(comment_begin, comment_end, str, n);
    free(comment_begin);
    free(comment_end);
    for (int i = 0; i < n; i++) {
        free(str[i]);
    }free(str);
    return 0;
}
