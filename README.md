# PLP-Ponteiros

# TRABALHO SOBRE PONTEIROS EM C: IMPLEMENTAÇÃO, EXPLICAÇÃO E ANÁLISE CRÍTICA

## Descrição
Este trabalho está sendo desenvolvido por discentes do curso de Ciência da Computação, na Universidade Federal de Alagoas (UFAL) — Campus Arapiraca, para a obtenção da nota na disciplina de Paradigmas de Linguagem de Programação (PLP) na Turma 2025.1.  Este artigo apresenta uma análise detalhada e um guia de implementação sobre ponteiros na linguagem C, cobrindo operadores básicos, aritmética de ponteiros, arrays, comparação entre char[] e const char*, passagem por referência, alocação dinâmica de matrizes (int **), ponteiros para funções e armadilhas comuns (wild pointers, dangling pointers, double free, memory leaks). A partir do código-fonte fornecido, descreve-se o fluxo de execução, a semântica de cada função, a representação de memória (stack/heap), o comportamento esperado em tempo de execução e as possíveis falhas. Propõem-se melhorias (checagens de erro, design de API segura, padrões de liberação, uso de sizeof com expressões, atribuição de NULL após free) e estratégias de verificação (sanitizers, análise estática). Discute-se também custos iniciais de adoção (tempo de formação, instrumentação) e implicações éticas para software crítico. O documento destina-se a estudantes e profissionais que buscam compreensão prática e segura do uso de ponteiros em C.

