# 📦 Sistema de Gerenciamento de Estoque em C

Um sistema completo de controle de estoque desenvolvido em linguagem C, focado em manipulação de estruturas de dados, gerenciamento de arquivos binários e lógica de organização de memória.

## 🚀 Funcionalidades

O sistema permite o gerenciamento total de uma loja, incluindo:

- **Cadastro de Produtos:** Registro de nome, categoria, quantidade, preço de custo e venda. IDs são gerados automaticamente.
- **Persistência de Dados:** Todos os dados são salvos em um arquivo binário (`produtos.dat`), garantindo que nada seja perdido ao fechar o programa.
- **Relatório Financeiro:** Exibe o estoque atual e calcula o **lucro previsto** (Diferença entre Custo e Venda * Quantidade).
- **Busca Inteligente:** Pesquisa por nome que ignora letras maiúsculas/minúsculas (Case Insensitive) e encontra partes do nome (ex: "gamer" encontra "Teclado Gamer").
- **Realizar Venda:** Baixa automática no estoque com validação para impedir vendas negativas.
- **Exclusão Organizada:** Ao excluir um item, o sistema reorganiza (shift) o array para não deixar "buracos" nos IDs.
- **Edição:** Permite alterar campos específicos de um produto já cadastrado.

## 🛠️ Tecnologias e Conceitos Aplicados

- **Linguagem C**
- **Structs:** Para modelagem dos dados do produto.
- **Manipulação de Arquivos (FILE*):** Leitura e escrita binária (`fread`/`fwrite`) para alta performance.
- **Algoritmos de Busca:** Uso de `strstr` com normalização de strings (função `toupper`) para buscas flexíveis.
- **Lógica de Ponteiros:** Passagem de parâmetros por referência para manipulação direta da memória.
- **Gerenciamento de Arrays:** Lógica de realocação de índices após exclusão.

## 📂 Estrutura do Projeto

O projeto é dividido em módulos para melhor organização:

- `main.c`: Menu principal e loop de execução.
- `funcoes.c`: Implementação de toda a lógica do sistema (CRUD, Vendas, Arquivos).
- `funcoes.h`: Cabeçalho com as definições das Structs e protótipos das funções.
- `produtos.dat`: Arquivo gerado automaticamente para armazenar os dados.

## 💻 Como Compilar e Rodar

Certifique-se de ter um compilador C instalado (como GCC).

1. Clone o repositório:
```bash
git clone [https://github.com/SEU-USUARIO/NOME-DO-REPO.git](https://github.com/SEU-USUARIO/NOME-DO-REPO.git)
```
2. Compile o código:
```bash
gcc main.c funcoes.c -o estoque
```
3. Execute o programa:  
- **Windows:**
  ```bash
  estoque.exe
  ```
- **Linux/Mac:**
  ```bash
  ./estoque
  ```
## 📝 Exemplo de Uso
Ao iniciar, o sistema carrega os dados do arquivo produtos.dat. O menu interativo permite navegar pelas opções:  
```bash
1 - Cadastrar Produto  
2 - Listar/Relatório  
3 - Pesquisar Produto  
4 - Alterar Dados  
5 - Realizar Venda  
6 - Excluir Produto  
0 - Sair
```
## 👨‍💻 Autor
Desenvolvido por **Pedro Henrique MF**, com foco em aprimorar lógica de programação e manipulação de memória em C.
