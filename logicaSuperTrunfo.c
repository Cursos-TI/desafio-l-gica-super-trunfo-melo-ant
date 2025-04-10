#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

#define MAX_CARDS 2
// Desafio Super Trunfo - Países
// Tema 2 - Comparação das Cartas
// Este código inicial serve como base para o desenvolvimento do sistema de comparação de cartas de cidades. 
// Siga os comentários para implementar cada parte do desafio.

struct cartaTrunfo {
    char estado[3];
    int cod;
    char cidade[34];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidade;
    float pibPerCapita;
    float superPoder; // area + pib + pontosTuristicos + pibPerCapita + populacao + 1/densidade
};

struct baralhoTrunfo {
    struct cartaTrunfo cartas[MAX_CARDS];
    int qtdCartas;
};


int contarCartasEstado(char sigla[2], struct baralhoTrunfo baralho){
    int qtdb = 0;
    if (baralho.qtdCartas > 0){
        for(int i = 0;i < baralho.qtdCartas;i++){
            if (strcmp(sigla, baralho.cartas[i].estado) == 0){
                qtdb = qtdb + 1;
            };

        };
    return qtdb;
    };
    return 0;
};

void to_upper(char *str) {
    while (*str) {
        *str = toupper((unsigned char) *str);
        str++;
    }
}

