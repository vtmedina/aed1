#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* longestNiceSubstring(char* s) {
    int slen = strlen(s);
    int mlen = 0, mind = 0;

    for (int i = 0; i < slen - 1; i++) {
        int upper = 0, lower = 0;
        for (int j = i; j < slen; j++) {
            if (s[j] >= 'A' && s[j] <= 'Z') {
                upper |= 1 << (s[j] - 'A');
            } else if (s[j] >= 'a' && s[j] <= 'z') {
                lower |= 1 << (s[j] - 'a');
            }

            if ((upper ^ lower) == 0 && (j - i + 1) > mlen) {
                mlen = j - i + 1;
                mind = i;
            }
        }
    }

    char* ans = malloc((mlen + 1) * sizeof(char));
    for (int k = 0; k < mlen; k++) {
        ans[k] = s[mind + k];
    }
    ans[mlen] = '\0';

    return ans;
}

int main() {
    char* input = "YazaAay";
    char* resultado = longestNiceSubstring(input);

    printf("substring maior: %s\n", resultado);

    free(resultado);

    return 0;
}