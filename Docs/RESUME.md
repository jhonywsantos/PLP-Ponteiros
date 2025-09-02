# **TRABALHO SOBRE PONTEIROS EM C: IMPLEMENTAÇÃO, EXPLICAÇÃO E ANÁLISE CRÍTICA**

 ¹Igor Mariano de Alencar e Silva, ²Jhony Wictor do Nascimento Santos, ³Karleandro Santos da Silva, ⁴Lucas Rosendo de Farias,   
⁵Luís Gustavo Correia de Oliveira, ⁶Washington Medeiros Mazzone Gaia

**Universidade Federal de Alagoas \- UFAL, Campus Arapiraca — SEDE.**  
**Bacharelado em Ciência da Computação.**

¹⁴⁵⁶Arapiraca — AL — Brasil  
³Girau do Ponciano — AL — Brasil  
²Teotônio Vilela — AL — Brasil

{igor.alencar,[jhony.santos](mailto:jhony.santos@arapiraca.ufal.br),[karleandro.silva,](mailto:karleandro.silva@arapiraca.ufal.br)   
[luis.correia,lucas.farias,washington.gaia}@arapiraca.ufal.br](mailto:karleandro.silva@arapiraca.ufal.br)

***ABSTRACT.** This article presents a detailed analysis and an implementation guide on pointers in the C language, covering basic operators, pointer arithmetic, arrays, comparison between char\[\] and const char\*, pass-by-reference, dynamic allocation of matrices (int \*\*), function pointers, and common pitfalls (wild pointers, dangling pointers, double free, memory leaks). Based on the provided source code, it describes the execution flow, the semantics of each function, memory representation (stack/heap), expected behavior at runtime, and possible failures. Improvements are proposed (error checking, safe API design, release patterns, use of sizeof with expressions, assigning NULL after free) and verification strategies (sanitizers, static analysis) are discussed. Initial adoption costs (training time, instrumentation) and ethical implications for critical software are also addressed. The document is intended for students and professionals seeking a practical and safe understanding of the use of pointers in C.*

***Keywords: pointers; C; dynamic allocation; pass by reference; memory safety.***

***RESUMO.** Este artigo apresenta uma análise detalhada e um guia de implementação sobre ponteiros na linguagem C, cobrindo operadores básicos, aritmética de ponteiros, arrays, comparação entre char\[\] e const char\*, passagem por referência, alocação dinâmica de matrizes (int \*\*), ponteiros para funções e armadilhas comuns (wild pointers, dangling pointers, double free, memory leaks). A partir do código-fonte fornecido, descreve-se o fluxo de execução, a semântica de cada função, a representação de memória (stack/heap), o comportamento esperado em tempo de execução e as possíveis falhas. Propõem-se melhorias (checagens de erro, design de API segura, padrões de liberação, uso de sizeof com expressões, atribuição de NULL após free) e estratégias de verificação (sanitizers, análise estática). Discute-se também custos iniciais de adoção (tempo de formação, instrumentação) e implicações éticas para software crítico. O documento destina-se a estudantes e profissionais que buscam compreensão prática e segura do uso de ponteiros em C.* 

***Palavras-chave: ponteiros; C; alocação dinâmica; passagem por referência; segurança de memória.***

1. ## **Introdução**

Ponteiros são um recurso central em C: permitem manejar endereços de memória, realizar passagem por referência, construir estruturas dinâmicas e criar abstrações de baixo nível. O poder vem acompanhado de responsabilidade: usos incorretos provocam comportamento indefinido, falhas de segurança e perda de disponibilidade. O código-base estudado neste artigo foi concebido didaticamente para cobrir um conjunto amplo de conceitos relacionados a ponteiros, combinando demonstrações práticas, exemplos com saída prevista e comentários sobre armadilhas. O objetivo deste trabalho é documentar e explicar, linha a linha, cada módulo do programa, incluindo sugestões de robustez e práticas de engenharia de software para reduzir risco.

2. ## **Revisão da Literatura**

Kernighan e Ritchie (1988) estabelecem os fundamentos do uso de ponteiros, enquanto Deitel & Deitel (2016) discutem sua aplicação em estruturas e algoritmos. O SEI CERT (2023) descreve vulnerabilidades comuns relacionadas à memória e recomenda práticas de mitigação (inicialização de ponteiros, verificação de alocação, utilização de sanitizers). Estudos pedagógicos indicam que a curva de aprendizado para ponteiros é íngreme, mas necessária para o domínio de programação de sistemas. Ferramentas modernas (AddressSanitizer, valgrind, analisadores estáticos) são amplamente recomendadas na literatura para complementar testes.

