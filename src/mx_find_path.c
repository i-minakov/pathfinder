#include "../inc/pathfinder.h"

static int **copy_matrix(int **mtrx, int len) {
    int **mtrx_copy = mx_malloc_matrix(len);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) 
            mtrx_copy[i][j] = mtrx[i][j];
    }
    return mtrx_copy;
}

static char *dst_reach(int **mtrx_copy, t_path *info, 
                        int index_src, char *tmp) {
    char *r = NULL;

    for (int j = 0; j < info->count; j++) {
        if (mtrx_copy[index_src][j] > 0 && j == info->index_dst) {
            r = mx_backjoin(tmp, mx_itoa(j));
            r = mx_delit_fre(r, "\n");
        }
    }
    return r;
}

static char *start_finder(int **mtrx, t_path *info, 
                            int index_src, char *tmp) {
    int **mtrx_copy = copy_matrix(mtrx, info->count);
    char *r = dst_reach(mtrx_copy, info, index_src, tmp);
    char *s = NULL;

    for (int i = 0; i < info->count; i++) 
        mtrx_copy[i][index_src] = -1;
    for (int i = 0; i < info->count; i++) {
        if (mtrx_copy[index_src][i] > 0 && i != info->index_dst) {
            mtrx_copy[index_src][i] = -1;
            s = mx_backjoin(tmp, mx_itoa(i));
            s = mx_delit_fre(s, "-");
            r = mx_cooljoin(r, start_finder(mtrx_copy, info, i, s));
            mx_strdel(&s);
        }
    }
    mx_matrix_free(&mtrx_copy, info->count);
    return r;
}

void mx_find_path(t_path *info) {
    char *s = NULL;
    char *tmp = NULL;
    char **res = NULL;

    for (int i = 0; i < info->count - 1; i++) {
        for (int j = i + 1; j < info->count; j++) {
            tmp = mx_itoa(i);
            tmp = mx_delit_fre(tmp, "-");
            info->index_src = i;
            info->index_dst = j;
            s = start_finder(info->mtrx, info, i, tmp);
            res = mx_strsplit(s, '\n');
            mx_result(res, info);
            mx_del_strarr(&res);
            mx_strdel(&s);
            mx_strdel(&tmp);
        }
    }
}
