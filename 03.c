#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#define ARQUIVO_JSON "dados.json"

void processarFaturamento(const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo JSON.\n");
        return;
    }

    // tamanho do arquivo
    fseek(fp, 0, SEEK_END);
    long tamanho = ftell(fp);
    rewind(fp);

    // todo o conteúdo do arquivo
    char *conteudo = (char *)malloc(tamanho + 1);
    fread(conteudo, 1, tamanho, fp);
    fclose(fp);
    conteudo[tamanho] = '\0';

    // Parse do JSON
    cJSON *json = cJSON_Parse(conteudo);
    free(conteudo);

    if (json == NULL) {
        printf("Erro ao interpretar o JSON.\n");
        return;
    }

    int diasAcimaMedia = 0, diasComFaturamento = 0;
    double menor = -1, maior = -1, soma = 0, media;

    // Percorre os itens do JSON
    cJSON *item;
    cJSON_ArrayForEach(item, json) {
        cJSON *valor = cJSON_GetObjectItemCaseSensitive(item, "valor");

        if (valor->valuedouble > 0) { // Ignora dias sem faturamento
            if (menor == -1 || valor->valuedouble < menor) {
                menor = valor->valuedouble;
            }
            if (maior == -1 || valor->valuedouble > maior) {
                maior = valor->valuedouble;
            }
            soma += valor->valuedouble;
            diasComFaturamento++;
        }
    }

    // Calcula a média mensal considerando apenas os dias com faturamento
    if (diasComFaturamento > 0) {
        media = soma / diasComFaturamento;

        // Contar dias acima da média
        cJSON_ArrayForEach(item, json) {
            cJSON *valor = cJSON_GetObjectItemCaseSensitive(item, "valor");
            if (valor->valuedouble > media) {
                diasAcimaMedia++;
            }
        }
    }

    printf("Menor faturamento: %.2f\n", menor);
    printf("Maior faturamento: %.2f\n", maior);
    printf("Dias com faturamento acima da media: %d\n", diasAcimaMedia);

    cJSON_Delete(json);
}

int main() {
    processarFaturamento(ARQUIVO_JSON);
    return 0;
}