3. ## **Metodologias Utilizadas**

Este estudo utiliza um programa em C (modular) que demonstra conceitos de ponteiros. Cada módulo corresponde a uma função que ilustra um tópico: (1) operadores & e \*; (2) arrays e aritmética de ponteiros; (3) strings (char\[\] vs const char\*); (4) passagem por referência (função swap); (5) alocação dinâmica de matrizes (função alocar\_matriz e liberar\_matriz); (6) ponteiros para funções (uso de qsort com comparar\_int); (7) armadilhas comentadas. O programa foi compilado com gcc e as saídas observadas; o código foi analisado em termos de alocação (stack/heap), riscos e melhorias. Recomendações de robustez foram propostas com base nas evidências e nas melhores práticas citadas.

## **3.1 Apêndice do Código**

/\*\*  
 \* Trabalho sobre Ponteiros em C  
 \*   
 \* Este programa demonstra conceitos fundamentais de ponteiros:  
 \* \- Operadores & (address-of) e \* (dereference)  
 \* \- Relação entre arrays e ponteiros  
 \* \- Diferença entre char s\[\] e const char \*  
 \* \- Função swap usando ponteiros (passagem por referência)  
 \* \- Alocação dinâmica de memória para matrizes  
 \* \- Ponteiros para funções (ex.: qsort)  
 \* \- Armadilhas comuns com ponteiros  
 \*/

\#include \<stdio.h\>  
\#include \<stdlib.h\>  
\#include \<string.h\>

// Protótipos das funções  
void demonstrar\_operadores\_ponteiro();  
void demonstrar\_arrays\_ponteiros();  
void demonstrar\_char\_array\_vs\_char\_pointer();  
void swap(int \*a, int \*b);  
int\*\* alocar\_matriz(int linhas, int colunas);  
void liberar\_matriz(int \*\*matriz, int linhas);  
int comparar\_int(const void \*a, const void \*b);  
void demonstrar\_ponteiro\_funcao();  
void demonstrar\_armadilhas();

int main() {  
    printf("=== TRABALHO SOBRE PONTEIROS EM C \===\\n\\n");  
      
    // 1\. Operadores & e \*  
    printf("1. OPERADORES & E \*\\n");  
    demonstrar\_operadores\_ponteiro();  
    printf("\\n");  
      
    // 2\. Arrays e ponteiros  
    printf("2. ARRAYS E PONTEIROS\\n");  
    demonstrar\_arrays\_ponteiros();  
    printf("\\n");  
      
    // 3\. Diferença entre char s\[\] e const char \*  
    printf("3. CHAR S\[\] VS CONST CHAR \*\\n");  
    demonstrar\_char\_array\_vs\_char\_pointer();  
    printf("\\n");  
      
    // 4\. Função swap usando ponteiros  
    printf("4. FUNÇÃO SWAP COM PONTEIROS\\n");  
    int x \= 10, y \= 20;  
    printf("Antes do swap: x \= %d, y \= %d\\n", x, y);  
    swap(\&x, \&y);  // Passando o endereço das variáveis  
    printf("Depois do swap: x \= %d, y \= %d\\n", x, y);  
    printf("\\n");  
      
    // 5\. Alocação dinâmica de matriz  
    printf("5. ALOCAÇÃO DINÂMICA DE MATRIZ\\n");  
    int linhas \= 3, colunas \= 4;  
    int \*\*matriz \= alocar\_matriz(linhas, colunas);  
      
    // Preencher a matriz com valores sequenciais  
    for (int i \= 0; i \< linhas; i++) {  
        for (int j \= 0; j \< colunas; j++) {  
            matriz\[i\]\[j\] \= i \* colunas \+ j \+ 1;  
        }  
    }  
      
    // Imprimir a matriz  
    printf("Matriz alocada dinamicamente:\\n");  
    for (int i \= 0; i \< linhas; i++) {  
        for (int j \= 0; j \< colunas; j++) {  
            printf("%2d ", matriz\[i\]\[j\]);  
        }  
        printf("\\n");  
    }  
      
    // Liberar a memória alocada  
    liberar\_matriz(matriz, linhas);  
    printf("\\n");  
      
    // 6\. Ponteiro para função  
    printf("6. PONTEIRO PARA FUNÇÃO\\n");  
    demonstrar\_ponteiro\_funcao();  
    printf("\\n");  
      
    // 7\. Armadilhas comuns  
    printf("7. ARMADILHAS COMUNS\\n");  
    demonstrar\_armadilhas();  
    printf("\\n");  
      
    printf("=== FIM DO PROGRAMA \===\\n");  
    return 0;  
}

