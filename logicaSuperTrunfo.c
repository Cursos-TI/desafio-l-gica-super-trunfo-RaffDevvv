#include <stdio.h>
#include <string.h>

int main(void) {
    /* ---------- CARTA 1 ---------- */
    char Estado1[30], Codigo1[4], Cidade1[50];
    int Pop1, Pontos1;
    float Area1, Pib1; /* PIB em BILHOES */

    /* ---------- CARTA 2 ---------- */
    char Estado2[30], Codigo2[4], Cidade2[50];
    int Pop2, Pontos2;
    float Area2, Pib2; /* PIB em BILHOES */

    printf("=== SUPER TRUNFO - NIVEL AVENTUREIRO ===\n\n");

    /* -------- Cadastro Carta 1 -------- */
    printf("--- CARTA 1 ---\n");
    printf("Estado (ex: Santa Catarina): ");
    scanf(" %29[^\n]", Estado1);
    printf("Codigo (ex: A01): ");
    scanf(" %3s", Codigo1);
    printf("Cidade: ");
    scanf(" %49[^\n]", Cidade1);
    printf("Populacao (inteiro): ");
    scanf(" %d", &Pop1);
    printf("Area (km2): ");
    scanf(" %f", &Area1);
    printf("PIB (em bilhoes de R$): ");
    scanf(" %f", &Pib1);
    printf("Pontos turisticos: ");
    scanf(" %d", &Pontos1);
    printf("\n");

    /* -------- Cadastro Carta 2 -------- */
    printf("--- CARTA 2 ---\n");
    printf("Estado: ");
    scanf(" %29[^\n]", Estado2);
    printf("Codigo: ");
    scanf(" %3s", Codigo2);
    printf("Cidade: ");
    scanf(" %49[^\n]", Cidade2);
    printf("Populacao (inteiro): ");
    scanf(" %d", &Pop2);
    printf("Area (km2): ");
    scanf(" %f", &Area2);
    printf("PIB (em bilhoes de R$): ");
    scanf(" %f", &Pib2);
    printf("Pontos turisticos: ");
    scanf(" %d", &Pontos2);
    printf("\n");

    /* ---------- Derivados ---------- */
    float Dens1 = (float)Pop1 / Area1;
    float Dens2 = (float)Pop2 / Area2;
    float PibPc1 = (Pib1 * 1e9f) / (float)Pop1; /* R$ por habitante */
    float PibPc2 = (Pib2 * 1e9f) / (float)Pop2;

    /* ---------- Menu ---------- */
    int opcao;
    printf("MENU - Escolha o atributo para comparar:\n");
    printf("1 - Populacao (maior vence)\n");
    printf("2 - Area (maior vence)\n");
    printf("3 - PIB em bilhoes (maior vence)\n");
    printf("4 - Densidade (MENOR vence)\n");
    printf("5 - PIB per capita (maior vence)\n");
    printf("6 - Comparacao ANINHADA (Populacao -> PIB per capita -> Densidade -> Pontos)\n");
    printf("Opcao: ");
    scanf(" %d", &opcao);
    printf("\n");

    int carta1Vence = 0;    /* 1 = Carta 1 venceu; 0 = Carta 2 venceu */
    int empate = 0;         /* 1 = empatou */
    const char *rotulo = "";
    double v1 = 0.0, v2 = 0.0;

    switch (opcao) {
        case 1: /* Populacao */
            rotulo = "Populacao";
            v1 = Pop1; v2 = Pop2;
            if (Pop1 > Pop2) carta1Vence = 1;
            else if (Pop1 == Pop2) empate = 1;
            break;

        case 2: /* Area */
            rotulo = "Area (km2)";
            v1 = Area1; v2 = Area2;
            if (Area1 > Area2) carta1Vence = 1;
            else if (Area1 == Area2) empate = 1;
            break;

        case 3: /* PIB bilhoes */
            rotulo = "PIB (bilhoes)";
            v1 = Pib1; v2 = Pib2;
            if (Pib1 > Pib2) carta1Vence = 1;
            else if (Pib1 == Pib2) empate = 1;
            break;

        case 4: /* Densidade - menor vence */
            rotulo = "Densidade (hab/km2)";
            v1 = Dens1; v2 = Dens2;
            if (Dens1 < Dens2) carta1Vence = 1; /* menor vence */
            else if (Dens1 == Dens2) empate = 1;
            break;

        case 5: /* PIB per capita */
            rotulo = "PIB per capita (R$)";
            v1 = PibPc1; v2 = PibPc2;
            if (PibPc1 > PibPc2) carta1Vence = 1;
            else if (PibPc1 == PibPc2) empate = 1;
            break;

        case 6: /* Comparacao aninhada (desempates encadeados) */
            rotulo = "ANINHADA: Pop -> PIBpc -> Densidade -> Pontos";
            /* 1) Populacao (maior vence) */
            if (Pop1 != Pop2) {
                carta1Vence = (Pop1 > Pop2);
            } else {
                /* 2) PIB per capita (maior vence) */
                if (PibPc1 != PibPc2) {
                    carta1Vence = (PibPc1 > PibPc2);
                } else {
                    /* 3) Densidade (menor vence) */
                    if (Dens1 != Dens2) {
                        carta1Vence = (Dens1 < Dens2);
                    } else {
                        /* 4) Pontos turisticos (maior vence) */
                        if (Pontos1 != Pontos2) {
                            carta1Vence = (Pontos1 > Pontos2);
                        } else {
                            empate = 1;
                        }
                    }
                }
            }
            /* v1/v2 apenas para exibir algo representativo */
            v1 = Pop1; v2 = Pop2;
            break;

        default:
            printf("Opcao invalida.\n");
            return 0;
    }

    /* ---------- Saida clara ---------- */
    printf("Comparacao de cartas (Atributo: %s)\n\n", rotulo);
    printf("Carta 1 - %s (%s): ", Cidade1, Estado1);
    if (opcao == 1)        printf("%d\n", Pop1);
    else if (opcao == 2)   printf("%.2f\n", Area1);
    else if (opcao == 3)   printf("%.2f\n", Pib1);
    else if (opcao == 4)   printf("%.2f\n", Dens1);
    else if (opcao == 5)   printf("%.2f\n", PibPc1);
    else /* 6 */           printf("Pop=%d, PIBpc=%.2f, Dens=%.2f, Pontos=%d\n",
                                  Pop1, PibPc1, Dens1, Pontos1);

    printf("Carta 2 - %s (%s): ", Cidade2, Estado2);
    if (opcao == 1)        printf("%d\n\n", Pop2);
    else if (opcao == 2)   printf("%.2f\n\n", Area2);
    else if (opcao == 3)   printf("%.2f\n\n", Pib2);
    else if (opcao == 4)   printf("%.2f\n\n", Dens2);
    else if (opcao == 5)   printf("%.2f\n\n", PibPc2);
    else /* 6 */           printf("Pop=%d, PIBpc=%.2f, Dens=%.2f, Pontos=%d\n\n",
                                  Pop2, PibPc2, Dens2, Pontos2);

    if (empate) {
        printf("Resultado: EMPATE\n");
    } else if (carta1Vence) {
        printf("Resultado: Carta 1 (%s) venceu!\n", Cidade1);
    } else {
        printf("Resultado: Carta 2 (%s) venceu!\n", Cidade2);
    }

    return 0;
}
