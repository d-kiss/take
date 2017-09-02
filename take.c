#include <stdio.h>
int main(int argc, char *argv[]) {
    printf("Command was ran with %d args\n", argc);
    printf("%s\n", argv[0]);
    return 0;
}
