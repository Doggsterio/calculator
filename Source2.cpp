#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 20

typedef struct string_ {
    char str[SIZE] = {0};
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
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case'*':
        return 2;
        break;
    case'/':
        return 2;
        break;
    }
    return 0;
}

int push(char stack[], unsigned cur, char symb)
{
    if (cur < SIZE)
    {
        stack[cur++] = symb;
    }
    return cur;
}

int empty(const char stack[], unsigned cur)
{
    if (cur == 0)
        return 1;
    else return 0;
}

int pop(char stack[], unsigned cur)
{
    if (empty(stack, cur) != 1)
    {
        --cur;
    }
    return cur;
}

void make_polish(variables var[], char str[], int curva) {
    int len = 0, cur = 0;
    char symb[SIZE] = { 0 };
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            var[curva].polish.str[len] = str[i];
            len++;
        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if (var[curva].polish.str[len - 1] != ' ')
            {
                var[curva].polish.str[len] = ' ';
                len++;
            }
            if (empty(symb, cur))
            {
                cur = push(symb, cur, str[i]);
            }
            else
                if (prior(str[i]) > prior(symb[cur - 1]))
                    cur = push(symb, cur, str[i]);
                else if (prior(str[i]) <= prior(symb[cur - 1]))
                {
                    while (prior(str[i]) <= prior(symb[cur - 1]) && !(empty(symb, cur)))
                    {
                        var[curva].polish.str[len] = symb[cur - 1];
                        len++;
                        var[curva].polish.str[len] = ' ';
                        len++;
                        cur = pop(symb, cur);
                    }
                    cur = push(symb, cur, str[i]);
                }
        }
        if (str[i] == '(')
        {
            if (len == 0)
                cur = push(symb, cur, str[i]);
            else
            {
                if (var[curva].polish.str[len - 1] != ' ')
                {
                    var[curva].polish.str[len] = ' ';
                    len++;
                }
                cur = push(symb, cur, str[i]);
            }
        }
        if (str[i] == ')')
        {
            var[curva].polish.str[len] = ' ';
            len++;
            while (symb[cur - 1] != '(')
            {
                var[curva].polish.str[len] = symb[cur - 1];
                len++;
                var[curva].polish.str[len] = ' ';
                len++;
                cur = pop(symb, cur);
            }
            cur = pop(symb, cur);
        }
        if (str[i + 1] == '\0' || str[i + 1] == '\n')
        {
            if (var[curva].polish.str[len - 1] != ' ')
            {
                var[curva].polish.str[len] = ' ';
                len++;
            }
        }
    }
    while (!(empty(symb, cur)))
    {
        var[curva].polish.str[len] = symb[cur - 1];
        len++;
        if (var[curva].polish.str[len - 1] != ' ')
        {
            var[curva].polish.str[len] = ' ';
            len++;
        }
        cur = pop(symb, cur);
    }
}

int main()
{
    variables var[SIZE];
    char str[SIZE] = { 0 };
    char polish[SIZE] = { 0 };
    char symb[SIZE] = { 0 };
    char chif[SIZE] = { 0 };
    int res[SIZE] = { 0 };
    int curva = 0;
    while (true) {
        scanf("%s = %s", var[curva].name, &var[curva].original.str);
        if (strcmp(var[curva].name, "stop") == 0) {
            break;
        }
        else {
            make_polish(var, var[curva].original.str, curva);
        }
    }
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
    printf("Result:\n");
    printf("%d", res[0]);
}