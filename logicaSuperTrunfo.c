#include <stdio.h>
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
        if(scanf("%d", &baralho.cartas[i].populacao) != 1){
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



void mostrarCarta(struct cartaTrunfo carta) {
    printf("===================================================\n");
    printf("SUPER PODER : %d\n", carta.superPoder);
    printf("===================================================\n");
    printf("Codigo : %d\n", carta.cod);
    printf("Estado : %s\n", carta.estado);
    printf("Cidade : %s\n", carta.cidade);
    printf("Populacao : %d\n", carta.populacao);
    printf("Pontos Turisticos : %d\n", carta.pontosTuristicos);
    printf("Area : %.2f km2\n", carta.area);
    printf("PIB : R$ %.2f \n", carta.pib);
    printf("Densidade populacional : %.2f hab/km2\n",carta.densidade);
    printf("PIB per capita %.2f PIB/hab \n",carta.pibPerCapita);
    printf("===================================================\n");
}

void compararCartas(struct cartaTrunfo cartaA, struct cartaTrunfo cartaB,int codDoAtributo){
    printf("===================================================\n");
    printf("Carta A (%d/%s) Vs Carta B(%d/%s) \n",cartaA.cod,cartaA.estado,cartaB.cod,cartaB.estado);


    if (cartaA.populacao > cartaB.populacao){
        printf("Populacao : Carta A vence (1)\n");
    }else{
        printf("Populacao : Carta B vence (0)\n");
    };

    if (cartaA.area > cartaB.area){
        printf("Area : Carta A vence (1)\n");
    }else{
        printf("Area : Carta B vence (0)\n");
    };

    if (cartaA.pib > cartaB.pib){
        printf("PIB : Carta A vence (1)\n");
    }else{
        printf("PIB : Carta B vence (0)\n");
    };

    if (cartaA.pontosTuristicos > cartaB.pontosTuristicos){
        printf("Pontos Turisticos : Carta A vence (1)\n");
    }else{
        printf("Pontos Turisticos : Carta B vence (0)\n");
    };

    if (cartaA.densidade < cartaB.densidade){
        printf("Densidade : Carta A vence (1)\n");
    }else{
        printf("Densidade: Carta B vence (0)\n");
    };
    
    if (cartaA.pibPerCapita	 > cartaB.pibPerCapita){
        printf("PIB per capita : Carta A vence (1)\n");
    }else{
        printf("PIB per capita : Carta B vence (0)\n");
    };

    if (cartaA.superPoder > cartaB.superPoder){
        printf("Super Poder : Carta A vence (1)\n");
    }else{
        printf("Super Poder : Carta B vence (0)\n");
    };

    printf("===================================================\n");
};
int main() {
    // Definição das variáveis para armazenar as propriedades das cidades
    // Você pode utilizar o código do primeiro desafio
    int codAttr = 0;
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
        printf("Insira o código do atributo para comparar : ");
        printf("Cód : Atributo");
        printf("0   :   Populacao");
        printf("1   :   Area");
        printf("2   :   PIB");
        printf("3   :   Pontos Turisticos");
        printf("4   :   Densidade");
        printf("5   :   Super Poder");
        scanf("%d",&codAttr);
        compararCartas(baralhoA.cartas[0],baralhoA.cartas[1],codAttr);
    };
    
    if (errno != 0){
        printf("Value of errno: %d\n", errno);
    }
    
    return 0;
}
