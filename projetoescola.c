#include<stdio.h>
#include<stdlib.h>
#define Max_alunos 40
#define Max_professores 40
#define Max_disciplinas 40

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
} disciplina;

void menu_principal();

int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno);
void deletar_aluno(aluno ListaAlunos[], int *indexAluno);
void listar_alunos(aluno ListaAlunos[], int *indexAluno);
int pesquisar_aluno_por_matricula(aluno ListaAlunos[], int *indexAluno);
void disciplinar_aluno(int DisciplinaEAlunos [] [], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno);
void desdisciplinar_aluno(int DisciplinaEAlunos [] [], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno);

int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor);
void deletar_professor(professor ListaProfessores[], int *indexProfessor);
void listar_professores(professor ListaProfessores[], int *indexProfessor);
int pesquisar_professor_por_matricula(professor ListaProfessores[], int *indexProfessor);

int inserir_dados_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor);
void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina);
void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[]);
void listar_disciplina_Detalhado(disciplina ListaDisciplinas[], int *indexDisciplina);
int pesquisar_matricula_por_codigo(professor ListaDisciplinas[], int *indexDisciplina);

int main()
{
	int sair = 0;
	int opcao = -1;
	int indexAluno = 0;
	int indexProfessor = 0;
	int indexDisciplina = 0;
	aluno ListaAlunos[Max_alunos+1];
	professor ListaProfessores[Max_professores+1];
	disciplina ListaDisciplinas[Max_disciplinas+1];
	int DisciplinaEAlunos [Max_disciplinas+1] [Max_alunos+1];

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
				printf("5 - cadastrar aluno(a) à uma disciplína\n");
				printf("6 - remover aluno(a) de uma disciplína\n");

				scanf(" %i", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairAluno = 1;
					break;

				case 1:
					if(inserir_dados_aluno(ListaAlunos, &indexAluno) == 1) {
						ListaAlunos[indexAluno] = ListaAlunos[Max_alunos];
						indexAluno++;
					}
					break;
				case 2:
					deletar_aluno(ListaAlunos, &indexAluno);
					break;
				case 3:
					int icont = pesquisar_aluno_por_matricula (ListaAlunos[], *indexAluno);
					if(icont) {
						printf("editando ");
						if(ListaAlunos[icont].sexo == 'f')
							printf("aluna");
						else
							printf("aluno");
						printf(" %s\n", ListaAlunos[icont].nome);

						if(inserir_dados_aluno(ListaAlunos, &indexAluno) == 1)
							ListaAlunos[indexAluno] = ListaAlunos[Max_alunos];
					}
					break;
				case 4:
					listar_alunos(ListaAlunos, &indexAluno);
					break;
				case 5:
					disciplinar_aluno(DisciplinaEAlunos [] [], ListaDisciplinas[], *indexDisciplina, ListaAlunos[], *indexAluno);
					break;
				case 6:
					desdisciplinar_aluno(DisciplinaEAlunos [] [], ListaDisciplinas[], *indexDisciplina, ListaAlunos[], *indexAluno);
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
					if(inserir_dados_professor(ListaProfessores, &indexProfessor) == 1) {
						ListaProfessores[indexProfessor] = ListaProfessores[Max_professores];
						indexProfessor++;
					}
					break;
				case 2:
					deletar_professor(ListaProfessores, &indexProfessor);
					break;
				case 3:
					int icont = pesquisar_professor_por_matricula (ListaProfessores[], *indexProfessor);
					if(icont) {
						printf("editando ");
						if(ListaProfessores[icont].sexo == 'f')
							printf("professora");
						else
							printf("professor");
						printf(" %s\n", ListaProfessores[icont].nome);

						if(inserir_dados_professor(ListaProfessores, &indexProfessor) == 1)
							ListaProfessores[indexProfessor] = ListaProfessores[Max_professores];
					}
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
				printf("4 - listar disciplínas\n");
				printf("5 - listar detalhado\n");
				printf("6 - cadastrar aluno(a) à uma disciplína\n");
				printf("7 - remover aluno(a) de uma disciplína\n");

				scanf(" %i", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairDisciplina = 1;
					break;

				case 1:
					if(inserir_dados_disciplina( ListaDisciplinas[], *indexDisciplina, ListaProfessores[], *indexProfessor) == 1) {
						ListaDisciplinas[indexDisciplina] = ListaDisciplinas[Max_disciplinas];
						indexDisciplina++;
					}
					break;
				case 2:
					deletar_disciplina(ListaDisciplinas, &indexDisciplina);
					break;
				case 3:
					int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas[], *indexDisciplina);
					if(icont) {
						printf("editando disciplína %s\n", ListaDisciplinas[icont].nome);

						if(inserir_dados_disciplina(ListaDisciplinas[], *indexDisciplina, ListaProfessores[], *indexProfessor) == 1)
							ListaDisciplinas[indexDisciplina] = ListaDisciplinas[Max_disciplinas];
					}
					break;
				case 4:
					listar_disciplinas(ListaDisciplinas, &indexDisciplina);
					break;
				case 5:
					listar_disciplinaDetalhado(ListaDisciplinas, &indexDisciplina);
					break;
				case 6:
					disciplinar_aluno(DisciplinaEAlunos [] [], ListaDisciplinas[], *indexDisciplina, ListaAlunos[], *indexAluno);
					break;
				case 7:
					desdisciplinar_aluno(DisciplinaEAlunos [] [], ListaDisciplinas[], *indexDisciplina, ListaAlunos[], *indexAluno);
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
	return 0;
}

void menu_principal() {
	printf("projeto escola\n\n");
	printf("0 - sair\n");
	printf("1 - aluno\n");
	printf("2 - professor\n");
	printf("3 - disciplina\n");
	printf("4 - relatórios\n");
}

//parte dos alunos______________________________________________________________________________________________________

int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno) {

	printf("digite a matrícula do aluno(a)\n");
	scanf(" %lld", &ListaAlunos[Max_alunos].matricula);

	if(ListaAlunos[Max_alunos].matricula <= 0) {
		printf("matricula invalida\n");
		return 0;
	}

	for(int icont = 0; icont < *indexAluno; icont++) {
		if(ListaAlunos[icont].matricula == ListaAlunos[Max_alunos].matricula) {
			printf("matricula invalida\n");
			return 0;
		}
	}

	printf("digite o nome do aluno(a)\n");
	scanf(" %49[^\n]", ListaAlunos[Max_alunos].nome);

	if(ListaAlunos[Max_alunos].nome[0] == '\0') {
		printf("nome invalido\n");
		return 0;
	}

	printf("digite o sexo do aluno(a) (m/f)\n");
	scanf(" %c", &ListaAlunos[Max_alunos].sexo);

	if(ListaAlunos[Max_alunos].sexo != 'm' && ListaAlunos[Max_alunos].sexo != 'f') {
		printf("sexo invalido\n");
		return 0;
	}

	int diasDoMes;
	printf("digite a data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
	scanf(" %d %d %d", &ListaAlunos[Max_alunos].dia, &ListaAlunos[Max_alunos].mes, &ListaAlunos[Max_alunos].ano);

	if(ListaAlunos[Max_alunos].ano <= 0) {
		printf("ano inválido\n");
		return 0;
	}

	switch(ListaAlunos[Max_alunos].mes) {
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
		if((ListaAlunos[Max_alunos].ano % 400) == 0 || ((ListaAlunos[Max_alunos].ano % 4) == 0 && (ListaAlunos[Max_alunos].ano % 100) != 0))
			diasDoMes = 29;
		break;

	default:
		printf("mês inválido\n");
		return 0;
	}

	if(ListaAlunos[Max_alunos].dia > diasDoMes || ListaAlunos[Max_alunos].dia <= 0) {
		printf("dia inválido\n");
		return 0;
	}

	printf("digite o CPF do aluno(a)\n");
	scanf(" %lld", &ListaAlunos[Max_alunos].CPF);

	if(ListaAlunos[Max_alunos].CPF <= 0) {
		printf("CPF invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexAluno; icont++) {
		if(ListaAlunos[icont].CPF == ListaAlunos[Max_alunos].CPF) {
			printf("CPF invalido\n");
			return 0;
		}
	}

	return 1;
}

int pesquisar_aluno_por_matricula (aluno ListaAlunos[], int *indexAluno) {
	long long int MatriculaPesquisada = 0;
	int encontrado = 0;
	printf("digite a matricula do(a) aluno(a) a ser editado(a)\n");
	scanf(" %lld", &MatriculaPesquisada);

	if(MatriculaPesquisada > 0) {
		for(int icont=0; icont<*indexAluno; icont++) {
			if(MatriculaPesquisada==ListaAlunos[icont].matricula) {
				return icont;
			}
		}
	}
	printf("aluno não encontrado\n");
	return 0;
}
void deletar_aluno(aluno ListaAlunos[], int *indexAluno) {
	int icont = pesquisar_aluno_por_matricula(ListaAlunos[], *indexAluno);
	if(ListaAlunos[icont].sexo == 'f')
		printf("aluna %s deletada\n", ListaAlunos[icont].nome);
	else
		printf("aluno %s deletado\n", ListaAlunos[icont].nome);
	for(int jcont=icont; jcont<*indexAluno; jcont++) {
		ListaAlunos[jcont]=ListaAlunos[jcont + 1];
	}
	(*indexAluno)--;
}

void listar_alunos(aluno ListaAlunos[], int *indexAluno) {
	for(int icont=0; icont<*indexAluno; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lli\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
	}
}

void disciplinar_aluno(int DisciplinaEAlunos [] [], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno) {
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas[], *indexDisciplina);
	int jcont = pesquisar_aluno_por_matricula(ListaAlunos[], *indexAluno);
	DisciplinaEAlunos [icont] [jcont] = 1;
}
void desdisciplinar_aluno(int DisciplinaEAlunos [] [], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno) {
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas[], *indexDisciplina);
	int jcont = pesquisar_aluno_por_matricula(ListaAlunos[], *indexAluno);
	DisciplinaEAlunos [icont] [jcont] = 0;
}
//parte dos professores:______________________________________________________________________________________________________

