#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100
#define MAX_LINHA 2201

typedef struct {
    char classe[20];
    int idade;
    char genero[15];
    char sobreviveu[5];
} Passageiro;

int verifica_abertura(FILE* arquivo) {
    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo\n");
        return 1;
    }
    return 0;
}

FILE* carregar_arquivo(char* nome_arquivo) {
    FILE *arquivo;
    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }
    return arquivo;
}

//Calcula o percentual de pessoas vivas
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

float percentual_vivos_classe(char* classe, Passageiro* p, int n_passageiros) {
    int i, n_vivos = 0;
    for (i = 0; i < n_passageiros; i++) {
        if (strcmp(p[i].classe, classe) == 0 && strcmp(p[i].sobreviveu, "sim") == 0) {
            n_vivos++;
        }
    }
    return (float)n_vivos * 100.0 / (float)n_passageiros;
}

float percentual_vivos_primeira_classe(Passageiro* p, int n_passageiros) {
    return percentual_vivos_classe("1st", p, n_passageiros);
}

float percentual_vivos_segunda_classe(Passageiro* p, int n_passageiros) {
    return percentual_vivos_classe("2nd", p, n_passageiros);
}

float percentual_vivos_terceira_classe(Passageiro* p, int n_passageiros) {
    return percentual_vivos_classe("3rd", p, n_passageiros);
}

float percentual_vivos_tripulacao(Passageiro* p, int n_passageiros) {
    return percentual_vivos_classe("tripulação", p, n_passageiros);
}

//LOGIN
int fazerLogin(char* username, char* password) {
    char line[MAX_LEN];
    int success = 0;

    FILE * arquivo = carregar_arquivo("Admin.txt");
    
    verifica_abertura(arquivo);

    while (fgets(line, MAX_LEN, arquivo)) {
        char *token = strtok(line, " \n"); // adiciona \n para remover espaços extras no final da linha
        if (token != NULL && strcmp(token, username) == 0) {
            token = strtok(NULL, " \n"); // adiciona \n para remover espaços extras no final da linha
            if (token != NULL && strcmp(token, password) == 0) {
                success = 1;
                break;
            }
        }
    }

    fclose(arquivo);

    return success;
}

void menu(){
    int op;
    
    printf("1 - Exibir número de passageiros por sexo\n");
    printf("2 - Exibir número de passageiros por classe\n");
    printf("3 - Exibir número de passageiros por situação\n");
    scanf("%d", &op);


}

int main() {
    char usuario[MAX_LEN], senha[MAX_LEN];
    printf("\n\nDigite o nome de usuário: ");
    scanf("%s", usuario);
    printf("\nDigite a senha: ");
    scanf("%s", senha);
    
    if (fazerLogin(usuario, senha)) {
        printf("Login bem sucedido.\n");
        
        menu();
        
        char linha[MAX_LINHA];    
        FILE *arquivo = carregar_arquivo("Passageiros.txt");
        verifica_abertura(arquivo);

        Passageiro p[MAX_LINHA];

        for (int i = 0; i < MAX_LINHA && fgets(linha, MAX_LINHA, arquivo); i++) {
            sscanf(linha, "%[^,],%d,%[^,],%s", p[i].classe, &p[i].idade, p[i].genero, p[i].sobreviveu);
        }

        //printf("Percentual de sobreviventes do sexo feminino: %.2f\n", percentual_mulheres_vivas(p, MAX_LINHA));


        fclose(arquivo);

    } else {
        printf("Nome de usuário ou senha incorretos.\n");
    }

    return 0;
}
