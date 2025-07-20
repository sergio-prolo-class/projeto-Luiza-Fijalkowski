#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define TAM_STRING 100

typedef struct {
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    float nota;
} livro;

// mostra o livoro do caso 1
void mostrarLivros(FILE *arquivo)
{
    livro l;
    rewind(arquivo);  // Volta ao início do arquivo

    printf("\n--- Livros Registrados ---\n");
    while (fread(&l, sizeof(livro), 1, arquivo) == 1) {
        printf("Título: %s\nAutor: %s\nNota: %.2f\n\n", l.titulo, l.autor, l.nota);
    }
}

// registro do livro
void registrarlivro(FILE *arquivo)
{
    livro l;

    printf("Título do livro: ");
    fgets(l.titulo, TAM_STRING, stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor do livro: ");
    fgets(l.autor, TAM_STRING, stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    printf("Nota do livro (0 a 10): ");
    scanf("%f", &l.nota);
    getchar();  // Limpa o '\n' do buffer

    fwrite(&l, sizeof(livro), 1, arquivo);
    printf("Livro registrado com sucesso!\n");
}

// lista de favoritos
void listarFavoritos(FILE *arquivo)
{
    livro l;
    rewind(arquivo);

    printf("\n--- Livros Favoritos (nota > 8) ---\n");
    while (fread(&l, sizeof(livro), 1, arquivo) == 1) {
        if (l.nota > 8.0) {
            printf("Título: %s\nAutor: %s\nNota: %.2f\n\n", l.titulo, l.autor, l.nota);
        }
    }
}

int contarLivros(FILE *arquivo)
{
    fseek(arquivo, 0, SEEK_END);
    return ftell(arquivo) / sizeof(livro);
}

int main()
{
    FILE *arquivo = fopen("livros.dat", "a+b");  // a+b: leitura e escrita binária
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int opcao;
    do {
        // menu
        printf("\n--- MENU ---\n");
        printf("1. ver livros registrados \n");
        printf("2. registrar livro \n");
        printf("3. lista de favoritos \n");
        printf("4. contar livors \n");
        printf("\n escolha uma opção; \n");
        scanf("%d", &opcao);
        getchar();  // limpa o \n deixado pelo scanf

        // depois do menu - (depois da escolha do usuario)
        switch (opcao) {
            case 1:
                mostrarLivros(arquivo);
                break;
            case 2:
                registrarlivro(arquivo);
                break;
            case 3:
                listarFavoritos(arquivo);
                break;
            case 4:
                printf("Total de livros registrados: %d\n", contarLivros(arquivo));
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    }

    while (opcao != 0);

    fclose(arquivo);
    return 0;
}