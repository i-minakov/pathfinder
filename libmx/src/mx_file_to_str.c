#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    char *str = NULL;
    int buf = 0;
    int fd = open(file, O_RDONLY);

    if (fd < 0)
        return NULL;
    for ( ; read(fd, &buf, 1) > 0; buf = 0) 
        str = mx_delit_fre(str, (char *)&buf);
    close(fd);
    return str;
}
