#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculate_circle.h"

int ESC;

int main()
{
    // printf("This message will be displayed once.\nTo exit the program, press
    // ESC.\n\n");

    // while ((ESC = getch()) != 27) { // only works on Windows
    char circle[] = "circle";
    char object[50];
    char input[50];

    char x[20], y[20], radius[20];

    int i, index;
    double x_num, y_num, radius_num, area_num, perimetr_num;

    int bracket_open = 0, bracket_close = 0, comma_counter = 0;
    int error_bracket_open = 0, error_bracket_close = 0;

    for (int i = 0; i < 50; i++) { // clear arrays
        object[i] = '\0';
        input[i] = '\0';
    }

    printf("enter the circle parameters in WKT format: ");
    fgets(input, sizeof(input), stdin); // get input from the user

    // convert input to lowercase
    for (unsigned int j = 0; j < strlen(input); j++)
        input[j] = tolower(input[j]);

    // remove extra spaces from the input
    for (unsigned int j = 0, m = 0; j < strlen(input); j++) {
        if ((input[j]) == ' ' && (input[j + 1] == ' '))
            continue;
        else {
            object[m] = input[j];
            m++;
        }
    }

    // check if input starts with "circle"
    if (object[0] == 'c') {
        for (i = 0; isalpha(object[i]) != 0; i++) {
            if (object[i] != circle[i]) {
                for (int k = 0; k < i; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at column %d: expected 'circle'\n", i + 1);
            }
        }
        // check if the input has a "("
        if (object[strlen(circle) + 1] != '(')
            error_bracket_open = strlen(circle) + 1;

        // check if the input has a ")" at the end
        if (object[strlen(object)] != ')')
            error_bracket_close = strlen(object);

        // count number of brackets and commas in the input
        for (unsigned int j = 0; j < strlen(object); j++) {
            if (object[j] == '(')
                bracket_open++;
            if (object[j] == ')')
                bracket_close++;
            if (object[j] == ',')
                comma_counter++;
        }
        // if number of OPENING braces in not equal to one, show the error
        if (bracket_open != 1) {
            for (int k = 0; k < error_bracket_open - 1; k++)
                printf(" ");
            printf("^\n");
            printf("Error at column %d: expected '('", error_bracket_open);
        }
        // if number of CLOSING braces in not equal to one, show the error
        if (bracket_close != 1) {
            for (int k = 0; k < error_bracket_close - 1; k++)
                printf(" ");
            printf("^\n");
            printf("Error at column %d: expected ')'", error_bracket_close);
        }
        // if number of commas in not equal to one, show the error
        if (comma_counter != 1) {
            printf("Error: expected 'circle(x y, r)'\n");
        }
        // loop until get the X (res: "circle(* ")
        for (int j = 0; object[i] != ' '; j++) {
            if (object[i] == ')') { // if circle(*)
                printf("Error: expected 'circle(x y, r)'\n");
            }
            if (object[i] == ',') { // if circle(*,
                printf("Error: expected 'circle(x y, r)'\n");
            }
            for (i = i + 1; object[i] != ' '; i++, j++) {
                x[j] = object[i];
            }
            index = j;
        } // created by Shipilov, Sivov, Maistrenko

        x_num = atof(x); // x_num is a double type x
        int indexX = index;

        for (int j = 0, point = 0, minus = 0; j < index; j++) {
            if (x[0] == '.') {
                for (unsigned int k = 0; k < strlen(circle) + 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %ld: expected '<double>'\n",
                       strlen(circle) + 2);
            }
            if (x[j] == '.')
                point++;
            if (x[j] == '-')
                minus++;
            if (isalpha(x[j]) != 0) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
            if (point > 1 || minus > 1) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
        }

        for (int j = 0; object[i] != ','; j++) {
            if (object[i] == ')') {
                printf("Error: expected 'circle(x y, r)'\n");
            }
            for (i = i + 1; object[i] != ','; i++, j++) {
                y[j] = object[i];
            }
            index = j;
        }

        y_num = atof(y);

        for (int j = 0, point = 0, minus = 0; j < index; j++) {
            if (y[0] == '.') {
                for (unsigned int k = 0; k < strlen(circle) + indexX + 2; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %ld: expected '<double>'\n",
                       strlen(circle) + indexX + 3);
            }
            if (y[j] == '.')
                point++;
            if (y[j] == '-')
                minus++;
            if (isalpha(y[j]) != 0) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
            if (point > 1 || minus > 1) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
        }

        int indexY = index;

        for (int j = 0; object[i] != ')'; j++) {
            for (i = i + 2; object[i] != ')'; i++, j++) {
                radius[j] = object[i];
            }
            index = j;
        }

        radius_num = atof(radius);
        for (int j = 0, point = 0, minus = 0; j < index; j++) {
            if (radius[0] == '.') {
                for (unsigned int k = 0;
                     k < strlen(circle) + indexX + indexY + 4;
                     k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %ld: expected '<double>'\n",
                       strlen(circle) + indexX + indexY + 5);
            }
            if (radius[j] == '.')
                point++;
            if (radius[j] == '-') {
                for (unsigned int k = 0; k < i - strlen(radius) + 2; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected positive number\n", i);
            }
            if (isalpha(radius[j]) != 0) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
            if (point > 1 || minus > 1) {
                for (int k = 0; k < i - 1; k++)
                    printf(" ");
                printf("^\n");
                printf("Error at collum %d: expected '<double>'\n", i);
            }
        }

        if (i + 1u != strlen(object) - 1) {
            printf("Error at column %d: unexpected token", i);
        }

        printf("%s", object);
        calculate_circle(radius_num, &area_num, &perimetr_num);
        printf("x = %f\ny = %f\nRadius = %f\nArea = %f\nPerimetr = %f\n",
               x_num,
               y_num,
               radius_num,
               area_num,
               perimetr_num);
    }

    else {
        printf("\nError at first word: expected 'circle'");
    }
    // }
    return 0;
}
