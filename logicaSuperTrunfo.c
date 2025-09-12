#include <stdio.h>
#include <string.h>

/* ===== Escolha do atributo NO CÓDIGO =====
   Use UMA destas strings:
   "POPULACAO", "AREA", "PIB", "DENSIDADE", "PIB_PC"
*/
#define ATRIBUTO "POPULACAO"

int main(void) {
    /* --------- CARTA 1 --------- */
    char Estado1[30];
    char Codigo1[4];
    char Cidade1[50];
    int   Populacao1;
    float Area1;
    float Pib1;                 // em bilhões de reais
    int   Pontos1;

    /* --------- CARTA 2 --------- */
    char Estado2[30];
    char Codigo2[4];
    char Cidade2[50];
    int   Populacao2;
    float Area2;
    float Pib2;                 // em bilhões de reais
    int   Pontos2;

    /* ===== Entrada de dados (interativa) ===== */
    printf("=== CADASTRO CARTA 1 ===\n");
    printf("Estado: ");                scanf(" %29[^\n]", Estado1);
    printf("Codigo (ex: A01): ");      scanf(" %3s", Codigo1);
    printf("Cidade: ");                scanf(" %49[^\n]", Cidade1);
    printf("Populacao (int): ");       scanf(" %d", &Populacao1);
    printf("Area (km2): ");            scanf(" %f", &Area1);
    printf("PIB (bilhoes): ");         scanf(" %f", &Pib1);
    printf("Pontos Turisticos: ");     scanf(" %d", &Pontos1);

    printf("\n=== CADASTRO CARTA 2 ===\n");
    printf("Estado: ");                scanf(" %29[^\n]", Estado2);
    printf("Codigo (ex: B02): ");      scanf(" %3s", Codigo2);
    printf("Cidade: ");                scanf(" %49[^\n]", Cidade2);
    printf("Populacao (int): ");       scanf(" %d", &Populacao2);
    printf("Area (km2): ");            scanf(" %f", &Area2);
    printf("PIB (bilhoes): ");         scanf(" %f", &Pib2);
    printf("Pontos Turisticos: ");     scanf(" %d", &Pontos2);

    /* ===== Derivados =====
       Densidade = Populacao / Area
       PIB per capita = (PIB em reais) / Populacao
       (entrada de PIB está em BILHOES → multiplica por 1e9)
    */
    float Dens1 = (float)Populacao1 / Area1;
    float Dens2 = (float)Populacao2 / Area2;

    float PibPc1 = (Pib1 * 1e9f) / (float)Populacao1;
    float PibPc2 = (Pib2 * 1e9f) / (float)Populacao2;

    /* ===== Exibe as cartas ===== */
    printf("\n=== CARTA 1 ===\n");
    printf("%s (%s) | Cod:%s\n", Cidade1, Estado1, Codigo1);
    printf("Populacao: %d\n", Populacao1);
    printf("Area: %.2f km2\n", Area1);
    printf("PIB: %.2f bilhoes\n", Pib1);
    printf("Pontos: %d\n", Pontos1);
    printf("Densidade: %.2f hab/km2\n", Dens1);
    printf("PIB per capita: %.2f R$\n", PibPc1);

    printf("\n=== CARTA 2 ===\n");
    printf("%s (%s) | Cod:%s\n", Cidade2, Estado2, Codigo2);
    printf("Populacao: %d\n", Populacao2);
    printf("Area: %.2f km2\n", Area2);
    printf("PIB: %.2f bilhoes\n", Pib2);
    printf("Pontos: %d\n", Pontos2);
    printf("Densidade: %.2f hab/km2\n", Dens2);
    printf("PIB per capita: %.2f R$\n\n", PibPc2);

    /* ===== Comparacao (um unico atributo) ===== */
    const char *rotulo = "";
    double v1 = 0.0, v2 = 0.0;   // para imprimir de forma uniforme
    int carta1Vence = 0;         // 1 = Carta 1 vence; 0 = Carta 2 vence

    if (strcmp(ATRIBUTO, "POPULACAO") == 0) {
        rotulo = "Populacao";
        v1 = Populacao1; v2 = Populacao2;
        carta1Vence = (Populacao1 > Populacao2);
    } else if (strcmp(ATRIBUTO, "AREA") == 0) {
        rotulo = "Area (km2)";
        v1 = Area1; v2 = Area2;
        carta1Vence = (Area1 > Area2);
    } else if (strcmp(ATRIBUTO, "PIB") == 0) {
        rotulo = "PIB (bilhoes)";
        v1 = Pib1; v2 = Pib2;
        carta1Vence = (Pib1 > Pib2);
    } else if (strcmp(ATRIBUTO, "DENSIDADE") == 0) {
        rotulo = "Densidade (hab/km2)";
        v1 = Dens1; v2 = Dens2;
        /* Regra especial: menor densidade vence */
        carta1Vence = (Dens1 < Dens2);
    } else { /* "PIB_PC" */
        rotulo = "PIB per capita (R$)";
        v1 = PibPc1; v2 = PibPc2;
        carta1Vence = (PibPc1 > PibPc2);
    }

    /* ===== Saida da comparacao ===== */
    printf("Comparacao de cartas (Atributo: %s)\n\n", rotulo);
    printf("Carta 1 - %s (%s): ", Cidade1, Estado1);
    if (strcmp(rotulo, "Populacao") == 0) printf("%d\n", Populacao1);
    else printf("%.2f\n", (float)v1);

    printf("Carta 2 - %s (%s): ", Cidade2, Estado2);
    if (strcmp(rotulo, "Populacao") == 0) printf("%d\n\n", Populacao2);
    else printf("%.2f\n\n", (float)v2);

    if (carta1Vence)
        printf("Resultado: Carta 1 (%s) venceu!\n", Cidade1);
    else
        printf("Resultado: Carta 2 (%s) venceu!\n", Cidade2);

    return 0;
}
