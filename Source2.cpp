#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 20

typedef struct string_ {
    char str[SIZE] = { 0 };
}strings;

typedef struct variable {
    char name[20];
    strings original;
    strings polish;
}variables;

int prior(int symb)
{
    switch (symb)
    {
    case'(':
        return 0;
    case '+':
    case '-':
        return 1;
    case'*':
    case'/':
        return 2;
    case'^':
        return 3;
    }
    return 3;
}



int push(strings stack[], unsigned cur, char buff[])
{
    if (cur < SIZE)
    {
        strcpy(stack[cur].str, buff);
        cur++;
    }
    return cur;
}

int empty(const strings stack[], unsigned cur)
{
    if (cur == 0)
        return 1;
    else return 0;
}

int pop(strings stack[], unsigned cur)
{
    if (empty(stack, cur) != 1)
    {
        --cur;
    }
    return cur;
}

int is_fun(strings fun[], char buff[], int cur_fun) {
    for (int i = 0; i < cur_fun; i++) {
        if (strcmp(fun[i].str, buff) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_const(strings con[], char buff[], int cur_con) {
    for (int i = 0; i < cur_con; i++) {
        if (strcmp(con[i].str, buff) == 0) {
            return 1;
        }
    }
    return 0;
}

void buff_clear(char buff[]) {
    int len = strlen(buff);
    for (int i = 0; i < len; i++) {
        buff[i] = '\0';
    }
}

void make_polish(variables var[], char str[], int curva, strings fun[], strings con[], int cur_fun, int cur_con, strings stack[], FILE *input) {
    int len = 0, cur = 0;
    char buff[SIZE] = { 0 };
    char c = '0';
    char check[SIZE] = { 0 };
    while (c != '\0') {
        fscanf(input, "%s", buff);
        if (strcmp(buff, check) == 0) {
            break;
        }
        if (is_fun(fun, buff, cur_fun) == 1) {
            if (empty(stack, cur) == 1) {
               cur = push(stack, cur, buff);
            }
            else if (prior(buff[0]) > prior(stack[cur - 1].str[0])) {
                cur = push(stack, cur, buff);
            }
            else if (prior(buff[0]) <= prior(stack[cur - 1].str[0])) {
                while (prior(buff[0]) <= prior(stack[cur - 1].str[0]) && !empty(stack, cur)) {
                    strcat(var[curva].polish.str, stack[cur-1].str);
                    var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                    cur = pop(stack, cur);
                }
                cur = push(stack, cur, buff);
            }
        }
        else if (strcmp(buff, "(") == 0) {
            cur = push(stack, cur, buff);
        }
        else if (strcmp(buff, ")") == 0) {
            var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
            while (strcmp(stack[cur - 1].str, ")") != 0) {
                strcat(var[curva].polish.str, stack[cur - 1].str);
                var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                cur = pop(stack, cur);
            }
            cur = pop(stack, cur);
        }
        else {
           cur = push(stack, cur, buff);
        }
        strcpy(check, buff);
    }
    if (empty(stack, cur) != 1) {
        while (empty(stack, cur) != 1) {
            strcat(var[curva].polish.str, stack[cur - 1].str);
            var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
            cur = pop(stack, cur);
        }
    }
}

int main(){
    variables var[SIZE];
    FILE *fun = fopen("function.txt", "r");
    FILE *con = fopen("const.txt", "r");
    FILE *input = fopen("input.txt", "r");
    strings fun_arr[SIZE];
    strings con_arr[SIZE];
    strings stack[SIZE];
    char str[SIZE] = { 0 };
    char c = '0';
    int curva = 0, cur_fun = 0, cur_con = 0;
    while (!feof(fun)) {
        fscanf(fun,"%s", fun_arr[cur_fun].str);
        cur_fun++;
    }
    while (!feof(con)) {
        fscanf(con,"%s", con_arr[cur_con].str);
        cur_con++;
    }
    while (!feof(input)) {
        fscanf(input, "%s", var[curva].name);
        c = fgetc(input);
        c = fgetc(input);
        c = fgetc(input);
        int len = 0, cur = 0;
        char buff[SIZE] = { 0 };
        char check[SIZE] = { 0 };
        while (c != '\n' && c != EOF) {
            fscanf(input, "%s", buff);
            if (is_fun(fun_arr, buff, cur_fun) == 1) {
                if (empty(stack, cur) == 1) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) > prior(stack[cur - 1].str[0])) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) <= prior(stack[cur - 1].str[0])) {
                    while (prior(buff[0]) <= prior(stack[cur - 1].str[0]) && !empty(stack, cur)) {
                        strcat(var[curva].polish.str, stack[cur - 1].str);
                        var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                        cur = pop(stack, cur);
                    }
                    cur = push(stack, cur, buff);
                }
            }
            else if (strcmp(buff, "(") == 0) {
                cur = push(stack, cur, buff);
            }
            else if (strcmp(buff, ")") == 0) {
                while (strcmp(stack[cur - 1].str, "(") != 0) {
                    strcat(var[curva].polish.str, stack[cur - 1].str);
                    var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                    cur = pop(stack, cur);
                }
                cur = pop(stack, cur);
            }
            else if(strcmp(buff,"+") == 0 || strcmp(buff, "-") == 0 || strcmp(buff, "*") == 0 || strcmp(buff, "/") == 0 || strcmp(buff, "^") == 0) {
                if (empty(stack, cur) == 1) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) > prior(stack[cur - 1].str[0])) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) <= prior(stack[cur - 1].str[0])) {
                    while (prior(buff[0]) <= prior(stack[cur - 1].str[0]) && !empty(stack, cur)) {
                        strcat(var[curva].polish.str, stack[cur - 1].str);
                        var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                        cur = pop(stack, cur);
                    }
                    cur = push(stack, cur, buff);
                }
            }
            else {
                strcat(var[curva].polish.str, buff);
                var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
            }
            c = fgetc(input);
        }
        if (empty(stack, cur) != 1) {
            while (empty(stack, cur) != 1) {
                strcat(var[curva].polish.str, stack[cur - 1].str);
                var[curva].polish.str[strlen(var[curva].polish.str)] = ' ';
                cur = pop(stack, cur);
            }
        }
        curva++;
    }
    printf("%s", var[0].polish.str);
    /* for (int i = 0; i < strlen(polish) - 1; i++)
     {
         if (polish[i] >= '0' && polish[i] <= '9')
         {
             chif[len] = polish[i];
             len++;
         }
         if (polish[i] == ' ' && (polish[i - 1] != '+' && polish[i - 1] != '-' && polish[i - 1] != '*' && polish[i - 1] != '/'))
         {
             res[cur] = cal(chif);
             len = 0;
             cur++;
         }
         if (polish[i] == '+' || polish[i] == '-' || polish[i] == '*' || polish[i] == '/')
         {
             switch (polish[i])
             {
             case '*':
                 res[cur - 2] = res[cur - 2] * res[cur - 1];
                 cur = cur - 1;
                 break;
             case '/':
                 res[cur - 2] = res[cur - 2] / res[cur - 1];
                 cur = cur - 1;
                 break;
             case '+':
                 res[cur - 2] = res[cur - 2] + res[cur - 1];
                 cur = cur - 1;
                 break;
             case '-':
                 res[cur - 2] = res[cur - 2] - res[cur - 1];
                 cur = cur - 1;
                 break;
             }
         }
     }
     if (cur == 0)
     {
         res[cur] = cal(chif);
         len = 0;
         cur++;
     }*/
    fclose(fun);
    fclose(con);
    fclose(input);
}
