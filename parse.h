// START OF PARSING TEMPLATE FOR C CHECKERS
#include<string.h>
#include <ctype.h>

#define INT_BOUND 11
#define UINT_BOUND 10
#define LLONG_BOUND 20
#define ULLONG_BOUND 20

static char INT_MAX_BOUND[] = "2147483647";
static char INT_MIN_BOUND[] = "-2147483648";
static char UINT_MAX_BOUND[] = "4294967296";

static char LLONG_MAX_BOUND[] = "9223372036854775807";
static char LLONG_MIN_BOUND[] = "-9223372036854775808";
static char ULLONG_MAX_BOUND[] = "18446744073709551616";

unsigned long long fread_ulong(FILE *in) {
    char line[ULLONG_BOUND + 1];
    char c = fgetc(in);
    while(c == ' ' || c == '\n') c = fgetc(in);
    if(c == '-') {
        printf("Underflow error.");
        exit(132);
    }
    int at = 0;
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        c = fgetc(in);
        if(at == ULLONG_BOUND) break;
    }
    line[at] = '\0';
    if(at == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(strlen(line) > strlen(ULLONG_MAX_BOUND)) {
        printf("Overflow error.");
        exit(132);
    }
    if(strlen(line) == strlen(ULLONG_MAX_BOUND) && strcmp(line, ULLONG_MAX_BOUND) == 1) {
        printf("Overflow error.");
        exit(132);
    }
    unsigned long long res = 0;
    int start = 0;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return res;
}

