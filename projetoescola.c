#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct {
	long long int matricula;
	char nome[50];
	char sexo;
	int dia;
	int mes;
	int ano;
	long long int CPF;
} aluno;

void menu_principal();
void cadastro_aluno(aluno ListaAlunos[40], int *indexAluno, int *opcao);
void deletar_aluno(aluno ListaAlunos[40], int *indexAluno);
void listar_alunos(aluno ListaAlunos[40], int *indexAluno);


int main()
{
	int sair = 0;
	int opcao = -1;
	int indexAluno = 0;
	aluno ListaAlunos[40];
	while(!sair) {
		menu_principal();
		scanf(" %i", &opcao);
		printf("\n");
		switch(opcao) {

		case 0:
			sair = 1;
			printf("obrigado pela preferência");
			break;
		case 1:
			printf("módulo aluno\n\n");
			int SairAluno = 0;
			while(!SairAluno) {
				opcao = -1;
				printf("0 - voltar\n");
				printf("1 - registrar aluno(a)\n");
				printf("2 - remover aluno(a)\n");
				printf("3 - editar informações do aluno(a)\n");
				printf("4 - listar alunos(a)\n");

				scanf(" %i", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairAluno = 1;
					break;

				case 1:
					cadastro_aluno(ListaAlunos, &indexAluno, &opcao);
					break;
				case 2:
					deletar_aluno(ListaAlunos, &indexAluno);
					break;
				case 3:
					cadastro_aluno(ListaAlunos, &indexAluno, &opcao);
					break;
				case 4:
					listar_alunos(ListaAlunos, &indexAluno);
					break;

				default:
					printf("opção inválida\n\n");
				}
			}
			break;
		case 2:
			printf("módulo professor\n");
			break;
		case 3:
			printf("módulo disciplinas\n");
			break;
		case 4:
			printf("listas e relatórios\n");
			break;
		default:
			printf("opção inválida\n\n");
		}
	}
}

void menu_principal() {
	printf("projeto escola\n\n");
	printf("0 - sair\n");
	printf("1 - aluno\n");
	printf("2 - professor\n");
	printf("3 - disciplina\n");
	printf("4 - relatórios\n");
}

void cadastro_aluno(aluno ListaAlunos[40], int *indexAluno, int *opcao) {

	int indexCadastro;
	int kcont;
	long long int MatriculaPesquisada;
	int encontrado = 0;
	switch(*opcao) {

	case(1):
		indexCadastro = *indexAluno;
		break;

	case(3):
		printf("digite a matricula do aluno a ser editado\n");
		scanf(" %lld", &MatriculaPesquisada);
		for(int icont=0; icont<=*indexAluno; icont++) {
			if(MatriculaPesquisada==ListaAlunos[icont].matricula) {
				indexCadastro = icont;
				encontrado=1;
				printf("editando ");
				if(ListaAlunos[indexCadastro].sexo == 'f')
					printf("aluna");
				else
					printf("aluno");
				printf(" %s\n", ListaAlunos[icont].nome);
				break;
			}
		}
	}
	if(encontrado==1 || *opcao!=3) {
		printf("digite a matrícula do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[indexCadastro].matricula);

		printf("digite o nome do aluno(a)\n");
		scanf(" %49[^\n]", ListaAlunos[indexCadastro].nome);

		printf("digite o sexo do aluno(a) (m/f)\n");
		scanf(" %c", &ListaAlunos[indexCadastro].sexo);

		printf("digite a data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
		scanf(" %d %d %d", &ListaAlunos[indexCadastro].dia, &ListaAlunos[indexCadastro].mes, &ListaAlunos[indexCadastro].ano);

		printf("digite o CPF do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[indexCadastro].CPF);

		if(*opcao==1) {
			(*indexAluno)++;
			if(ListaAlunos[indexCadastro].sexo == 'f')
				printf("aluna %s cadastrada\n", ListaAlunos[indexCadastro].nome);
			else
				printf("aluno %s cadastrado\n", ListaAlunos[indexCadastro].nome);
		}
		if(*opcao==3) {
			if(ListaAlunos[indexCadastro].sexo == 'f')
				printf("aluna %s atualizada\n", ListaAlunos[indexCadastro].nome);
			else
				printf("aluno %s atualizado\n", ListaAlunos[indexCadastro].nome);

		}
	}
}

void deletar_aluno(aluno ListaAlunos[40], int *indexAluno) {
	long long int MatriculaPesquisada;
	int encontrado = 0;
	printf("digite a matricula do aluno a ser deletado\n");
	scanf(" %lld", &MatriculaPesquisada);
	for(int icont=0; icont<*indexAluno; icont++) {
		if(MatriculaPesquisada==ListaAlunos[icont].matricula) {
			if(ListaAlunos[icont].sexo == 'f')
				printf("aluna %s deletada\n", ListaAlunos[icont].nome);
			else
				printf("aluno %s deletado\n", ListaAlunos[icont].nome);
			for(int jcont=icont; jcont<*indexAluno; jcont++) {
				ListaAlunos[jcont]=ListaAlunos[jcont + 1];
			}
			(*indexAluno)--;
			encontrado=1;
			break;
		}
	}
	if(encontrado==0)
		printf("aluno não encontrado\n");
}

void listar_alunos(aluno ListaAlunos[40], int *indexAluno) {
	for(int icont=0; icont<*indexAluno; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lli\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
	}
}
