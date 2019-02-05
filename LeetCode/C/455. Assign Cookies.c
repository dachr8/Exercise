//455. Assign Cookies
int findContentChildren(int *g, int gSize, int *s, int sSize) {

    void sort(int *array, int size);

    int output = 0;

    sort(g, gSize);
    sort(s, sSize);

    for (int i = 0; output < gSize && i < sSize; i++)
        if (g[output] <= s[i])
            output++;

    return output;
}

void sort(int *array, int size) {
    int tmp;

    for (_Bool flag = 1; flag;) {
        flag = 0;
        for (int i = 0; i < size - 1; i++)
            if (array[i] > array[i + 1]) {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                flag = 1;
            }
    }
}
