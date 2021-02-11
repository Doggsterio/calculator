#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 10000

typedef struct string_ {
    char str[SIZE];
}string;

int cal(char str[])
{
    int a = 0, power, count = 0;
    power = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++)
    {
        a = a + (str[i] - '0') * pow(10, power);
        power--;
    }
    while (str[count] != '\0')
    {
        str[count] = '\0';
        count++;
    }
    return a;
}

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

int main()
{
    char str[SIZE] = { 0 };
    char polish[SIZE] = { 0 };
    char symb[SIZE] = { 0 };
    char chif[SIZE] = { 0 };
    int res[SIZE] = { 0 };
    int len = 0, a = 0, cur = 0;
    fgets(str, SIZE, stdin);
    printf("Expression:\n");
    printf("%s\n", str);
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            polish[len] = str[i];
            len++;
        }
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
        {
            if (polish[len - 1] != ' ')
            {
                polish[len] = ' ';
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
                        polish[len] = symb[cur - 1];
                        len++;
                        polish[len] = ' ';
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
                if (polish[len - 1] != ' ')
                {
                    polish[len] = ' ';
                    len++;
                }
                cur = push(symb, cur, str[i]);
            }
        }
        if (str[i] == ')')
        {
            polish[len] = ' ';
            len++;
            while (symb[cur - 1] != '(')
            {
                polish[len] = symb[cur - 1];
                len++;
                polish[len] = ' ';
                len++;
                cur = pop(symb, cur);
            }
            cur = pop(symb, cur);
        }
        if (str[i + 1] == '\0' || str[i + 1] == '\n')
        {
            if (polish[len - 1] != ' ')
            {
                polish[len] = ' ';
                len++;
            }
        }
    }
    while (!(empty(symb, cur)))
    {
        polish[len] = symb[cur - 1];
        len++;
        if (polish[len - 1] != ' ')
        {
            polish[len] = ' ';
            len++;
        }
        cur = pop(symb, cur);
    }
    printf("Reverse Polish Notation:\n");
    printf("%s\n", polish);
    len = 0;
    cur = 0;
    for (int i = 0; i < strlen(polish) - 1; i++)
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
    }
    printf("Result:\n");
    printf("%d", res[0]);
}
