//Trabalho de AED, feito por Allan Jose & Gabriel Saraiva 
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"
#include "livro.h"

int main() {
  Biblioteca biblioteca;
  biblioteca.livros = malloc(MAX_LIVROS * sizeof(Livro));
  biblioteca.quantidadeLivros = 0;

  int opcao;

  do {
    imprimirMenu();
    if (scanf("%d", &opcao) != 1) {
      limparBuffer();
      opcao = -1;
    }

    switch (opcao) {
      case 1: {
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          inserirNoInicio(arquivo, &biblioteca);
          limparBuffer();
          fechar(arquivo);
          printf("Livro inserido com sucesso.\n");
          linha();
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
          break;
        }
      }
      case 2:{
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          inserirFim(arquivo, &biblioteca);
          limparBuffer();
          fechar(arquivo);
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
          break;
        }
      }
      case 3:{
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          inserirPorPosicao(arquivo);
          limparBuffer;
          fechar(arquivo);
          printf("Livro inserido com sucesso.\n");
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
          break;
        }
      }

      case 4: {
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          imprimirEstoque(arquivo);
          limparBuffer();
          fechar(arquivo);
          linha();
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
          break;
        }
      }

      case 5: {
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          excluirPorID(arquivo);
          limparBuffer();
          fechar(arquivo);
          printf("Livro removido com sucesso.\n");
          linha();
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
        break;
        }
      }

      case 6: {
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          excluirPorPos(arquivo);
          limparBuffer();
          fechar(arquivo);
          printf("Livro removido com sucesso.\n");
          linha();
          printf("Pressione enter para voltar para o menu.\n");
          getchar();
        break;
        }
      }

      case 7: {
        FILE *arquivo = abrir();
        if (arquivo != NULL) {
          buscarPorID(arquivo, &biblioteca);
          limparBuffer();
          fechar(arquivo);

          printf("Pressione enter para voltar para o menu.\n");
          getchar();
          break;
        }
      }

      case 0:
        printf("Fechando Programa\n");
        break;

      default:
        printf("opção inválida\n");
    }
  } while (opcao != 0);

  free(biblioteca.livros);

  return 0;
}
