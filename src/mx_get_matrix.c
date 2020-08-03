#include "../inc/pathfinder.h"

static int get_ind_of_isl(char *island, t_path *info) {
    for (int i = 0; info->isle[i]; i++) {
        if (!mx_strcmp(info->isle[i], island))
            return i;
    }
    return -1;
}

int *mx_malloc_mas(int len) {
    int *mas = (int *)malloc(sizeof(int) * (len + 1));

    mas[len] = -1;
    for (int i = 0; i < len; i++)
        mas[i] = 0;
    return mas;
}

void mx_matrix_free(int ***mtrx, int len) {
    if (!mtrx || !*mtrx)
        return ;
    int **m = *mtrx;

    for (int i = 0; i < len; i++)
        free(m[i]);
    free(*mtrx);
    *mtrx = NULL;
}

int **mx_malloc_matrix(int len) {
    int **mtrx = (int **)malloc(sizeof(int *) * (len + 1));

    mtrx[len] = NULL;
    for (int i = 0; mtrx[i]; i++) {
        mtrx[i] = (int *)malloc(sizeof(int) * (len));
        for (int j = 0; j < len; j++) 
            mtrx[i][j] = 0;
    }
    return mtrx;
}

int **mx_get_matrix(t_path *info) {
    int **mtrx = mx_malloc_matrix(info->count);
    char **arr = mx_strsplit(info->str, '\n');
    char **m = NULL;
    char **p = NULL;

    for (int i = 1; arr[i]; i++) {
        m = mx_strsplit(arr[i], '-');
        p = mx_strsplit(m[1], ',');
        mtrx[get_ind_of_isl(m[0], info)][get_ind_of_isl(p[0], info)]
            = mx_atoi(p[1]);
        mtrx[get_ind_of_isl(p[0], info)][get_ind_of_isl(m[0], info)]
            = mx_atoi(p[1]);
        mx_del_strarr(&m);
        mx_del_strarr(&p);
    }
    mx_del_strarr(&arr);
    return mtrx;
}
