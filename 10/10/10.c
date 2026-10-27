#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <math.h>

double f1(double x);
double f2(double x);
double sinN(double x, int n);
double sinEps(double x, double eps);
double rectangleArea(double height, double width);
const char* figureDefinition(int figureType);
char drawRectanglePosition(int row, int col, int height, int width, char symbol);

int main()
{
    double x;
    double first;
    double second;
    double result;
    double eps;
    int choice;
    int n;

    double height;
    double width;
    char symbol;
    int row;
    int col;
    int figureChoice;

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF8");

    /* Задание 1 */
    printf("\nЗАДАНИЕ 1. Функции F1(x) и F2(x)\n");
    printf("Введите x: ");
    if (scanf_s("%lf", &x) == 1)
    {
        first = f1(x);
        second = f2(x);

        printf("F1(x) = %.6f\n", first);
        printf("F2(x) = %.6f\n", second);

        printf("\nВыберите операцию:\n");
        printf("1 - произведение F1 и F2\n");
        printf("2 - разность квадратов F1 и F2\n");
        printf("3 - удвоенная сумма F1 и F2\n");
        printf("Ваш выбор: ");

        if (scanf_s("%d", &choice) == 1)
        {
            if (choice == 1)
            {
                result = first * second;
                printf("Произведение = %.6f\n", result);
            }
            else if (choice == 2)
            {
                result = first * first - second * second;
                printf("Разность квадратов = %.6f\n", result);
            }
            else if (choice == 3)
            {
                result = 2.0 * (first + second);
                printf("Удвоенная сумма = %.6f\n", result);
            }
            else
            {
                printf("Ошибка: такого пункта меню нет.\n");
            }
        }
        else
        {
            printf("Ошибка ввода операции.\n");
        }
    }
    else
    {
        printf("Ошибка ввода x.\n");
    }

    /* Задание 2 */
    printf("\nЗАДАНИЕ 2. Вычисление sin(x) тремя способами\n");
    printf("Введите x в радианах: ");

    if (scanf_s("%lf", &x) == 1)
    {
        printf("Введите количество членов ряда N: ");
        if (scanf_s("%d", &n) == 1 && n > 0)
        {
            printf("Введите точность eps (больше нуля): ");
            if (scanf_s("%lf", &eps) == 1 && eps > 0.0)
            {
                printf("sin(x) из библиотеки = %.10f\n", sin(x));
                printf("sin(x) суммой N членов = %.10f\n", sinN(x, n));
                printf("sin(x) с точностью eps = %.10f\n", sinEps(x, eps));
            }
            else
            {
                printf("Ошибка: точность должна быть больше нуля.\n");
            }
        }
        else
        {
            printf("Ошибка: N должно быть положительным целым числом.\n");
        }
    }
    else
    {
        printf("Ошибка ввода x.\n");
    }

    /* Задание 3 — индивидуальное */
    printf("\nЗАДАНИЕ 3. Работа с прямоугольником\n");
    printf("Введите высоту прямоугольника: ");
    if (scanf_s("%lf", &height) == 1 && height > 0.0)
    {
        printf("Введите ширину прямоугольника: ");
        if (scanf_s("%lf", &width) == 1 && width > 0.0)
        {
            printf("Введите символ для рисования: ");
            if (scanf_s(" %c", &symbol, 1) == 1)
            {
                printf("\nВыберите операцию:\n");
                printf("1 - вычислить площадь\n");
                printf("2 - вывести определение фигуры\n");
                printf("3 - нарисовать фигуру\n");
                printf("Ваш выбор: ");

                if (scanf_s("%d", &figureChoice) == 1)
                {
                    if (figureChoice == 1)
                    {
                        result = rectangleArea(height, width);
                        printf("Площадь прямоугольника = %.2f\n", result);
                    }
                    else if (figureChoice == 2)
                    {
                        printf("%s\n", figureDefinition(1));
                    }
                    else if (figureChoice == 3)
                    {
                        int drawHeight = (int)height;
                        int drawWidth = (int)width;

                        if (drawHeight > 0 && drawWidth > 0 &&
                            drawHeight <= 30 && drawWidth <= 60)
                        {
                            for (row = 0; row < drawHeight; row++)
                            {
                                for (col = 0; col < drawWidth; col++)
                                {
                                    printf("%c", drawRectanglePosition(
                                        row, col, drawHeight, drawWidth, symbol));
                                }
                                printf("\n");
                            }
                        }
                        else
                        {
                            printf("Для рисования задайте целые размеры: высота 1-30, ширина 1-60.\n");
                        }
                    }
                    else
                    {
                        printf("Ошибка: такого пункта меню нет.\n");
                    }
                }
                else
                {
                    printf("Ошибка ввода операции.\n");
                }
            }
            else
            {
                printf("Ошибка ввода символа.\n");
            }
        }
        else
        {
            printf("Ошибка: ширина должна быть больше нуля.\n");
        }
    }
    else
    {
        printf("Ошибка: высота должна быть больше нуля.\n");
    }

    return 0;
}

double f1(double x)
{
    if (x <= 3.0)
    {
        return x * x - 3.0 * x + 9.0;
    }

    return 1.0 / (x * x * x + 3.0);
}

double f2(double x)
{
    return x * exp(sin(x * x));
}

double sinN(double x, int n)
{
    double sum = x;
    double term = x;
    int k;

    for (k = 2; k <= n; k++)
    {
        term = -term * x * x / ((2.0 * k - 2.0) * (2.0 * k - 1.0));
        sum += term;
    }

    return sum;
}

double sinEps(double x, double eps)
{
    double sum = x;
    double term = x;
    int k = 2;

    while (fabs(term) > eps && k < 10000)
    {
        term = -term * x * x / ((2.0 * k - 2.0) * (2.0 * k - 1.0));
        sum += term;
        k++;
    }

    return sum;
}

double rectangleArea(double height, double width)
{
    return height * width;
}

const char* figureDefinition(int figureType)
{
    if (figureType == 1)
    {
        return "Прямоугольник — четырёхугольник, у которого все углы прямые.";
    }

    return "Неизвестная фигура.";
}

char drawRectanglePosition(int row, int col, int height, int width, char symbol)
{
    if (row >= 0 && row < height && col >= 0 && col < width)
    {
        return symbol;
    }

    return ' ';
}
