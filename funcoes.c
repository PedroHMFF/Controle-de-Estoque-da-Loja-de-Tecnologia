#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>
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
    if (total_produtos == MAX_PRODUTOS){//testando pra verificar se esta no maximo de produtos
        printf("Maximo de produtos na loja!!\n");
        return;
    }//if

    novoProduto->id = total_produtos + 1;//aumentando o id pra adicionar o produto

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
    
    produtos[total_produtos] = *novoProduto;//pega o conteudo do novo produto, e coloca na variavel global produtos
    total_produtos++;//incrementa o contador para apontar para a próxima vaga

    salvarProdutos();// salvando os produtos

    printf("\n✅ Produto cadastrado com sucesso!\n");
}//cadastrar os produtos

void salvarProdutos(){
    FILE* arqB = fopen(ARQUIVO_PRODUTOS_BIN,"wb");

    if (arqB == NULL){
        printf("Erro em abrir arquivo dos produtos!!\n");
        return;
    }//if

    //grava primeiro o número total e depois o array inteiro de uma vez
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

    printf("\n%-4s | %-20s | %-20s | %-5s | %-10s | %-10s\n", "ID", "NOME","CATEGORIA", "QTD", "PRECO V.", "LUCRO PREV.");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < total_produtos; i++){// Cálculo do lucro baseado na diferença de preço multiplicada pela quantidade
        // (Venda - Custo) que e pra descobrir o lucro por unidade, * Quantidade
        float lucroItem = (produtos[i].precoVenda - produtos[i].precoCusto) * produtos[i].quantidade;

        lucroTotalEstoque += lucroItem;//Acumula para o final


        printf("\n%-4d | %-20s | %-20s | %-5d | %.2f | %.2f\n", produtos[i].id,
                                                            produtos[i].nome,
                                                            produtos[i].categoria,
                                                            produtos[i].quantidade,
                                                            produtos[i].precoVenda,
                                                            lucroItem);
    }//for
    printf("----------------------------------------------------------------------\n");
    printf("LUCRO TOTAL PREVISTO PARA O ESTOQUE: R$ %.2f\n", lucroTotalEstoque);
    
}//relatorio do estoque 

void excluirProduto(){
    int idExcluir;
    int idx = -1;// comeca com -1 para indicar que ainda não achou o ID
    printf("Digite o id do produto que deseja excluir:");
    scanf("%d",&idExcluir);
    
    for (int i = 0; i < total_produtos; i++){
        if (idExcluir == produtos[i].id){
            idx = i;
            break;
        }//if interno
    }//for externo
    
    if (idx == -1){
        printf("Erro: Produto com ID %d nao encontrado.\n", idExcluir);
        return;
    }//
    //deslocamento--> puxa os itens da frente para "tapar o buraco" do excluído, se eu tirar o 1, o 2 vai no lugar dele e assim por diante
    for (int i = idx; i < total_produtos - 1; i++) {
        produtos[i] = produtos[i + 1];
    }//for
    total_produtos--;//diminuindo o total de produtos

    //reatribui os IDs para manter a ordem sequencial (1, 2, 3...)
    for (int i = 0; i < total_produtos; i++) {
        produtos[i].id = i + 1;
    }

    salvarProdutos(); 
    printf("Produto excluido e IDs reorganizados com sucesso!\n");
}//Excluir o produto

