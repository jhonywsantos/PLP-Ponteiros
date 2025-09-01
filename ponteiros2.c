/**
 * Trabalho sobre Ponteiros em C
 * 
 * Este programa demonstra conceitos fundamentais de ponteiros:
 * - Operadores & (address-of) e * (dereference)
 * - Relação entre arrays e ponteiros
 * - Diferença entre char s[] e const char *
 * - Função swap usando ponteiros (passagem por referência)
 * - Alocação dinâmica de memória para matrizes
 * - Ponteiros para funções (ex.: qsort)
 * - Armadilhas comuns com ponteiros
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Protótipos das funções
void demonstrar_operadores_ponteiro();
void demonstrar_arrays_ponteiros();
void demonstrar_char_array_vs_char_pointer();
void swap(int *a, int *b);
int** alocar_matriz(int linhas, int colunas);
void liberar_matriz(int **matriz, int linhas);
int comparar_int(const void *a, const void *b);
void demonstrar_ponteiro_funcao();
void demonstrar_armadilhas();

int main() {
    printf("=== TRABALHO SOBRE PONTEIROS EM C ===\n\n");
    
    // 1. Operadores & e *
    printf("1. OPERADORES & E *\n");
    demonstrar_operadores_ponteiro();
    printf("\n");
    
    // 2. Arrays e ponteiros
    printf("2. ARRAYS E PONTEIROS\n");
    demonstrar_arrays_ponteiros();
    printf("\n");
    
    // 3. Diferença entre char s[] e const char *
    printf("3. CHAR S[] VS CONST CHAR *\n");
    demonstrar_char_array_vs_char_pointer();
    printf("\n");
    
    // 4. Função swap usando ponteiros
    printf("4. FUNÇÃO SWAP COM PONTEIROS\n");
    int x = 10, y = 20;
    printf("Antes do swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);  // Passando o endereço das variáveis
    printf("Depois do swap: x = %d, y = %d\n", x, y);
    printf("\n");
    
    // 5. Alocação dinâmica de matriz
    printf("5. ALOCAÇÃO DINÂMICA DE MATRIZ\n");
    int linhas = 3, colunas = 4;
    int **matriz = alocar_matriz(linhas, colunas);
    
    // Preencher a matriz com valores sequenciais
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = i * colunas + j + 1;
        }
    }
    
    // Imprimir a matriz
    printf("Matriz alocada dinamicamente:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    
    // Liberar a memória alocada
    liberar_matriz(matriz, linhas);
    printf("\n");
    
    // 6. Ponteiro para função
    printf("6. PONTEIRO PARA FUNÇÃO\n");
    demonstrar_ponteiro_funcao();
    printf("\n");
    
    // 7. Armadilhas comuns
    printf("7. ARMADILHAS COMUNS\n");
    demonstrar_armadilhas();
    printf("\n");
    
    printf("=== FIM DO PROGRAMA ===\n");
    return 0;
}

/**
 * Demonstra o uso dos operadores & (endereçamento) e * (desreferência)
 */
void demonstrar_operadores_ponteiro() {
    int var = 42;
    int *ptr = &var; // ptr guarda o endereço de var
    
    printf("Valor de var: %d\n", var);
    printf("Endereço de var: %p\n", (void*)&var);
    printf("Valor de ptr (endereço armazenado): %p\n", (void*)ptr);
    printf("Valor apontado por ptr (*ptr): %d\n", *ptr);
    
    // Modificando o valor através do ponteiro
    *ptr = 100;
    printf("Após *ptr = 100, valor de var: %d\n", var);
}

/**
 * Mostra como arrays e ponteiros estão relacionados
 */

void demonstrar_arrays_ponteiros() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr; // Aponta para o primeiro elemento do array
    
    printf("Array original: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Acesso usando aritmética de ponteiros
    printf("Acesso via aritmética de ponteiros:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d (endereço: %p)\n", i, *(ptr + i), (void*)(ptr + i));
    }
    
    // Diferença entre arr e &arr
    printf("arr = %p (endereço do primeiro elemento)\n", (void*)arr);
    printf("&arr = %p (endereço do array)\n", (void*)&arr);
    printf("&arr[0] = %p (endereço do primeiro elemento)\n", (void*)&arr[0]);
}

/**
 * Demonstra a diferença entre array de char e ponteiro para string literal
 */

void demonstrar_char_array_vs_char_pointer() {
    char s1[] = "Hello"; // Array de char: pode ser modificado
    s1[0] = 'h';
    printf("s1 (array): %s\n", s1);
    
    const char *s2 = "World"; // Ponteiro para string literal: não modifique!
    printf("s2 (ponteiro): %s\n", s2);
    
    // Ponteiro pode apontar para outra string
    s2 = "Mundo";
    printf("s2 após reassinalação: %s\n", s2);
    
    // Array não pode ser reassinalado
    // s1 = "Nova string"; // ERRO
}

/**
 * Troca valores de duas variáveis usando ponteiros
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Aloca uma matriz dinamicamente (ponteiro para ponteiro)
 */

int** alocar_matriz(int linhas, int colunas) {
    int **matriz = (int**)malloc(linhas * sizeof(int*));
    if (!matriz) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
        if (!matriz[i]) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
    }
    
    return matriz;
}

/**
 * Libera a memória alocada para uma matriz
 */

void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

/**
 * Função de comparação usada pelo qsort
 */

int comparar_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Demonstra o uso de ponteiros para funções com qsort
 */

void demonstrar_ponteiro_funcao() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array antes da ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    qsort(arr, n, sizeof(int), comparar_int); // Ponteiro para função
    
    printf("Array após a ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Mostra armadilhas comuns com ponteiros (comentadas para evitar crashes)
 */

void demonstrar_armadilhas() {
    printf("=== ARMADILHAS COMUNS ===\n");
    
    // 1. Ponteiro selvagem: não inicializado
    printf("1. Ponteiro Selvagem:\n");
    int *wild_ptr;
    // *wild_ptr = 5; // PERIGO
    
    // 2. Ponteiro pendurado (dangling pointer)
    printf("2. Ponteiro Pendurado:\n");
    int *dangling_ptr = (int*)malloc(sizeof(int));
    *dangling_ptr = 42;
    free(dangling_ptr);
    // *dangling_ptr = 100; // PERIGO
    
    // 3. Double free
    printf("3. Double Free:\n");
    int *double_free_ptr = (int*)malloc(sizeof(int));
    free(double_free_ptr);
    // free(double_free_ptr); // PERIGO
    
    // 4. Vazamento de memória
    printf("4. Vazamento de Memória:\n");
    int *leak_ptr = (int*)malloc(sizeof(int));
    *leak_ptr = 42;
    // free(leak_ptr) não chamado -> vazamento
    
    printf("Estas armadilhas foram comentadas para evitar crashes!\n");
}
