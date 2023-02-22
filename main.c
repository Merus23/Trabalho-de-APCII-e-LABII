#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 2201

typedef struct {
    char classe[20];
    int idade;
    char genero[15];
    char sobreviveu[5];
} Passageiro;

int main() {
    FILE *arquivo;
    char linha[MAX_LINHA];
    
    arquivo = fopen("Passageiros.txt", "r");
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }

    Passageiro p[MAX_LINHA];

    for (int i = 0; i < MAX_LINHA && fgets(linha, MAX_LINHA, arquivo); i++) {
        sscanf(linha, "%[^,],%d,%[^,],%s", p[i].classe, &p[i].idade, p[i].genero, p[i].sobreviveu);
    }

    for (int i = 0; i < MAX_LINHA && p[i].idade > 0; i++) {
        printf("Passageiro %d:\n", i + 1);
        printf("Classe: %s\n", p[i].classe);
        printf("Idade: %d\n", p[i].idade);
        printf("Gênero: %s\n", p[i].genero);
        printf("Sobreviveu: %s\n\n", p[i].sobreviveu);
    }



    fclose(arquivo);


    return 0;
}