long long fread_long(FILE *in) {
    char line[LLONG_BOUND + 1];
    char c = fgetc(in);
    while(c == ' ' || c == '\n') c = fgetc(in);
    int at = 0;
    int digits = 0;
    if(c == '-') {
        line[at++] = c;
        c = fgetc(in);
    }
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        digits++;
        c = fgetc(in);
        if(at == LLONG_BOUND) break;
    }
    line[at] = '\0';
    if(digits == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(line[0] == '-') {
        if(strlen(line) > strlen(LLONG_MIN_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(LLONG_MIN_BOUND) && strcmp(line, LLONG_MIN_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    else {
        if(strlen(line) > strlen(LLONG_MAX_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(LLONG_MAX_BOUND) && strcmp(line, LLONG_MAX_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    long long res = 0;
    int start = 0;
    if(line[0] == '-') start++;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return line[0] == '-' ? -res : res;
}

unsigned int fread_uint(FILE *in) {
    char line[UINT_BOUND + 1];
    char c = fgetc(in);
    while(c == ' ' || c == '\n') c = fgetc(in);
    if(c == '-') {
        printf("Underflow error.");
        exit(132);
    }
    int at = 0;
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        c = fgetc(in);
        if(at == UINT_BOUND) break;
    }
    line[at] = '\0';
    if(at == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(strlen(line) > strlen(UINT_MAX_BOUND)) {
        printf("Overflow error.");
        exit(132);
    }
    if(strlen(line) == strlen(UINT_MAX_BOUND) && strcmp(line, UINT_MAX_BOUND) == 1) {
        printf("Overflow error.");
        exit(132);
    }
    unsigned int res = 0;
    int start = 0;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return res;
}

int fread_int(FILE *in) {
    char line[INT_BOUND + 1];
    char c = fgetc(in);
    while(c == ' ' || c == '\n') c = fgetc(in);
    int at = 0;
    int digits = 0;
    if(c == '-') {
        line[at++] = c;
        c = fgetc(in);
    }
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        digits++;
        c = fgetc(in);
        if(at == INT_BOUND) break;
    }
    line[at] = '\0';
    if(digits == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(line[0] == '-') {
        if(strlen(line) > strlen(INT_MIN_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(INT_MIN_BOUND) && strcmp(line, INT_MIN_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    else {
        if(strlen(line) > strlen(INT_MAX_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(INT_MAX_BOUND) && strcmp(line, INT_MAX_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    int res = 0;
    int start = 0;
    if(line[0] == '-') start++;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return line[0] == '-' ? -res : res;
}

unsigned long long read_ulong() {
    char line[ULLONG_BOUND + 1];
    char c = getchar();
    while(c == ' ' || c == '\n') c = getchar();
    if(c == '-') {
        printf("Underflow error.");
        exit(132);
    }
    int at = 0;
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        c = getchar();
        if(at == ULLONG_BOUND) break;
    }
    line[at] = '\0';
    if(at == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(strlen(line) > strlen(ULLONG_MAX_BOUND)) {
        printf("Overflow error.");
        exit(132);
    }
    if(strlen(line) == strlen(ULLONG_MAX_BOUND) && strcmp(line, ULLONG_MAX_BOUND) == 1) {
        printf("Overflow error.");
        exit(132);
    }
    unsigned long long res = 0;
    int start = 0;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return res;
}

long long read_long() {
    char line[LLONG_BOUND + 1];
    char c = getchar();
    while(c == ' ' || c == '\n') c = getchar();
    int at = 0;
    int digits = 0;
    if(c == '-') {
        line[at++] = c;
        c = getchar();
    }
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        digits++;
        c = getchar();
        if(at == LLONG_BOUND) break;
    }
    line[at] = '\0';
    if(digits == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(line[0] == '-') {
        if(strlen(line) > strlen(LLONG_MIN_BOUND)) {
            printf("Underflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(LLONG_MIN_BOUND) && strcmp(line, LLONG_MIN_BOUND) == 1) {
            printf("Underflow error.");
            exit(132);
        }
    }
    else {
        if(strlen(line) > strlen(LLONG_MAX_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(LLONG_MAX_BOUND) && strcmp(line, LLONG_MAX_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    long long res = 0;
    int start = 0;
    if(line[0] == '-') start++;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return line[0] == '-' ? -res : res;
}

unsigned int read_uint() {
    char line[UINT_BOUND + 1];
    char c = getchar();
    while(c == ' ' || c == '\n') c = getchar();
    if(c == '-') {
        printf("Underflow error.");
        exit(132);
    }
    int at = 0;
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        c = getchar();
        if(at == UINT_BOUND) break;
    }
    line[at] = '\0';
    if(at == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(strlen(line) > strlen(UINT_MAX_BOUND)) {
        printf("Overflow error.");
        exit(132);
    }
    if(strlen(line) == strlen(UINT_MAX_BOUND) && strcmp(line, UINT_MAX_BOUND) == 1) {
        printf("Overflow error.");
        exit(132);
    }
    unsigned int res = 0;
    int start = 0;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return res;
}

int read_int() {
    char line[INT_BOUND + 1];
    char c = getchar();
    while(c == ' ' || c == '\n') c = getchar();
    int at = 0;
    int digits = 0;
    if(c == '-') {
        line[at++] = c;
        c = getchar();
    }
    while(c != ' ' && c != '\n') {
        if(!isdigit(c)) {
            printf("Invalid type. There is a non-digit character in the input\n");
            exit(132);
        }
        line[at++] = c;
        digits++;
        c = getchar();
        if(at == INT_BOUND) break;
    }
    line[at] = '\0';
    if(digits == 0) {
        printf("No digits found.\n");
        exit(132);
    }
    if(isdigit(c)) {
        printf("Overflow error.\n");
        exit(132);
    }
    if(line[0] == '-') {
        if(strlen(line) > strlen(INT_MIN_BOUND)) {
            printf("Underflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(INT_MIN_BOUND) && strcmp(line, INT_MIN_BOUND) == 1) {
            printf("Underflow error.");
            exit(132);
        }
    }
    else {
        if(strlen(line) > strlen(INT_MAX_BOUND)) {
            printf("Overflow error.");
            exit(132);
        }
        if(strlen(line) == strlen(INT_MAX_BOUND) && strcmp(line, INT_MAX_BOUND) == 1) {
            printf("Overflow error.");
            exit(132);
        }
    }
    int res = 0;
    int start = 0;
    if(line[0] == '-') start++;
    while(start < at) {
        res = 10 * res + line[start] - '0';
        start++;
    }
    return line[0] == '-' ? -res : res;
}

// END OF PARSING TEMPLATE