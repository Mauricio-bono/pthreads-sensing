#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

char* ler_arquivo(const char* nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long tamanho = ftell(f);
    rewind(f);

    char *buffer = (char*)malloc(tamanho + 1);
    fread(buffer, 1, tamanho, f);
    buffer[tamanho] = '\0';

    fclose(f);
    return buffer;
}

int main() {
    char *json_string = ler_arquivo("senzemo_cx_bg.json");

    if (!json_string) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    cJSON *json = cJSON_Parse(json_string);

    if (!json) {
        printf("Erro ao parsear JSON\n");
        return 1;
    }

    cJSON *deviceName = cJSON_GetObjectItem(json, "deviceName");
    cJSON *idade = cJSON_GetObjectItem(json, "idade");
    cJSON *ativo = cJSON_GetObjectItem(json, "ativo");

    printf("deviceName: %s\n", deviceName->valuestring);
    printf("Idade: %d\n", idade->valueint);
    printf("Ativo: %s\n", cJSON_IsTrue(ativo) ? "true" : "false");

    // Limpeza
    cJSON_Delete(json);
    free(json_string);

    return 0;
}