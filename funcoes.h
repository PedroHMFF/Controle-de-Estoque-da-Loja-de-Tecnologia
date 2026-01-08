#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    int id;//id do produto
    char nome[50];//nome do produto
    char categoria[30]; // Ex: Periféricos, Hardware, Monitores
    int quantidade;     // Para controle de estoque
    float precoCusto;   // Quanto a loja pagou
    float precoVenda;   // Por quanto vai vender
} Produto;

void cadastrarProduto(Produto *novoProduto);
void realizarVenda();
void relatorioEstoque();
void alterarProduto();

void salvarProdutos();
void carregarEstoque();

#endif 