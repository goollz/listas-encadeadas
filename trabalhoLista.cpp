#include<stdio.h>
#include<conio2.h>
#include<stdlib.h>
#include "tadTrabalho.h"
int main()
{
	TpElementoArq reg;
	TpPais *Pais;
	TpMedicamento *Med;
	TpDescritor D;
	char linha[400],op,pais[40],medicamento[200];
	int x=1,y=1;
	gotoxy(x,y);
	FILE *arq=fopen("dadosMed.txt","r");
	
	if(arq==NULL){
		y+=5;
		x+=30;
		gotoxy(x,y);
		textcolor(4);
		printf("Erro na abertura de arquivo");
		textcolor(15);
		y+=6;
		gotoxy(x,y);
	}
	else
	{
		inicializarDescritor(D);
		do
		{
			op=menu(x,y);
			printf("\n");
			switch(op)
			{
				case 'A':
					if(!feof(arq))
					{
						do
						{
							fgets(linha,400,arq);
							inserirLista(D,linha);		
						}while(!feof(arq));
						clrscr();
						linhas_menu();
						y=14;x=45;gotoxy(x,y);
						textcolor(10);
						printf("Paises Inseridos");
						textcolor(15);
						y++;gotoxy(x,y);						
					}
					else
					{
						clrscr();
						linhas_menu();
						y=14;x=43;gotoxy(x,y);
						textcolor(10);
						printf("Arquivo ja inserido");
						textcolor(15);
						y++;gotoxy(x,y);
					}
					getch();
						break;
				case 'B':
						clrscr();
						linhas_menu();
						y=12;x=40;gotoxy(x,y);
						printf("Digite o nome de um pais:");
						fflush(stdin);
						y++;gotoxy(x,y);
						gets(pais);
						y++;gotoxy(x,y);
						excluirPais(D,pais,x,y);
						break;
				case 'C':
						clrscr();
						linhas_menu();
						y=12;x=38;gotoxy(x,y);
						printf("Digite o nome de um medicamento:");
						fflush(stdin);
						y++;gotoxy(x,y);
						fflush(stdin);
						gets(medicamento);
						excluirMedicamento(D,medicamento,x,y);
						break;
				case 'D':
						clrscr();
						linhas_menu();
						y=14;x=45;gotoxy(x,y);
						textcolor(4);
						if(D.inicio!=NULL){
							textcolor(10);
							gerarRelatorio(D);
							printf("Relatorio gerado");
						}
						else
							printf("Listas Vazias");
						textcolor(15);
						getch();
						break;
				case 'E':
						clrscr();
						linhas_menu();
						y=12;x=41;gotoxy(x,y);
						printf("Digite o nome de um pais:");
						fflush(stdin);
						y++;gotoxy(x,y);
						fflush(stdin);
						gets(pais);
						Pais=paisCadastrado(D,pais);
						if(Pais==NULL)
						{	
							y+=2;x+=5;gotoxy(x,y);
							textcolor(4);
							if(D.inicio!=NULL)
								printf("Pais nao encontrado");
							else
								printf("Fila Vazia");
							textcolor(15);
							y++;gotoxy(x,y);
							getch();
						}
						else
						{
							clrscr();
							textcolor(12);
							x=(100-strlen(pais))/2;y=2;gotoxy(x,y);
							printf("%s",pais);
							textcolor(15);
							y++;gotoxy(x,y);
							exibirMedicamentosPais(Pais,x,y);
							getch();
						}
						break;
				case 'F':
						clrscr();
						linhas_menu();
						y=12;x=36;gotoxy(x,y);
						printf("Digite o nome de um medicamento");
						fflush(stdin);
						y++;gotoxy(x,y);			
						fflush(stdin);
						gets(medicamento);
						exibirMedicamento(D,medicamento,x,y);
						break;
			}
			clrscr();
		}while(op!=27);
	}
}

