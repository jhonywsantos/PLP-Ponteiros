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
 *
 * Apêndice A: Código completo com comentários explicativos.
 */

#include <stdio.h>   // printf, etc.
#include <stdlib.h>  // malloc, free, qsort, exit
#include <string.h>  // (incluído para possíveis manipulações de string)

// Protótipos das funções demonstrativas.
// Declarações permitem organizar o código abaixo do main.
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
    // Cabeçalho do programa
    printf("=== TRABALHO SOBRE PONTEIROS EM C ===\n\n");

    // 1) Demonstração dos operadores & e *
    printf("1. OPERADORES & E *\n");
    demonstrar_operadores_ponteiro(); // chama função que ilustra address-of e dereference
    printf("\n");

    // 2) Arrays e relação com ponteiros
    printf("2. ARRAYS E PONTEIROS\n");
    demonstrar_arrays_ponteiros();
    printf("\n");

    // 3) Diferença entre char s[] (array) e const char * (literal)
    printf("3. CHAR S[] VS CONST CHAR *\n");
    demonstrar_char_array_vs_char_pointer();
    printf("\n");

    // 4) Função swap usando passagem por referência (ponteiros)
    printf("4. FUNÇÃO SWAP COM PONTEIROS\n");
    int x = 10, y = 20; // variáveis locais no stack
    printf("Antes do swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);               // passa endereços de x e y para swap
    printf("Depois do swap: x = %d, y = %d\n", x, y);
    printf("\n");

    // 5) Alocação dinâmica de matriz (int **)
    printf("5. ALOCAÇÃO DINÂMICA DE MATRIZ\n");
    int linhas = 3, colunas = 4;
    int **matriz = alocar_matriz(linhas, colunas); // matriz alocada no heap

    // Preencher matriz com valores sequenciais
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = i * colunas + j + 1; // atribui 1..(linhas*colunas)
        }
    }

    // Imprimir matriz
    printf("Matriz alocada dinamicamente:\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%2d ", matriz[i][j]); // imprime elemento [i][j]
        }
        printf("\n");
    }

    liberar_matriz(matriz, linhas); // libera memória alocada no heap
    printf("\n");

    // 6) Ponteiro para função com qsort
    printf("6. PONTEIRO PARA FUNÇÃO\n");
    demonstrar_ponteiro_funcao();
    printf("\n");

    // 7) Demonstração (comentada) de armadilhas com ponteiros
    printf("7. ARMADILHAS COMUNS\n");
    demonstrar_armadilhas();
    printf("\n");

    printf("=== FIM DO PROGRAMA ===\n");
    return 0;
}

/* -------------------------------------------------------------------------
 *  Função: demonstrar_operadores_ponteiro
 *  Objetivo: mostrar uso de & (address-of) e * (dereference)
 * ------------------------------------------------------------------------- */
void demonstrar_operadores_ponteiro() {
    int var = 42;            // 'var' é alocada na stack com valor 42
    int *ptr = &var;         // 'ptr' recebe o endereço de 'var' (pointer to int)

    // Imprime o valor atual de var
    printf("Valor de var: %d\n", var);

    // Imprime endereço de var — casting para (void*) é portável em printf("%p")
    printf("Endereço de var: %p\n", (void*)&var);

    // Imprime o valor armazenado em ptr (deverá ser igual ao endereço de var)
    printf("Valor de ptr (endereço armazenado): %p\n", (void*)ptr);

    // Imprime o valor apontado por ptr (desreferência)
    printf("Valor apontado por ptr (*ptr): %d\n", *ptr);

    // Modificando o valor através do ponteiro: altera var indiretamente
    *ptr = 100; // escreve na posição apontada por ptr (ou seja, na variável var)
    printf("Após *ptr = 100, valor de var: %d\n", var);
}

/* -------------------------------------------------------------------------
 *  Função: demonstrar_arrays_ponteiros
 *  Objetivo: explicar relação entre arrays e ponteiros e aritmética de ponteiros
 * ------------------------------------------------------------------------- */
