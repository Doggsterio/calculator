#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 100

typedef struct string_ {
    char str[SIZE];
}strings;

typedef struct variable {
    char name[20];
    char original[SIZE];
    char polish[SIZE];
    double res;
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
    case '~':
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

int is_fun(strings fun[SIZE], char buff[SIZE], int cur_fun) {
    for (int i = 0; i < cur_fun; i++) {
        if (strcmp(fun[i].str, buff) == 0) {
            return 1;
        }
    }
    return 0;
}

int is_const(strings con[SIZE], char buff[SIZE], int cur_con) {
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

double calculate_fun(double stack[SIZE], char temp[SIZE], int cur)
{
    if (strcmp(temp, "cos") == 0)
    {
        return cos(stack[cur - 1]);
    }
    else if (strcmp(temp, "sin") == 0)
    {
        return sin(stack[cur - 1]);
    }
    else if (strcmp(temp, "tg") == 0)
    {
        return sin(stack[cur - 1]) / cos(stack[cur - 1]);
    }
    else if (strcmp(temp, "ctg") == 0)
    {
        return cos(stack[cur - 1]) / sin(stack[cur - 1]);
    }
    else if (strcmp(temp, "exp") == 0)
    {
        return exp(stack[cur - 1]);
    }
    else if (strcmp(temp, "log") == 0)
    {
        return log(stack[cur - 1]);
    }
    else if (strcmp(temp, "sqrt") == 0)
    {
        return sqrt(stack[cur - 1]);
    }
    else if (strcmp(temp, "sqr") == 0)
    {
        return pow(stack[cur - 1], 2);
    }
    else if (strcmp(temp, "abs") == 0)
    {
        return abs(stack[cur - 1]);
    }
    //real & imag (?)
}

double calculate_const(double stack[SIZE], char temp[SIZE], int cur)
{
    if (strcmp(temp, "pi") == 0)
    {
        return 3.14159;
    }
    else if (strcmp(temp, "e") == 0)
    {
        return 2.71828;
    }
}

double calculate(double stack[SIZE], char temp[SIZE], int cur)
{
    double x = stack[cur - 2];
    double y = stack[cur - 1];
    switch (temp[0])
    {
    case '+':
        return x + y;
        break;
    case '-':
        return x - y;
        break;
    case '*':
        return x * y;
        break;
    case '/':
        return x / y;
        break;
    case '^':
        return pow(x, y);
        break;
    }
}

int is_sign(char temp[SIZE])
{
    if (strcmp(temp, "+") == 0 || strcmp(temp, "-") == 0 || strcmp(temp, "*") == 0 ||
        strcmp(temp, "/") == 0 || strcmp(temp, "^") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double variab(variables var[SIZE], char temp[SIZE], int curva)
{
    for (int i = curva - 1; i >= 0; --i)
    {
        if (strcmp(temp, var[i].name) == 0)
        {
            return var[i].res;
        }
    }
}

int main()
{
    variables var[SIZE] = { 0 };
    FILE *fun = fopen("function.txt", "r");
    FILE *con = fopen("const.txt", "r");
    FILE *input = fopen("input.txt", "r");
    FILE* counting = fopen("count.txt", "r+");
    FILE* ans = fopen("output.txt", "w");
    strings fun_arr[SIZE] = { 0 };
    strings con_arr[SIZE] = { 0 };
    strings stack[SIZE] = { 0 };
    char str[SIZE] = { 0 };
    char c = '0';
    int curva = 0, cur_fun = 0, cur_con = 0;
    int len = 0, cur = 0;
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
                        strcat(var[curva].polish, stack[cur - 1].str);
                        var[curva].polish[strlen(var[curva].polish)] = ' ';
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
                    strcat(var[curva].polish, stack[cur - 1].str);
                    var[curva].polish[strlen(var[curva].polish)] = ' ';
                    cur = pop(stack, cur);
                }
                cur = pop(stack, cur);
            }
            else if(strcmp(buff,"+") == 0 || strcmp(buff, "-") == 0 || strcmp(buff, "*") == 0 || strcmp(buff, "/") == 0 || strcmp(buff, "^") == 0 || strcmp(buff, "~") == 0) {
                if (empty(stack, cur) == 1) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) > prior(stack[cur - 1].str[0])) {
                    cur = push(stack, cur, buff);
                }
                else if (prior(buff[0]) <= prior(stack[cur - 1].str[0])) {
                    while (prior(buff[0]) <= prior(stack[cur - 1].str[0]) && !empty(stack, cur)) {
                        strcat(var[curva].polish, stack[cur - 1].str);
                        var[curva].polish[strlen(var[curva].polish)] = ' ';
                        cur = pop(stack, cur);
                    }
                    cur = push(stack, cur, buff);
                }
            }
            else {
                strcat(var[curva].polish, buff);
                var[curva].polish[strlen(var[curva].polish)] = ' ';
            }
            c = fgetc(input);
        }
        if (empty(stack, cur) != 1) {
            while (empty(stack, cur) != 1) {
                strcat(var[curva].polish, stack[cur - 1].str);
                var[curva].polish[strlen(var[curva].polish)] = ' ';
                cur = pop(stack, cur);
            }
        }
        curva++;
        len = 0;
        cur = 0;
    }

    for (int i = 0; i < curva; i++) {
        printf("%s\n", var[i].polish);
    }

    for (int i = curva - 1; i >= 0; --i)
    {
        fprintf(counting, "%s\n", var[i].polish);
    }

    rewind(counting);
    
    double stack1[SIZE] = { 0 };
    int cnt = 0;
    
    for (int i = curva - 1; i >= 0; --i)
    {
        char temp[SIZE] = { 0 };

        while (cnt != strlen(var[i].polish))
        {
            fscanf(counting, "%s", temp);
            c = fgetc(counting);

            if (atof(temp) != 0)
            {
                stack1[cur] = atof(temp);
                cur++;
            }
            else if (is_fun(fun_arr, temp, cur_fun) == 1)
            {
                stack1[cur - 1] = calculate_fun(stack1, temp, cur);
            }
            else if (is_const(con_arr, temp, cur_con) == 1)
            {
                stack1[cur] = calculate_const(stack1, temp, cur);
                cur++;
            }
            else if (is_sign(temp) == 1)
            {
                stack1[cur - 2] = calculate(stack1, temp, cur);
                cur--;
            }
            else if (strcmp(temp, "~") == 0)
            {
                stack1[cur - 1] = -stack1[cur - 1];
            }
            else
            {
                stack1[cur] = variab(var, temp, curva);
                cur++;
            }

            cnt += strlen(temp) + 1;
        }

        var[i].res = stack1[0];
        cur = 0;
        cnt = 0;
    }

    //for (int i = 0; i < curva; ++i)
    //{
    //    fprintf(ans, "%s = %lf\n", var[i].name, var[i].res);
    //}

    fprintf(ans, "Ответ: %s = %lf\n", var[0].name, var[0].res);

    fclose(fun);
    fclose(con);
    fclose(input);
    fclose(counting);
    fclose(ans);
}
