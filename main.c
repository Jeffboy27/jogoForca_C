#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Header files (declaração de funções para não importar a ordem do programa ao ler.
//as funções tambem podem ficar dentro de um header file para facilitar o codigo.
#include "Headerteste.h"


//variaveis geral
char palavra[8];
int chutesdados =0;

//Funções do programa. Elas podem ta num Headerfile, mas deixei aqui pra ver tudo direito.
void adicionapalavra()
{
    char quer; //apenas um caracter

    printf("Você deseja  adicionar uma nova palavra no jogo (S/N)?");
    scanf(" %c", &quer); //só le um caracter

    if(quer == 'S')
    {
        char novapalavra[20];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("bancodedados.txt", "r+");
        if(f == 0) {
            printf("Banco de dados de palavras não disponível\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);

    }

}

void escolhapalavra ()
{
    FILE* f;

    f = fopen("bancodedados.txt", "r");
    if(f == 0) {
        printf("Banco de dados de palavras não disponível\n\n");
        exit(1);
    }

    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    srand(time(0));
    int randomico = rand() % qtddepalavras;

    for(int i = 0; i <= randomico; i++) {
        fscanf(f, "%s", palavra);
    }

    fclose(f);

}

void abertura () //função para abertura
{
    printf("==================\n");
    printf("= Jogo da forca! =\n");
    printf("==================\n");

}
void chuta(char chutes[26])//função novo chute. O * Serve para fazer com que pegue na memoria o conteudo o que se tinha em Tentativa na Main
{
    char chute;
    scanf(" %c",&chute);
    chutes[chutesdados] = chute;
    chutesdados ++;// este incrementa tentativa na função que por consequencia tambem muda as chutesdados dentro do Do while
}


int jachutouuu(char letra, char chutes [26]) // como ha uma contagem em achou (achou = 0) é preciso retornar um numero inteiro. Logo, não se coloca Void
{
    int achou = 0;
    for (int j = 0; j< chutesdados; j++)//faz a contagem/busca de letra dentro do strlen
    {
        if(chutes[j]==letra)//marca as letras achadas
            {
                achou=1;
                break;
            }
    }
    return achou;
}

void desenhaforca ( char chutes[26])
{
            for(int i = 0; i<strlen(palavra); i++)//strlen faz a contagem das letras na string/palavra
        {
            //Aqui estava o codigo Jachutou!!!!!
            int achou = jachutouuu(palavra[i],chutes);

            if(achou)//mostra se a letra foi achada e onde...
            {
                printf ("%c", palavra[i]);
            }
            else
            {
                printf("_ ");
            }

        }
        printf("\n");

}

int acertou (char chutes[26])
{
    for(int i=0; i<strlen(palavra); i++)
    {
        if (!jachutouuu(palavra[i],chutes))
        {
            return 0;
        }
    }
    return 1;
}

int enforcou(char chutes[26])
{
	int erros = 0;

	for(int i = 0; i < chutesdados; i++) {

		int existe = 0;

		for(int j = 0; j < strlen(palavra); j++) {
			if(chutes[i] == palavra[j]) {
				existe = 1;
				break;
			}
		}

		if(!existe) erros++;
	}

	return erros >= 5;
}

/////////////////////////////////////////////codigo principal\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


int main()//função principa
{
    abertura();//chamando a abertura para abrir dentro do codigo principal
    escolhapalavra();

    char chutes[26]; // faz total diferença mudar esse chute para outro lugar, pois moda a forma do codigo. Não consegui leva-la variavel geral
    do
    {
        desenhaforca(chutes);
        chuta(chutes);//função chuta. O & comercial é para guardar algo na memoria. Dai o Tentativas fica salvo o conteudo e vai pra o void.
    }while(!acertou(chutes) && !enforcou(chutes));

    adicionapalavra();
    return 0;
}





/*
        for(int i=0;i<strlen(palavra);i++)
        {
            if(palavra[i]==chute)
            {
                printf("A posição %d tem essa letra\n", i);

            }
        }
*/