void demonstrar_arrays_ponteiros() {
    int arr[5] = {10, 20, 30, 40, 50}; // array de 5 ints na stack
    int ptr = arr; // em expressões, 'arr' decai para &arr[0] (tipo int)

    // Imprime o array usando indexação tradicional
    printf("Array original: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Acesso via aritmética de ponteiros: *(ptr + i) == arr[i]
    printf("Acesso via aritmética de ponteiros:\n");
    for (int i = 0; i < 5; i++) {
        // (void*)(ptr + i) mostra o endereço do elemento i
        printf("*(ptr + %d) = %d (endereço: %p)\n",
               i, (ptr + i), (void)(ptr + i));
    }

    // Diferença semântica entre arr, &arr e &arr[0]
    printf("arr = %p (endereço do primeiro elemento)\n", (void*)arr);
    printf("&arr = %p (endereço do array inteiro)\n", (void*)&arr);
    printf("&arr[0] = %p (endereço do primeiro elemento)\n", (void*)&arr[0]);
}

/* -------------------------------------------------------------------------
 *  Função: demonstrar_char_array_vs_char_pointer
 *  Objetivo: demonstrar diferença entre string como array mutável e literal
 * ------------------------------------------------------------------------- */
void demonstrar_char_array_vs_char_pointer() {
    // char s1[] é um array local (modifiable). A cópia do literal "Hello" é colocada no stack.
    char s1[] = "Hello";
    s1[0] = 'h'; // permitido: modifica o array s1
    printf("s1 (array): %s\n", s1); // saída: "hello"

    // const char *s2 aponta para um literal no segmento de texto (geralmente read-only)
    const char *s2 = "World";
    // s2[0] = 'w'; // PROIBIDO: tentativa de modificar um literal causaria undefined behavior
    printf("s2 (ponteiro): %s\n", s2);

    // Ponteiro pode ser reatribuído para outro literal (s2 apontando para "Mundo")
    s2 = "Mundo";
    printf("s2 após reassinal: %s\n", s2);

    // Observação: arrays não podem ser reassinalados (s1 = "Nova string" é inválido).
}

/* -------------------------------------------------------------------------
 *  Função: swap
 *  Objetivo: trocar os valores entre duas variáveis por passagem de ponteiros
 * ------------------------------------------------------------------------- */
void swap(int *a, int *b) {
    // 'a' e 'b' são ponteiros válidos esperados (não devem ser NULL)
    int temp = *a; // lê valor apontado por a
    *a = *b;       // escreve valor apontado por b na posição apontada por a
    *b = temp;     // escreve temp na posição apontada por b
    // Observação: função altera diretamente os locais referenciados em quem chamou.
}

/* -------------------------------------------------------------------------
 *  Função: alocar_matriz
 *  Objetivo: alocar dinamicamente uma matriz (int **) — linhas x colunas
 *  Retorna: ponteiro para vetor de ponteiros (cada item aponta para int[])
 * ------------------------------------------------------------------------- */
int** alocar_matriz(int linhas, int colunas) {
    // Aloca vetor de 'linhas' ponteiros para int.
    // (int**)cast não é necessário em C, mas está presente no código original.
    int *matriz = (int)malloc(linhas * sizeof(int));
    if (matriz == NULL) { // checagem de erro fundamental
        printf("Erro na alocação de memória!\n");
        exit(1); // em produção, retornar código de erro seria preferível
    }

    // Para cada linha, aloca um array de 'colunas' inteiros
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
        if (matriz[i] == NULL) {
            // Em caso de falha parcial, liberar já alocado evita leaks.
            printf("Erro na alocação de memória!\n");
            // liberar as linhas já alocadas antes de sair (melhoria prática)
            for (int k = 0; k < i; k++) {
                free(matriz[k]);
            }
            free(matriz);
            exit(1);
        }
    }

    return matriz; // retorna ponteiro para área no heap
}

/* -------------------------------------------------------------------------
 *  Função: liberar_matriz
 *  Objetivo: liberar toda a memória alocada por alocar_matriz
 * ------------------------------------------------------------------------- */
void liberar_matriz(int **matriz, int linhas) {
    // Libera cada linha (cada malloc de colunas)
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]); // libera bloco de colunas
    }
    free(matriz); // libera o vetor de ponteiros
    // Nota: seria prudente, no chamador (main), atribuir matriz = NULL depois.
}

/* -------------------------------------------------------------------------
 *  Função: comparar_int
 *  Objetivo: função de comparação para qsort — converte void* para int*.
 *  Observação: a expressão ( (int)a - (int)b ) pode causar overflow.
 * ------------------------------------------------------------------------- */
int comparar_int(const void *a, const void *b) {
    // Implementação original (simples), mantida:
    return ((int)a - (int)b);
    // Versão mais segura sugerida:
    // int ia = (const int)a;
    // int ib = (const int)b;
    // if (ia < ib) return -1;
    // if (ia > ib) return 1;
    // return 0;
}

/* -------------------------------------------------------------------------
 *  Função: demonstrar_ponteiro_funcao
 *  Objetivo: demonstrar uso de ponteiro para função com a qsort da stdlib.
 * ------------------------------------------------------------------------- */
void demonstrar_ponteiro_funcao() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};          // array local
    int n = sizeof(arr) / sizeof(arr[0]);              // número de elementos

    // Imprime estado inicial
    printf("Array antes da ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Chama qsort: recebe ponteiro para função de comparação (comparar_int)
    qsort(arr, n, sizeof(int), comparar_int);

    // Imprime estado final (ordenado)
    printf("Array após a ordenação: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/* -------------------------------------------------------------------------
 *  Função: demonstrar_armadilhas
 *  Objetivo: ilustrar perigos com ponteiros (comentados para não crashar)
 * ------------------------------------------------------------------------- */
void demonstrar_armadilhas() {
    printf("=== ARMADILHAS COMUNS ===\n");

    // 1. Ponteiro selvagem (wild pointer) — não inicializado
    printf("1. Ponteiro Selvagem:\n");
    int *wild_ptr; // variável não inicializada -> contém lixo -> UB se dereferenciada
    // *wild_ptr = 5; // PERIGO: acesso indefinido (não executar)

    // 2. Ponteiro pendurado (dangling pointer)
    printf("2. Ponteiro Pendurado:\n");
    int dangling_ptr = (int)malloc(sizeof(int)); // aloca no heap
    *dangling_ptr = 42;                            // escreve valor
    free(dangling_ptr);                            // libera memória
    // *dangling_ptr = 100; // PERIGO: acessar após free é UB

    // 3. Double free
    printf("3. Double Free:\n");
    int double_free_ptr = (int)malloc(sizeof(int));
    free(double_free_ptr);
    // free(double_free_ptr); // PERIGO: double free causa comportamento indefinido

    // 4. Vazamento de memória (memory leak)
    printf("4. Vazamento de Memória:\n");
    int leak_ptr = (int)malloc(sizeof(int));
    *leak_ptr = 42;
    // Se não houver free(leak_ptr) ocorrerá vazamento até o fim do processo

    printf("Estas armadilhas foram comentadas para evitar crashes!\n");
}
