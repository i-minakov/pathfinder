#include "../inc/pathfinder.h"

static void swap_elements(int **x, int **y, char **s, char **t) {
    int *tmp = NULL;
    char *str = NULL;

    tmp = *x;
    *x = *y;
    *y = tmp;
    str = *s;
    *s = *t;
    *t = str;
}

static void mx_sort_mas(int **mas, int ***matrix, char ***p, int len) {
    int k;
    int tmp;
    int *ar = *mas;
    char **paths = *p;
    int **mtrx = *matrix;

    for (int i = 0; i < len - 1; i++) {
        k = i;
        for (int j = i; j < len; j++) {
            if (ar[j] < ar[k])
                k = j;
        }
        tmp = ar[i];
        ar[i] = ar[k];
        ar[k] = tmp;
        swap_elements(&mtrx[i], &mtrx[k], &paths[i], &paths[k]);
    }
}

static int *sum_of_path(int **mtrx, int len) {
    int *sum = mx_malloc_mas(len);

    for (int i = 0; i < len; i++) {
        for (int j = 0; mtrx[i][j] != -1; j++)
            sum[i] += mtrx[i][j];
    }
    return sum;
}

static int **distance_of_path(int len_arr, char **paths, t_path *info) {
    char **tmp = NULL;
    int **mtrx_rout = (int **)malloc(sizeof(int *) * (len_arr + 1));

    mtrx_rout[len_arr] = NULL;
    for (int i = 0; paths[i]; i++) {
        tmp = mx_strsplit(paths[i], '-');
        mtrx_rout[i] = mx_malloc_mas(mx_len_of_array(tmp) - 1);
        for (int j = 0; j < mx_len_of_array(tmp) - 1; j++)
            mtrx_rout[i][j] = info->mtrx[mx_atoi(tmp[j])][mx_atoi(tmp[j + 1])];
        mx_del_strarr(&tmp);
    }
    return mtrx_rout;
}


void mx_result(char **paths, t_path *info) {
    int c = mx_len_of_array(paths);
    int **rout = distance_of_path(c, paths, info);
    int *sum = sum_of_path(rout, c);
    char **tmp = NULL;
    char **res = NULL;

    mx_sort_mas(&sum, &rout, &paths, c);
    for (int i = 0; i < c; i++) {
        tmp = mx_strsplit(paths[i], '-');
        for (int j = 0; tmp[j]; j++)
            res = mx_arrjoin(res, info->isle[mx_atoi(tmp[j])]);
        mx_del_strarr(&tmp);
        mx_print(res, rout[i], sum[i]);
        mx_del_strarr(&res);
        if (sum[i + 1] != sum[i])
            break;
    }
    mx_matrix_free(&rout, c);
    free(sum);
}