Autores: [¹Igor Mariano de Alencar e Silva](https://github.com/Southcruz), [²Jhony Wictor do Nascimento Santos](https://github.com/jhonywsantos), [³Karleandro Santos da Silva](https://github.com/karleandrosilva), [⁴Lucas Rosendo de Farias](https://github.com/LucaRosendo), [⁵Luís Gustavo Correia de Oliveira](https://github.com/LuisGustavoCo), [⁶Washington Medeiros Mazzone Gaia](https://github.com/washingmg)

---

## Conceitos Abordados

### Operadores Fundamentais
- **Operador `&`**: Obtém o endereço de memória de uma variável  
- **Operador `*`**: Acessa o valor armazenado no endereço apontado por um ponteiro  
- **Modificação de valores através de dereferenciação de ponteiros**

### Arrays e Ponteiros
- Relação intrínseca entre arrays e aritmética de ponteiros  
- Diferença entre o endereço do primeiro elemento e o endereço do array  
- Acesso a elementos de array através de aritmética de ponteiros  

### Strings: Array vs Ponteiro
- `char s[]`: Array de caracteres modificável alocado na stack  
- `const char *`: Ponteiro para string literal em memória read-only  
- Restrições de modificação e reassinalamento para cada abordagem  

### Passagem por Referência
- Implementação da função `swap` que demonstra passagem de parâmetros por referência  
- Manipulação de valores originais através de seus endereços de memória  

### Alocação Dinâmica de Memória

#### Matrizes Dinâmicas
- Alocação de matrizes bidimensionais usando ponteiro para ponteiro (`int**`)  
- Alocação em duas etapas: array de ponteiros e arrays de inteiros  
- Liberação correta de memória na ordem inversa da alocação  

#### Gerenciamento de Memória
- Verificação de sucesso na alocação de memória  
- Liberação completa de todos os recursos alocados  
- Prevenção de vazamentos de memória  

### Ponteiros para Funções
- Declaração e uso de ponteiros para funções  
- Aplicação prática com a função `qsort` da biblioteca padrão  
- Implementação de função de comparação para ordenação  

---

## Boas Práticas e Armadilhas Comuns

### Práticas Recomendadas
- Inicialização de ponteiros antes do uso  
- Verificação de retorno de funções de alocação  
- Liberação de memória alocada dinamicamente  
- Uso de `const` para proteger dados não-modificáveis  

### Armadilhas Demonstradas
- **Ponteiros selvagens**: Uso de ponteiros não inicializados  
- **Ponteiros pendurados**: Acesso a memória já liberada  
- **Double free**: Tentativa de liberar memória já liberada  
- **Vazamentos de memória**: Falha em liberar memória alocada  

---

## Compilação e Execução
```bash
gcc -o ponteiros ponteiros.c
./ponteiros
```

### Estrutura do Programa

O programa segue uma sequência didática, apresentando cada conceito de forma incremental com exemplos práticos e comentários explicativos.
A saída do programa mostra claramente o comportamento de cada operação com ponteiros.

---

### Exemplo de Saída Esperada
```bash
=== TRABALHO SOBRE PONTEIROS EM C ===

1. OPERADORES & E *
Valor de var: 42
Endereço de var: 0x7ffd...
Valor de ptr (endereço armazenado): 0x7ffd...
Valor apontado por ptr (*ptr): 42
Após *ptr = 100, valor de var: 100

2. ARRAYS E PONTEIROS
Array original: 10 20 30 40 50 
Acesso via aritmética de ponteiros:
*(ptr + 0) = 10 (endereço: 0x7ffd...)
*(ptr + 1) = 20 (endereço: 0x7ffd...)
...

3. CHAR S[] VS CONST CHAR *
s1 (array): hello
s2 (ponteiro): World
s2 após reassinal: Mundo

4. FUNÇÃO SWAP COM PONTEIROS
Antes do swap: x = 10, y = 20
Depois do swap: x = 20, y = 10

5. ALOCAÇÃO DINÂMICA DE MATRIZ
Matriz alocada dinamicamente:
 1,  2,  3,  4, 
 5,  6,  7,  8, 
 9, 10, 11, 12, 

6. PONTEIRO PARA FUNÇÃO
Array antes da ordenação: 64 34 25 12 22 11 90 
Array após a ordenação: 11 12 22 25 34 64 90 

7. ARMADILHAS COMUNS
=== ARMADILHAS COMUNS ===
1. Ponteiro Selvagem:
2. Ponteiro Pendurado:
3. Double Free:
4. Vazamento de Memória:
Estas armadilhas foram comentadas para evitar crashes!

=== FIM DO PROGRAMA ===
```
---
### Diagrama de Memória

## Modelo de Memória em C
Esta imagem ilustra a arquitetura de memória lógica que um sistema operacional normalmente aloca para um programa em C quando ele é executado. Entender essa separação é crucial para saber onde suas variáveis são armazenadas e como gerenciá-las.
![Diagrama de Memória](https://github.com/user-attachments/assets/5e1a601b-0f8c-4f26-8f34-2f6e9d28548b)

#### Fundamentos e Conceitos:

O modelo é dividido em quatro segmentos principais, organizados de endereços de memória mais baixos para mais altos:

1. Código (Texto)
    - Conceito: Esta é a área de memória onde as instruções do programa (o código de máquina compilado) são armazenadas.
    - Fundamento: É uma área somente leitura (*read-only) para impedir que o programa modifique acidentalmente suas próprias instruções durante a execução. O README.md menciona que um const char * aponta para uma string literal que geralmente fica em memória read-only, sendo um exemplo de dado protegido contra escrita.

2. Dados
    - Conceito: Armazena variáveis globais e estáticas. Essas variáveis são inicializadas antes de o programa começar a executar e sua vida útil dura por toda a execução do programa.
    - Fundamento: Diferente da Stack e da Heap, o tamanho deste segmento é fixo e determinado em tempo de compilação.

3. Heap
    - Conceito: É uma região de memória usada para alocação dinâmica, controlada explicitamente pelo programador através de funções como malloc e calloc. O README.md aborda isso diretamente na seção de "Alocação Dinâmica de Memória", como na criação de matrizes com int**.
    - Fundamento: A Heap "cresce para cima", em direção a endereços de memória mais altos. O programador é totalmente responsável por gerenciar essa memória: alocar quando necessário e, crucialmente, liberar (free) quando o uso terminar. Falhas nesse gerenciamento causam as "armadilhas" citadas no README.md, como *vazamentos de memória* (falha em liberar) e *double free* (tentativa de liberar duas vezes).

4. Stack (Pilha)
   - Conceito: Armazena variáveis locais de funções, parâmetros de funções e informações de controle para chamadas de função. Por exemplo, o char s[] do README.md é um array alocado na stack.
   - Fundamento: A Stack é gerenciada automaticamente pelo compilador. A memória é alocada quando uma função é chamada e liberada quando a função retorna. Ela "cresce para baixo", em direção a endereços de memória mais baixos. Se uma função chama a si mesma recursivamente muitas vezes ou declara variáveis locais muito grandes, pode ocorrer um "estouro de pilha" (*stack overflow). O uso de *ponteiros pendurados* (dangling pointers) pode ocorrer quando um ponteiro tenta acessar um endereço na stack de uma função que já retornou e cuja memória já foi liberada.

 
---
### Aritmética de Ponteiros
![Diagrama de Aritmética de Ponteiros](https://github.com/user-attachments/assets/6070e4c1-ec3b-4e0c-8aab-49b9561d56cc)

