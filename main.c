#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "funcoes.h"

int main(){
  
    int opc;
    carregarEstoque();
    
    
    do{
        printf("\n==Controle de Estoque da Loja de Tecnologia==\n");
        printf("Escolha sua opcao\n");
        printf("1-Cadastrar produto\n");
        printf("2-Realizar Venda\n");
        printf("3-Relatório de Estoque\n");
        printf("4-Alterar o produto\n");
        printf("0-Para sair\n");
        printf("--->");
        scanf("%d",&opc);

        if (opc != 1){
            printf("Entrada inválida detectada.\n");
            setbuf(stdin,NULL);
            opc = -1;//pra rodar denovo o do while
            continue;
        }//if pra verificar se a entrada e valida ou nao
        
        switch (opc){
        case 1:{
            Produto temp;
            cadastrarProduto(&temp);
            break;
        }
        case 2:
            /*realizarVenda();*/
            break;

        case 3:
            /*relatorioEstoque();*/
            break;

        case 4:
            /*alterarProduto();*/
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Erro, digite a opcao entre 1 a 4\n");
            break;
        }//switch
        
    } while(opc != 0);
    
    

    return 0;
}//main