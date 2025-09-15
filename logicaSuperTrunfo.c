#include <stdio.h>
#include <string.h>
#include <math.h>

/* ---------------------------- Modelo de dados ---------------------------- */
typedef struct {
    char  estado[30];
    char  codigo[4];
    char  cidade[50];
    unsigned long populacao;
    float area;     // km²
    float pib;      // EM BILHOES DE REAIS
    int   pontos;

    float densidade; // hab/km²
    float pib_pc;    // R$ por habitante
} Carta;

/* ---------------------------- Utilidades ---------------------------- */
void ler_carta(Carta *c, int idx) {
    printf("--- CADASTRO DA CARTA %d ---\n", idx);
    printf("Estado (ex: Santa Catarina): ");
    scanf(" %29[^\n]", c->estado);
    printf("Codigo (ex: A01): ");
    scanf(" %3s", c->codigo);
    printf("Cidade: ");
    scanf(" %49[^\n]", c->cidade);
    printf("Populacao (inteiro positivo): ");
    scanf(" %lu", &c->populacao);
    printf("Area (km2): ");
    scanf(" %f", &c->area);
    printf("PIB (em BILHOES de R$): ");
    scanf(" %f", &c->pib);
    printf("Pontos turisticos: ");
    scanf(" %d", &c->pontos);

    c->densidade = (float)c->populacao / c->area;
    c->pib_pc    = (c->pib * 1e9f) / (float)c->populacao;
    puts("");
}

void mostrar_carta(const Carta *c, int idx) {
    printf("--- CARTA %d ---\n", idx);
    printf("Estado: %s\n", c->estado);
    printf("Codigo: %s\n", c->codigo);
    printf("Cidade: %s\n", c->cidade);
    printf("Populacao: %lu\n", c->populacao);
    printf("Area: %.2f km2\n", c->area);
    printf("PIB: %.2f bilhoes\n", c->pib);
    printf("Pontos Turisticos: %d\n", c->pontos);
    printf("Densidade: %.2f hab/km2\n", c->densidade);
    printf("PIB per capita: %.2f R$\n\n", c->pib_pc);
}

const char* nome_atributo(int op) {
    switch (op) {
        case 1: return "Populacao";
        case 2: return "Area (km2)";
        case 3: return "PIB (bilhoes)";
        case 4: return "Pontos turisticos";
        case 5: return "Densidade (MENOR vence)";
        case 6: return "PIB per capita (R$)";
        default: return "Atributo invalido";
    }
}

double valor_attr(const Carta *c, int op) {
    switch (op) {
        case 1: return (double)c->populacao;
        case 2: return (double)c->area;
        case 3: return (double)c->pib;      // ainda em bilhões
        case 4: return (double)c->pontos;
        case 5: return (double)c->densidade;
        case 6: return (double)c->pib_pc;   // em R$
        default: return 0.0;
    }
}

/* 1: C1 vence | -1: C2 vence | 0: empate
   regra especial: densidade => MENOR vence */
int compara_um_atributo(const Carta *c1, const Carta *c2, int op) {
    const double EPS = 1e-6;
    double v1 = valor_attr(c1, op);
    double v2 = valor_attr(c2, op);
    if (fabs(v1 - v2) < EPS) return 0;
    int menorVence = (op == 5);
    return menorVence ? (v1 < v2 ? 1 : -1)
                      : (v1 > v2 ? 1 : -1);
}

void print_valor(const Carta *c, int op) {
    if (op == 1) printf("%lu", c->populacao);
    else         printf("%.2f", (float)valor_attr(c, op));
}

/* ---------------------------- Programa principal ---------------------------- */
int main(void) {
    Carta c1, c2;

    printf("=== SUPER TRUNFO - NIVEL MESTRE ===\n\n");
    ler_carta(&c1, 1);
    ler_carta(&c2, 2);

    printf("=== CARTAS CADASTRADAS ===\n\n");
    mostrar_carta(&c1, 1);
    mostrar_carta(&c2, 2);

    while (1) {
        int a, b;

        puts("Menu de comparacao (escolha DOIS atributos diferentes)");
        puts("1 - Populacao (maior vence)");
        puts("2 - Area (maior vence)");
        puts("3 - PIB em bilhoes (maior vence)");
        puts("4 - Pontos turisticos (maior vence)");
        puts("5 - Densidade (MENOR vence)");
        puts("6 - PIB per capita (maior vence)");
        puts("0 - Sair");

        printf("Primeiro atributo: ");
        if (scanf(" %d", &a) != 1 || a == 0) break;
        if (a < 1 || a > 6) { puts("Opcao invalida.\n"); continue; }

        /* --- menu 2 DINAMICO (sem a opcao escolhida) --- */
        puts("\nSegundo atributo (opcao ja escolhida removida):");
        for (int i = 1; i <= 6; ++i) {
            if (i == a) continue;
            printf("%d - %s\n", i, nome_atributo(i));
        }
        puts("0 - Cancelar/Voltar");

        printf("Segundo atributo: ");
        if (scanf(" %d", &b) != 1 || b == 0) { puts("Cancelado.\n"); continue; }
        if (b < 1 || b > 6 || b == a) { puts("Opcao invalida (ou repetida).\n"); continue; }
        puts("");

        /* --- Comparacoes individuais --- */
        int r1 = compara_um_atributo(&c1, &c2, a);
        int r2 = compara_um_atributo(&c1, &c2, b);

        printf("Comparacao de DOIS atributos:\n");
        printf("Atributo 1: %s\n", nome_atributo(a));
        printf("  Carta 1 (%s): ", c1.cidade); print_valor(&c1, a);
        printf("\n  Carta 2 (%s): ", c2.cidade); print_valor(&c2, a); puts("");
        printf("  Resultado A1: %s\n",
               r1==0 ? "Empate" : (r1==1 ? "Carta 1 venceu" : "Carta 2 venceu"));

        printf("\nAtributo 2: %s\n", nome_atributo(b));
        printf("  Carta 1 (%s): ", c1.cidade); print_valor(&c1, b);
        printf("\n  Carta 2 (%s): ", c2.cidade); print_valor(&c2, b); puts("");
        printf("  Resultado A2: %s\n",
               r2==0 ? "Empate" : (r2==1 ? "Carta 1 venceu" : "Carta 2 venceu"));

        /* --- SOMA dos atributos (requisito do enunciado) --- */
        double somaC1 = valor_attr(&c1, a) + valor_attr(&c1, b);
        double somaC2 = valor_attr(&c2, a) + valor_attr(&c2, b);

        printf("\nSoma dos atributos:\n");
        printf("  Carta 1: %.2f\n", (float)somaC1);
        printf("  Carta 2: %.2f\n", (float)somaC2);

        int vencedorSoma = (fabs(somaC1 - somaC2) < 1e-6) ? 0 : (somaC1 > somaC2 ? 1 : -1);

        printf("\nPlacar por atributo: Carta 1 = %d | Carta 2 = %d\n",
               (r1==1) + (r2==1), (r1==-1) + (r2==-1));

        if (vencedorSoma == 0) {
            printf("Resultado FINAL (pela soma): EMPATE!\n\n");
        } else {
            printf("Resultado FINAL (pela soma): %s venceu!\n\n",
                   vencedorSoma==1 ? "Carta 1" : "Carta 2");
        }
    }

    puts("\nEncerrado. Obrigado por jogar!");
    return 0;
}
