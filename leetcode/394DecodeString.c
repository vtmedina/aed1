#define STACK_SIZE 1000
#define BUF_SIZE 10000

char* decodeString(const char* s) {
    int repeat_stack[STACK_SIZE];
    char* str_stack[STACK_SIZE];
    int top = -1;

    char* curr = (char*)malloc(BUF_SIZE);
    curr[0] = '\0';
    int curr_len = 0;
    int k = 0;

    for (int i = 0; s[i]; ++i) {
        if (isdigit(s[i])) {
            k = k * 10 + (s[i] - '0');
        } else if (s[i] == '[') {
            repeat_stack[++top] = k;
            str_stack[top] = curr;
            curr = (char*)malloc(BUF_SIZE);
            curr[0] = '\0';
            curr_len = 0;
            k = 0;
        } else if (s[i] == ']') {
            int repeat = repeat_stack[top];
            char* prev = str_stack[top--];

            int len = strlen(curr);
            for (int j = 0; j < repeat; ++j) {
                strcat(prev, curr);
            }

            free(curr);
            curr = prev;
        } else {
            int len = strlen(curr);
            curr[len] = s[i];
            curr[len + 1] = '\0';
        }
    }

    return curr;
}
