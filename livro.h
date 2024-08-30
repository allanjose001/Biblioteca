#ifndef livro_h
#define livro_h

typedef struct Livro {
  int id;
  char titulo[50];
  char autor[50];
  char editora[50];
  int ano;
  int disponivel;
} Livro;

typedef struct{
    Livro *livros;
    int quantidadeLivros;
} Biblioteca;

//declaração de funções

FILE *abrir();
void fechar(FILE *arquivo);
int inserirNoInicio(FILE *arquivo, Biblioteca *biblioteca);
int inserirFim(FILE *arquivo, Biblioteca *biblioteca);
int inserirPorPosicao(FILE *arquivo);
void imprimirBiblioteca(FILE *arquivo);
int excluirPorID(FILE *arquivo);
int excluirPorPos(FILE *arquivo);
int buscarPorID(FILE *arquivo, Biblioteca *biblioteca);

#endif