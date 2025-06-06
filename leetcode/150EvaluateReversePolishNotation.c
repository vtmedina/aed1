int evalRPN(char** tokens, int tokensSize) {
    int stack[tokensSize];
    int top = -1;

    for (int i = 0; i < tokensSize; ++i) {
        char* t = tokens[i];

        if (t[1] == '\0' && (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
            int b = stack[top--];
            int a = stack[top--];

            switch (t[0]) {
                case '+': stack[++top] = a + b; break;
                case '-': stack[++top] = a - b; break;
                case '*': stack[++top] = a * b; break;
                case '/': stack[++top] = a / b; break;
            }
        } else {
            stack[++top] = atoi(t);
        }
    }

    return stack[top];
}
