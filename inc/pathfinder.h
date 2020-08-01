#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

typedef struct s_path {
    int count;
    char *str;
    int **mtrx;
    char **isle;
    int index_src;
    int index_dst;
}              t_path;

int **malloc_matrix(int len);
int mx_validation(char *str);
int **mx_get_matrix(t_path *info);
bool mx_check_count_island(char **arr, int len);
void mx_find_path(t_path *info);
void mx_matrix_free(int ***mtrx, int len);

#endif
