int upperBound(int* row, int n, int target) {
    int left = 0, right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (row[mid] <= target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

int countLessEqual(int** matrix, int n, int* matrixColSize, int mid) {
    int count = 0;
    for (int i = 0; i < n; ++i) {
        count += upperBound(matrix[i], matrixColSize[i], mid);
    }
    return count;
}

int kthSmallest(int** matrix, int matrixSize, int* matrixColSize, int k) {
    int low = matrix[0][0];
    int high = matrix[matrixSize-1][matrixColSize[matrixSize-1]-1];

    while (low < high) {
        int mid = low + (high - low) / 2;
        int cnt = countLessEqual(matrix, matrixSize, matrixColSize, mid);

        if (cnt < k)
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
