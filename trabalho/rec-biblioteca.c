#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define que o maximo de livros registrados e 100
#define MAX_LIVROS 100

// declaração de variaveis e strings
typedef struct {
    char titulo[100];
    char autor[100];
    char saga[100];
    char genero[100];
    float nota;
} Livro;

// essas funções estao aqui para dizer ao main que elas existem, mesmo que so sejam desenvolvidas mais tarde no codigo.
void registrarLivro();
void mostrarLivros();
void listarFavoritos();
void contarLivros();
void editarLivro();
int carregarLivros(Livro *livros);

int main()
{
    int opcao;

    // o menu como o usuario vai ver no terminal
    do {
        printf("\n--- MENU ---\n");
        printf("1. Registrar livro\n");
        printf("2. Ver livros registrados\n");
        printf("3. Lista de favoritos (nota > 8)\n");
        printf("4. Contar livros\n");
        printf("5. Editar livro\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();  // limpar \n

        // diz a função a ser usada em cada caso
        switch (opcao) {
            case 1:
                registrarLivro();
                break;
            case 2:
                mostrarLivros();
                break;
            case 3:
                listarFavoritos();
                break;
            case 4:
                contarLivros();
                break;
            case 5:
                editarLivro();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default: printf("Opção inválida.\n");
        }

    } while (opcao != 6);

    return 0;
}

// essa função registra o livro no arquivo
void registrarLivro()
{
    FILE *arquivo = fopen("Biblioteca.txt", "a");  // abre o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;  // se nao tiver arquivo ele diz a menssagem
    }

    Livro l;  // cria uma variavel l com campo de string e de float
    printf("Digite o título do livro: ");
    fgets(l.titulo, sizeof(l.titulo), stdin);  // sizeof = diz ao fgets quantos bites pode ter no maximo.
    l.titulo[strcspn(l.titulo, "\n")] = '\0';  // remover \n

    printf("Nome do autor: ");
    fgets(l.autor, sizeof(l.autor), stdin);  // stdin = entrada padrao
    l.autor[strcspn(l.autor, "\n")] = '\0';  // remove \n

    printf("Saga-voluma: ");
    fgets(l.saga, sizeof(l.saga), stdin);
    l.saga[strcspn(l.saga, "\n")] = '\0';  // remove o \n

    printf("genero literario: ");
    fgets(l.genero, sizeof(l.genero), stdin);
    l.genero[strcspn(l.genero, "\n")] = '\0';  // remove o \n

    do {
        printf("Digite a nota do livro (0 a 10): ");
        if (scanf("%f", &l.nota) != 1) {
            printf("Entrada inválida! Use números.\n");
            while (getchar() != '\n')
                ;                                // limpa buffer
            l.nota = -1;                         // força repetir
        } else if (l.nota < 0 || l.nota > 10) {  // diz que nota so pode ir de um a 10
            printf("Nota deve estar entre 0 e 10!\n");
        }
    } while (l.nota < 0 || l.nota > 10);
    getchar();  // limpar \n após scanf

    fprintf(arquivo, "%s; %s; %s; %s; %.2f\n", l.titulo, l.autor, l.saga, l.genero, l.nota);  // serve para que ao inves de escrever na tela escreva no arquivo
    fclose(arquivo);                                                                          // fecha o arquivo
    printf("Livro registrado com sucesso!\n");
}

void mostrarLivros()
{
    Livro livros[MAX_LIVROS];
    int qtd = carregarLivros(livros);  // chama o livor de carregar livros

    if (qtd == 0) {  // diz o que acontece se nao tiver nenhum livor registrado
        printf("Nenhum livro registrado.\n");
        return;
    } else {
        printf("\n--- Livros Registrados ---\n");
        for (int i = 0; i < qtd; i++) {
            printf("%d, %s, %s, %s, %s (nota %.2f)\n", i + 1, livros[i].titulo, livros[i].autor, livros[i].saga, livros[i].genero, livros[i].nota);  // mostra os livros registrados
        }
    }
}

