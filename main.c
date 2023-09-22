#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
  int codigo_produto;
  float valor;
  char nome[10];
};

struct Vendedor {
  int codigo_vendedor;
  char nome[10];
};

struct Venda {
  int codigo_vendedor;
  int codigo_produto;
  int qtde;
};

int main() {
  FILE *vendas_arquivo = fopen("vendas.txt", "r");
  FILE *produtos_arquivo = fopen("produtos.txt", "r");
  FILE *vendedores_arquivo = fopen("vendedores.txt", "r");

  struct Venda vendas[20];
  struct Produto produtos[10];
  struct Vendedor vendedores[5];
  int n_vendas = 0, n_produtos = 0, n_vendedores = 0;

  if (vendas_arquivo == NULL || produtos_arquivo == NULL || vendedores_arquivo == NULL) {
    printf("Erro ao abrir um dos arquivos de entrada.\n");
    return 1;
  }

  while (
      fscanf(produtos_arquivo, "%d %f %s", &produtos[n_produtos].codigo_produto,
             &produtos[n_produtos].valor, produtos[n_produtos].nome) != EOF) {
    n_produtos++;
  }

  while (fscanf(vendedores_arquivo, "%d %s",
                &vendedores[n_vendedores].codigo_vendedor,
                vendedores[n_vendedores].nome) != EOF) {
    n_vendedores++;
  }

  while (fscanf(vendas_arquivo, "%d %d %d", &vendas[n_vendas].codigo_vendedor,
                &vendas[n_vendas].codigo_produto,
                &vendas[n_vendas].qtde) != EOF) {
    n_vendas++;
  }

  fclose(vendas_arquivo);
  fclose(produtos_arquivo);
  fclose(vendedores_arquivo);

  float total_por_produto[100] = {0};
  float total_por_vendedor[100] = {0};
  float total_geral = 0;

  for (int i = 0; i < n_vendas; i++) {
    int vendedor = vendas[i].codigo_vendedor;
    int produto = vendas[i].codigo_produto;
    int unidades = vendas[i].qtde;

    for (int j = 0; j < n_vendas; j++) {
      if (produtos[j].codigo_produto == produto) {
        total_geral += produtos[j].valor * unidades;
        total_por_produto[produtos[j].codigo_produto] +=
            produtos[j].valor * unidades;
        break;
      }
    }
    
    for (int j = 0; j < n_produtos; j++) {
      if (produtos[j].codigo_produto == produto) {
        float valor_venda = produtos[j].valor * unidades;
        total_por_vendedor[vendedor] += valor_venda;
        break;
      }
    }
  }

  FILE *totais_file = fopen("totais.txt", "w");

  fprintf(totais_file, "Total Geral de Vendas: %.2f\n\n", total_geral);

  fprintf(totais_file, "Total por Produto:\n");
  for (int i = 0; i < n_produtos; i++) {
    fprintf(totais_file, "Produto: %s - Total: %.2f\n", produtos[i].nome,
            total_por_produto[produtos[i].codigo_produto]);
  }

  fprintf(totais_file, "\nTotal por Vendedor:\n");
  for (int i = 0; i < n_vendedores; i++) {
    fprintf(totais_file, "Vendedor: %s - Total: %.2f\n", vendedores[i].nome,
            total_por_vendedor[vendedores[i].codigo_vendedor]);
  }

  fclose(totais_file);

  printf("Totais calculados e gravados em totais.txt com sucesso!\n");

  return 0;
}
