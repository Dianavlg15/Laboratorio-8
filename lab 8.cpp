#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 30

// Función auxiliar para comparar si dos strings tienen los mismos caracteres
bool isAnagram(const char *s1, const char *s2, int len) {
    int count[26] = {0};
    for (int i = 0; i < len; ++i) {
        count[s1[i] - 'a']++;
        count[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; ++i) {
        if (count[i] != 0)
            return false;
    }
    return true;
}

// Memoización con 3D array: -1 = no calculado, 0 = false, 1 = true
int memo[MAX_LEN][MAX_LEN][MAX_LEN + 1];

bool dfs(const char *s1, const char *s2, int i1, int i2, int len) {
    if (memo[i1][i2][len] != -1)
        return memo[i1][i2][len];

    if (strncmp(s1 + i1, s2 + i2, len) == 0)
        return memo[i1][i2][len] = 1;

    if (!isAnagram(s1 + i1, s2 + i2, len))
        return memo[i1][i2][len] = 0;

    for (int i = 1; i < len; ++i) {
        if (dfs(s1, s2, i1, i2, i) && dfs(s1, s2, i1 + i, i2 + i, len - i))
            return memo[i1][i2][len] = 1;

        if (dfs(s1, s2, i1, i2 + len - i, i) && dfs(s1, s2, i1 + i, i2, len - i))
            return memo[i1][i2][len] = 1;
    }

    return memo[i1][i2][len] = 0;
}

bool isScramble(const char *s1, const char *s2) {
    int len = strlen(s1);
    if (len != strlen(s2))
        return false;

    for (int i = 0; i < MAX_LEN; ++i)
        for (int j = 0; j < MAX_LEN; ++j)
            for (int k = 0; k <= MAX_LEN; ++k)
                memo[i][j][k] = -1;

    return dfs(s1, s2, 0, 0, len);
}

int main() {
    const char *s1 = "great";
    const char *s2 = "rgeat";
    printf("Input: \"%s\", \"%s\"\n", s1, s2);
    printf("Output: %s\n", isScramble(s1, s2) ? "true" : "false");

    const char *s3 = "abcde";
    const char *s4 = "caebd";
    printf("Input: \"%s\", \"%s\"\n", s3, s4);
    printf("Output: %s\n", isScramble(s3, s4) ? "true" : "false");

    const char *s5 = "a";
    const char *s6 = "a";
    printf("Input: \"%s\", \"%s\"\n", s5, s6);
    printf("Output: %s\n", isScramble(s5, s6) ? "true" : "false");

    return 0;
}

