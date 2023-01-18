#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
struct TpPessoa
{
	char cod[20],sexo,data[12];
	TpPessoa *prox;
};


struct TpMedicamento
{
	char medicamento[200];
	TpMedicamento *prox;
	TpPessoa *pessoas;
};

struct TpPais
{
	char pais[40];
	TpPais *ant,*prox;
	TpMedicamento *medicamentos;
};

struct TpDescritor
{
	TpPais *inicio,*fim;
};

struct TpElementoArq
{
	char cod[20],sexo,medicamento[200],data[12],pais[40];
};

//************************************ DESCRITOR ************************************************
void inicializarDescritor(TpDescritor &descritor)
{
	descritor.inicio=NULL;
	descritor.fim=NULL;	
}

//*********************************** NOVAS CAIXAS ***************************************************
TpPais *NovoPais(char nome[])
{
	TpPais *pCaixa=new TpPais;
	pCaixa->ant=NULL;
	pCaixa->prox=NULL;
	pCaixa->medicamentos=NULL;
	strcpy(pCaixa->pais,nome);
	return pCaixa;
}

TpMedicamento *NovoMedicamento(char nome[])
{
	TpMedicamento *pCaixa=new TpMedicamento;
	pCaixa->prox=NULL;
	pCaixa->pessoas=NULL;
	strcpy(pCaixa->medicamento,nome);
	return pCaixa;
}

TpPessoa *NovaPessoa(char cod[],char sexo,char data[])
{
	TpPessoa *pCaixa=new TpPessoa;
	pCaixa->prox=NULL;
	strcpy(pCaixa->cod,cod);
	pCaixa->sexo=sexo;
	strcpy(pCaixa->data,data);
	return pCaixa;
}
//*************************************** MENU ********************************************
//QUADRO
void linhas_menu()
{
	int x,y,a;
	x=32;
	y=8;
	gotoxy(x,y);
	textcolor(14);
	for( ;x<75;x++)
	{
		gotoxy(x,y);
		printf("*");
	}
	
	for( ;y<22;y++)
	{
		gotoxy(x,y);
		printf("*");
	}
	
	for( ;x>32;x--)
	{
		gotoxy(x,y);
		printf("*");
	}
	
	for( ;y>8;y--)
	{
		gotoxy(x,y);
		printf("*");
	}
	textcolor(15);
}
char menu(int &x,int&y)
{
	linhas_menu();
	x=48;y=10;gotoxy(x,y);
	textcolor(8);
	printf("** MENU **");
	textcolor(15);
	x=38;y+=2;gotoxy(x,y);
	printf("[A] Inserir pessoa");
	y++;gotoxy(x,y);
	printf("[B] Excluir um pais");
	y++;gotoxy(x,y);
	printf("[C] Excluir medicamento");
	y++;gotoxy(x,y);
	printf("[D] Gerar relatorio");
	y++;gotoxy(x,y);
	printf("[E] Exibir um pais");
	y++;gotoxy(x,y);
	printf("[F] Exibir medicamento");
	y+=3;gotoxy(x,y);
	printf("Digite uma opcao:");
	return toupper(getche());
}

//*************************************** PAISES *****************************************************
//Procurar se um país já está cadastrado
TpPais *paisCadastrado(TpDescritor descritor,char nome[])
{
	TpPais *atual;
	atual=descritor.inicio;
	if(descritor.inicio!=NULL)
	{	
		while(strcmp(atual->pais,nome)<0 && atual->prox!=NULL)
		{
			atual=atual->prox;
		}
		if(strcmp(atual->pais,nome)==0)
			return atual;
		else
			return NULL;
	}
	return NULL;
	
}