void listarFavoritos()
{
    Livro livros[MAX_LIVROS];
    int qtd = carregarLivros(livros);  // chama os livros
    int encontrou = 0;

    printf("\n--- Livros Favoritos (nota > 8) ---\n");

    for (int i = 0; i < qtd; i++) {
        if (livros[i].nota > 8.0) {  // livos com nota igual ou mair que 8 sao favoritos
            // Remover espaços extras se existirem (opcional)
            printf("%s, %s, %s, %s (nota %.2f)\n",
                   livros[i].titulo,
                   livros[i].autor,
                   livros[i].saga,
                   livros[i].genero,
                   livros[i].nota);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum livro favorito encontrado.\n");
    }
}

void contarLivros()
{
    Livro livros[MAX_LIVROS];
    int qtd = carregarLivros(livros);
    printf("Total de livros registrados: %d\n", qtd);  // diz a quantidade livros registrados
}

void editarLivro()
{
    Livro livros[MAX_LIVROS];
    int qtd = carregarLivros(livros);  // carregar os livros do arquivo

    if (qtd == 0) {
        printf("Nenhum livro para editar.\n");
        return;
    }

    // Mostrar livros para escolher
    printf("\n--- Livros Disponíveis ---\n");
    for (int i = 0; i < qtd; i++) {  // diz o numero do livro
        printf("%d. %s, %s, %s, %s (nota %.2f)\n", i + 1, livros[i].titulo, livros[i].autor, livros[i].saga, livros[i].genero, livros[i].nota);
    }

    int escolha;
    printf("Digite o número do livro que deseja editar: ");
    scanf("%d", &escolha);
    getchar();  // limpa \n

    if (escolha < 1 || escolha > qtd) {
        printf("Número inválido.\n");
        return;  // filtra se o numero escolhido e valido
    }

    Livro *l = &livros[escolha - 1];  // ajusta a escolha do do ussuario para o numero do arquivo

    printf("Novo título: ");
    fgets(l->titulo, sizeof(l->titulo), stdin);
    l->titulo[strcspn(l->titulo, "\n")] = '\0';  // o -> e um ponteiro para a estrutura

    printf("Novo autor: ");
    fgets(l->autor, sizeof(l->autor), stdin);
    l->autor[strcspn(l->autor, "\n")] = '\0';

    printf("Nova saga-volume: ");
    fgets(l->saga, sizeof(l->saga), stdin);
    l->saga[strcspn(l->saga, "\n")] = '\0';

    printf("Novo gênero literário: ");
    fgets(l->genero, sizeof(l->genero), stdin);
    l->genero[strcspn(l->genero, "\n")] = '\0';

    do {
        printf("Nova nota: ");
        if (scanf("%f", &l->nota) != 1 || l->nota < 0 || l->nota > 10) {
            printf("Nota inválida! Digite um valor entre 0 e 10.\n");
            while (getchar() != '\n')  // checa denovo se nota e valida
                ;
            l->nota = -1;
        }
    } while (l->nota < 0 || l->nota > 10);
    getchar();  // limpa \n

    // Salvar alterações sobrescrevendo o arquivo
    FILE *arquivo = fopen("Biblioteca.txt", "w");  // "w" abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar alterações.\n");
        return;  // checa a existencia do arquivo
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(arquivo, "%s; %s; %s; %s; %.2f\n", livros[i].titulo, livros[i].autor, livros[i].saga, livros[i].genero, livros[i].nota);
    }

    fclose(arquivo);
    printf("Livro editado com sucesso!\n");
}

int carregarLivros(Livro *livros)
{
    FILE *arquivo = fopen("Biblioteca.txt", "r");
    if (arquivo == NULL) {
        return 0;
    }

    int count = 0;
    char linha[512];
    while (fgets(linha, sizeof(linha), arquivo) != NULL && count < MAX_LIVROS) {
        linha[strcspn(linha, "\n")] = '\0';  // remover \n

        // Quebrar os campos com strtok
        char *token = strtok(linha, ";");
        if (token != NULL)
            strcpy(livros[count].titulo, token);

        token = strtok(NULL, ";");
        if (token != NULL)
            strcpy(livros[count].autor, token);

        token = strtok(NULL, ";");
        if (token != NULL)
            strcpy(livros[count].saga, token);

        token = strtok(NULL, ";");
        if (token != NULL)
            strcpy(livros[count].genero, token);

        token = strtok(NULL, ";");
        if (token != NULL)
            livros[count].nota = atof(token);

        count++;
    }

    fclose(arquivo);
    return count;
}
