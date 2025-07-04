#include <stdio.h>
#include <stdbool.h>

int main()
{
    // variaveis
    float nota, favoritos;
    -1, titulo;
    int escolha;

    do {
        // menu
        printf("\n escolha uma opção; \n");
        printf("1. ver livros registrados \n");
        printf("2. registrar livro \n");
        printf("3. comparar livros \n");
        printf("4. ver livros favoritos \n");
        printf("5. classificar sagas, trilogias e/ou universos \n");
        printf("6. calcular media de de sagas e trilogias \n");
        printf("7. sair");
        scanf("%d", &escolha);

        // depois do menu - (depois da escolha do usuario)
        switch (escolha) {
            case 7:
                printf("1. livros registrados");

            case 6:
                printf("2. registre o livro");
                if (nota >= 8.0) {
                    titulo = favoritos;
                } else {
                }

            case 5:
                printf("3. compare as notas");

            case 4:
                printf("4. lista de favoritos");
                printf("%f", favoritos);

            case 3:
                printf("5. classificaçao de trilogias, sagas e universos");

            case 2:
                printf("6. calcular media das trilogias, sagas e universos");

            case 1:
                if (escolha == 1) {
                    break;
                }

            default:
                printf("opção inexistente");
        }
    } while (escolha <= 7);
    return 0;
}