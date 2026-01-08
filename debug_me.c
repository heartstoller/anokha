#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ptrace.h>

/*
 * One Binary – Seven Debugging Gates
 * Rules:
 *  - No recompilation
 *  - No patching source
 *  - Only GDB / pwndbg allowed
 */

int level = 1;

/* -------------------------------------------------- */
void banner() {
    puts("====================================");
    puts("         DEBUG ME IF YOU CAN        ");
    puts("====================================");
}

/* -------------------------------------------------- */
/* LEVEL 1 – Register Tampering */
int check(int key) {
    if (key == 0xdeadbeef)
        return 1;
    return 0;
}

void lvl1() {
    puts("[+] Level 1: Registers");
    int x = 0x1337;

    if (check(x)) {
        puts("Level 1 passed");
        level++;
    } else {
        puts("Level 1 failed");
        sleep(1);
    }
}

/* -------------------------------------------------- */
/* LEVEL 2 – Return Value Forgery */
int verify() {
    puts("Verifying password...");
    return 0;
}

void lvl2() {
    puts("[+] Level 2: Return Values");

    if (verify()) {
        puts("Level 2 passed");
        level++;
    } else {
        puts("Level 2 failed");
        sleep(1);
    }
}

/* -------------------------------------------------- */
/* LEVEL 3 – Stack Inspection (telescope) */
void lvl3() {
    puts("[+] Level 3: Stack Secrets");

    char secret[64];
    strcpy(secret, "LEVEL3_STACK_SECRET");

    puts("The secret is somewhere on the stack...");
    sleep(5);

    if (strcmp(secret, "LEVEL3_STACK_SECRET") == 0) {
        puts("Level 3 passed");
        level++;
    }
}

/* -------------------------------------------------- */
/* LEVEL 4 – Runtime Patching */
void lvl4() {
    puts("[+] Level 4: Patching");

    int auth = 0;

    if (auth) {
        puts("Level 4 passed");
        level++;
    } else {
        puts("Nope.");
        sleep(1);
    }
}

/* -------------------------------------------------- */
/* LEVEL 5 – GOT Hijack */
void lvl5() {
    puts("[+] Level 5: GOT Hijacking");

    puts("/bin/sh");
    puts("If this became a shell, you did it right 😉");

    level++;
}

/* -------------------------------------------------- */
/* LEVEL 6 – Heap Inspection */
struct user {
    int is_admin;
    char name[32];
};

void lvl6() {
    puts("[+] Level 6: Heap");

    struct user *u = malloc(sizeof(struct user));
    u->is_admin = 0;
    strcpy(u->name, "guest");

    if (u->is_admin) {
        puts("Welcome admin");
        level++;
    } else {
        puts("Not an admin");
        sleep(1);
    }

    free(u);
}

/* -------------------------------------------------- */
/* LEVEL 7 – Anti-Debugging */
void lvl7() {
    puts("[+] Level 7: Anti-Debugging");

    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        puts("Debugger detected! Exiting.");
        exit(0);
    }

    puts("Level 7 passed");
    level++;
}

/* -------------------------------------------------- */
int main() {
    banner();

    while (level <= 7) {
        switch (level) {
            case 1: lvl1(); break;
            case 2: lvl2(); break;
            case 3: lvl3(); break;
            case 4: lvl4(); break;
            case 5: lvl5(); break;
            case 6: lvl6(); break;
            case 7: lvl7(); break;
        }
    }

    puts("====================================");
    puts("FLAG{pwndbg_mastered}");
    puts("====================================");

    return 0;
}
