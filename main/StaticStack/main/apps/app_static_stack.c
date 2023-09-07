#include <stdlib.h>

int main() {

    /**
     * Os testes foram feitos usando uma pilha estática de inteiros, mas como é usado o conceito de generics,
     * basta implementar corretamente as funções de comparação, conversão e impressão do tipo de dados que quiser
     * aplicar, seja um tipo primitivo ou um ADT.
     */
    char *command = "make run_tests";
    int executed = system(command);
    if (executed != 0) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}