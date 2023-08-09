
#include <stdio.h>
#include <fenv.h>

void show_registers_fe(int exception) {
    printf("EXEÇÃO FE_INEXACT: %d\n", (exception & FE_INEXACT) > 0);
    printf("EXEÇÃO FE_DIVBYZERO: %d\n", (exception & FE_DIVBYZERO) > 0);
    printf("EXEÇÃO FE_UNDERFLOW: %d\n", (exception & FE_UNDERFLOW) > 0);
    printf("EXEÇÃO FE_OVERFLOW: %d\n", (exception & FE_OVERFLOW) > 0);
    printf("EXEÇÃO FE_INVALID: %d\n\n", (exception & FE_INVALID) > 0);
}

void print_float_in_binary_number(float number) {
    int val2 = *((int*)&number);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (val2 >> i) & 1);
        if (i == 31 || i == 23) {
            printf(" ");
        }
    }
}

int main(int argc, char const *argv[])
{
    float number, number2, result;
    char op[] = "+";
    int exception;

    // number = 21.1f;
    // number2 = 2.2f;
    scanf("%f %s %f", &number, op, &number2);

    feclearexcept(FE_ALL_EXCEPT);
    // exception = fetestexcept(FE_ALL_EXCEPT);
    // show_registers_fe(exception);

    switch (*op) {
        case '+':
            result = number + number2;
            break;
        case '-':
            result = number - number2;
            break;
        case '*':
            result = number * number2;
            break;
        case '/':
            result = number / number2;
            break;
        default:
            printf("Operação inválida\n");
            return 1;
    }

    exception = fetestexcept(FE_ALL_EXCEPT);
    printf("Recebi %f %s %f e deu %f\n\n", number, op, number2, result);

    printf("val1 = ");
    print_float_in_binary_number(number);
    printf(" = %.26f\n", number);

    printf("val2 = ");
    print_float_in_binary_number(number2);
    printf(" = %.26f\n", number2);

    printf("res =  ");
    print_float_in_binary_number(result);
    printf(" = %.26f\n\n", result);

    show_registers_fe(exception);
    return 0;
}