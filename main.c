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


void itemB(Passageiro *p, int num_passageiros){
    printf("Homens : %.2f%%\n", percentual_homens_vivos(p, num_passageiros));
    printf("Mulheres : %.2f%%\n", percentual_mulheres_vivas(p, num_passageiros));
    printf("Crianças  : %.2f%%\n", percentual_criancas_vivas(p, num_passageiros));
    printf("Adultos  : %.2f%%\n", percentual_adultos_vivos(p, num_passageiros));
    printf("Primeira classe : %.2f%%\n", percentual_vivos_primeira_classe(p, num_passageiros));
    printf("Segunda classe : %.2f%%\n", percentual_vivos_segunda_classe(p, num_passageiros));
    printf("Terceira classe : %.2f%%\n", percentual_vivos_terceira_classe(p, num_passageiros));
    printf("Tripulação : %.2f%%\n", percentual_vivos_tripulacao(p, num_passageiros));
}


void exibe_sexo(Passageiro *p, int n) {
    int cont_feminino = 0, cont_masculino = 0;
    int cont_faixa_etaria[2][4] = {0}; // matriz auxiliar para contar a quantidade de passageiros em cada faixa etária para cada sexo

    for (int i = 0; i < n; i++) {
        if (strcmp(p[i].genero, "feminino") == 0) {
            cont_feminino++;
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[0][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[0][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[0][2]++;
            } else {
                cont_faixa_etaria[0][3]++;
            }
        } else if (strcmp(p[i].genero, "masculino") == 0) {
            cont_masculino++;
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[1][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[1][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[1][2]++;
            } else {
                cont_faixa_etaria[1][3]++;
            }
        }
    }

    printf("Passageiros do sexo feminino: %d\n", cont_feminino);
    printf("Passageiros do sexo masculino: %d\n", cont_masculino);
    printf("Passageiros no total : %d\n", cont_feminino + cont_masculino);
    // printf("Passageiros por faixa etária e sexo:\n\n");
    printf("PASSAGEIROS POR FAIXA ETÁRIA E SEXO:\n\n");
    printf("   | 0-19 | 20-39 | 40-59 | 60+  |\n");
    printf("---+------+------+------+------+\n");
    printf(" F | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[0][0], cont_faixa_etaria[0][1], cont_faixa_etaria[0][2], cont_faixa_etaria[0][3]);
    printf(" M | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[1][0], cont_faixa_etaria[1][1], cont_faixa_etaria[1][2], cont_faixa_etaria[1][3]);
}

void exibe_classe(Passageiro *p, int n) {
    int primeira = 0, segunda = 0, terceira = 0, tripulacao = 0;
    
    int primeira_classe_feminino = 0, primeira_classe_masculino = 0;
    int segunda_classe_feminino = 0, segunda_classe_masculino = 0;
    int terceira_classe_feminino = 0, terceira_classe_masculino = 0;
    int tripulacao_feminino = 0, tripulacao_masculino = 0;
    
    //4 classes e 4 faixas etárias
    int cont_faixa_etaria[4][4] = {0};

    for (int i = 0; i < n; i++) {
        
        if (strcmp(p[i].classe, "1st") == 0) {
            
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[0][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[0][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[0][2]++;
            } else {
                cont_faixa_etaria[0][3]++;
            }
            
            primeira++;
            if (strcmp(p[i].genero, "feminino") == 0) {
                primeira_classe_feminino++;
            } else {
                primeira_classe_masculino++;
            }
        } else if (strcmp(p[i].classe, "2nd") == 0) {
            
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[1][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[1][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[1][2]++;
            } else {
                cont_faixa_etaria[1][3]++;
            }
            
            segunda++;
            if (strcmp(p[i].genero, "masculino") == 0) {
                segunda_classe_feminino++;
            } else {
                segunda_classe_masculino++;
            }
        } else if (strcmp(p[i].classe, "3rd") == 0) {
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[2][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[2][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[2][2]++;
            } else {
                cont_faixa_etaria[2][3]++;
            }
            
            terceira++;
            if (strcmp(p[i].genero, "feminino") == 0) {
                terceira_classe_feminino++;
            } else {
                terceira_classe_masculino++;
            }
        } else {
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                cont_faixa_etaria[3][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                cont_faixa_etaria[3][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                cont_faixa_etaria[3][2]++;
            } else {
                cont_faixa_etaria[3][3]++;
            }
            
            tripulacao++;
            if (strcmp(p[i].genero, "feminino") == 0) {
                tripulacao_feminino++;
            } else {
                tripulacao_masculino++;
            }
        }
        
    }

    
    // printf("Número de passageiros por classe:\n");
    printf("NÚMERO DE PASSAGEIROS POR CLASSE:\n");
    printf("Primeira classe: %d\n", primeira);
    printf("Segunda classe: %d\n", segunda);
    printf("Terceira classe: %d\n", terceira);
    printf("Tripulação: %d\n", tripulacao);
    
    printf("NÚMERO DE PASSAGEIROS POR CLASSE E SEXO:\n");
    printf("Primeira classe - Feminino: %d | Masculino: %d\n", primeira_classe_feminino, primeira_classe_masculino);
    printf("Segunda classe - Feminino: %d | Masculino: %d\n", segunda_classe_feminino, segunda_classe_masculino);
    printf("Terceira classe - Feminino: %d | Masculino: %d\n", terceira_classe_feminino, terceira_classe_masculino);
    printf("Tripulação - Feminino: %d | Masculino: %d\n", tripulacao_feminino, tripulacao_masculino);
    
    
    printf("NÚMERO DE PASSAGEIROS POR CLASSE E FAIXA ETÁRIA:\n\n");
    printf("      | 0-19 | 20-39 | 40-59 | 60+    |\n");
    printf("------+------+------+------+--------+\n");
    printf(" 1st  | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[0][0], cont_faixa_etaria[0][1], cont_faixa_etaria[0][2], cont_faixa_etaria[0][3]);
    printf(" 2nd  | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[1][0], cont_faixa_etaria[1][1], cont_faixa_etaria[1][2], cont_faixa_etaria[1][3]);
    printf(" 3nd  | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[2][0], cont_faixa_etaria[2][1], cont_faixa_etaria[2][2], cont_faixa_etaria[2][3]);
    printf(" tri. | %-4d | %-5d | %-5d | %-5d |\n", cont_faixa_etaria[3][0], cont_faixa_etaria[3][1], cont_faixa_etaria[3][2], cont_faixa_etaria[3][3]);
    
}


void faixa_etaria_dados(Passageiro *p, int n){
    
    for (int  i = 0; i < n; i++){
        if (strcmp(p[i].sobreviveu, "sim") == 0){
            
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                printf("\nSobrevivente (0-19) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);        
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                printf("\nSobrevivente (20-39)- Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);        
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                printf("\nSobrevivente (40-59) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);        
            } else {
                printf("\nSobrevivente (59+) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);        
            }

        }else{
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                printf("\nNão sobrevivente (0-19) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);   
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                printf("\nNão sobrevivente (20-39) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                printf("\nNão sobrevivente (40-59) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);     
            } else {
                printf("\nNão sobrevivente (59+) - Classe: %s; Sexo: %s; Idade: %d\n", p[i].classe, p[i].genero, p[i].idade);  
            }

        }
        
        
    }
    
}

void exibe_situacao(Passageiro *p, int n){
    int cont_sobreviventes = 0;
    int cont_nao_sobreviventes = 0;
    
    int sobrevivente_masc_femi[2][2] = {0};
    int sobrevivente_faixa_etaria[2][4] = {0};

    for (int i = 0; i < n; i++) {
        if (strcmp(p[i].sobreviveu, "sim") == 0) {
            cont_sobreviventes++;
            
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                sobrevivente_faixa_etaria[0][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                sobrevivente_faixa_etaria[0][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                sobrevivente_faixa_etaria[0][2]++;
            } else {
                sobrevivente_faixa_etaria[0][3]++;
            }


            if (p[i].genero == "masculino") {
                sobrevivente_masc_femi[0][0]++;
            } else {
                sobrevivente_masc_femi[0][1]++;
            }

        
        } else {
            
            if (p[i].idade >= 0 && p[i].idade <= 19) {
                sobrevivente_faixa_etaria[1][0]++;
            } else if (p[i].idade >= 20 && p[i].idade <= 39) {
                sobrevivente_faixa_etaria[1][1]++;
            } else if (p[i].idade >= 40 && p[i].idade <= 59) {
                sobrevivente_faixa_etaria[1][2]++;
            } else {
                sobrevivente_faixa_etaria[1][3]++;
            }

            if (p[i].genero == "masculino") {
                sobrevivente_masc_femi[1][0]++;
            } else {
                sobrevivente_masc_femi[1][1]++;
            }
            cont_nao_sobreviventes++;
        }
    }
    printf("NÚMERO DE PASSAGEIROS POR SITUAÇÃO:\n");
    printf("Sobreviventes: %d\n", cont_sobreviventes);
    printf("Não sobreviventes: %d\n", cont_nao_sobreviventes);

    printf("SEXO\n");
    printf("Sobreviventes - Masculino: %d | Feminino: %d\n", sobrevivente_masc_femi[0][0], sobrevivente_masc_femi[0][1]);
    printf("Não sobreviventes - Masculino: %d | Feminino: %d\n", sobrevivente_masc_femi[1][0], sobrevivente_masc_femi[1][1]);


    printf("FAIXA ETÁRIA\n");
    printf("Sobreviventes - 0-19: %d | 20-39: %d | 40-59: %d | 60+: %d\n", sobrevivente_faixa_etaria[0][0], sobrevivente_faixa_etaria[0][1], sobrevivente_faixa_etaria[0][2], sobrevivente_faixa_etaria[0][3]);
    printf("Não sobreviventes - 0-19: %d | 20-39: %d | 40-59: %d | 60+: %d\n", sobrevivente_faixa_etaria[1][0], sobrevivente_faixa_etaria[1][1], sobrevivente_faixa_etaria[1][2], sobrevivente_faixa_etaria[1][3]);

    printf("FAIXA ETÁRIA:\n\n");
    printf("                  | 0-19 | 20-39 | 40-59 | 60+  |\n");
    printf("------------------+------+------+------+------+\n");
    printf(" Sobrevivente     | %-4d | %-5d | %-5d | %-5d |\n", sobrevivente_faixa_etaria[0][0], sobrevivente_faixa_etaria[0][1], sobrevivente_faixa_etaria[0][2], sobrevivente_faixa_etaria[0][3]);
    printf(" Não sobrevivente | %-4d | %-5d | %-5d | %-5d |\n", sobrevivente_faixa_etaria[1][0], sobrevivente_faixa_etaria[1][1], sobrevivente_faixa_etaria[1][2], sobrevivente_faixa_etaria[1][3]);

    // printf("FAIXA ETÁRIA COM DADOS:\n\n");
    // faixa_etaria_dados(p, n);
}


void opcao(){
    printf("\n\n");
    printf("1 - Qual a porcentagem de X que sobreviveram ao acidente? Onde X seria :\n");
    printf("2 - Exibir número de passageiros por sexo\n");
    printf("3 - Exibir número de passageiros por classe\n");
    printf("4 - Exibir número de passageiros por situação\n");
    printf("0 - Sair\n");  
    printf("\n\n");
}

void menu(){
    int op;
    
    opcao();
    scanf("%d", &op);
    
    
    char linha[MAX_LINHA];
    FILE *arquivo = carregar_arquivo("Passageiros.txt");
    verifica_abertura(arquivo);

    Passageiro p[MAX_LINHA];

    for (int i = 0; i < MAX_LINHA && fgets(linha, MAX_LINHA, arquivo); i++) {
        sscanf(linha, "%[^,],%d,%[^,],%s", p[i].classe, &p[i].idade, p[i].genero, p[i].sobreviveu);
    }

    while (op != 0){
        switch(op){
            case 1: 
                itemB(p, MAX_LINHA);
                opcao();
                scanf("%d", &op);

                break;
            case 2:
                exibe_sexo(p, MAX_LINHA);
                opcao();
                scanf("%d", &op);
                break;
            case 3:
                exibe_classe(p, MAX_LINHA);
                opcao();
                scanf("%d", &op);
                break;
            case 4:
                exibe_situacao(p, MAX_LINHA);
                opcao();
                scanf("%d", &op);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }    
    }
    
    

}

int main() {
    
    char usuario[MAX_LEN], senha[MAX_LEN];
    printf("\n\nDigite o nome de usuário: ");
    scanf("%s", usuario);
    printf("\nDigite a senha: ");
    scanf("%s", senha);
    
    if (fazerLogin(usuario, senha)) {
        printf("\nLogin bem sucedido.\n\n");
        
        menu();
       

    } else {
        printf("Nome de usuário ou senha incorretos.\n");
    }

    return 0;
}