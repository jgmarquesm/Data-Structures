#include <stdlib.h>

int main() {

    char *command = "make run_tests";
    int executed = system(command);
    if (executed != 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
