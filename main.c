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

//Percentual de homens vivos
float percentual_homens_vivos(Passageiro *p, int num_passageiros) 
{
    int homens_vivos = 0;
    int homens = 0;
    for (int i = 0; i < num_passageiros; i++) {
        if (strcmp(p[i].genero, "masculino") == 0) {
            homens++;
            if (strcmp(p[i].sobreviveu, "sim") == 0) {
                homens_vivos++;
            }
        }
    }
    return ((float) homens_vivos / homens) * 100.0;
}

float percentual_mulheres_vivas(Passageiro *p, int num_passageiros) 
{
    int mulheres_vivas = 0;
    int mulheres = 0;
    for (int i = 0; i < num_passageiros; i++) {
        if (strcmp(p[i].genero, "feminino") == 0) {
            mulheres++;
            if (strcmp(p[i].sobreviveu, "sim") == 0) {
                mulheres_vivas++;
            }
        }
    }
    return ((float) mulheres_vivas / mulheres) * 100.0;
}

float percentual_criancas_vivas(Passageiro* passageiros, int num_passageiros) {
    int num_criancas = 0, num_criancas_vivas = 0;

    for (int i = 0; i < num_passageiros; i++) {
        if (passageiros[i].idade <= 16) {
            num_criancas++;
            if (strcmp(passageiros[i].sobreviveu, "sim") == 0) {
                num_criancas_vivas++;
            }
        }
    }

    return (float) num_criancas_vivas / num_criancas * 100;
}

float percentual_adultos_vivos(Passageiro* passageiros, int num_passageiros) {
    int num_adultos = 0, num_adultos_vivos = 0;

    for (int i = 0; i < num_passageiros; i++) {
        if (passageiros[i].idade > 16) {
            num_adultos++;
            if (strcmp(passageiros[i].sobreviveu, "sim") == 0) {
                num_adultos_vivos++;
            }
        }
    }

    return (float) num_adultos_vivos / num_adultos * 100;
}



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
    
    /*//Verificar dados
    for (int i = 0; i < MAX_LINHA && p[i].idade > 0; i++) {
        printf("Passageiro %d:\n", i + 1);
        printf("Classe: %s\n", p[i].classe);
        printf("Idade: %d\n", p[i].idade);
        printf("Gênero: %s\n", p[i].genero);
        printf("Sobreviveu: %s\n\n", p[i].sobreviveu);
    }
    */

    printf("\n\n");
    printf("\nPERCENTUAL DE HOMENS VIVOS: %.2f%% \n", percentual_homens_vivos(p, MAX_LINHA));
    printf("\nPERCENTUAL DE MULHERES VIVAS: %.2f%% \n", percentual_mulheres_vivas(p, MAX_LINHA));
    printf("\nPERCENTUAL DE CRIANÇAS VIVAS: %.2f%% \n", percentual_criancas_vivas(p, MAX_LINHA));
    printf("\nPERCENTUAL DE ADULTOS VIVAS: %.2f%% \n", percentual_adultos_vivos(p, MAX_LINHA));
    
    fclose(arquivo);


    return 0;
}
