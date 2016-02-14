void BubbleSort(int a[], int N) {
    for(int i(0); i < N-1; i++)
        for(int j(N-1); j > i; j--)
            if(a[j-1] > a[j])
                swap(a[j-1], a[j]);
}

void InsertionSort(int a[], int N) {
    for (int i(1); i < N; i++) {
        int j = i;
        for(; j > 0 && a[j-1] > a[i]; j--)
            a[j] = a[j-1];
        a[j] = a[i];
        /*
         * for(; j > 0 && a[j-1] > a[j]; j--)
         *     swap(a[j-1], a[j]);
         */
    }
}

void SelectionSort(int a[], int N) {
    for(int i(1); i < N-1; ++i) {
        int min = i;
        for(int j(N-1); j > i; j--)
            if(a[j] > a[min])
                min = j;
        swap(a[min], a[i]);
    }
}
