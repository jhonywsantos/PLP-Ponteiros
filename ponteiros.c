/**
 * Trabalho sobre Ponteiros em C
 * 
 * Este programa demonstra os conceitos fundamentais de ponteiros:
 * - Declaração e uso básico
 * - Aritmética de ponteiros
 * - Alocação dinâmica de memória
 * - Passagem por referência
 * - Ponteiros para ponteiros
 * - Ponteiros para funções
 * - Armadilhas comuns
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
    
    // 3. char s[] vs const char *
    printf("3. CHAR S[] VS CONST CHAR *\n");
    demonstrar_char_array_vs_char_pointer();
    printf("\n");
    
    // 4. Função swap com ponteiros
    printf("4. FUNÇÃO SWAP COM PONTEIROS\n");
    int x = 10, y = 20;
    printf("Antes do swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("Depois do swap: x = %d, y = %d\n", x, y);
    printf("\n");
    
    // 5. Alocação dinâmica de matriz
    printf("5. ALOCAÇÃO DINÂMICA DE MATRIZ\n");
    int linhas = 3, colunas = 4;
    int **matriz = alocar_matriz(linhas, colunas);
    
    // Preencher matriz com valores
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = i * colunas + j + 1;
        }
    }
    
    // Imprimir matriz
    printf("Matriz alocada dinamicamente:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%2d ", matriz[i][j]);
        }
        printf("\n");
    }
    
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
 * Demonstra o uso dos operadores & (address-of) e * (dereference)
 */
void demonstrar_operadores_ponteiro() {
    int var = 42;
    int *ptr = &var; // ptr armazena o endereço de var
    
    printf("Valor de var: %d\n", var);
    printf("Endereço de var: %p\n", (void*)&var);
    printf("Valor de ptr (endereço armazenado): %p\n", (void*)ptr);
    printf("Valor apontado por ptr (*ptr): %d\n", *ptr);
    
    // Modificando o valor através do ponteiro
    *ptr = 100;
    printf("Após *ptr = 100, valor de var: %d\n", var);
}

/**
 * Demonstra a relação entre arrays e ponteiros
 */
void demonstrar_arrays_ponteiros() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr; // ptr aponta para o primeiro elemento do array
    
    printf("Array original: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Acesso através de aritmética de ponteiros
    printf("Acesso via aritmética de ponteiros:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d (endereço: %p)\n", 
               i, *(ptr + i), (void*)(ptr + i));
    }
    
    // Diferença entre arr e &arr
    printf("arr = %p (endereço do primeiro elemento)\n", (void*)arr);
    printf("&arr = %p (endereço do array)\n", (void*)&arr);
    printf("&arr[0] = %p (endereço do primeiro elemento)\n", (void*)&arr[0]);
}

/**
 * Demonstra a diferença entre char s[] e const char *
 */
void demonstrar_char_array_vs_char_pointer() {
    // char s[] - array de caracteres (modificável)
    char s1[] = "Hello";
    s1[0] = 'h'; // Permitido - modifica o array
    printf("s1 (array): %s\n", s1);
    
    // const char * - ponteiro para string literal (não modificável)
    const char *s2 = "World";
    // s2[0] = 'w'; // ERRO: tentativa de modificar string literal
    printf("s2 (ponteiro): %s\n", s2);
    
    // Ponteiro pode apontar para outra string
    s2 = "Mundo";
    printf("s2 após reassinal: %s\n", s2);
    
    // Array não pode ser reassinalado
    // s1 = "Nova string"; // ERRO: array não pode ser reassinalado
}

/**
 * Função swap que troca valores usando ponteiros
 * Demonstra passagem por referência
 */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Aloca dinamicamente uma matriz usando ponteiro para ponteiro (T**)
 * Demonstra alocação dinâmica e ponteiros para ponteiros
 */
int** alocar_matriz(int linhas, int colunas) {
    // Aloca array de ponteiros (linhas)
    int **matriz = (int**)malloc(linhas * sizeof(int*));
    if (matriz == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    
    // Para cada linha, aloca array de inteiros (colunas)
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
    }
    
    return matriz;
}

/**
 * Libera memória alocada para uma matriz
 * Demonstra boa prática de liberação de memória
 */
void liberar_matriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]); // Libera cada linha
    }
    free(matriz); // Libera array de ponteiros
}

/**
 * Função de comparação para qsort
 */
int comparar_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Demonstra uso de ponteiro para função com qsort
 */
void demonstrar_ponteiro_funcao() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array antes da ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // qsort recebe ponteiro para função de comparação
    qsort(arr, n, sizeof(int), comparar_int);
    
    printf("Array após a ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
 * Demonstra armadilhas comuns com ponteiros
 * ATENÇÃO: Estas são demonstrações de erros - não execute em produção!
 */
void demonstrar_armadilhas() {
    printf("=== ARMADILHAS COMUNS ===\n");
    
    // 1. Ponteiro selvagem (wild pointer)
    printf("1. Ponteiro Selvagem:\n");
    int *wild_ptr; // Não inicializado - comportamento indefinido
    // *wild_ptr = 5; // PERIGO: pode causar segmentation fault
    
    // 2. Ponteiro pendurado (dangling pointer)
    printf("2. Ponteiro Pendurado:\n");
    int *dangling_ptr = (int*)malloc(sizeof(int));
    *dangling_ptr = 42;
    free(dangling_ptr); // Memória liberada
    // *dangling_ptr = 100; // PERIGO: acesso a memória já liberada
    
    // 3. Double free
    printf("3. Double Free:\n");
    int *double_free_ptr = (int*)malloc(sizeof(int));
    free(double_free_ptr);
    // free(double_free_ptr); // PERIGO: liberar memória já liberada
    
    // 4. Vazamento de memória
    printf("4. Vazamento de Memória:\n");
    int *leak_ptr = (int*)malloc(sizeof(int));
    *leak_ptr = 42;
    // Esquecer de chamar free(leak_ptr) causa vazamento de memória
    
    printf("Estas armadilhas foram comentadas para evitar crashes!\n");
}