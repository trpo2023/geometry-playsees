#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define Size 30
#define pi 3.14

typedef struct point
{
    double x;
    double y;
} Point;

typedef struct circle
{
    Point p;
    double r;
} Circle;


void errPrint(int num, int errnum){
    for (int i = 0; i < num;i++)
        putchar(' ');
    putchar('^');
    printf("\n");
    switch (errnum)
    {
    case 1:
        printf("Error at column 0: expected 'circle'\n");
        exit(0);
        break;

    case 2:
        printf("Error at column %d: expected '<double>'\n", num+1);
        exit(0);
        break;
    case 3:
        printf("Error at column %d: expected ')'\n", num);
        exit(0);
        break;

    case 4:
        printf("Error at column %d: unexpected token\n", num);
        exit(0);
        break;
    case 5:
        printf("Error at column %d: excepcted '(' in line\n", num);
        exit(0);
        break;
    }
}

double getNumber(int* num){
    char curch;
    char temp[Size];
    int cnt = 0;
    char* end;
    while ((curch=getchar()) != ')')
    {
      temp[cnt] = curch;
        if (temp[cnt] == ' '){
            cnt++;
            break;
        }
        if (temp[cnt] == '.'){
            cnt++;
            continue;
        }
        if (temp[cnt] == ','){
            cnt++;
            cnt++;
            getchar();
            break;
        }
        if (temp[cnt] == ')'){
            cnt++;
            break;
        }
        if(temp[cnt] == '('){
            errPrint(*num+cnt, 3);
            exit(0);
        }
        if (temp[cnt] != '.' && (!isdigit(temp[cnt]))) {
                errPrint(*num+cnt, 2);
                exit(0);
            }
        cnt++;
    }
    *num += cnt+1;
    return strtod(temp,&end);
}

void getPointData(Point* p, int* num){
    p->x = getNumber(num);
    *num -= 1;
    p->y = getNumber(num);
    *num -= 1;
}

void tokenContron(int* num){
    char curch =getchar();
    if (curch != '\n'){
        if (curch != ' '){
            errPrint(*num, 4);
            exit(0);
        }
        else{
            if(getchar()=='\n')
                exit(0);
            else{
                *num += 1;
                errPrint(*num,4);
            }
        }
    }
}

void getCircleData(Circle* circle, int* num){
  getPointData(&circle->p, num);
    circle->r = getNumber(num);
    tokenContron(num);
}

void pushInfo(Circle* circle){
    printf("circle(%f %f, %f)\n", circle->p.x, circle->p.y, circle->r);
    double perimeter = 2 * pi * circle->r;
    double area = pi * circle->r * circle->r;
    printf("perimeter = %f\n", perimeter);
    printf("area = %f\n", area);
}


int main(){
    char str[Size];
    char curch;
    int symbnum = 0;
    char ach = '(';
    Circle circle;
    do
    {
        curch = getchar();

        if (curch == '('){
            if (strcmp(str, "circle") == 0){
                str[symbnum++] = curch;
                getCircleData(&circle, &symbnum);
                pushInfo(&circle);
                exit(0);
            }
            else
            {
                errPrint(0, 1);
            }
        }
        str[symbnum++] = curch;
        if (symbnum > 6 &&      (strchr(str, ach)== NULL))
                errPrint(0, 5);
        if (curch == '\n' || curch == EOF)
                break;
    } while (1);

        if (symbnum < 6 || curch == '\n')
                errPrint(0, 1);
    return 0;
}
