#include "../inc/pathfinder.h"

static void print_distance(int *rout, int sum) {
    mx_printstr("Distance: ");
    for (int i = 0; rout[1] != -1 && rout[i] != -1; i++) {
        mx_printint(rout[i]);
        if (rout[i + 1] != -1)
            mx_printstr(" + ");
        else
            mx_printstr(" = ");
    }
    mx_printint(sum);
    mx_printstr("\n==========================================\n");
}

void mx_print(char **res, int *rout, int sum) {
    mx_printstr("==========================================\n");
    mx_printstr("Path: ");
    mx_printstr(res[0]);
    mx_printstr(" -> ");
    mx_printstr(res[mx_len_of_array(res) - 1]);
    mx_printstr("\nRoute: ");
    for (int i = 0; res[i]; i++) {
        mx_printstr(res[i]);
        if (res[i + 1])
            mx_printstr(" -> ");
        else 
        mx_printstr("\n");
    }
    print_distance(rout, sum);
}
