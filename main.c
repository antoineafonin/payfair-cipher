#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 5
#define ALPHABET_SIZE 26

void generate_table(const char *key, char keyTable[TABLE_SIZE][TABLE_SIZE]) {
    int used[ALPHABET_SIZE] = {0};
    int i = 0, j = 0;

    for (int k = 0; key[k] != '\0'; k++) {
        char ch = tolower(key[k]);
        if (ch == 'w') ch = 'v';
        if (ch < 'a' || ch > 'z' || used[ch - 'a']) continue;

        keyTable[i][j++] = toupper(ch);
        used[ch - 'a'] = 1;

        if (j == TABLE_SIZE) {
            i++;
            j = 0;
        }
    }

    for (int k = 0; k < ALPHABET_SIZE; k++) {
        if (k == ('w' - 'a') || used[k]) continue;

        keyTable[i][j++] = toupper(k + 'a');
        if (j == TABLE_SIZE) {
            i++;
            j = 0;
        }
    }
}

void find_position(char table[TABLE_SIZE][TABLE_SIZE], char ch, int *row,
                   int *col) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (int j = 0; j < TABLE_SIZE; j++) {
            if (table[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

char *prepare_text(const char *text) {
    int len = strlen(text);
    char *new_text = malloc(2 * len + 2);
    if (!new_text) return NULL;

    int index = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = toupper(text[i]);
        if (ch == ' ') continue;
        if (ch == 'W') ch = 'V';

        if (index > 0 && new_text[index - 1] == ch && ch != 'X') {
            new_text[index++] = 'X';
        }
        new_text[index++] = ch;
    }

    if (index % 2 != 0) new_text[index++] = 'X';
    new_text[index] = '\0';
    return new_text;
}

char *playfair_encrypt(const char *key, const char *text) {
    if (!key || !text) return NULL;

    char table[TABLE_SIZE][TABLE_SIZE];
    generate_table(key, table);

    char *prepared_text = prepare_text(text);
    if (!prepared_text) return NULL;

    int len = strlen(prepared_text);
    char *encrypted_text = malloc(3 * len / 2 + 1);
    if (!encrypted_text) {
        free(prepared_text);
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        find_position(table, prepared_text[i], &r1, &c1);
        find_position(table, prepared_text[i + 1], &r2, &c2);

        if (r1 == r2) {
            encrypted_text[index++] = table[r1][(c1 + 1) % TABLE_SIZE];
            encrypted_text[index++] = table[r2][(c2 + 1) % TABLE_SIZE];
        } else if (c1 == c2) {
            encrypted_text[index++] = table[(r1 + 1) % TABLE_SIZE][c1];
            encrypted_text[index++] = table[(r2 + 1) % TABLE_SIZE][c2];
        } else {
            encrypted_text[index++] = table[r1][c2];
            encrypted_text[index++] = table[r2][c1];
        }
        encrypted_text[index++] = ' ';
    }

    encrypted_text[index - 1] = '\0';
    free(prepared_text);
    return encrypted_text;
}

char *playfair_decrypt(const char *key, const char *text) {
    if (!key || !text) return NULL;
    if (strchr(text, 'W')) return NULL;

    char table[TABLE_SIZE][TABLE_SIZE];
    generate_table(key, table);

    int len = strlen(text);
    char *decrypted_text = malloc(len + 1);
    if (!decrypted_text) return NULL;

    int index = 0;
    for (int i = 0; i < len; i += 3) {
        int r1, c1, r2, c2;
        find_position(table, text[i], &r1, &c1);
        find_position(table, text[i + 1], &r2, &c2);

        if (r1 == r2) {
            decrypted_text[index++] = table[r1][(c1 + 4) % TABLE_SIZE];
            decrypted_text[index++] = table[r2][(c2 + 4) % TABLE_SIZE];
        } else if (c1 == c2) {
            decrypted_text[index++] = table[(r1 + 4) % TABLE_SIZE][c1];
            decrypted_text[index++] = table[(r2 + 4) % TABLE_SIZE][c2];
        } else {
            decrypted_text[index++] = table[r1][c2];
            decrypted_text[index++] = table[r2][c1];
        }
    }
    decrypted_text[index] = '\0';
    return decrypted_text;
}

int main() {
    char *encrypted, *decrypted;

    // even length of string
    encrypted = playfair_encrypt("SeCReT", "Hello world");
    printf("%s", encrypted);
    // "Hello world" --> "HELXLOVORLDX"
    // IS JZ JQ XN TK JC
    decrypted = playfair_decrypt("SeCReT", encrypted);
    printf("%s", decrypted);
    // HELXLOVORLDX
    free(encrypted);
    free(decrypted);

    // odd length of string
    encrypted = playfair_encrypt("world", "Hello");
    printf("%s", encrypted);
    // "Hello" --> "HELXLO"
    // JB RY DR
    decrypted = playfair_decrypt("world", encrypted);
    printf("%s", decrypted);
    // HELXLO
    free(encrypted);
    free(decrypted);

    // letter 'X' in message
    encrypted = playfair_encrypt("Password", "Taxi please");
    printf("%s", encrypted);
    // "Taxi please" --> "TAXIPLEASE"
    // UP YH AK DO OB
    decrypted = playfair_decrypt("Password", encrypted);
    printf("%s", decrypted);
    // TAXIPLEASE
    free(encrypted);
    free(decrypted);

    // multi 'X's in message
    encrypted = playfair_encrypt("please", "Taxxxiii");
    printf("%s", encrypted);
    // "Taxxxiii" --> "TAXXXIIXIX"
    // RS EE VJ JV JV
    decrypted = playfair_decrypt("please", encrypted);
    printf("%s", decrypted);
    // TAXXXIIXIX
    free(encrypted);
    free(decrypted);
    return 0;
}
