# 🗺️ Sistema de Gerenciamento de Grafos em C

Aplicação de terminal desenvolvida em **C** para gerenciar conexões entre cidades utilizando estruturas de dados do tipo grafo. O projeto implementa operações de inserção, remoção, consulta e percorrimento de vértices, aplicando conceitos fundamentais de estruturas de dados e algoritmos.

## 📌 Sobre o Projeto

O sistema representa cidades como vértices e as conexões entre elas como arestas de um grafo não direcionado.

A aplicação permite cadastrar cidades, estabelecer ou remover conexões, consultar cidades adjacentes e percorrer a estrutura utilizando os algoritmos **DFS (Depth-First Search)** e **BFS (Breadth-First Search)**.

O projeto foi desenvolvido com foco na aplicação prática de conceitos de Ciência da Computação, incluindo listas encadeadas, ponteiros, gerenciamento de memória e algoritmos de busca.

## 🚀 Funcionalidades

- **Cadastro de cidades:** adiciona novos vértices ao grafo.
- **Criação de conexões:** estabelece relações bidirecionais entre duas cidades.
- **Remoção de conexões:** exclui arestas existentes entre cidades.
- **Consulta de adjacências:** lista as cidades diretamente conectadas a uma cidade informada.
- **Visualização do grafo:** exibe as cidades e suas respectivas conexões.
- **Busca em profundidade (DFS):** percorre o grafo explorando os caminhos em profundidade.
- **Busca em largura (BFS):** percorre o grafo por níveis de distância a partir de uma cidade inicial.
- **Gerenciamento dinâmico de memória:** utiliza alocação e liberação de memória para os nós das listas de adjacência.

## 🛠️ Tecnologias e Conceitos

| Tecnologia ou conceito | Aplicação |
|---|---|
| Linguagem C | Implementação da aplicação |
| Estruturas de dados | Representação de grafos e listas encadeadas |
| Ponteiros | Manipulação de nós e estruturas alocadas dinamicamente |
| Alocação dinâmica | Utilização de `malloc()` e `free()` |
| Listas de adjacência | Representação das conexões entre cidades |
| DFS | Busca em profundidade |
| BFS | Busca em largura utilizando fila |
| Biblioteca padrão C | Entrada, saída e manipulação de strings |

## 🧠 Estrutura de Dados

O grafo é representado por uma lista de adjacência. Cada cidade possui uma lista encadeada contendo os índices das cidades conectadas a ela.

A implementação utiliza duas estruturas principais:

- `Grafo`: armazena o número de cidades, seus nomes e as listas de adjacência.
- `No`: representa uma conexão com outra cidade por meio de um índice e de um ponteiro para o próximo nó.

A estrutura limita o cadastro a **100 cidades**, com nomes de até 49 caracteres úteis, além do terminador de string.

### Representação conceitual

```text
São Paulo
├── Belo Horizonte
└── Rio de Janeiro

Belo Horizonte
├── Salvador
└── São Paulo

Rio de Janeiro
└── São Paulo

Salvador
└── Belo Horizonte
```

Essa representação ilustra as conexões iniciais definidas no programa. A ordem de exibição pode variar conforme a ordem de inserção das arestas.

## 🔎 Algoritmos de Busca

### DFS — Depth-First Search

A busca em profundidade explora uma conexão e continua avançando pelo grafo antes de retornar aos vértices anteriores.

A implementação utiliza recursão e um vetor de visitados para evitar revisitar cidades durante a mesma busca.

### BFS — Breadth-First Search

A busca em largura explora primeiro as cidades diretamente conectadas à origem e depois avança para os níveis seguintes.

A implementação utiliza uma fila baseada em vetor e um vetor de visitados, permitindo percorrer os vértices alcançáveis a partir da cidade inicial.

Em ambos os algoritmos, somente as cidades alcançáveis a partir do vértice inicial são visitadas.

## ⚙️ Como Compilar e Executar

### Pré-requisitos

- Compilador C, como GCC.
- Terminal ou ambiente de desenvolvimento compatível com C.

### 1. Clone o repositório

```bash
git clone https://github.com/SEU-USUARIO/gerenciamento-grafos-c.git
cd gerenciamento-grafos-c
```

Substitua `SEU-USUARIO` pelo seu nome de usuário do GitHub e ajuste o nome do repositório conforme necessário.

### 2. Compile o programa

Considerando que o arquivo principal se chama `main.c`:

```bash
gcc -std=c11 -Wall -Wextra main.c -o gerenciamento_grafos
```

### 3. Execute

No Linux ou macOS:

```bash
./gerenciamento_grafos
```

No Windows, utilizando GCC:

```bash
gerenciamento_grafos.exe
```

## 🖥️ Menu da Aplicação

Ao iniciar, o programa cadastra quatro cidades e algumas conexões iniciais. Em seguida, apresenta um menu interativo:

```text
------ MENU ------
1. Adicionar cidade
2. Adicionar conexão
3. Remover conexão
4. Buscar conexões de uma cidade
5. Imprimir o grafo
6. Buscar cidades com DFS
7. Buscar cidades com BFS
8. Sair
```

O usuário pode selecionar uma operação, informar os nomes das cidades e visualizar os resultados diretamente no terminal.

## ⏱️ Complexidade dos Algoritmos

Considerando \(V\) vértices e \(E\) arestas:

| Operação | Complexidade |
|---|---|
| Buscar uma cidade pelo nome | \(O(V)\) |
| Adicionar uma conexão | \(O(V)\), devido à busca dos vértices |
| Remover uma conexão | \(O(V + d(u) + d(v))\), incluindo a busca dos vértices e a remoção nas listas |
| DFS | \(O(V + E)\) |
| BFS | \(O(V + E)\) |
| Imprimir o grafo | \(O(V + E)\) |

Aqui, \(d(u)\) e \(d(v)\) representam os graus dos vértices envolvidos na remoção de uma conexão. As complexidades pressupõem que as operações de alocação e liberação de memória tenham custo constante.

## 📚 Aprendizados e Objetivos

O projeto demonstra a aplicação de conceitos fundamentais de programação e algoritmos, incluindo:

- Modelagem de relações por meio de grafos.
- Implementação de listas encadeadas.
- Manipulação de ponteiros e memória dinâmica.
- Desenvolvimento de algoritmos de busca.
- Utilização de filas e vetores de controle.
- Organização de funcionalidades em funções reutilizáveis.
- Interação com o usuário por meio de menus em terminal.

## 🔮 Possíveis Melhorias Futuras

- Implementar validações adicionais para impedir cidades duplicadas e conexões repetidas.
- Tratar falhas de alocação de memória e entradas inválidas.
- Adicionar funcionalidades para remover cidades.
- Implementar busca pelo menor caminho entre duas cidades.
- Incluir pesos nas arestas para representar distâncias entre cidades.
- Criar testes automatizados para validar as operações do grafo.
- Desenvolver uma interface gráfica para visualizar a estrutura dinamicamente.

## 👨‍💻 Objetivo Profissional

Projeto desenvolvido para aplicar e consolidar conhecimentos em linguagem C, estruturas de dados, gerenciamento de memória e algoritmos de grafos, demonstrando a capacidade de transformar conceitos teóricos em uma aplicação funcional.

**Principais competências demonstradas:** C · Estruturas de Dados · Grafos · Listas Encadeadas · Ponteiros · Alocação Dinâmica · DFS · BFS · Análise de Complexidade

---

*Projeto educacional para estudo de estruturas de dados e algoritmos.*
