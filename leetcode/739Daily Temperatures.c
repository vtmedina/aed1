int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* res = (int*)calloc(temperaturesSize, sizeof(int));
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));
    int top = -1;

    for (int i = temperaturesSize - 1; i >= 0; i--) {
        while (top >= 0 && temperatures[i] >= temperatures[stack[top]]) {
            top--;
        }

        if (top >= 0) {
            res[i] = stack[top] - i;
        }

        stack[++top] = i;
    }

    free(stack);
    return res;
}
