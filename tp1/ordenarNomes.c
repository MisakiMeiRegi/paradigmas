/* Desenvolvedora: M�rcia Regina da Concei��o Silva
   Data: 08/09/2016
*/
#include <stdio.h>
#include <stdlib.h>
#define TAM 100000

struct ganhadores
{
    char nome[50];
}; //Cria��o da struct

struct ganhadores G[TAM];

//Fun��o para compara��o de nomes
int comparaNome(const void * a, const void * b )
{
    int r = strcmp((*(struct ganhadores*)a).nome,
                   (*(struct ganhadores*)b).nome);

    if (r == 0)
        return 0; //nomes iguais
    else if(r < 0)
        return -1;//nome vem antes
    else
        return 1;//nome vem depois
}//fim da compara��o

//Fun��o que abrir o arquivo e gera o html de nomes com R
void odernarNomes(void)
{

    int i=1, aux=0, j=0;

    FILE *arquivo_ganhadores;

    //Abrindo arquivo com os ganhadores
    arquivo_ganhadores = fopen("arq_ganhadores.txt","r+");

    //verifica se o arquivo e v�lido
    if(arquivo_ganhadores == 0)
        printf("Erro ao abrir o arrquivo");
    else
    {
        //printf("Arquivo aberto com sucesso\n");

        //A fun��o fflush() � usada para esvaziar o conte�do de um buffer de sa�da
        fflush(arquivo_ganhadores);

        //leitura dos ganhadores
        while(!feof(arquivo_ganhadores))
        {
            fscanf(arquivo_ganhadores,"%s\t",G[i].nome);
            aux++;
            i++;
        }
        //fecha o arquivo
        fclose(arquivo_ganhadores);

        FILE *arqGanhadores ;
        //Criar um arquivo com os nomes em formato html
        arqGanhadores = fopen("ganhadores.html","a+");

        if(arqGanhadores == 0)
            printf("Erro ao abrir o arquivo");
        else
        {
            //printf("Arquivo aberto com sucesso\n");

            //A fun��o fflush() � usada para esvaziar o conte�do de um buffer de sa�da
            fflush(arqGanhadores);

            //Ordena os nomes usando a fun��o qsort
            qsort(G,i,sizeof(struct ganhadores), comparaNome);

            //Abre a tag de lista em html
            fprintf(arqGanhadores,"<ul> \n");
            for(i=1; i<=aux; i++)
            {
                //Verifica os nomes que iniciam com a letra R
                if((G[i].nome[0] == 'R'))
                {
                    //Sslva os nomes em um arquvo html
                    fprintf(arqGanhadores,"<li> \t");
                    fprintf(arqGanhadores, "%s\t",G[i].nome);
                    fprintf(arqGanhadores,"</li> \t");
                    fprintf(arqGanhadores,"\n");

                }
            }
            //Fecha a tag de lista em html
            fprintf(arqGanhadores,"\n </ul> \n");

            printf("\n Lista de ganhadores em html gerada!!!\n");

            //fechando arquivo
            fclose(arqGanhadores);
        }

    }
}//fim da ordena��o.

int main()
{
    //chama a fun��o
    odernarNomes();
    system("pause");
    return 0;
}
