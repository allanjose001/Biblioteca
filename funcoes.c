//Trabalho de AED, feito por Allan Jose & Gabriel Saraiva
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "livro.h"

#define MAX_LIVROS 10
#define MAX_TITULO 50
#define MAX_AUTOR 50
#define MAX_EDITORA 50

int linha() {
  printf("================================\n");
  return 0;
}

int limparBuffer() {
  int ch;
  while ((ch = getchar()) != '\n' && ch != EOF);
}

FILE *abrir() {
  const char *arquivo = "estoque.txt";
  FILE *stq = fopen(arquivo, "a+");

  if (stq == NULL) {
    perror("erro ao abrir arquivo");
    return NULL;
  }
  
  return stq;
}

void fechar(FILE *arquivo) {
  if (arquivo != NULL) {
    fclose(arquivo);
  }
}

//===============Op��es do Menu===============

int inserirNoInicio(FILE *arquivo, Biblioteca *biblioteca) {
  Livro novoLivro;

  printf("Digite os dados do novo livro:\n");
  printf("ID: ");
  scanf("%d", &novoLivro.id);
  printf("T�tulo: ");
  scanf("%s", novoLivro.titulo);
  printf("Autor: ");
  scanf("%s", novoLivro.autor);
  printf("Editora: ");
  scanf("%s", novoLivro.editora);
  printf("Ano: ");
  scanf("%d", &novoLivro.ano);
  printf("Dispon�vel (1 para sim, 0 para n�o): ");
  scanf("%d", &novoLivro.disponivel);

  FILE *arquivoTemporario = fopen("estoque_temp.txt", "w");
  if (arquivoTemporario == NULL) {
    perror("Erro ao criar arquivo tempor�rio");
    return 0;
  }

  fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
  novoLivro.id, novoLivro.titulo,
  novoLivro.autor, novoLivro.editora,
  novoLivro.ano, novoLivro.disponivel);

  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroAtual;

  while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroAtual.id, livroAtual.titulo,
  livroAtual.autor, livroAtual.editora,
  &livroAtual.ano, &livroAtual.disponivel) == 6) {
    fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
    livroAtual.id, livroAtual.titulo,
    livroAtual.autor, livroAtual.editora,
    livroAtual.ano, livroAtual.disponivel);
  }

  fclose(arquivoTemporario);
  fclose(arquivo);

  if (remove("estoque.txt") != 0) {
    perror("Erro ao excluir arquivo original");
    return 0; // Falha na exclus�o do arquivo original
  }

  if (rename("estoque_temp.txt", "estoque.txt") != 0) {
    perror("Erro ao renomear arquivo tempor�rio");
    return 0; // Falha ao renomear o arquivo tempor�rio
  }

  return 1; // Livro inserido no in�cio com sucesso
}

int inserirFim(FILE *arquivo, Biblioteca *biblioteca) {
  if (arquivo == NULL || biblioteca == NULL) {
    return 0;
  }

  Livro novoLivro;  // Criar uma vari�vel para armazenar os dados do novo livro

  printf("Digite os dados do novo livro:\n");
  printf("ID: ");
  scanf("%d", &novoLivro.id);
  limparBuffer();

  printf("T�tulo: ");
  scanf("%49[^\n]", novoLivro.titulo);
  limparBuffer();

  printf("Autor: ");
  scanf("%49[^\n]", novoLivro.autor);
  limparBuffer();

  printf("Editora: ");
  scanf("%49[^\n]", novoLivro.editora);
  limparBuffer();

  printf("Ano: ");
  scanf("%d", &novoLivro.ano);
  limparBuffer();

  printf("Disponivel (1 para sim, 0 para n�o): ");
  scanf("%d", &novoLivro.disponivel);
  limparBuffer();

  // Posiciona o cursor no final do arquivo
  fseek(arquivo, 0, SEEK_END);

  // Escreve o novo livro no final do arquivo
  fprintf(arquivo, "%d;%s;%s;%s;%d;%d\n",
    novoLivro.id, novoLivro.titulo,
    novoLivro.autor, novoLivro.editora,
    novoLivro.ano, novoLivro.disponivel);

  printf("\nLivro inserido com sucesso.\n");
  linha();

  return 1;
}

int inserirPorPosicao(FILE *arquivo) {
  int posicao;
  printf("Digite a posi��o do livro que deseja inserir: ");
  scanf("%d", &posicao);

  Livro novoLivro;

  printf("Digite os dados do novo livro:\n");
  printf("ID: ");
  scanf("%d", &novoLivro.id);
  printf("T�tulo: ");
  scanf("%s", novoLivro.titulo);
  printf("Autor: ");
  scanf("%s", novoLivro.autor);
  printf("Editora: ");
  scanf("%s", novoLivro.editora);
  printf("Ano: ");
  scanf("%d", &novoLivro.ano);
  printf("Dispon�vel (1 para sim, 0 para n�o): ");
  scanf("%d", &novoLivro.disponivel);

  FILE *arquivoTemporario = fopen("estoque_temp.txt", "w");
  if (arquivoTemporario == NULL) {
    perror("Erro ao criar arquivo tempor�rio");
    return 0; // Falha na cria��o do arquivo tempor�rio
  }

  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroAtual;
  int i;

  for (i = 1; fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroAtual.id, livroAtual.titulo,
  livroAtual.autor, livroAtual.editora,
  &livroAtual.ano, &livroAtual.disponivel) == 6; i++) {

    if (i == posicao) {
      fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
      novoLivro.id, novoLivro.titulo,
      novoLivro.autor, novoLivro.editora,
      novoLivro.ano, novoLivro.disponivel);
      }

      fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
      livroAtual.id, livroAtual.titulo,
      livroAtual.autor, livroAtual.editora,
      livroAtual.ano, livroAtual.disponivel);
    
  }

  //caso a posi��o seja maior do que o n�mero de livros no arquivo,
  //insere o novo livro no final
  if (i < posicao) {
    fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
    novoLivro.id, novoLivro.titulo,
    novoLivro.autor, novoLivro.editora,
    novoLivro.ano, novoLivro.disponivel);
  }

  fclose(arquivoTemporario);
  fclose(arquivo);

  if (remove("estoque.txt") != 0) {
    perror("Erro ao excluir arquivo original");
    return 0; // Falha na exclus�o do arquivo original
  }

  if (rename("estoque_temp.txt", "estoque.txt") != 0) {
    perror("Erro ao renomear arquivo tempor�rio");
    return 0; // Falha ao renomear o arquivo tempor�rio
  }

  return 1; // Livro inserido na posi��o com sucesso
}

