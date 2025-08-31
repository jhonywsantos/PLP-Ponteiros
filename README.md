# PLP-Ponteiros

# Trabalho sobre Ponteiros em C

## Descrição
Este programa demonstra os conceitos fundamentais de ponteiros na linguagem C através de exemplos práticos e implementações funcionais. O código serve como material educativo para compreender o funcionamento, aplicações e cuidados necessários no uso de ponteiros.

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