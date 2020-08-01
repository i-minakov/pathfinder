#include "../inc/pathfinder.h"

bool mx_check_count_island(char **arr, int len) {
    bool res = true;

    if (mx_atoi(arr[0]) != len)
        res = false;
    mx_del_strarr(&arr);
    return res;
}

static bool check_first(char *s) {
    for (int i = 0; s[i]; i++) 
        if (mx_isdigit(s[i]) == false)
            return false;
    return true;
}

static int check_second(char **arr) {
    int j;

    for (int i = 1; arr[i]; i++) {
        j = 0;
        for ( ; arr[i][j] != '-'; j++)
            if (mx_isalpha(arr[i][j]) == false)
                return i;
        for (j++; arr[i][j] != ','; j++)
            if (mx_isalpha(arr[i][j]) == false)
                return i;
        for (j++; arr[i][j]; j++)
            if (mx_isdigit(arr[i][j]) == false)
                return i;
    }
    return -1;
}

int mx_validation(char *str) {
    char **arr = mx_strsplit(str, '\n');
    int res = 0;

    if (arr == NULL || arr[1] == NULL) {
        mx_del_strarr(&arr);
        return 1;
    }
    if (check_first(arr[0]) == false)
        return 1;
    res = check_second(arr);
    mx_del_strarr(&arr);
    return res + 1;
}
