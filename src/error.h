#ifndef INCLUDE_ERROR_H
#define INCLUDE_ERROR_H

#define ERROR(str,flag,ret) { \
    printf("%s\n", (str));    \
    (flag) = (ret);           \
}

#define RET(str,ret) {     \
    printf("%s\n", (str)); \
    return (ret);          \
}

#endif