int buscarPorID(FILE *arquivo, Biblioteca *biblioteca) {
  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroEncontrado;
  int idDesejado;
  
  linha();
  printf("Digite o ID do livro que deseja buscar: ");
  scanf("%d", &idDesejado);

  while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroEncontrado.id, livroEncontrado.titulo,
  livroEncontrado.autor, livroEncontrado.editora,
  &livroEncontrado.ano, &livroEncontrado.disponivel) == 6) {
    if (livroEncontrado.id == idDesejado) {
      linha();
      printf("Livro encontrado:\n");
      printf("ID: %d\n", livroEncontrado.id);
      printf("T�tulo: %s\n", livroEncontrado.titulo);
      printf("Autor: %s\n", livroEncontrado.autor);
      printf("Editora: %s\n", livroEncontrado.editora);
      printf("Ano: %d\n", livroEncontrado.ano);
      printf("Dispon�vel: %d\n", livroEncontrado.disponivel);
      linha();
      return 1;
    }
  }

  printf("Livro n�o encontrado.\n");
  return 0; 
}

int excluirPorID(FILE *arquivo) {
  int id;
  printf("Digite o ID do livro que deseja excluir: ");
  scanf("%d", &id);

  FILE *arquivoTemporario = fopen("estoque_temp.txt", "w");
  if (arquivoTemporario == NULL) {
    perror("Erro ao criar arquivo tempor�rio");
    return 0; // Falha na cria��o do arquivo tempor�rio
  }

  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroAtual;

  while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroAtual.id, livroAtual.titulo,
  livroAtual.autor, livroAtual.editora,
  &livroAtual.ano, &livroAtual.disponivel) == 6) {
    if (livroAtual.id != id) {
      fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
      livroAtual.id, livroAtual.titulo,
      livroAtual.autor, livroAtual.editora,
      livroAtual.ano, livroAtual.disponivel);
    }
  }

  fclose(arquivoTemporario);
  fclose(arquivo);

  if (remove("estoque.txt") != 0) {
    perror("Erro ao excluir arquivo original");
    return 0; // Falha na exclus�o do arquivo original
  }

  if (rename("estoque_temp.txt", "estoque.txt") != 0) {
    perror("Erro ao renomear arquivo tempor�rio");
    return 0; // Falha ao renomear o arquivo tempor�rio
  }

  return 1;
}

int excluirPorPos(FILE *arquivo) {
  int posicao;
  printf("Digite a posi��o do livro que deseja excluir: ");
  scanf("%d", &posicao);

  FILE *arquivoTemporario = fopen("estoque_temp.txt", "w");
  if (arquivoTemporario == NULL) {
    perror("Erro ao criar arquivo tempor�rio");
    return 0;
  }

  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroAtual;

  for (int i = 1; fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroAtual.id, livroAtual.titulo,
  livroAtual.autor, livroAtual.editora,
  &livroAtual.ano, &livroAtual.disponivel) == 6; i++) {
    if (i != posicao) {
      fprintf(arquivoTemporario, "%d;%s;%s;%s;%d;%d\n",
      livroAtual.id, livroAtual.titulo,
      livroAtual.autor, livroAtual.editora,
      livroAtual.ano, livroAtual.disponivel);
    }
  }

  fclose(arquivoTemporario);
  fclose(arquivo);

  if (remove("estoque.txt") != 0) {
    perror("Erro ao excluir arquivo original");
    return 0;
  }

  if (rename("estoque_temp.txt", "estoque.txt") != 0) {
    perror("Erro ao renomear arquivo tempor�rio");
    return 0; 
  }

  return 1;
}

void imprimirEstoque(FILE *arquivo) {
  rewind(arquivo); // Retorna o ponteiro do arquivo para o in�cio

  Livro livroAtual;

  linha();
  printf("ID | T�tulo | Autor | Editora | Ano | Dispon�vel\n");

  while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d\n",
  &livroAtual.id, livroAtual.titulo,
  livroAtual.autor, livroAtual.editora,
  &livroAtual.ano, &livroAtual.disponivel) == 6) {
    printf("%d | %s | %s | %s | %d | %d\n",
    livroAtual.id, livroAtual.titulo,
    livroAtual.autor, livroAtual.editora,
    livroAtual.ano, livroAtual.disponivel);
  }
}

int imprimirMenu() {
  linha();
  printf("1 - Inserir livro no Inicio\n");
  printf("2 - Inserir livro no Fim\n");
  printf("3 - Inserir livro por posi��o\n");
  printf("4 - Listar biblioteca\n");
  printf("5 - Excluir livro por ID\n");
  printf("6 - Excluir livro por Posi��o\n");
  printf("7 - Buscar por um livro\n");
  printf("0 - Sair\n");
  linha();
}