/\*\*  
 \* Demonstra o uso dos operadores & (endereçamento) e \* (desreferência)  
 \*/  
void demonstrar\_operadores\_ponteiro() {  
    int var \= 42;  
    int \*ptr \= \&var; // ptr guarda o endereço de var  
      
    printf("Valor de var: %d\\n", var);  
    printf("Endereço de var: %p\\n", (void\*)\&var);  
    printf("Valor de ptr (endereço armazenado): %p\\n", (void\*)ptr);  
    printf("Valor apontado por ptr (\*ptr): %d\\n", \*ptr);  
      
    // Modificando o valor através do ponteiro  
    \*ptr \= 100;  
    printf("Após \*ptr \= 100, valor de var: %d\\n", var);  
}

/\*\*  
 \* Mostra como arrays e ponteiros estão relacionados  
 \*/

void demonstrar\_arrays\_ponteiros() {  
    int arr\[5\] \= {10, 20, 30, 40, 50};  
    int \*ptr \= arr; // Aponta para o primeiro elemento do array  
      
    printf("Array original: ");  
    for (int i \= 0; i \< 5; i++) {  
        printf("%d ", arr\[i\]);  
    }  
    printf("\\n");  
      
    // Acesso usando aritmética de ponteiros  
    printf("Acesso via aritmética de ponteiros:\\n");  
    for (int i \= 0; i \< 5; i++) {  
        printf("\*(ptr \+ %d) \= %d (endereço: %p)\\n", i, \*(ptr \+ i), (void\*)(ptr \+ i));  
    }  
      
    // Diferença entre arr e \&arr  
    printf("arr \= %p (endereço do primeiro elemento)\\n", (void\*)arr);  
    printf("\&arr \= %p (endereço do array)\\n", (void\*)\&arr);  
    printf("\&arr\[0\] \= %p (endereço do primeiro elemento)\\n", (void\*)\&arr\[0\]);  
}

/\*\*  
 \* Demonstra a diferença entre array de char e ponteiro para string literal  
 \*/

void demonstrar\_char\_array\_vs\_char\_pointer() {  
    char s1\[\] \= "Hello"; // Array de char: pode ser modificado  
    s1\[0\] \= 'h';  
    printf("s1 (array): %s\\n", s1);  
      
    const char \*s2 \= "World"; // Ponteiro para string literal: não modifique\!  
    printf("s2 (ponteiro): %s\\n", s2);  
      
    // Ponteiro pode apontar para outra string  
    s2 \= "Mundo";  
    printf("s2 após reassinalação: %s\\n", s2);  
      
    // Array não pode ser reassinalado  
    // s1 \= "Nova string"; // ERRO  
}

/\*\*  
 \* Troca valores de duas variáveis usando ponteiros  
 \*/

void swap(int \*a, int \*b) {  
    int temp \= \*a;  
    \*a \= \*b;  
    \*b \= temp;  
}

/\*\*  
 \* Aloca uma matriz dinamicamente (ponteiro para ponteiro)  
 \*/

int\*\* alocar\_matriz(int linhas, int colunas) {  
    int \*\*matriz \= (int\*\*)malloc(linhas \* sizeof(int\*));  
    if (\!matriz) {  
        printf("Erro na alocação de memória\!\\n");  
        exit(1);  
    }  
      
    for (int i \= 0; i \< linhas; i++) {  
        matriz\[i\] \= (int\*)malloc(colunas \* sizeof(int));  
        if (\!matriz\[i\]) {  
            printf("Erro na alocação de memória\!\\n");  
            exit(1);  
        }  
    }  
      
    return matriz;  
}

/\*\*  
 \* Libera a memória alocada para uma matriz  
 \*/