//Inserir um país de forma ordenada
void inserirPais(TpDescritor &descritor,char pais[])
{
	TpPais *atual,*novoPais;
	
	novoPais=NovoPais(pais);
	if(descritor.inicio==NULL)
	{
		descritor.inicio=novoPais;
		descritor.fim=novoPais;
	}
	else
	{
		if(strcmp(descritor.inicio->pais,novoPais->pais)>0)
		{
			novoPais->prox=descritor.inicio;
			descritor.inicio->ant=novoPais;
			descritor.inicio=novoPais;
		}
		else
		{
			if(strcmp(descritor.fim->pais,novoPais->pais)<0)
			{
				novoPais->ant=descritor.fim;
				descritor.fim->prox=novoPais;
				descritor.fim=novoPais;
			}
			else
			{
				atual=descritor.inicio->prox;
				while(strcmp(atual->pais,novoPais->pais)<0)
					atual=atual->prox;
					
				novoPais->prox=atual;
				novoPais->ant=atual->ant;
				atual->ant->prox=novoPais;
				atual->ant=novoPais;
			}
		}
	}
}

//Excluir um determinado país
void excluirMedicamentosPais(TpPais *Pais);
void excluirPais(TpDescritor &descritor,char nome[],int x,int y)
{
	TpPais *Pais;
	char op;
	Pais=paisCadastrado(descritor,nome);
	if(Pais==NULL){
		
		textcolor(4);
		if(descritor.inicio==NULL)
		{
			y+=2;x+=8;gotoxy(x,y);
			printf("Lista Vazia");
		}
		else
		{
			y+=2;x+=4;gotoxy(x,y);
			printf("Pais nao encontrado");
		}
		textcolor(15);
		y++;gotoxy(x,y);
		getch();
	}
	else
	{
		clrscr();
		linhas_menu();
		y=10;x=34;gotoxy(x,y);
		if(Pais->medicamentos!=NULL)
		{
			printf("Pais: %s",Pais->pais);
			y++;gotoxy(x,y);
			printf("Excluir?<S/N>");
			op=toupper(getche());
		}
		else
			op='S';
		if(op=='S')
		{
			excluirMedicamentosPais(Pais);
			
			if(Pais->ant==NULL)
			{
				Pais->prox->ant=NULL;
				descritor.inicio=Pais->prox;
				delete(Pais);
			}
			else
			{
				if(Pais->prox==NULL)
				{
					Pais->ant->prox=NULL;
					descritor.fim=Pais->ant;
					delete(Pais);
				}
				else
				{
					Pais->ant->prox=Pais->prox;
					Pais->prox->ant=Pais->ant;
					delete(Pais);
				}
			}
			textcolor(10);
			y+=4;x+=11;gotoxy(x,y);
			printf("Pais foi deletado",nome);
			textcolor(15);
			y++;gotoxy(x,y);
			getch();
		}
		else
		{
			textcolor(4);
			y+=4;x+=11;gotoxy(x,y);
			printf("Pais nao deletado",nome);
			textcolor(15);
			y++;gotoxy(x,y);
			getch();
		}
	}
}

//************************************ MEDICAMENTOS ****************************************************
//Procurar se um medicamento ja esta cadastrado em um pais
TpMedicamento *medicamentoCadastrado(TpPais *pais,char med[])
{
	TpMedicamento *atual;
	if(pais->medicamentos!=NULL)
	{
		atual=pais->medicamentos;	
		while(strcmp(atual->medicamento,med)!=0 && atual->prox!=NULL)
		{
			atual=atual->prox;
		}
		if(strcmp(atual->medicamento,med)==0)
			return atual;
		else
			return NULL;
	}
	return NULL;
}

//Inserir um medicamento em um pais
void inserirMedicamento(TpPais *Pais,char med[])
{
	TpMedicamento *novoMed,*atual;
	novoMed=NovoMedicamento(med);
	if(Pais->medicamentos==NULL)
		Pais->medicamentos=novoMed;
	else
	{
		atual=Pais->medicamentos;
		while(atual->prox!=NULL)
			atual=atual->prox;
		atual->prox=novoMed;
	}
	
}

//Exibir medicamentos utilizados em um país
void exibirMedicamentosPais(TpPais *Pais,int &x,int &y)
{
	TpMedicamento *atual;
	y++;x=15;gotoxy(x,y);
	if(Pais->medicamentos==NULL)
		printf("Nenhum medicamento cadastrado");
	else
	{
		atual=Pais->medicamentos;
		while(atual!=NULL)
		{
			printf("     ->%s",atual->medicamento);
			y++;gotoxy(x,y);
			atual=atual->prox;
		}
	}
}

