// Calculator Project in C
// BCA 1st Semester

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 10   // how many calculations we keep in history

char history[MAX][60];
int count = 0;

// removes leftover characters from the input
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// asks the user for a number until they enter a valid one
double get_number(char msg[]) {
    double n;
    while (1) {
        printf("%s", msg);
        if (scanf("%lf", &n) == 1) {
            clear_buffer();
            return n;
        }
        if (feof(stdin)) {
            printf("\nInput ended. Bye!\n");
            exit(0);
        }
        printf("Invalid input! Please enter a number.\n");
        clear_buffer();
    }
}

// same thing but for the menu choice (integer)
int get_choice() {
    int ch;
    while (1) {
        printf("Enter your choice: ");
        if (scanf("%d", &ch) == 1) {
            clear_buffer();
            return ch;
        }
        if (feof(stdin)) {
            printf("\nInput ended. Bye!\n");
            exit(0);
        }
        printf("Invalid choice! Enter a number from the menu.\n");
        clear_buffer();
    }
}

// saves a calculation in history
void save_history(char text[]) {
    int i;
    if (count == MAX) {
        // history is full, remove the oldest one
        for (i = 0; i < MAX - 1; i++) {
            strcpy(history[i], history[i + 1]);
        }
        count--;
    }
    strcpy(history[count], text);
    count++;
}

// asks if the user wants to continue, returns 1 for yes and 0 for no
int ask_continue() {
    char again;
    while (1) {
        printf("\nDo you want to continue? (y/n): ");
        if (scanf(" %c", &again) != 1) {
            return 0;   // input ended
        }
        clear_buffer();
        if (again == 'y' || again == 'Y') {
            return 1;
        }
        if (again == 'n' || again == 'N') {
            return 0;
        }
        printf("Please type y or n only.\n");
    }
}

void show_history() {
    int i;
    if (count == 0) {
        printf("History is empty.\n");
        return;
    }
    printf("\n--- History ---\n");
    for (i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

void show_menu() {
    printf("\n========== CALCULATOR ==========\n");
    printf(" 1. Addition\n");
    printf(" 2. Subtraction\n");
    printf(" 3. Multiplication\n");
    printf(" 4. Division\n");
    printf(" 5. Modulus\n");
    printf(" 6. Power\n");
    printf(" 7. Square Root\n");
    printf(" 8. Factorial\n");
    printf(" 9. Percentage\n");
    printf("10. Show History\n");
    printf(" 0. Exit\n");
    printf("================================\n");
}

int main() {
    int choice, i, n;
    double a, b, result;
    long long fact;
    char text[60];

    do {
        show_menu();
        choice = get_choice();

        if (choice == 0) {
            break;   // exit without asking y/n
        }

        switch (choice) {
            case 1:
                a = get_number("Enter first number: ");
                b = get_number("Enter second number: ");
                result = a + b;
                printf("Result = %g\n", result);
                sprintf(text, "%g + %g = %g", a, b, result);
                save_history(text);
                break;

            case 2:
                a = get_number("Enter first number: ");
                b = get_number("Enter second number: ");
                result = a - b;
                printf("Result = %g\n", result);
                sprintf(text, "%g - %g = %g", a, b, result);
                save_history(text);
                break;

            case 3:
                a = get_number("Enter first number: ");
                b = get_number("Enter second number: ");
                result = a * b;
                printf("Result = %g\n", result);
                sprintf(text, "%g * %g = %g", a, b, result);
                save_history(text);
                break;

            case 4:
                a = get_number("Enter first number: ");
                b = get_number("Enter second number: ");
                if (b == 0) {
                    printf("Error: cannot divide by zero!\n");
                } else {
                    result = a / b;
                    printf("Result = %g\n", result);
                    sprintf(text, "%g / %g = %g", a, b, result);
                    save_history(text);
                }
                break;

            case 5:
                a = get_number("Enter first number: ");
                b = get_number("Enter second number: ");
                if (b == 0) {
                    printf("Error: modulus by zero is not allowed!\n");
                } else {
                    result = fmod(a, b);
                    printf("Result = %g\n", result);
                    sprintf(text, "%g %% %g = %g", a, b, result);
                    save_history(text);
                }
                break;

            case 6:
                a = get_number("Enter base: ");
                b = get_number("Enter power: ");
                result = pow(a, b);
                if (isnan(result) || isinf(result)) {
                    printf("Error: result is not valid or too big!\n");
                } else {
                    printf("Result = %g\n", result);
                    sprintf(text, "%g ^ %g = %g", a, b, result);
                    save_history(text);
                }
                break;

            case 7:
                a = get_number("Enter a number: ");
                if (a < 0) {
                    printf("Error: square root of negative number is not possible!\n");
                } else {
                    result = sqrt(a);
                    printf("Result = %g\n", result);
                    sprintf(text, "sqrt(%g) = %g", a, result);
                    save_history(text);
                }
                break;

            case 8:
                a = get_number("Enter a whole number (0 to 20): ");
                if (a < 0 || a != (int)a) {
                    printf("Error: enter a positive whole number!\n");
                } else if (a > 20) {
                    printf("Error: number is too big (max 20)!\n");
                } else {
                    n = (int)a;
                    fact = 1;
                    for (i = 1; i <= n; i++) {
                        fact = fact * i;
                    }
                    printf("Result = %lld\n", fact);
                    sprintf(text, "%d! = %lld", n, fact);
                    save_history(text);
                }
                break;

            case 9:
                a = get_number("Enter percentage: ");
                b = get_number("Enter the number: ");
                result = (a * b) / 100;
                printf("Result = %g\n", result);
                sprintf(text, "%g%% of %g = %g", a, b, result);
                save_history(text);
                break;

            case 10:
                show_history();
                break;

            default:
                printf("Invalid choice! Please select 0 to 10.\n");
        }

    } while (ask_continue());

    printf("Thank you for using the calculator!\n");
    return 0;
}
