/*
Enzo Benedetto Proença - 10418579
Gabriel Alves de Freitas Spinola Sucupira - 10418133
Pedro Henrique Lanfredi Moreiras - 10441998
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define BUFFER (1024)

char *lerTextoDoTeclado(int *tamanho) {
    int capacidade = BUFFER;
    // Aloca memória inicial
    char *texto = malloc(capacidade * sizeof(char));

    if (texto == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    printf("Insira o texto, para identificar o seu idioma: \n");

    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        c = tolower(c);
        texto[(*tamanho)++] = c;

        // Se o tamanho atingir a capacidade, realocar mais memória
        if (*tamanho >= capacidade) {
            capacidade *= 2;
            texto = realloc(texto, capacidade * sizeof(char));

            if (texto == NULL) {
                printf("Erro ao realocar memória.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    texto[*tamanho] = '\0';    

    return texto;
}

char *identificar(int vetor[], int tamanho) {
    int chancePT = 0, chanceEN = 0;
    double porcentagem_letra[26];
    
    // Percentuais definidos pela lingua, referência https://pt.wikipedia.org/wiki/Frequência_de_letras
    double portugues[26] = {14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30,
                            1.28,  6.18, 0.40, 0.02, 2.78,  4.74, 5.05,
                            10.73, 2.52, 1.20, 6.53, 7.81,  4.34, 4.63,
                            1.67,  0.01, 0.21, 0.01, 0.47};
    double ingles[26] = {8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015,
                         6.094, 6.966, 0.153, 0.772, 4.025,  2.406, 6.749,
                         7.507, 1.929, 0.095, 5.987, 6.327,  9.056, 2.758,
                         0.978, 2.360, 0.150, 1.974, 0.074};

    //Percorre o vetor com os contadores, comparando com os percentuais e escolhe a maior diferença para adicionar o ponto em chancePT ou chanceEN
      for (int i = 0; i < 26; i++) {
        porcentagem_letra[i] = (vetor[i] * 100) / tamanho;

        /* 
        Verifica a diferença entre a porcentagem de vezes que uma letra aparece
        por língua e a porcentagem da mesma letra do texto (isso é feito por
        língua), a língua em que a diferença for mais próxima de 0 aumenta as
        chances de sua língua ser a detectada
        */
          
        if (fabs(porcentagem_letra[i] - portugues[i]) < fabs(porcentagem_letra[i] - ingles[i]))
          chancePT++;
        if (fabs(porcentagem_letra[i] - portugues[i]) > fabs(porcentagem_letra[i] - ingles[i]))
          chanceEN++;
      }

    if (chanceEN > chancePT)
        return "\nSaida = Ingles";
    return "\nSaida = Portugues";
}

void incrementarContadoresPorLetra(int *vetorContadores, const char *texto, int tamanhoTexto) {
    for (int i = 0; i < tamanhoTexto; i++) {
        if (isalpha(texto[i])) {
            // Usa da propriedade do C em que a letra 'a' tem o valor 97 (em ASCII) e ao subtrai-lo dessa forma transforma em número
            vetorContadores[texto[i] - 'a']++;
        }
    }
}

int main(void) {
    int contadorLetras[26] = {0};
    int tamanho = 0;
    char *entrada = lerTextoDoTeclado(&tamanho);
    printf("Tamanho = %d ", tamanho);
    incrementarContadoresPorLetra(contadorLetras, entrada, tamanho);
    printf("%s\n", identificar(contadorLetras, tamanho));
    free(entrada);

    return 0;
}

// Link Replit: https://replit.com/@GabrielSpinola3/Atividade-Avaliativa-2-Proj-e-Analise-de-Algoritmos?v=1#main.c
