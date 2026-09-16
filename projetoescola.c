#include<stdio.h>
#include<stdlib.h>

typedef struct {
	long long int matricula;
	char nome[50];
	char sexo;
	int dia;
	int mes;
	int ano;
	long long int CPF;
} aluno;

typedef struct {
	long long int matricula;
	char nome[50];
	char sexo;
	int dia;
	int mes;
	int ano;
	long long int CPF;
} professor;

typedef struct {
	char nome[50];
	char codigo[8];
	int semestre;
	professor professorAssociado;
	aluno alunosAssociados[40];
} disciplina;

void menu_principal();

void cadastro_aluno(aluno ListaAlunos[], int *indexAluno, int *opcao);
void deletar_aluno(aluno ListaAlunos[], int *indexAluno);
void listar_alunos(aluno ListaAlunos[], int *indexAluno);

void cadastro_professor(professor ListaProfessores[], int *indexProfessor, int *opcao);
void deletar_professor(professor ListaProfessores[], int *indexProfessor);
void listar_professores(professor ListaProfessores[], int *indexProfessor);

void cadastro_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, int *opcao);
void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina);
void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina);
void listar_disciplinaDetalhado(disciplina ListaDisciplinas[], *indexDisciplina);

int main()
{
	int sair = 0;
	int opcao = -1;
	int indexAluno = 0;
	int indexProfessor = 0;
	int indexDisciplina = 0;
	aluno ListaAlunos[40+1];
	professor ListaProfessores[40+1];
	disciplina ListaDisciplinas[40+1];

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
				printf("4 - listar alunos(as)\n");

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
			int SairProfessor = 0;
			while(!SairProfessor) {
				opcao = -1;
				printf("0 - voltar\n");
				printf("1 - registrar professor(a)\n");
				printf("2 - remover professor(a)\n");
				printf("3 - editar informações do professor(a)\n");
				printf("4 - listar professores(as)\n");

				scanf(" %i", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairProfessor = 1;
					break;

				case 1:
					cadastro_professor(ListaProfessores, &indexProfessor, &opcao);
					break;
				case 2:
					deletar_professor(ListaProfessores, &indexProfessor);
					break;
				case 3:
					cadastro_professor(ListaProfessores, &indexProfessor, &opcao);
					break;
				case 4:
					listar_professores(ListaProfessores, &indexProfessor);
					break;

				default:
					printf("opção inválida\n\n");
				}
			}
			break;
		case 3:
			printf("módulo disciplína\n");
			int SairDisciplina = 0;
			while(!SairDisciplina) {
				opcao = -1;
				printf("0 - voltar\n");
				printf("1 - registrar disciplína\n");
				printf("2 - remover disciplína\n");
				printf("3 - editar informações da disciplína\n");
				printf("4 - listar disciplínas)\n");

				scanf(" %i", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairDisciplina = 1;
					break;

				case 1:
					cadastro_disciplina(ListaDisciplinas, &indexDisciplina, &opcao);
					break;
				case 2:
					deletar_disciplina(ListaDisciplinas, &indexDisciplina);
					break;
				case 3:
					cadastro_disciplina(ListaDisciplinas, &indexDisciplina, &opcao);
					break;
				case 4:
					listar_disciplinas(ListaDisciplinas, &indexDisciplina);
					break;
                case 5:
					listar_disciplinaDetalhado(ListaDisciplinas, &indexDisciplina);
					break;
				default:
					printf("opção inválida\n\n");
				}
			}
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

void cadastro_aluno(aluno ListaAlunos[], int *indexAluno, int *opcao) {

	int indexCadastro = -1;
	long long int MatriculaPesquisada;
	int encontrado = 0;

	switch(*opcao) {

	case(1):
		if(*indexAluno >= 40) {
			printf("limite de alunos atingido\n");
			return;
		}

		indexCadastro = *indexAluno;
		break;

	case(3):
		printf("digite a matricula do aluno a ser editado\n");
		scanf(" %lld", &MatriculaPesquisada);

		if(MatriculaPesquisada <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont=0; icont<*indexAluno; icont++) {
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
		break;
	}


	if(*opcao==1) {
		printf("digite a matrícula do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[indexCadastro].matricula);

		if(ListaAlunos[indexCadastro].matricula <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			if(ListaAlunos[icont].matricula == ListaAlunos[indexCadastro].matricula) {
				printf("matricula invalida\n");
				return;
			}
		}

		printf("digite o nome do aluno(a)\n");
		scanf(" %49[^\n]", ListaAlunos[indexCadastro].nome);

		if(ListaAlunos[indexCadastro].nome[0] == '\0') {
			printf("nome invalido\n");
			return;
		}

		printf("digite o sexo do aluno(a) (m/f)\n");
		scanf(" %c", &ListaAlunos[indexCadastro].sexo);

		if(ListaAlunos[indexCadastro].sexo != 'm' && ListaAlunos[indexCadastro].sexo != 'f') {
			printf("sexo invalido\n");
			return;
		}

		int diasDoMes;
		printf("digite a data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
		scanf(" %d %d %d", &ListaAlunos[indexCadastro].dia, &ListaAlunos[indexCadastro].mes, &ListaAlunos[indexCadastro].ano);

		if(ListaAlunos[indexCadastro].ano <= 0) {
			printf("ano inválido\n");
			return;
		}

		switch(ListaAlunos[indexCadastro].mes) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			diasDoMes = 31;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			diasDoMes = 30;
			break;

		case 2:
			diasDoMes = 28;
			if((ListaAlunos[indexCadastro].ano % 400) == 0 || ((ListaAlunos[indexCadastro].ano % 4) == 0 && (ListaAlunos[indexCadastro].ano % 100) != 0))
				diasDoMes = 29;
			break;

		default:
			printf("mês inválido\n");
			return;
		}

		if(ListaAlunos[indexCadastro].dia > diasDoMes || ListaAlunos[indexCadastro].dia <= 0) {
			printf("dia inválido\n");
			return;
		}

		printf("digite o CPF do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[indexCadastro].CPF);

		if(ListaAlunos[indexCadastro].CPF <= 0) {
			printf("CPF invalido\n");
			return;
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			if(ListaAlunos[icont].CPF == ListaAlunos[indexCadastro].CPF) {
				printf("CPF invalido\n");
				return;
			}
		}

		(*indexAluno)++;

		if(ListaAlunos[indexCadastro].sexo == 'f')
			printf("aluna %s cadastrada\n", ListaAlunos[indexCadastro].nome);
		else
			printf("aluno %s cadastrado\n", ListaAlunos[indexCadastro].nome);
	}


	if(*opcao==3 && encontrado == 1) {
		printf("digite a nova matrícula do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[40].matricula);

		if(ListaAlunos[40].matricula <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			if(icont != indexCadastro && ListaAlunos[icont].matricula == ListaAlunos[40].matricula) {
				printf("matricula invalida\n");
				return;
			}
		}

		printf("digite o novo nome do aluno(a)\n");
		scanf(" %49[^\n]", ListaAlunos[40].nome);

		if(ListaAlunos[40].nome[0] == '\0') {
			printf("nome invalido\n");
			return;
		}

		printf("digite o novo sexo do aluno(a) (m/f)\n");
		scanf(" %c", &ListaAlunos[40].sexo);

		if(ListaAlunos[40].sexo != 'm' && ListaAlunos[40].sexo != 'f') {
			printf("sexo invalido\n");
			return;
		}

		int diasDoMes;
		printf("digite a nova data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
		scanf(" %d %d %d", &ListaAlunos[40].dia, &ListaAlunos[40].mes, &ListaAlunos[40].ano);

		if(ListaAlunos[40].ano <= 0) {
			printf("ano inválido\n");
			return;
		}

		switch(ListaAlunos[40].mes) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			diasDoMes = 31;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			diasDoMes = 30;
			break;

		case 2:
			diasDoMes = 28;
			if((ListaAlunos[40].ano % 400) == 0 || ((ListaAlunos[40].ano % 4) == 0 && (ListaAlunos[40].ano % 100) != 0))
				diasDoMes = 29;
			break;

		default:
			printf("mês inválido\n");
			return;
		}

		if(ListaAlunos[40].dia > diasDoMes || ListaAlunos[40].dia <= 0) {
			printf("dia inválido\n");
			return;
		}

		printf("digite o novo CPF do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[40].CPF);

		if(ListaAlunos[40].CPF <= 0) {
			printf("CPF invalido\n");
			return;
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			if(icont != indexCadastro && ListaAlunos[icont].CPF == ListaAlunos[40].CPF) {
				printf("CPF invalido\n");
				return;
			}
		}

		ListaAlunos[indexCadastro] = ListaAlunos[40];

		if(ListaAlunos[indexCadastro].sexo == 'f')
			printf("aluna %s atualizada\n", ListaAlunos[indexCadastro].nome);
		else
			printf("aluno %s atualizado\n", ListaAlunos[indexCadastro].nome);
	}

	if(*opcao == 3 && encontrado == 0) {
		printf("aluno(a) não encontrado\n");
	}
}


void deletar_aluno(aluno ListaAlunos[], int *indexAluno) {
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
		printf("aluno(a) não encontrado\n");
}

void listar_alunos(aluno ListaAlunos[], int *indexAluno) {
	for(int icont=0; icont<*indexAluno; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lli\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
	}
}

void cadastro_professor(professor ListaProfessores[], int *indexProfessor, int *opcao) {
	int indexCadastro = -1;
	long long int MatriculaPesquisada;
	int encontrado = 0;

	switch(*opcao) {

	case(1):
		if(*indexProfessor >= 40) {
			printf("limite de professores atingido\n");
			return;
		}

		indexCadastro = *indexProfessor;
		break;

	case(3):
		printf("digite a matricula do professor a ser editado\n");
		scanf(" %lld", &MatriculaPesquisada);

		if(MatriculaPesquisada <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont=0; icont<*indexProfessor; icont++) {
			if(MatriculaPesquisada==ListaProfessores[icont].matricula) {
				indexCadastro = icont;
				encontrado=1;
				printf("editando ");
				if(ListaProfessores[indexCadastro].sexo == 'f')
					printf("professora");
				else
					printf("professor");
				printf(" %s\n", ListaProfessores[icont].nome);
				break;
			}
		}
		break;
	}


	if(*opcao==1) {
		printf("digite a matrícula do professor(a)\n");
		scanf(" %lld", &ListaProfessores[indexCadastro].matricula);

		if(ListaProfessores[indexCadastro].matricula <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont = 0; icont < *indexProfessor; icont++) {
			if(ListaProfessores[icont].matricula == ListaProfessores[indexCadastro].matricula) {
				printf("matricula invalida\n");
				return;
			}
		}

		printf("digite o nome do professor(a)\n");
		scanf(" %49[^\n]", ListaProfessores[indexCadastro].nome);

		if(ListaProfessores[indexCadastro].nome[0] == '\0') {
			printf("nome invalido\n");
			return;
		}

		printf("digite o sexo do professor(a) (m/f)\n");
		scanf(" %c", &ListaProfessores[indexCadastro].sexo);

		if(ListaProfessores[indexCadastro].sexo != 'm' && ListaProfessores[indexCadastro].sexo != 'f') {
			printf("sexo invalido\n");
			return;
		}

		int diasDoMes;
		printf("digite a data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
		scanf(" %d %d %d", &ListaProfessores[indexCadastro].dia, &ListaProfessores[indexCadastro].mes, &ListaProfessores[indexCadastro].ano);

		if(ListaProfessores[indexCadastro].ano <= 0) {
			printf("ano inválido\n");
			return;
		}

		switch(ListaProfessores[indexCadastro].mes) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			diasDoMes = 31;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			diasDoMes = 30;
			break;

		case 2:
			diasDoMes = 28;
			if((ListaProfessores[indexCadastro].ano % 400) == 0 || ((ListaProfessores[indexCadastro].ano % 4) == 0 && (ListaProfessores[indexCadastro].ano % 100) != 0))
				diasDoMes = 29;
			break;

		default:
			printf("mês inválido\n");
			return;
		}

		if(ListaProfessores[indexCadastro].dia > diasDoMes || ListaProfessores[indexCadastro].dia <= 0) {
			printf("dia inválido\n");
			return;
		}

		printf("digite o CPF do professor(a)\n");
		scanf(" %lld", &ListaProfessores[indexCadastro].CPF);

		if(ListaProfessores[indexCadastro].CPF <= 0) {
			printf("CPF invalido\n");
			return;
		}

		for(int icont = 0; icont < *indexProfessor; icont++) {
			if(ListaProfessores[icont].CPF == ListaProfessores[indexCadastro].CPF) {
				printf("CPF invalido\n");
				return;
			}
		}

		(*indexProfessor)++;

		if(ListaProfessores[indexCadastro].sexo == 'f')
			printf("professora %s cadastrada\n", ListaProfessores[indexCadastro].nome);
		else
			printf("professor %s cadastrado\n", ListaProfessores[indexCadastro].nome);
	}


	if(*opcao==3 && encontrado == 1) {
		printf("digite a nova matrícula do professor(a)\n");
		scanf(" %lld", &ListaProfessores[40].matricula);

		if(ListaProfessores[40].matricula <= 0) {
			printf("matricula invalida\n");
			return;
		}

		for(int icont = 0; icont < *indexProfessor; icont++) {
			if(icont != indexCadastro && ListaProfessores[icont].matricula == ListaProfessores[40].matricula) {
				printf("matricula invalida\n");
				return;
			}
		}

		printf("digite o novo nome do professor(a)\n");
		scanf(" %49[^\n]", ListaProfessores[40].nome);

		if(ListaProfessores[40].nome[0] == '\0') {
			printf("nome invalido\n");
			return;
		}

		printf("digite o novo sexo do professor(a) (m/f)\n");
		scanf(" %c", &ListaProfessores[40].sexo);

		if(ListaProfessores[40].sexo != 'm' && ListaProfessores[40].sexo != 'f') {
			printf("sexo invalido\n");
			return;
		}

		int diasDoMes;
		printf("digite a nova data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
		scanf(" %d %d %d", &ListaProfessores[40].dia, &ListaProfessores[40].mes, &ListaProfessores[40].ano);

		if(ListaProfessores[40].ano <= 0) {
			printf("ano inválido\n");
			return;
		}

		switch(ListaProfessores[40].mes) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			diasDoMes = 31;
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			diasDoMes = 30;
			break;

		case 2:
			diasDoMes = 28;
			if((ListaProfessores[40].ano % 400) == 0 || ((ListaProfessores[40].ano % 4) == 0 && (ListaProfessores[40].ano % 100) != 0))
				diasDoMes = 29;
			break;

		default:
			printf("mês inválido\n");
			return;
		}

		if(ListaProfessores[40].dia > diasDoMes || ListaProfessores[40].dia <= 0) {
			printf("dia inválido\n");
			return;
		}

		printf("digite o novo CPF do professor(a)\n");
		scanf(" %lld", &ListaProfessores[40].CPF);

		if(ListaProfessores[40].CPF <= 0) {
			printf("CPF invalido\n");
			return;
		}

		for(int icont = 0; icont < *indexProfessor; icont++) {
			if(icont != indexCadastro && ListaProfessores[icont].CPF == ListaProfessores[40].CPF) {
				printf("CPF invalido\n");
				return;
			}
		}

		ListaProfessores[indexCadastro] = ListaProfessores[40];

		if(ListaProfessores[indexCadastro].sexo == 'f')
			printf("professora %s atualizada\n", ListaProfessores[indexCadastro].nome);
		else
			printf("professor %s atualizado\n", ListaProfessores[indexCadastro].nome);
	}

	if(*opcao == 3 && encontrado == 0) {
		printf("professor(a) não encontrado\n");
	}
}

void deletar_professor(professor ListaProfessores[], int *indexProfessor) {
	long long int MatriculaPesquisada;
	int encontrado = 0;
	printf("digite a matricula do professor a ser deletado\n");
	scanf(" %lld", &MatriculaPesquisada);
	for(int icont=0; icont<*indexProfessor; icont++) {
		if(MatriculaPesquisada==ListaProfessores[icont].matricula) {
			if(ListaProfessores[icont].sexo == 'f')
				printf("professora %s deletada\n", ListaProfessores[icont].nome);
			else
				printf("professor %s deletado\n", ListaProfessores[icont].nome);
			for(int jcont=icont; jcont<*indexProfessor; jcont++) {
				ListaProfessores[jcont]=ListaProfessores[jcont + 1];
			}
			(*indexProfessor)--;
			encontrado=1;
			break;
		}
	}
	if(encontrado==0)
		printf("professor(a) não encontrado\n");
}

void listar_professor(professor ListaProfessores[], int *indexProfessores) {
	for(int icont=0; icont<*indexProfessor; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lli\n\n", ListaProfessores[icont].nome, ListaProfessores[icont].matricula, ListaProfessores[icont].sexo, ListaProfessores[icont].dia, ListaProfessores[icont].mes, ListaProfessores[icont].ano, ListaProfessores[icont].CPF);
	}
}
