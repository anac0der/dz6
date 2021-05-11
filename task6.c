#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define m1 2 //константа для методов касательных и хорд, cчитается как минимум разностей производных всех функций по модулю на всех отрезках
#define p 0.3333 //константа для правила Рунге
#define e1 0.0001
#define e2 0.00001

double f1(double x);
double f2(double x);
double f3(double x);
double f1p(double x);
double f2p(double x);
double f3p(double x);

double root(double (*f)(double x), double (*g)(double x), double a, double b, double eps1, int *cnt){ // для функций с f` > 0 и f`` < 0 на нужном отрезке
    double f1prime = f(a) - g(a) - f(b) + g(b), x;
    double f2prime = f((a + b)/2) - g((a + b)/2) - 0.5 * (f(a) - g(a) + f(b) - g(b));
    if(f1prime * f2prime < 0){
    	double h = f(b) - g(b), k = f(a) - g(a);
    	x = b;
    	while(fabsl(h) >= m1 * eps1){ //(11.12) в ИСС
        	x = x - h * (x - a)/(h - k);
        	h = f(x) - g(x);
        	(*cnt)++;
        }
    }
    else{
        double h = f(a) - g(a), k = f(b) - g(b);
        x = a;
    	while(fabsl(h) >= m1 * eps1){ //(11.12) в ИСС
        	x = x - h * (x - b)/(h - k);
        	h = f(x) - g(x);
        	(*cnt)++;
        }
    }
    return x;
}

double root_newton(double (*f)(double x), double (*g)(double x), double (*fp)(double x), double (*gp)(double x), double a, double b, double eps1, int *cnt){
	double f1prime = f(a) - g(a) - f(b) + g(b), x;
    double f2prime = f((a + b)/2) - g((a + b)/2) - 0.5 * (f(a) - g(a) + f(b) - g(b));
    if(f1prime * f2prime < 0){
        x = a;
    }
    else{
        x = b;
    }
    double h = f(x) - g(x);
    while(fabsl(h) >= m1 * eps1){ //(11.12) в ИСС
        	x = x - h / (fp(x) - gp(x));
        	h = f(x) - g(x);
        	(*cnt)++;
    }
    return x;
}

double integral(double(*f)(double x), double a, double b, double eps2){
    int n = 100;
    double sumn = 10, x_i, sum2n = 0;
    while(p * fabsl(sum2n - sumn) >= eps2){
    	sumn = sum2n;
    	sum2n = 0;
	    for(int i = 0; i < n; i++){
	        x_i = a + ((b - a)/(2 * n)) * (2 * i + 1);
	        sum2n += f(x_i) * (b - a)/n;
	    }
	    n *= 2;
    }
    return sum2n;
}

int main(int argc, char *argv[]){
    printf("%s\n%s\n%s\n", "Кривая 1: y = ln x", "Кривая 2: y = 14 - 2x", "Кривая 2: y = 1/(2 - x) + 6");
    int cnt12 = 0, cnt23 = 0, cnt13 = 0;  //счетчики числа итераций
    double x12 = 0, x13 = 0, x23 = 0;
    #ifdef newton
    x12 = root_newton(f1, f2, f1p, f2p, 5, 7, e1, &cnt12);
    x13 = root_newton(f3, f1, f3p, f1p, 2.1, 2.5, e1, &cnt13);
    x23 = root_newton(f3, f2, f3p, f2p, 4, 4.5, e1, &cnt23);
    #endif
    #ifdef secant
    x12 = root(f1, f2, 5, 7, e1, &cnt12);
    x13 = root(f3, f1, 2.1, 2.5, e1, &cnt13);
    x23 = root(f3, f2, 4, 4.5, e1, &cnt23);
    #endif
    double int3 = integral(f3, x13, x23, e2);
    double int1 = integral(f1, x13, x12, e2);
    double int2 = integral(f2, x23, x12, e2);
    //обработка аргументов командной строки
    int j = 1;
    double roots[6] = {0, 0, 0, x12, x13, x23};
    int counts[6] = {0, 0, 0, cnt12, cnt13, cnt23};
    int f_1, f_2, counter= 0;
    double a, b, eps;
    double (*arr[6])(double x)= {f1, f2, f3, f1p, f2p, f3p}; //массив функций и их производных
    while(j < argc){
        if(!strcmp(argv[j], "p")){ //печать точек пересечения
            sscanf(argv[j + 1], "%d", &f_1);
            sscanf(argv[j + 2], "%d", &f_2);
            printf("%s %d %s %d %s %lf\n", "Абсцисса пересечения кривыx", f_1, "и", f_2, ":", roots[f_1 + f_2]);
            printf("%s %d\n", "Количество итераций:", *(counts + f_1 + f_2));
            j += 3;
        }
        else if(!strcmp(argv[j], "r")){ //тестирование методов хорд и касательных
            sscanf(argv[j + 1], "%d", &f_1);
            sscanf(argv[j + 2], "%d", &f_2);
            sscanf(argv[j + 3], "%lf", &a);
            sscanf(argv[j + 4], "%lf", &b);
            sscanf(argv[j + 5], "%lf", &eps);
            double test_root = 0;
            #ifdef newton
            test_root = root_newton(*(arr + f_1 - 1), *(arr + f_2 - 1), *(arr + f_1 + 2), *(arr + f_2 + 2), a, b, eps, &counter);
            #endif
            #ifdef secant
            test_root = root(*(arr + f_1 - 1), *(arr + f_2 - 1), a, b, eps, &counter);
            #endif
            printf("%s %d %s %d %s %lf %s %lf %s %lf\n", "Абсцисса пересечения кривыx", f_1, "и", f_2, "на отрезке от", a, "до", b, ":", test_root);
            printf("%s %d\n", "Количество итераций:", counter);
            j += 6;
        }
        else if(!strcmp(argv[j], "i")){ //тестирование метода прямоугольников
            sscanf(argv[j + 1], "%d", &f_1);
            sscanf(argv[j + 2], "%lf", &a);
            sscanf(argv[j + 3], "%lf", &b);
            sscanf(argv[j + 4], "%lf", &eps);
            printf("%s %d %s %lf %s %lf %s %lf\n", "Площадь под кривой", f_1, "на отрезке от", a, "до", b, "равна", integral(*(arr + f_1 - 1), a, b, eps));
            j += 5 ;
        }
        else if(!strcmp(argv[j], "--help")){ // --help
            FILE *file = fopen("help.txt", "r");
            int s;
            while((s = fgetc(file)) >= 0){
                printf("%c", s);
            }
            fclose(file);
            j++;
        }
        else{
            j++;
        }
    }
    printf("%s %lf\n", "Площадь фигуры, ограниченной заданными кривыми, равна", int3 + int2 - int1);
    return 0;
}
