#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void strToLower(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        str[i] = tolower(str[i]);
}

int checkFigure(char* str)
{
    int ret = 1;
    char rec[SIZE];
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] != '(')
            rec[i] = str[i];
        else
            break;
    }
    char figure[] = "circle";
    if (strcmp(rec, figure) == 0) {
        ret = 0;
    }
    return ret;
}

int checkArguments(char* str)
{
    int ret = 0;
    int count = 0;
    for (int i = 7; str[i] != ',' && i < strlen(str); i++) {
        if ((str[i] != '.' && str[i] != ' ')
            && !(str[i] >= 48 && str[i] <= 57)) {
            printf("Figure coordinates entered incorrectly\n\n");
            ret++;
            return 1;
        }
        if (str[i] >= 48 && str[i] <= 57 && str[i + 1] == ' ')
            count++;
        if (str[i] == '.' && str[i + 1] == ')')
            count += 2;
    }
    if (count + 1 != 2) {
        printf("Figure coordinates entered incorrectly\n\n");
        ret++;
        return ret;
    }
    int index = 0;
    for (int i = 0; i != strlen(str); i++) {
        if (str[i] == ',') {
            index = i + 1;
            i = strlen(str) - 1;
        }
    }
    for (; str[index] != ')' && index < strlen(str); index++) {
        if ((str[index] != '.' && str[index] != ' ')
            && !(str[index] >= 48 && str[index] <= 57)) {
            printf("Figure radius entered incorrectly\n\n");
            ret++;
            return 1;
        }
        if (str[index] >= 48 && str[index] <= 57 && str[index + 1] == ' ')
            count++;
        if (str[index] == '.' && str[index + 1] == ' ')
            count += 2;
    }
    if (count != 1) {
        printf("Figure radius entered incorrectly\n\n");
        ret++;
    }
    return ret;
}

int checkEnd(char* str)
{
    int ret = 1, firstBracket = 0;
    int endingSymbol;
    if (str[strlen(str) - 1] == '\n')
        endingSymbol = strlen(str) - 2;
    else
        endingSymbol = strlen(str) - 1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ')') {
            firstBracket = i;
            break;
        }
    }
    if (firstBracket == endingSymbol)
        ret = 0;
    return ret;
}

int printErrors(char* str, int countFigures)
{
    printf("Figure %d:\n", countFigures);
    printf("%s", str);
    if (checkFigure(str))
        printf("Incorrect input of figure name\n\n");
    else if (checkArguments(str))
        return 0;
    else if (checkEnd(str))
        printf("Wrong final symbol\n\n");
   
    return 0;
}

int main()
{
    FILE* file;
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error of oppening file!");
        return 1;
    }
    char str1[SIZE];
    int countFigures = 0;
    while (fgets(str1, SIZE, file)) {
        countFigures++;
        strToLower(str1);
        printErrors(str1, countFigures);
    }
    fclose(file);
    return 0;
}