void alterarProduto(){
    int id_alterar;
    int opc;

    printf("Digite o ID do produto que deseja alterar:");
    scanf("%d",&id_alterar);

    //validação de segurança para evitar estoque negativo
    for (int i = 0; i < total_produtos; i++){
        if (produtos[i].id == id_alterar){
            printf("\nDigite algum dos numeoros abaixo pra alterar oque deseja:\n");
            printf("1 - Alterar o nome\n");
            printf("2 - Alterar a categoria\n");
            printf("3 - Alterar a quantidade\n");
            printf("4 - Alterar o preco que custou pra loja\n");
            printf("5 - Alterar o preco de venda\n");
            printf("0 - Para sair\n");
            printf("-->");
            scanf("%d",&opc);

            switch (opc){
            case 1:
                limpar_buffer();
                printf("Digite o novo nome do produto:");
                fgets(produtos[i].nome,50,stdin);
                produtos[i].nome[strcspn(produtos[i].nome, "\n")] = '\0';
                break;
             case 2:
                limpar_buffer();
                printf("Digite a nova categoria do produto:");
                fgets(produtos[i].categoria,30,stdin);
                produtos[i].categoria[strcspn(produtos[i].categoria, "\n")] = '\0';
                break;
             case 3:
                printf("Digite a nova quantidade do produto:");
                scanf("%d",&produtos[i].quantidade);
                break;
             case 4:
                printf("Digite o novo preco de custo pra loja:");
                scanf("%f",&produtos[i].precoCusto);
                break;
             case 5:
                printf("Digite o novo preco de venda:");
                scanf("%f",&produtos[i].precoVenda);
                break;
             case 0:
                printf("Saindo...");
                
                break;
            default:
                printf("Alternativa errada, digite entre 0 e 5");
                break;
            }//switch
        salvarProdutos();// salvando os produtos
        printf("Alteracao realizada com sucesso!\n");
        return;
        }//if
    }//for

}//alterar o produto

void realizarVenda(){
    int id_venda,quant;
    int encontrou = 0;//sabe se achou o id ou nao
    

    printf("Digite o id do produto que vendeu:");
    scanf("%d",&id_venda);

    for (int i = 0; i < total_produtos; i++){
        if (produtos[i].id == id_venda){
            encontrou = 1;

            printf("Produto: %s | Estoque atual: %d\n", produtos[i].nome, produtos[i].quantidade);
            printf("Qual a quantidade que vendeu: ");
            scanf("%d",&quant);

            if (produtos[i].quantidade >= quant){
                produtos[i].quantidade -= quant;
                printf("Venda realizada! Novo estoque: %d\n", produtos[i].quantidade);

                if (produtos[i].quantidade == 0) {
                    printf("O estoque desse produto acabou!\n");; 

                }else{
                    printf("Novo estoque: %d\n", produtos[i].quantidade);
                }//if
                salvarProdutos(); 
            }else{
                printf("Erro: Estoque insuficiente. Voce tem %d mas tentou vender %d.\n", produtos[i].quantidade, quant);
            }//if
        return;
        }//if
    }//for

    if (encontrou == 0) {
        printf("Produto com ID %d nao encontrado.\n", id_venda);
    }//if pra verificar se encontrou

}//realizar a venda do produto

void pesquisarProduto(){
    char termo[50];
    char termoMaiusculo[50];
    char nomeNoBancoMaiusculo[50];
    int encontrou = 0;

    limpar_buffer();
    printf("Digite o nome do produto que deseja buscar:");
    fgets(termo,50,stdin);
    termo[strcspn(termo, "\n")] = '\0';

    //Converte termo de busca para maiúsculo
    for (int i = 0; i < termo[i]; i++){
        termoMaiusculo[i] = toupper(termo[i]);
    }
    termoMaiusculo[strlen(termo)] = '\0';
    
    printf("\n=== RESULTADO ===\n");

    for (int i = 0; i < total_produtos; i++) {
        //Converte nome do produto no banco para maiúsculo antes de comparar
        for (int j = 0; produtos[i].nome[j]; j++) {
            nomeNoBancoMaiusculo[j] = toupper(produtos[i].nome[j]);
        }//for
        nomeNoBancoMaiusculo[strlen(produtos[i].nome)] = '\0';
        //Verifica se o termo existe em qualquer parte do nome
        if (strstr(nomeNoBancoMaiusculo,termoMaiusculo)!= NULL){
            printf("ID: %d | Nome: %s | Qtd: %d\n", 
                produtos[i].id, produtos[i].nome, produtos[i].quantidade);
                encontrou = 1;
        }//if
    }//for
    if (!encontrou) printf("Nada encontrado.\n");
}//pesquisa produto
