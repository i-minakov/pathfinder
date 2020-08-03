#include "../inc/pathfinder.h"

static int mx_usage(int flag, int line, t_path *info) {
    if (flag == 0)
        write(2, "usage: ./pathfinder [filename]\n", 31);
    if (flag == 1)
        write(2, "error: file islands does not exist\n", 35);
    if (flag == 2) {
        write(2, "error: line ", 12);
        mx_printint(line);
        write(2, " is not valid\n", 14);
    }
    if (flag == 3)
        write(2, "error: invalid number of islands\n", 33);
    mx_strdel(&info->str);
    mx_del_strarr(&info->isle);
    free(info);
    return EXIT_FAILURE;
}

static bool isle_exist(char **arr, char *str) {
    if (arr == NULL)
        return false;
    for (int i = 0; arr[i]; i++)
        if (!mx_strcmp(arr[i], str))
            return true;
    return false;
}

static char **get_island(char **arr) {
    char **res = NULL;
    char **tmp = NULL;
    char **p = NULL;
    
    for (int i = 1; arr[i]; i++) {
        tmp = mx_strsplit(arr[i], '-');
        !isle_exist(res, tmp[0]) ? res = mx_arrjoin(res, tmp[0]) : 0;
        p = mx_strsplit(tmp[1], ',');
        !isle_exist(res, p[0]) ? res = mx_arrjoin(res, p[0]) : 0;
        mx_del_strarr(&p);
        mx_del_strarr(&tmp);
    }
    return res;
}

static t_path *create_struct() {
    t_path *info = (t_path *)malloc(sizeof(t_path));

    info->str = NULL;
    info->isle = NULL;
    info->mtrx = NULL;
    return info;
}

int main(int argc, char *c[]) {
    t_path *info = create_struct();
    char **m = NULL;
    int err;

    if (argc == 1 || argc > 2)
        return mx_usage(0, 0, info);
    info->str = mx_file_to_str(c[1]);
    if (info->str == NULL)
        return mx_usage(1, 0, info);
    if ((err = mx_validation(info->str)) > 0)
        return mx_usage(2, err, info);
    m = mx_strsplit(info->str, '\n');
    info->isle = get_island(m);
    if (!mx_check_count_island(m, mx_len_of_array(info->isle)))
        return mx_usage(3, 0, info);
    info->count = mx_len_of_array(info->isle);
    info->mtrx = mx_get_matrix(info);
    mx_find_path(info);
    mx_del_strarr(&info->isle);
    mx_strdel(&info->str);
    mx_matrix_free(&info->mtrx, info->count);
    free(info);
    return 0;
}