//Exibir as pessoas que utilizam um determinado medicamento
void exibirPessoas(TpPessoa *Pessoa,char pais[],int &x,int &y);
void exibirMedicamento(TpDescritor descritor,char nome[],int &x,int &y)
{
	TpPais *atualP;
	int achou=0;
	clrscr();
	
	TpMedicamento *Med;
	if(descritor.inicio==NULL)
	{
		clrscr();
		linhas_menu();
		y=14;x=45;gotoxy(x,y);
		textcolor(4);
		printf("Lista Vazia");
		textcolor(15);
		
		y++;gotoxy(x,y);
	}
	else
	{
		atualP=descritor.inicio;
		x=(100-strlen(nome))/2;y=3;gotoxy(x,y);
		textcolor(12);
		printf("%s",nome);
		textcolor(15);
		y+=2;x=20;gotoxy(x,y);
		while(atualP!=NULL){
			Med=medicamentoCadastrado(atualP,nome);
			if(Med!=NULL)
			{
				achou=1;
				exibirPessoas(Med->pessoas,atualP->pais,x,y);
			}
			atualP=atualP->prox;
		}
		if(achou==0)
		{
			clrscr();
			linhas_menu();
			y=14;x=40;gotoxy(x,y);
			textcolor(4);
			printf("Medicamento nao cadastrado");
			textcolor(15);
			
			y++;gotoxy(x,y);
		}
	}
	getch();
}

//Excluir todos os medicamentos de um país
void excluirPessoasMedicamento(TpMedicamento *Med);
void excluirMedicamentosPais(TpPais *Pais)
{
	TpMedicamento *Med;
	while(Pais->medicamentos!=NULL)
	{
		Med=Pais->medicamentos;
		if(Med->pessoas!=NULL)
		{
			excluirPessoasMedicamento(Med);
		}
		Pais->medicamentos=Pais->medicamentos->prox;
		delete(Med);
	}
}

//Excluir determinado medicamento de todos os países
void excluirMedicamento(TpDescritor descritor,char nome[],int &x,int &y)
{
	TpPais *atualP,*auxP;
	TpMedicamento *antM,*atualM;
	int achou=0;
	char pais[50],resp;
	
	if(descritor.inicio!=NULL)
	{
		atualP=descritor.inicio;
		while(atualP!=NULL)
		{
			if(atualP->medicamentos!=NULL)
			{
				if(strcmp(atualP->medicamentos->medicamento,nome)==0)
				{
					clrscr();
					linhas_menu();
					y=12;x=34;gotoxy(x,y);
					printf("Excluir do pais: %s <S/N>",atualP->pais);
					
					if(toupper(getche())=='S')
					{
						atualM=atualP->medicamentos;
						atualP->medicamentos=atualP->medicamentos->prox;
						excluirPessoasMedicamento(atualM);
						delete(atualM);
						y+=4;x+=10;gotoxy(x,y);
						textcolor(10);
						printf("Medicamento excluido");
						textcolor(15);
					}
					else
					{
						y+=4;x+=6;gotoxy(x,y);
						textcolor(4);
						printf("Medicamento nao excluido");
						textcolor(15);
					}
					getch();
					achou=1;
				}
				else
				{
					atualM=atualP->medicamentos;
					while(atualM->prox!=NULL && strcmp(atualM->medicamento,nome)!=0)
					{
						antM=atualM;
						atualM=atualM->prox;
					}
					if(strcmp(atualM->medicamento,nome)==0)
					{
						clrscr();
						linhas_menu();
						y=12;x=34;gotoxy(x,y);
						printf("Excluir do pais: %s <S/N>",atualP->pais);
						if(toupper(getche())=='S')
						{
							antM->prox=atualM->prox;
							excluirPessoasMedicamento(atualM);
							delete(atualM);
							y+=4;x+=10;gotoxy(x,y);
							textcolor(10);
							printf("Medicamento excluido");
							textcolor(15);
						}
						else
						{
							y+=4;x+=6;gotoxy(x,y);
							textcolor(4);
							printf("Medicamento nao excluido");
							textcolor(15);
						}
						getch();
						achou=1;
					}
				}
				auxP=atualP;
				atualP=atualP->prox;
				if(auxP->medicamentos==NULL)
				{
					y++;x-=5;gotoxy(x,y);
					printf("O pais nao possui medicamentos");
					getch();
					strcpy(pais,auxP->pais);
					excluirPais(descritor,pais,x,y);
				}
			}
			else
				atualP=atualP->prox;
			
		}
		if(achou!=1)
		{
			clrscr();
			linhas_menu();
			y=14;x=40;gotoxy(x,y);
			textcolor(4);
			printf("Medicamento nao encontrado");
			textcolor(15);
			getch();
		}
		
	}
	else
	{
		y=16;x=48;gotoxy(x,y);
		textcolor(4);
		printf("Lista Vazia");
		getch();
		textcolor(15);
	}
}
//*************************************** PESSOAS *****************************************************

