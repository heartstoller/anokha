#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
 * pwndbg Basics Playground
 * Purpose: Teach GDB / pwndbg commands
 */

int global_flag = 0;

/* ---------------------------------- */
void countdown(int n) {
    while (n > 0) {
        printf("Count: %d\n", n);
        n--;

        if (n == 2)
            puts("Almost there");
    }
}

/* ---------------------------------- */
int compute_sum(int limit) {
    int sum = 0;

    for (int i = 0; i < limit; i++) {
        sum += i;

        if (sum > 20)
            break;
    }

    return sum;
}

/* ---------------------------------- */
void process_input(const char *input) {
    char buf[32];

    strcpy(buf, input);

    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] == 'a')
            global_flag++;
        else
            global_flag--;
    }

    if (global_flag > 5)
        puts("High flag");
    else
        puts("Low flag");
}

/* ---------------------------------- */
void decision(int x) {
    if (x < 0)
        puts("Negative");
    else if (x < 10)
        puts("Small");
    else if (x < 20)
        puts("Medium");
    else
        puts("Large");
}

/* ---------------------------------- */
int main() {
    puts("Starting pwndbg basics");

    countdown(5);

    int result = compute_sum(10);
    printf("Result = %d\n", result);

    process_input("banana");

    decision(result);

    puts("Done");
    return 0;
}
