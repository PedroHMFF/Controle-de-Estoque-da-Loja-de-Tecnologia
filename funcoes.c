#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "funcoes.h"

#define MAX_PRODUTOS 20
#define ARQUIVO_PRODUTOS_BIN "produtos.dat"
Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;

void limpar_buffer() {// pra limpar
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarProduto(Produto *novoProduto){   
    if (total_produtos == MAX_PRODUTOS){
        printf("Maximo de produtos na loja!!\n");
        return;
    }//if

    novoProduto->id = total_produtos + 1;

    printf("\n==Cadastrando Produto==\n");
    printf("Digite o nome do produto:");
    fgets(novoProduto->nome,50,stdin);
    novoProduto->nome[strcspn(novoProduto->nome,"\n")] = '\0';

    limpar_buffer();

    printf("Digite a categoria do Produto(Ex: Periféricos, Hardware, Monitores):");
    fgets(novoProduto->categoria,30,stdin);
    novoProduto->categoria[strcspn(novoProduto->categoria,"\n")] = '\0';
    
    printf("Digite a quantidade de produto:");
    scanf("%d",&novoProduto->quantidade);

    printf("Digite quanto a loja pagou em cada produto:");
    scanf("%f",&novoProduto->precoCusto);

    printf("Digite o valor que sera vendido o produto:");
    scanf("%f",&novoProduto->precoVenda);

    limpar_buffer();
    
    produtos[total_produtos] = *novoProduto;
    total_produtos++;

    salvarProdutos();// salvando os produtos

    printf("\n✅ Produto cadastrado com sucesso!\n");
}//cadastrar os produtos

void salvarProdutos(){
    FILE* arqB = fopen(ARQUIVO_PRODUTOS_BIN,"wb");

    if (arqB == NULL){
        printf("Erro em abrir arquivo dos produtos!!\n");
        return;
    }//if

    fwrite(&total_produtos,sizeof(int),1,arqB);
    fwrite(produtos,sizeof(Produto),total_produtos,arqB);

    fclose(arqB);

}//salvar produtos

void carregarEstoque(){
    FILE *arq = fopen(ARQUIVO_PRODUTOS_BIN,"rb");

    if (arq == NULL){
        printf("Erro em abrir arquivo dos produtos\n");
        total_produtos = 0;
        return;
    }//if

    fread(&total_produtos,sizeof(int),1,arq);
    fread(produtos,sizeof(Produto),total_produtos,arq);

}//carregar os produtos no estoque

void relatorioEstoque(){   //arrumar depois
    if (total_produtos == 0){
        printf("Estoque esta vazio\n");
        return;
    }//if

    float lucroTotalEstoque = 0;// Para somar o lucro da loja toda

    printf("\n%-4s | %-20s | %-5s | %-10s | %-10s\n", "ID", "NOME", "QTD", "PRECO V.", "LUCRO PREV.");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < total_produtos; i++){
        // (Venda - Custo) que e pra descobrir o lucro por unidade, * Quantidade
        float lucroItem = (produtos[i].precoVenda - produtos[i].precoCusto) * produtos[i].quantidade;

        lucroTotalEstoque += lucroItem;//Acumula para o final


        printf("\n%-4d | %-20s | %-5d | %-10f | %-10f\n", produtos[i].id,
                                                            produtos[i].nome,
                                                            produtos[i].quantidade,
                                                            produtos[i].precoVenda);
    }//for
    printf("----------------------------------------------------------------------\n");
    printf("LUCRO TOTAL PREVISTO PARA O ESTOQUE: R$ %.2f\n", lucroTotalEstoque);
    
}//relatorio do estoque 

void excluirProduto(){
    int idExcluir,idx;
    printf("Digite o id do produto que deseja excluir");
    scanf("%d",&idExcluir);
    
    for (int i = 0; i < total_produtos; i++){
        if (idExcluir == produtos[i].id){
            idx = i;
        }//if interno
    }//for externo
    
    if (idx == -1){
        return;
    }//
    
    for (int i = idx; i < total_produtos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }//for
    total_produtos--;//diminuindo o total de produtos

    for (int i = 0; i < total_produtos; i++) {
        produtos[i].id = i + 1;
    }// realocando os ids do inicio

}//Excluir o produto

void alterarProduto(){



}//alterar o produto

void realizarVenda(){



}//realizar a venda do produto