void inserirPessoa (TpMedicamento *Med,TpElementoArq elem)
{
	TpPessoa *atual,*novo;
	novo=NovaPessoa(elem.cod,elem.sexo,elem.data);
	if(Med->pessoas==NULL)
	{
		Med->pessoas=novo;
	}
	else
	{
		atual=Med->pessoas;
		while(atual->prox!=NULL)
			atual=atual->prox;
		atual->prox=novo;
	}
}

void exibirPessoas(TpPessoa *Pessoa,char pais[],int &x,int &y)
{
	if(Pessoa!=NULL)
	{
		printf("->COD: %s    Sexo: %c    DATA: %s  PAIS: %s",Pessoa->cod,Pessoa->sexo,Pessoa->data,pais);
		y++;gotoxy(x,y);
		Pessoa=Pessoa->prox;
		exibirPessoas(Pessoa,pais,x,y);
	}
}

void excluirPessoasMedicamento(TpMedicamento *Med)
{
	TpPessoa *atual;
	
	if(Med->pessoas!=NULL)
	{
		while(Med->pessoas!=NULL)
		{
			atual=Med->pessoas;
			Med->pessoas=Med->pessoas->prox;
			delete(atual);
		}	
	}
}
//*************************************** LISTAS ******************************************************

//Separando dados da linha
void separarInformacao(char linha[],TpElementoArq &reg)
{
	int pos=0,p=0;
	
	//Código da pessoa
	while(linha[pos]!=';')
	{
		reg.cod[p]=linha[pos];
		p++;
		pos++;
	}
	reg.cod[pos]='\0';
	reg.sexo=linha[++pos];
	p=0;
	pos+=2;
	//Se houver mais de uma medicina na linha
	if(linha[pos]=='"')
	{
		pos++;
		while(linha[pos]!='"')
		{
			reg.medicamento[p]=linha[pos];
			pos++;
			p++;
		}
		reg.medicamento[p]='\0';
		pos+=2;
	}
	//Se houver apenas uma medicina
	else
	{
		while(linha[pos]!=';')
		{
			reg.medicamento[p]=linha[pos];
			pos++;
			p++;
		}
		reg.medicamento[p]='\0';
		pos++;
	}
	p=0;
	//Data da última compra
	while(linha[pos]!=';')
	{
		reg.data[p]=linha[pos];
		pos++;
		p++;
	}
	reg.data[p]='\0';
	p=0;
	pos++;
	//Pegar o país
	while(pos<strlen(linha) && linha[pos]!='\n')
	{
		reg.pais[p]=linha[pos];
		pos++;
		p++;
	}
	reg.pais[p]='\0';
}
void inserirLista(TpDescritor &descritor,char linha[])
{
	TpElementoArq reg;
	TpPais *pais;
	TpMedicamento *med;
	int pos=0,p=0;
	char medicina[200];
		
	separarInformacao(linha,reg);
	
	//inserindo no pais
	if(paisCadastrado(descritor,reg.pais)==NULL)
	{
		inserirPais(descritor,reg.pais);
	}
	//inserindo o medicamento
	pais=paisCadastrado(descritor,reg.pais);
	pos=0;
	while(pos<strlen(reg.medicamento))
	{	
		p=0;
		while(pos<strlen(reg.medicamento) && reg.medicamento[pos]!=';')
		{
			medicina[p]=reg.medicamento[pos];
			pos++;
			p++;
		}
		medicina[p]='\0';
		if(medicamentoCadastrado(pais,medicina)==NULL)
		{
			inserirMedicamento(pais,medicina);		
		}
		med=medicamentoCadastrado(pais,medicina);
		//Inserir a pessoa
		inserirPessoa(med,reg);
		if(pos<strlen(reg.medicamento))
			pos+=2;
	}
}
 //************************************* RELATÓRIO ********************************************

