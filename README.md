# PLP-Ponteiros

# Trabalho sobre Ponteiros em C

## Descrição
Este trabalho está sendo desenvolvido por discentes do curso de Ciência da Computação, na Universidade Federal de Alagoas (UFAL) — Campus Arapiraca, para a obtenção da nota na disciplina de Paradigmas de Linguagem de Programação (PLP) na Turma 2025.1.  Este trabalho trata-se de um programa demonstrando os conceitos fundamentais de ponteiros na linguagem C através de exemplos práticos e implementações funcionais. O código serve como material educativo para compreender o funcionamento, aplicações e cuidados necessários no uso de ponteiros.

Autores: [Igor Silva](https://github.com/Southcruz), [Jhony Santos](https://github.com/jhonywsantos), [Karleandro Silva](https://github.com/karleandrosilva), [Lucas Farias](https://github.com/LucaRosendo), [Luis Correia](https://github.com/LuisGustavoCo), [Washington Gaia](https://github.com/washingmg)

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
```bash
+-----------------------+
|       Stack           |  -> Variáveis locais, parâmetros de função
|       (crescimento)   |  -> Alocação automática
+-----------------------+
|          |            |
|          v            |
|                       |
|          ^            |
|          |            |
+-----------------------+
|         Heap          |  -> Memória alocada dinamicamente (malloc, calloc)
|       (crescimento)   |  -> Alocação manual (programador controla)
+-----------------------+
|   Dados Globais/      |  -> Variáveis globais e estáticas
|      Estáticos        |  -> Alocação estática
+-----------------------+
|        Código         |  -> Instruções do programa (text segment)
+-----------------------+
```

---
### Aritmética de Ponteiros
```bash
Array: [10, 20, 30, 40, 50]
Endereços: 1000, 1004, 1008, 1012, 1016

ptr = 1000 (aponta para primeiro elemento)
ptr + 0 = 1000 -> valor 10
ptr + 1 = 1004 -> valor 20  (avança sizeof(int) bytes)
ptr + 2 = 1008 -> valor 30
```
