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