char codigoDentroArquivo(TpPais *Pais,TpMedicamento *Med,char cod[])
{
	int achou=0;
	TpMedicamento *atual;
	TpPessoa *Pessoa;
	atual=Pais->medicamentos;
	while(strcmp(atual->medicamento,Med->medicamento)!=0 && achou==0)
	{
		Pessoa=atual->pessoas;
		while(Pessoa!=NULL && achou==0)
		{
			if(strcmp(Pessoa->cod,cod)==0)
				achou=1;
			Pessoa=Pessoa->prox;
		}
		atual=atual->prox;
	}
	return achou==1;
}

void procurarOutrosMedicamentosPessoa(FILE *arq,TpMedicamento *Med,char cod[])
{
	TpPessoa *Pessoa;
	Med=Med->prox;
	while(Med!=NULL)
	{
		Pessoa=Med->pessoas;
		while(Pessoa!=NULL && strcmp(Pessoa->cod,cod)!=0)
		{
			Pessoa=Pessoa->prox;
		}
		if(Pessoa!=NULL)
		{
			fprintf(arq," %s,",Med->medicamento);
		}
		Med=Med->prox;
	}
}
void gerarRelatorio(TpDescritor descritor)
{
	TpPais *Pais;
	TpMedicamento *Med,*Med2;
	TpPessoa *Pessoa;
	Pais=descritor.inicio;
	int achou;
	FILE *arq=fopen("dadosRelat.txt","w");
	while(Pais!=NULL)
	{
		achou=0;
		fprintf(arq,"***** %s ******\n",Pais->pais);
		fprintf(arq,"	--->Feminino\n");

		Med=Pais->medicamentos;
		while(Med!=NULL)
		{
			Pessoa=Med->pessoas;
			while(Pessoa!=NULL)
			{
				if(Pessoa->sexo=='F')
				{
					if(!codigoDentroArquivo(Pais,Med,Pessoa->cod))
					{
						fprintf(arq,"		==>%s  Data: %s Medicamentos: %s,",Pessoa->cod,Pessoa->data,Med->medicamento);
						procurarOutrosMedicamentosPessoa(arq,Med,Pessoa->cod);
						fprintf(arq,"\n");
						achou=1;
					}
				}
				Pessoa=Pessoa->prox;
			}
			Med=Med->prox;
		}
		if(achou==0)
			fprintf(arq,"		Nenhum cadastrado\n");
		Med=Pais->medicamentos;
		achou=0;
		fprintf(arq,"	--->Masculino\n");
		while(Med!=NULL)
		{
			Pessoa=Med->pessoas;
			while(Pessoa!=NULL)
			{
				if(Pessoa->sexo=='M')
				{
					if(!codigoDentroArquivo(Pais,Med,Pessoa->cod))
					{
						fprintf(arq,"		==>%s  Data: %s Medicamentos: %s,",Pessoa->cod,Pessoa->data,Med->medicamento);
						procurarOutrosMedicamentosPessoa(arq,Med,Pessoa->cod);
						fprintf(arq,"\n");
						achou=1;
					}
				}
				Pessoa=Pessoa->prox;
			}
			Med=Med->prox;
		}
		Pais=Pais->prox;
		if(achou==0)
			fprintf(arq,"		Nenhum cadastrado\n");
	}
	fclose(arq);
}