struct baralhoTrunfo criarCarta(struct baralhoTrunfo baralho, int qtd) {
    for (int i = 0; i < qtd; i++) {
        int next;
        next = 0;
        while (next == 0){
            int cod;
            char estado[3];
            printf("===================================================\n");
            printf("Insira a sigla do estado (Exp : PB, AM, MA e etc)..... ");
            if(scanf("%2s", estado) != 1){ //tratamento de erro do scanf
                printf("Erro ao ler o estado\n");
                return baralho;
            }
            
            char estadoUpper[3];
            to_upper(estado);
            cod = contarCartasEstado(estado,baralho);
            printf("[!]( qtd de cartas com esse estado : %d )\n",cod);
            if (cod + 1 > 4){
                next = 0;
                printf("Já existem 4 cartas com o mesmo estado\n");
            }else{
                next = 1;
                baralho.cartas[i].cod = cod + 1;
                strcpy(baralho.cartas[i].estado,estado);
            }
           
        }
        getchar();
        char cidade_temp[34];

        printf("Insira o nome da cidade..... ");
        if (fgets(cidade_temp,33,stdin) != NULL){
            cidade_temp[strcspn(cidade_temp, "\n")] = '\0';
            if (strlen(cidade_temp) > 33) {
                printf("Erro: Cidade excede o tamanho máximo de 33 caracteres.\n");
                return baralho; // Retorna o baralho sem modificações
            }
    
            // Copiar a cidade para o baralho e converter para maiúsculas
            strcpy(baralho.cartas[i].cidade, cidade_temp);
            to_upper(baralho.cartas[i].cidade);
        }else{
            printf("Erro ao ler cidade\n");
            return baralho;
        }
        fflush(stdin);

        printf("Insira a populacao..... ");
        if(scanf("%ld", &baralho.cartas[i].populacao) != 1){
            printf("Erro ao ler a populacao\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira a area da cidade(em km²)..... ");
        if(scanf("%f", &baralho.cartas[i].area) != 1){
            printf("Erro ao ler a area\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira o PIB da cidade..... ");
        if(scanf("%f", &baralho.cartas[i].pib) != 1){
            printf("Erro ao ler o PIB\n");
            return baralho;
        }
        fflush(stdin);
        printf("Insira a quantidade de pontos turisticos..... ");
        if(scanf("%d", &baralho.cartas[i].pontosTuristicos) != 1){
            printf("Erro ao ler os pontos turisticos\n");
            return baralho;
        }  
        fflush(stdin);
        
        printf("===================================================\n");
        //calcular pib per capita e densidade
        baralho.cartas[i].densidade = (float)baralho.cartas[i].populacao / baralho.cartas[i].area;
        baralho.cartas[i].pibPerCapita = (baralho.cartas[i].pib) /(float)baralho.cartas[i].populacao;

        //canculando super-poder
        baralho.cartas[i].superPoder = baralho.cartas[i].populacao + baralho.cartas[i].area + baralho.cartas[i].pib + baralho.cartas[i].pontosTuristicos + baralho.cartas[i].pibPerCapita + (1/baralho.cartas[i].densidade);


        baralho.qtdCartas++;
    }
    return baralho;
}

float pegarAtributoPorID(int codDoAtributo, struct cartaTrunfo carta){
    switch (codDoAtributo)
    {
    case 0:
        /* code */
        /**populacao */
        return carta.populacao;
        break;
    case 1:
        /* AREA */
        return carta.area;
        break;
    case 2:
        return carta.pib;
        break;
    case 3:
        return carta.pontosTuristicos;
        break;
    case 4:
        return carta.densidade;
        break;
    case 5:
        return carta.pibPerCapita;
        break;
    default:
        return carta.superPoder;
        break;
    }
};

void mostrarCarta(struct cartaTrunfo carta) {
    printf("===================================================\n");
    printf("SUPER PODER : %.2f\n", carta.superPoder);
    printf("===================================================\n");
    printf("Codigo : %d\n", carta.cod);
    printf("Estado : %s\n", carta.estado);
    printf("Cidade : %s\n", carta.cidade);
    printf("Populacao : %ld\n", carta.populacao);
    printf("Pontos Turisticos : %d\n", carta.pontosTuristicos);
    printf("Area : %.2f km2\n", carta.area);
    printf("PIB : R$ %.2f \n", carta.pib);
    printf("Densidade populacional : %.2f hab/km2\n",carta.densidade);
    printf("PIB per capita %.2f PIB/hab \n",carta.pibPerCapita);
    printf("===================================================\n");
}

float compararCartas(struct cartaTrunfo cartaA, struct cartaTrunfo cartaB,int codDoAtributo){
    printf("===================================================\n");
    printf("Carta A (%d/%s - %s) Vs Carta B(%d/%s - %s) \n",cartaA.cod,cartaA.estado,cartaA.cidade,cartaB.cod,cartaB.estado,cartaB.cidade);

    switch (codDoAtributo)
    {
    case 0:
        /* code */
        printf("Populacao (%ld) Vs Populacao(%ld)",cartaA.populacao,cartaB.populacao);
        if (cartaA.populacao > cartaB.populacao){
            printf("Populacao : Carta A vence (1)\n");
        }else if (cartaA.populacao < cartaB.populacao){
            printf("Populacao : Carta B vence (0)\n");
        }else{
            printf("Populacao : Empate)\n");
        };
        break;
    case 1:
        printf("Area (%.2f) Vs Area(%.2f)",cartaA.area,cartaB.area);
        if (cartaA.area > cartaB.area){
            printf("Area : Carta A vence (1)\n");
        }else if(cartaA.area < cartaB.area){
            printf("Area : Carta B vence (0)\n");
        }else{
            printf("Area : Empate\n");
        };
        break;
    case 2:
        printf("PIB (%.2f) Vs PIB(%.2f)",cartaA.area,cartaB.area);
        if (cartaA.pib > cartaB.pib){
            printf("PIB : Carta A vence (1)\n");
        }else if(cartaA.pib < cartaB.pib){
            printf("PIB : Carta B vence (0)\n");
        }else{
            printf("PIB : Empate\n");
        };
        break;
    case 3:
        printf("Pontos Turisticos (%d) Vs Pontos Turisticos (%d)",cartaA.pontosTuristicos,cartaB.pontosTuristicos);
        if (cartaA.pontosTuristicos > cartaB.pontosTuristicos){
            printf("Pontos Turisticos : Carta A vence (1)\n");
        }else if(cartaA.pontosTuristicos < cartaB.pontosTuristicos){
            printf("Pontos Turisticos : Carta B vence (0)\n");
        }else{
            printf("Pontos Turisticos : Empate\n");
        };
        break;
    case 4:
        printf("Densidade (%.2f) Vs Densidade (%.2f)",cartaA.densidade,cartaB.densidade);
        if (cartaA.densidade < cartaB.densidade){
            printf("Densidade : Carta A vence (1)\n");
        }else if(cartaA.densidade > cartaB.densidade){
            printf("Densidade: Carta B vence (0)\n");
        }else{
            printf("Empate\n");
        };
        break;
    case 5:
        printf("PIB per Capita (%.2f) Vs PIB per Capita(%.2f)",cartaA.pibPerCapita,cartaB.pibPerCapita);
        if (cartaA.pibPerCapita	 > cartaB.pibPerCapita){
            printf("PIB per capita : Carta A vence (1)\n");
        }else if(cartaA.pibPerCapita < cartaB.pibPerCapita){
            printf("PIB per capita : Carta B vence (0)\n");
        }else{
            printf("PIB per Capite : Empate\n");
        };

        break;
    default:
        printf("Superpoder (%.2f) Vs Superpoder(%.2f)",cartaA.superPoder,cartaB.superPoder);
        if (cartaA.superPoder > cartaB.superPoder){
            printf("Super Poder : Carta A vence (1)\n");
        }else if(cartaA.superPoder < cartaB.superPoder){
            printf("Super Poder : Carta B vence (0)\n");
        }else{
            printf("Super Poder : Empate");
        };
        break;
    }
    
    printf("===================================================\n");
};
int main() {
    // Definição das variáveis para armazenar as propriedades das cidades
    // Você pode utilizar o código do primeiro desafio
    int codAttrA = 0;
    int codAttrB = 0;
    float somaA = 0.0;
    float somaB = 0.0;
    int sair = 1;
    struct baralhoTrunfo baralhoA;
    baralhoA.qtdCartas = 0;
    
    // Cadastro das Cartas:
    // Implemente a lógica para solicitar ao usuário que insira os dados das cidades
    // utilizando a função scanf para capturar as entradas.
    // utilize o código do primeiro desafio
    
    int qtdA;
    printf("Digite quantas cartas voce quer criar? ");
    if(scanf("%d", &qtdA) != 1){
        printf("Erro ao ler a quantidade de cartas\n");
        return 1;
    }
    if(qtdA > MAX_CARDS){
        printf("Erro, quantidade de cartas supera a capacidade do baralho(32)");
        return 1;
    }
    
    baralhoA = criarCarta(baralhoA, qtdA);

    // Comparação de Cartas:
    // Desenvolva a lógica de comparação entre duas cartas.
    // Utilize estruturas de decisão como if, if-else para comparar atributos como população, área, PIB, etc.

    // Exemplo:
    // if (populacaoA > populacaoB) {
    //     printf("Cidade 1 tem maior população.\n");
    // } else {
    //     printf("Cidade 2 tem maior população.\n");
    // }

    // Exibição dos Resultados:
    // Após realizar as comparações, exiba os resultados para o usuário.
    // Certifique-se de que o sistema mostre claramente qual carta venceu e com base em qual atributo.

    // Exemplo:
    // printf("A cidade vencedora é: %s\n", cidadeVencedora);
    if (baralhoA.qtdCartas == 2){
        do
        {
            system("cls");
            printf("Cód : Atributo\n");
            printf("0   :   Populacao\n");
            printf("1   :   Area\n");
            printf("2   :   PIB\n");
            printf("3   :   Pontos Turisticos\n");
            printf("4   :   Densidade\n");
            printf("5   :   PIB per Capita\n");
            printf("6   :   Super Poder\n");
            printf("Insira o código do primeiro atributo para comparar : \n");
            
            codAttrA = 0;
            codAttrB = 0;

            if(scanf("%d",&codAttrA) != 1){
                printf("Primeiro código não processado\n");
            };

            do{
                
                /* code */
                system("cls");
                printf("Cód : Atributo\n");
                if(codAttrA !=0){printf("0   :   Populacao\n");};
                if(codAttrA !=1){printf("1   :   Area\n");};
                if(codAttrA !=2){printf("2   :   PIB\n");};
                if(codAttrA !=3){("3   :   Pontos Turisticos\n");};
                if(codAttrA !=4){printf("4   :   Densidade\n");};
                if(codAttrA !=5){printf("5   :   PIB per Capita\n");};
                if(codAttrA !=6){printf("6   :   Super Poder\n");};
                printf("Insira o código do segundo atributo para comparar : \n");
                if(scanf("%d",&codAttrB) != 1){
                    printf("Segundo código não processado\n");
                };
                if(codAttrB == codAttrA){
                    printf("Código já selecionado, favor selecionar outro\n");
                }else{
                    break;
                }
            } while (codAttrB == codAttrA);
            
            compararCartas(baralhoA.cartas[0],baralhoA.cartas[1],codAttrA);
            compararCartas(baralhoA.cartas[0],baralhoA.cartas[1],codAttrB);
            somaA = pegarAtributoPorID(codAttrA,baralhoA.cartas[0]) + pegarAtributoPorID(codAttrB,baralhoA.cartas[0]);
            somaB = pegarAtributoPorID(codAttrA,baralhoA.cartas[1]) + pegarAtributoPorID(codAttrB,baralhoA.cartas[1]);
            printf("SOMA A( %f ) vs SOMA B ( %f )\n",somaA,somaB);
            if (somaA > somaB){
                printf("Carta A ganhou\n");
            }else if(somaA < somaB){
                printf("Carta B ganhou\n");
            }else{
                printf("Empate");
            };


            printf("Finalizar comparacao ? \n[Sim = 0 / Nao = 1]\n");
            if(scanf("%d", &sair) != 1){
                printf("Erro no codigo\n");
                return 1;
            }else if(sair == 0){
                break;
            };
            
        } while (sair == 1);
        
    };
    
    if (errno != 0){
        printf("Value of errno: %d\n", errno);
    }
    
    return 0;
}