int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor) {

	printf("digite a matrícula do professor(a)\n");
	scanf(" %lld", &ListaProfessores[Max_professores].matricula);

	if(ListaProfessores[Max_professores].matricula <= 0) {
		printf("matricula invalida\n");
		return 0;
	}

	for(int icont = 0; icont < *indexProfessor; icont++) {
		if(ListaProfessores[icont].matricula == ListaProfessores[Max_professores].matricula) {
			printf("matricula invalida\n");
			return 0;
		}
	}

	printf("digite o nome do professor(a)\n");
	scanf(" %49[^\n]", ListaProfessores[Max_professores].nome);

	if(ListaProfessores[Max_professores].nome[0] == '\0') {
		printf("nome invalido\n");
		return 0;
	}

	printf("digite o sexo do professor(a) (m/f)\n");
	scanf(" %c", &ListaProfessores[Max_professores].sexo);

	if(ListaProfessores[Max_professores].sexo != 'm' && ListaProfessores[Max_professores].sexo != 'f') {
		printf("sexo invalido\n");
		return 0;
	}

	int diasDoMes;
	printf("digite a data de nascimento dia(dd) mês (mm) e ano (aaaa)\n");
	scanf(" %d %d %d", &ListaProfessores[Max_professores].dia, &ListaProfessores[Max_professores].mes, &ListaProfessores[Max_professores].ano);

	if(ListaProfessores[Max_professores].ano <= 0) {
		printf("ano inválido\n");
		return 0;
	}

	switch(ListaProfessores[Max_professores].mes) {
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
		if((ListaProfessores[Max_professores].ano % 400) == 0 || ((ListaProfessores[Max_professores].ano % 4) == 0 && (ListaProfessores[Max_professores].ano % 100) != 0))
			diasDoMes = 29;
		break;

	default:
		printf("mês inválido\n");
		return 0;
	}

	if(ListaProfessores[Max_professores].dia > diasDoMes || ListaProfessores[Max_professores].dia <= 0) {
		printf("dia inválido\n");
		return 0;
	}

	printf("digite o CPF do professor(a)\n");
	scanf(" %lld", &ListaProfessores[Max_professores].CPF);

	if(ListaProfessores[Max_professores].CPF <= 0) {
		printf("CPF invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexProfessor; icont++) {
		if(ListaProfessores[icont].CPF == ListaProfessores[Max_professores].CPF) {
			printf("CPF invalido\n");
			return 0;
		}
	}

	return 1;
}

int pesquisar_professor_por_matricula(professor ListaProfessores[], int *indexProfessor) {
	long long int MatriculaPesquisada = 0;
	int encontrado = 0;
	printf("digite a matricula do(a) professor(a) a ser editado(a)\n");
	scanf(" %lld", &MatriculaPesquisada);

	if(MatriculaPesquisada > 0) {
		for(int icont=0; icont<*indexProfessor; icont++) {
			if(MatriculaPesquisada==ListaProfessores[icont].matricula) {
				return icont;
			}
		}
	}
	printf("professor não encontrado\n");
	return 0;
}

void deletar_professor(professor ListaProfessores[], int *indexProfessor) {
	int icont = pesquisar_professor_por_matricula(ListaProfessores[], *indexProfessor);
	if(ListaProfessores[icont].sexo == 'f')
		printf("professora %s deletada\n", ListaProfessores[icont].nome);
	else
		printf("professor %s deletado\n", ListaProfessores[icont].nome);
	for(int jcont=icont; jcont<*indexProfessor; jcont++) {
		ListaProfessores[jcont]=ListaProfessores[jcont + 1];
	}
	(*indexProfessor)--;
}

void listar_professores(professor ListaProfessores[], int *indexProfessor) {
	for(int icont=0; icont<*indexProfessor; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lli\n\n", ListaProfessores[icont].nome, ListaProfessores[icont].matricula, ListaProfessores[icont].sexo, ListaProfessores[icont].dia, ListaProfessores[icont].mes, ListaProfessores[icont].ano, ListaProfessores[icont].CPF);
	}
}

//parte das disciplínas:______________________________________________________________________________________________________

int inserir_dados_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor) {
	printf("digite o nome da disciplina)\n");
	scanf(" %lld", &ListaDisciplinas[Max_disciplinas].nome);

	if(ListaDisciplinas[Max_disciplinas].nome <= 0) {
		printf("nome invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexDisciplina; icont++) {
		if(ListaDisciplinas[icont].nome == ListaDisciplinas[Max_disciplinas].nome) {
			printf("nome invalido\n");
			return 0;
		}
	}

	printf("digite o semestre\n");
	scanf(" %c", &ListaDisciplinas[Max_disciplinas].semestre);

	if(ListaDisciplinas[Max_disciplinas].semestre <= 0 || ListaDisciplinas[Max_disciplinas].semestre > 10) {
		printf("semestre invalido\n");
		return 0;
	}

	printf("digite o codigo da disciplina\n");
	scanf(" %lld", &ListaDisciplinas[Max_disciplinas].codigo);

	if(ListaDisciplinas[Max_disciplinas].codigo <= 0) {
		printf("codigo invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexDisciplina; icont++) {
		if(ListaDisciplinas[icont].codigo == ListaDisciplinas[Max_disciplinas].codigo) {
			printf("codigo invalido\n");
			return 0;
		}
	}

	printf("digite a matricula do professor(a) associado(a)\n");
	int icont = pesquisar_professor_por_matricula (ListaProfessores[], *indexProfessor);
	if(icont) {
		ListaDisciplinas[Max_disciplinas].professorAssociado = ListaProfessores[icont]
		        else
			        return icont;

		return 1;
	}

	int pesquisar_disciplina_por_codigo(disciplina ListaDisciplinas[], int *indexDisciplina) {
		long long int CodigoPesquisado = 0;
		int encontrado = 0;
		printf("digite o codigo da disciplina a ser editada\n");
		scanf(" %lld", &CodigoPesquisado);

		if(CodigoPesquisado > 0) {
			for(int icont=0; icont<*indexDisciplina; icont++) {
				if(CodigoPesquisado==ListaDisciplinas[icont].matricula) {
					return icont;
				}
			}
		}
		printf("disciplina não encontrada\n");
		return 0;
	}

	void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina) {
		int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas[], *indexDisciplina);
		printf("disciplina %s deletada\n", ListaDisciplinas[icont].nome);
		for(int jcont=icont; jcont<*indexDisciplina; jcont++) {
			ListaDisciplinas[jcont]=ListaDisciplinas[jcont + 1];
		}
		(*indexDisciplina)--;
	}

	void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[]) {
		for(int icont=0; icont<*indexDisciplina; icont++) {
			printf("nome: %s\ncodigo: %s\nsemestre: %d\n", ListaDisciplinas[icont].nome, ListaDisciplinas[icont].codigo, ListaDisciplinas[icont].semestre, ListaProfessores[icont].professorAssociado.nome);
		}
	}
	void listar_disciplinas_Detalhado(disciplina ListaDisciplinas[], int *indexDisciplina) {

	}