void liberar\_matriz(int \*\*matriz, int linhas) {  
    for (int i \= 0; i \< linhas; i++) {  
        free(matriz\[i\]);  
    }  
    free(matriz);  
}

/\*\*  
 \* Função de comparação usada pelo qsort  
 \*/

int comparar\_int(const void \*a, const void \*b) {  
    return (\*(int\*)a \- \*(int\*)b);  
}

/\*\*  
 \* Demonstra o uso de ponteiros para funções com qsort  
 \*/

void demonstrar\_ponteiro\_funcao() {  
    int arr\[\] \= {64, 34, 25, 12, 22, 11, 90};  
    int n \= sizeof(arr) / sizeof(arr\[0\]);  
      
    printf("Array antes da ordenação: ");  
    for (int i \= 0; i \< n; i++) {  
        printf("%d ", arr\[i\]);  
    }  
    printf("\\n");  
      
    qsort(arr, n, sizeof(int), comparar\_int); // Ponteiro para função  
      
    printf("Array após a ordenação: ");  
    for (int i \= 0; i \< n; i++) {  
        printf("%d ", arr\[i\]);  
    }  
    printf("\\n");  
}

/\*\*  
 \* Mostra armadilhas comuns com ponteiros (comentadas para evitar crashes)  
 \*/

void demonstrar\_armadilhas() {  
    printf("=== ARMADILHAS COMUNS \===\\n");  
      
    // 1\. Ponteiro selvagem: não inicializado  
    printf("1. Ponteiro Selvagem:\\n");  
    int \*wild\_ptr;  
    // \*wild\_ptr \= 5; // PERIGO  
      
    // 2\. Ponteiro pendurado (dangling pointer)  
    printf("2. Ponteiro Pendurado:\\n");  
    int \*dangling\_ptr \= (int\*)malloc(sizeof(int));  
    \*dangling\_ptr \= 42;  
    free(dangling\_ptr);  
    // \*dangling\_ptr \= 100; // PERIGO  
      
    // 3\. Double free  
    printf("3. Double Free:\\n");  
    int \*double\_free\_ptr \= (int\*)malloc(sizeof(int));  
    free(double\_free\_ptr);  
    // free(double\_free\_ptr); // PERIGO  
      
    // 4\. Vazamento de memória  
    printf("4. Vazamento de Memória:\\n");  
    int \*leak\_ptr \= (int\*)malloc(sizeof(int));  
    \*leak\_ptr \= 42;  
    // free(leak\_ptr) não chamado \-\> vazamento  
      
    printf("Estas armadilhas foram comentadas para evitar crashes\!\\n");  
}

## **3.2 Funcionamento do Código**
    Esta seção analisa cada módulo do programa, explicando a semântica do código, o gerenciamento de memória e as melhores práticas associadas.

### **3.2.1 Operadores & e \***
    O módulo demonstra que & obtém o endereço de uma variável e * desreferencia um ponteiro. Exemplo: int var = 42; int *ptr = &var; *ptr = 100; — após a operação, var passa a valer 100. A observação prática é que ptr armazena endereço em stack e *ptr acessa conteúdo. É recomendável imprimir endereços com (void*) para portabilidade.

### **3.2.2 Arrays e aritmética de ponteiros**
    Um array int arr[5] ocupa memória contígua na stack. Em contextos expressivos, arr decai para int* (endereço do primeiro elemento), permitindo *(arr + i) como equivalente a arr[i]. A diferença entre arr e &arr (tipo e semântica) é explicada e ilustrada com impressão de endereços.

### **3.2.3 char\[\] vs const char\***
    char s1[] = "Hello"; cria um array mutável; const char *s2 = "World"; aponta para literal de texto tipicamente read-only. Modificar o literal provoca comportamento indefinido. A prática recomendada é declarar literais como const char* e usar malloc/arrays quando for preciso modificar a string.

### **3.2.4 Passagem por referência: função swap**
    A função swap(int *a, int *b) troca valores apontados por a e b sem copiar toda a estrutura. É eficiente e demonstra manipulação direta de memória. Para tornar API robusta em código de produção, checar NULL em parâmetros públicos.

### **3.2.5 Alocação dinâmica de matrizes (int \*\*)**

4. ## **Resultados e Discussão**

5. ## **Considerações Finais**

6. ## **Referências**
