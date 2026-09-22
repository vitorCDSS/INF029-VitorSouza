#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max_alunos 40
#define Max_professores 40
#define Max_disciplinas 40#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
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
	long long int matriculaProfessor;
	int vagas;
} disciplina;

void menu_principal();

int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno, int *excecao);
void deletar_aluno(aluno ListaAlunos[], int *indexAluno, int *indexDisciplina, int DisciplinaEAlunos[][Max_alunos], long long int *Vies);
void listar_alunos(aluno ListaAlunos[], int *indexAluno);
void filtrar_alunos_sexo(aluno ListaAlunos[], int *indexAluno);
void filtrar_alunos_poucas_matriculas(aluno ListaAlunos[], int *indexAluno, int DisciplinaEAlunos[][Max_alunos], int *indexDisciplina);
void filtrar_aniversariante_do_mes(aluno ListaAlunos[], int *indexAluno, professor ListaProfessores[], int *indexProfessor, int *mesAtual);
void ordenar_alunos_nome(aluno ListaAlunos[], int *indexAluno);
void ordenar_alunos_nascismento(aluno ListaAlunos[], int *indexAluno);
int pesquisar_aluno_por_matricula(aluno ListaAlunos[], int *indexAluno, long long int *Vies);
void disciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno, long long int *Vies);
void desdisciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno, long long int *Vies);
void listar_por_nome_pesquisado (aluno ListaAlunos[], int *indexAluno, professor ListaProfessores[], int *indexProfessor);
void para_minusculo(char *destino, char *origem);

int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor, int *excecao);
void deletar_professor(professor ListaProfessores[], int *indexProfessor, long long int *Vies);
void listar_professores(professor ListaProfessores[], int *indexProfessor);
void filtrar_professores_sexo(professor ListaProfessores[], int *indexProfessor);
void ordenar_professores_nome(professor ListaProfessores[], int *indexProfessor);
void ordenar_professores_nascismento(professor ListaProfessores[], int *indexProfessor);
int pesquisar_professor_por_matricula(professor ListaProfessores[], int *indexProfessor, long long int *Vies);

int inserir_dados_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, int DisciplinaEAlunos[][Max_alunos], int *indexAluno, int *excecao, long long int *Vies);
void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, int *indexAluno, int DisciplinaEAlunos[][Max_alunos]);
void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, long long int *vies);
void listar_disciplinas_Detalhado(disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, int DisciplinaEAlunos[][Max_alunos], professor ListaProfessores[], int *indexProfessor, long long int *Vies, char Cvies[]);
int pesquisar_disciplina_por_codigo(disciplina ListaDisciplinas[], int *indexDisciplina, char Cvies[]);
void filtrar_disciplina_vagas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, long long int *Vies);

int main()
{
	int sair = 0;
	int opcao = -1;
	int subopcao = -1;
	int excecao = 0;
	long long int Vies = 0;
	time_t tempo_atual = time(NULL);
	struct tm *info_tempo = localtime(&tempo_atual);
	int mesAtual = info_tempo->tm_mon + 1;
	char Cvies[8];
	Cvies[0] = '\0';
	int indexAluno = 0;
	int indexProfessor = 0;
	int indexDisciplina = 0;
	aluno ListaAlunos[Max_alunos+1];
	professor ListaProfessores[Max_professores+1];
	disciplina ListaDisciplinas[Max_disciplinas+1];
	int DisciplinaEAlunos [Max_disciplinas] [Max_alunos];
	for(int icont = 0; icont < Max_disciplinas; icont++) {
		for(int jcont = 0; jcont < Max_alunos; jcont++) {
			DisciplinaEAlunos [icont] [jcont] = 0;
		}
	}
	while(!sair) {
		excecao = 0;
		menu_principal();
		scanf(" %d", &opcao);
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairAluno = 1;
					break;

				case 1:
					excecao = -1;
					if(indexAluno < Max_alunos) {
						if(inserir_dados_aluno(ListaAlunos, &indexAluno, &excecao) == 1) {
							ListaAlunos[indexAluno] = ListaAlunos[Max_alunos];
							indexAluno++;
							if(ListaAlunos[indexAluno-1].sexo == 'f')
								printf("aluna %s cadastrada com sucesso\n", ListaAlunos[indexAluno-1].nome);
							else
								printf("aluno %s cadastrado com sucesso\n", ListaAlunos[indexAluno-1].nome);
						}
					}
					else
						printf("maximo de alunos atingido\n");
					break;
				case 2:
					Vies = 0;
					deletar_aluno(ListaAlunos, &indexAluno, &indexDisciplina, DisciplinaEAlunos, &Vies);
					break;
				case 3:
					Vies=0;
					int icont = pesquisar_aluno_por_matricula (ListaAlunos, &indexAluno, &Vies);
					excecao = icont;
					if(icont >= 0) {
						printf("editando ");
						if(ListaAlunos[icont].sexo == 'f')
							printf("aluna");
						else
							printf("aluno");
						printf(" %s\n", ListaAlunos[icont].nome);

						if(inserir_dados_aluno(ListaAlunos, &indexAluno, &excecao) == 1) {
							ListaAlunos[icont] = ListaAlunos[Max_alunos];
							printf("alterações salvas");
						}
					}
					break;
				case 4:
					listar_alunos(ListaAlunos, &indexAluno);
					break;
				case 5:
					Vies = 0;
					disciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				case 6:
					Vies = 0;
					desdisciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				default:
					printf("opção inválida\n\n");
					break;
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairProfessor = 1;
					break;

				case 1:
					excecao = -1;
					if(indexProfessor < Max_professores) {
						if(inserir_dados_professor(ListaProfessores, &indexProfessor, &excecao) == 1) {
							ListaProfessores[indexProfessor] = ListaProfessores[Max_professores];
							indexProfessor++;
							if(ListaProfessores[indexProfessor-1].sexo == 'f')
								printf("professora %s cadastrada com sucesso\n", ListaProfessores[indexProfessor-1].nome);
							else
								printf("professor %s cadastrado com sucesso\n", ListaProfessores[indexProfessor-1].nome);
						}
					}
					else
						printf("maximo de professores atingido\n");
					break;
				case 2:
					deletar_professor(ListaProfessores, &indexProfessor, &Vies);
					break;
				case 3:
					Vies=0;
					int icont = pesquisar_professor_por_matricula (ListaProfessores, &indexProfessor, &Vies);
					excecao = icont;
					if(icont >= 0) {
						printf("editando ");
						if(ListaProfessores[icont].sexo == 'f')
							printf("professora");
						else
							printf("professor");
						printf(" %s\n", ListaProfessores[icont].nome);

						if(inserir_dados_professor(ListaProfessores, &indexProfessor, &excecao) == 1)
							ListaProfessores[icont] = ListaProfessores[Max_professores];
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairDisciplina = 1;
					break;

				case 1:
					excecao = -1;
					Vies = 0;
					if(indexDisciplina < Max_disciplinas) {
						if(inserir_dados_disciplina( ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, DisciplinaEAlunos, &indexAluno, &excecao, &Vies) == 1) {
							ListaDisciplinas[indexDisciplina] = ListaDisciplinas[Max_disciplinas];
							indexDisciplina++;
							printf("disciplina %s cadastrada com sucesso\n", ListaDisciplinas[indexDisciplina-1].nome);
						}
					}
					else
						printf("maximo de disciplinas atingido\n");

					break;
				case 2:
					deletar_disciplina(ListaDisciplinas, &indexDisciplina, &indexAluno, DisciplinaEAlunos);
					break;
				case 3:
					Vies = 0;
					int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, &indexDisciplina, "");
					excecao = icont;
					if(icont >= 0) {
						printf("editando disciplína %s\n", ListaDisciplinas[icont].nome);

						if(inserir_dados_disciplina(ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, DisciplinaEAlunos, &indexAluno, &excecao, &Vies) == 1)
							ListaDisciplinas[icont] = ListaDisciplinas[Max_disciplinas];
					}
					break;
				case 4:
					listar_disciplinas(ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, &Vies);
					break;
				case 5:
					listar_disciplinas_Detalhado(ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, DisciplinaEAlunos, ListaProfessores, &indexProfessor, &Vies, Cvies);
					break;
				case 6:
					Vies = 0;
					disciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					Vies = 0;
					break;
				case 7:
					Vies = 0;
					desdisciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				default:
					printf("opção inválida\n\n");
					break;
				}
			}
			break;
		case 4:
			printf("listas e relatórios\n");
			int SairRelatorio = 0;
			while(!SairRelatorio) {
				opcao = -1;
				printf("0 - voltar\n");
				printf("1 - listar alunos ordenados\n");
				printf("2 - filtrar alunos\n");
				printf("3 - listar professores ordenados\n");
				printf("4 - filtrar professores por sexo\n");
				printf("5 - pesquisar por nome\n");
				printf("6 - aniversariante do mês\n");
				printf("7 - listar disciplinas com mais de 40 vagas\n");

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {
				case 0:
					SairDisciplina = 1;
					break;
				case 1:
					subopcao = 0;
					printf("1 - ordenar por nome\n2 - ordenar por data de nascimento");
					scanf("%d", &subopcao);
					switch(subopcao) {
					case 1:
						ordenar_alunos_nome(ListaAlunos, &indexAluno);
						break;
					case 2:
						ordenar_alunos_nascismento(ListaAlunos, &indexAluno);
						break;
					default:
						printf("opção inválida\n\n");
						break;
					}
					break;
				case 2:
					subopcao = 0;
					printf("1 - filtrar por sexo\n2 - alunos com menos de 3 disciplinas");
					scanf("%d", &subopcao);
					switch(subopcao) {
					case 1:
						filtrar_alunos_sexo(ListaAlunos, &indexAluno);
						break;
					case 2:
						filtrar_alunos_poucas_matriculas(ListaAlunos, &indexAluno, DisciplinaEAlunos, &indexDisciplina);
						break;
					default:
						printf("opção inválida\n\n");
						break;
					}
				case 3:
					subopcao = 0;
					printf("1 - ordenar por nome\n2 - ordenar por data de nascimento");
					scanf("%d", &subopcao);
					switch(subopcao) {
					case 1:
						ordenar_professores_nome(ListaProfessores, &indexProfessor);
						break;
					case 2:
						ordenar_professores_nascismento(ListaProfessores, &indexProfessor);
						break;
					default:
						printf("opção inválida\n\n");
						break;
					}
					break;
				case 4:
					filtrar_professores_sexo(ListaProfessores, &indexProfessor);
					break;
				case 5:
					listar_por_nome_pesquisado (ListaAlunos, &indexAluno, ListaProfessores, &indexProfessor);
					break;
				}
			case 6:
				filtrar_aniversariante_do_mes(ListaAlunos, &indexAluno, ListaProfessores, &indexProfessor, &mesAtual);
				break;
			case 7:
			    filtrar_disciplina_vagas(ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, &Vies);
			    break;
			default:
				printf("opção inválida\n\n");
				break;
			}
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

//parte dos alunos______________________________________________________________________________________________________

int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno, int *excecao) {

	printf("digite a matrícula do aluno(a)\n");
	scanf(" %lld", &ListaAlunos[Max_alunos].matricula);

	if(ListaAlunos[Max_alunos].matricula <= 0) {
		printf("matricula invalida\n");
		return 0;
	}

	for(int icont = 0; icont < *indexAluno; icont++) {
		if(ListaAlunos[icont].matricula == ListaAlunos[Max_alunos].matricula && icont != *excecao) {
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
		if(ListaAlunos[icont].CPF == ListaAlunos[Max_alunos].CPF && icont != *excecao) {
			printf("CPF invalido\n");
			return 0;
		}
	}

	return 1;
}

int pesquisar_aluno_por_matricula (aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
	long long int MatriculaPesquisada = 0;
	int encontrado = 0;
	if(*Vies == 0) {
		printf("digite a matricula do(a) aluno(a) que deseja selecionar\n");
		scanf(" %lld", &MatriculaPesquisada);
	}
	else
		MatriculaPesquisada = *Vies;

	if(MatriculaPesquisada > 0) {
		for(int icont=0; icont<*indexAluno; icont++) {
			if(MatriculaPesquisada==ListaAlunos[icont].matricula) {
				return icont;
			}
		}
	}
	printf("aluno não encontrado\n");
	return -1;
}
void deletar_aluno(aluno ListaAlunos[], int *indexAluno, int *indexDisciplina, int DisciplinaEAlunos[][Max_alunos], long long int *Vies) {
	int icont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
	if(icont >= 0) {
		if(ListaAlunos[icont].sexo == 'f')
			printf("aluna %s deletada\n", ListaAlunos[icont].nome);
		else
			printf("aluno %s deletado\n", ListaAlunos[icont].nome);
		for(int jcont=icont; jcont<*indexAluno-1; jcont++) {
			ListaAlunos[jcont]=ListaAlunos[jcont + 1];
			for(int kcont = 0; kcont<*indexDisciplina; kcont++) {
				DisciplinaEAlunos [kcont] [jcont] = DisciplinaEAlunos [kcont] [jcont+1];
			}
		}
		for (int kcont = 0; kcont < Max_disciplinas; kcont++) {
			DisciplinaEAlunos[kcont][*indexAluno-1] = 0;
		}
		(*indexAluno)--;
	}
}
void listar_alunos(aluno ListaAlunos[], int *indexAluno) {
	for(int icont=0; icont<*indexAluno; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
	}
}

void filtrar_alunos_sexo(aluno ListaAlunos[], int *indexAluno) {
	char sexoPesquisado;
	scanf(" %c", sexoPesquisado);
	for(int icont=0; icont<*indexAluno; icont++) {
		if(ListaAlunos[icont].sexo == sexoPesquisado) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
		}
	}
}

void filtrar_aniversariante_do_mes(aluno ListaAlunos[], int *indexAluno, professor ListaProfessores[], int *indexProfessor, int *mesAtual) {
	for(int icont=0; icont<*indexAluno; icont++) {
		if(ListaAlunos[icont].mes == *mesAtual) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
		}
	}
	for(int jcont=0; jcont<*indexProfessor; jcont++) {
		if(ListaProfessores[jcont].mes == *mesAtual) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaProfessores[jcont].nome, ListaProfessores[jcont].matricula, ListaProfessores[jcont].sexo, ListaProfessores[jcont].dia, ListaProfessores[jcont].mes, ListaProfessores[jcont].ano, ListaProfessores[jcont].CPF);
		}
	}
}

void filtrar_alunos_poucas_matriculas(aluno ListaAlunos[], int *indexAluno, int DisciplinaEAlunos[][Max_alunos], int *indexDisciplina) {
	int qtDisciplinas;
	for(int icont=0; icont<*indexAluno; icont++) {
		qtDisciplinas = 0;
		for(int jcont = 0; jcont < *indexDisciplina; jcont++) {
			if(DisciplinaEAlunos[jcont][icont] = 1)
				qtDisciplinas++;
		}
		if(qtDisciplinas < 3) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
		}
	}
}

void ordenar_alunos_nome(aluno ListaAlunos[], int *indexAluno) {
	aluno CopiaListaAlunos[Max_alunos];
	aluno tro_K;
	for (int kcont = 0; kcont < *indexAluno; kcont++) {
		CopiaListaAlunos[kcont] = ListaAlunos[kcont];
	}

	for(int icont = 0; icont < *indexAluno; icont++) {
		for(int jcont = icont; jcont < *indexAluno; jcont++) {
			if(strcmp(CopiaListaAlunos[jcont].nome, CopiaListaAlunos[jcont+1].nome) > 0) {
				tro_K = CopiaListaAlunos[jcont];
				CopiaListaAlunos[jcont] = CopiaListaAlunos[jcont+1];
				CopiaListaAlunos[jcont+1] = tro_K;
			}
		}
	}

	for(int kcont = 0; kcont < *indexAluno; kcont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaAlunos[kcont].nome, CopiaListaAlunos[kcont].matricula, CopiaListaAlunos[kcont].sexo, CopiaListaAlunos[kcont].dia, CopiaListaAlunos[kcont].mes, CopiaListaAlunos[kcont].ano, CopiaListaAlunos[kcont].CPF);
	}
}

void ordenar_alunos_nascismento(aluno ListaAlunos[], int *indexAluno) {
	aluno CopiaListaAlunos[Max_alunos];
	aluno tro_K;
	for (int kcont = 0; kcont < *indexAluno; kcont++) {
		CopiaListaAlunos[kcont] = ListaAlunos[kcont];
	}

	for(int icont = 0; icont < *indexAluno; icont++) {
		for(int jcont = icont; jcont < *indexAluno; jcont++) {
			if(CopiaListaAlunos[jcont].ano*10000+CopiaListaAlunos[jcont].mes*100+CopiaListaAlunos[jcont].dia < CopiaListaAlunos[jcont+1].ano*10000+CopiaListaAlunos[jcont+1].mes*100+CopiaListaAlunos[jcont+1].dia) {
				tro_K = CopiaListaAlunos[jcont];
				CopiaListaAlunos[jcont] = CopiaListaAlunos[jcont+1];
				CopiaListaAlunos[jcont+1] = tro_K;
			}
		}
	}

	for(int kcont = 0; kcont < *indexAluno; kcont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaAlunos[kcont].nome, CopiaListaAlunos[kcont].matricula, CopiaListaAlunos[kcont].sexo, CopiaListaAlunos[kcont].dia, CopiaListaAlunos[kcont].mes, CopiaListaAlunos[kcont].ano, CopiaListaAlunos[kcont].CPF);
	}
}

void disciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, "");
	if(icont >= 0) {
		int jcont = 1;
		printf("digite -1 para sair ou ");
		while(jcont>=0) {
			jcont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
			if(icont >= 0 && jcont >= 0) {
				DisciplinaEAlunos [icont] [jcont] = 1;
			}
		}
	}
}

void desdisciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, "");
	if(icont >= 0) {
		int jcont = 1;
		printf("digite -1 para sair ou ");
		while(jcont>=0) {
			jcont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
			if(icont >= 0 && jcont >=0) {
				DisciplinaEAlunos [icont] [jcont] = 0;
			}
		}
	}
}

void listar_por_nome_pesquisado (aluno ListaAlunos[], int *indexAluno, professor ListaProfessores[], int *indexProfessor) {
	char nomePesquisado[50] = "";
	char nominusculoPesquisado[50] = "";
	char nominusculo[50] = "";
	int encontrado = 0;

	printf("digite o nome ou trecho do nome dos alunos/professores a pesquisar\n");
	scanf(" %s", &nomePesquisado);

	if (strlen(nomePesquisado) < 3) {
		printf("digite pelo menos 3 letras.\n");
		return;
	}
	para_minusculo(nominusculoPesquisado, nomePesquisado);

	for(int icont=0; icont<*indexAluno; icont++) {
		para_minusculo(nominusculo, ListaAlunos[icont].nome);
		if(strstr(nominusculo, nominusculoPesquisado) != 0) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
		}
	}
	for(int jcont=0; jcont<*indexProfessor; jcont++) {
		para_minusculo(nominusculo, ListaProfessores[jcont].nome);
		if(strstr(nominusculo, nominusculoPesquisado) != 0) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaProfessores[jcont].nome, ListaProfessores[jcont].matricula, ListaProfessores[jcont].sexo, ListaProfessores[jcont].dia, ListaProfessores[jcont].mes, ListaProfessores[jcont].ano, ListaProfessores[jcont].CPF);
		}
	}
}

void para_minusculo(char *destino, char *origem) {
	for (int i = 0; origem[i] != '\0'; i++) {
		destino[i] = tolower((unsigned char)origem[i]);
	}
	destino[strlen(origem)] = '\0';
}
//parte dos professores:______________________________________________________________________________________________________

int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor, int *excecao) {

	printf("digite a matrícula do professor(a)\n");
	scanf(" %lld", &ListaProfessores[Max_professores].matricula);

	if(ListaProfessores[Max_professores].matricula <= 0) {
		printf("matricula invalida\n");
		return 0;
	}

	for(int icont = 0; icont < *indexProfessor; icont++) {
		if(ListaProfessores[icont].matricula == ListaProfessores[Max_professores].matricula && icont != *excecao) {
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
		if(ListaProfessores[icont].CPF == ListaProfessores[Max_professores].CPF && icont != *excecao) {
			printf("CPF invalido\n");
			return 0;
		}
	}
	return 1;
}

int pesquisar_professor_por_matricula(professor ListaProfessores[], int *indexProfessor, long long int *Vies) {
	long long int MatriculaPesquisada = 0;
	int encontrado = 0;
	if(*Vies==0) {
		printf("digite a matricula do(a) professor(a) que deseja selecionar\n");
		scanf(" %lld", &MatriculaPesquisada);
	}
	else
		MatriculaPesquisada = *Vies;
	if(MatriculaPesquisada > 0) {
		for(int icont=0; icont<*indexProfessor; icont++) {
			if(MatriculaPesquisada==ListaProfessores[icont].matricula) {
				return icont;
			}
		}
	}
	printf("professor não encontrado\n");
	return -1;
}

void deletar_professor(professor ListaProfessores[], int *indexProfessor, long long int *Vies) {
	int icont = pesquisar_professor_por_matricula(ListaProfessores, indexProfessor, Vies);
	if(icont >= 0) {
		if(ListaProfessores[icont].sexo == 'f')
			printf("professora %s deletada\n", ListaProfessores[icont].nome);
		else
			printf("professor %s deletado\n", ListaProfessores[icont].nome);
		for(int jcont=icont; jcont<*indexProfessor-1; jcont++) {
			ListaProfessores[jcont]=ListaProfessores[jcont + 1];
		}
		(*indexProfessor)--;
	}
}

void listar_professores(professor ListaProfessores[], int *indexProfessor) {
	for(int icont=0; icont<*indexProfessor; icont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaProfessores[icont].nome, ListaProfessores[icont].matricula, ListaProfessores[icont].sexo, ListaProfessores[icont].dia, ListaProfessores[icont].mes, ListaProfessores[icont].ano, ListaProfessores[icont].CPF);
	}
}

void filtrar_professores_sexo(professor ListaProfessores[], int *indexProfessor) {
	char sexoPesquisado;
	scanf(" %c", sexoPesquisado);
	for(int icont=0; icont<*indexProfessor; icont++) {
		if(ListaProfessores[icont].sexo == sexoPesquisado) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaProfessores[icont].nome, ListaProfessores[icont].matricula, ListaProfessores[icont].sexo, ListaProfessores[icont].dia, ListaProfessores[icont].mes, ListaProfessores[icont].ano, ListaProfessores[icont].CPF);
		}
	}
}

void ordenar_professores_nome(professor ListaProfessores[], int *indexProfessor) {
	professor CopiaListaProfessores[Max_professores];
	professor tro_K;
	for (int kcont = 0; kcont < *indexProfessor; kcont++) {
		CopiaListaProfessores[kcont] = ListaProfessores[kcont];
	}

	for(int icont = 0; icont < *indexProfessor; icont++) {
		for(int jcont = icont; jcont < *indexProfessor; jcont++) {
			if(strcmp(CopiaListaProfessores[jcont].nome, CopiaListaProfessores[jcont+1].nome) > 0) {
				tro_K = CopiaListaProfessores[jcont];
				CopiaListaProfessores[jcont] = CopiaListaProfessores[jcont+1];
				CopiaListaProfessores[jcont+1] = tro_K;
			}
		}
	}

	for(int kcont = 0; kcont < *indexProfessor; kcont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaProfessores[kcont].nome, CopiaListaProfessores[kcont].matricula, CopiaListaProfessores[kcont].sexo, CopiaListaProfessores[kcont].dia, CopiaListaProfessores[kcont].mes, CopiaListaProfessores[kcont].ano, CopiaListaProfessores[kcont].CPF);
	}
}

void ordenar_professores_nascismento(professor ListaProfessores[], int *indexProfessor) {
	professor CopiaListaProfessores[Max_professores];
	professor tro_K;
	for (int kcont = 0; kcont < *indexProfessor; kcont++) {
		CopiaListaProfessores[kcont] = ListaProfessores[kcont];
	}

	for(int icont = 0; icont < *indexProfessor; icont++) {
		for(int jcont = icont; jcont < *indexProfessor; jcont++) {
			if(CopiaListaProfessores[jcont].ano*10000+CopiaListaProfessores[jcont].mes*100+CopiaListaProfessores[jcont].dia < CopiaListaProfessores[jcont+1].ano*10000+CopiaListaProfessores[jcont+1].mes*100+CopiaListaProfessores[jcont+1].dia) {
				tro_K = CopiaListaProfessores[jcont];
				CopiaListaProfessores[jcont] = CopiaListaProfessores[jcont+1];
				CopiaListaProfessores[jcont+1] = tro_K;
			}
		}
	}

	for(int kcont = 0; kcont < *indexProfessor; kcont++) {
		printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaProfessores[kcont].nome, CopiaListaProfessores[kcont].matricula, CopiaListaProfessores[kcont].sexo, CopiaListaProfessores[kcont].dia, CopiaListaProfessores[kcont].mes, CopiaListaProfessores[kcont].ano, CopiaListaProfessores[kcont].CPF);
	}
}


//parte das disciplínas:______________________________________________________________________________________________________

int inserir_dados_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, int DisciplinaEAlunos[][Max_alunos], int *indexAluno, int *excecao, long long int *Vies) {
	printf("digite o nome da disciplina)\n");
	scanf(" %49[^\n]", ListaDisciplinas[Max_disciplinas].nome);

	if (ListaDisciplinas[Max_disciplinas].nome[0] == '\0') {
		printf("nome invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexDisciplina; icont++) {
		if(strcmp(ListaDisciplinas[icont].nome, ListaDisciplinas[Max_disciplinas].nome) == 0 && icont != *excecao) {
			printf("nome invalido\n");
			return 0;
		}
	}

	printf("digite o semestre\n");
	scanf(" %d", &ListaDisciplinas[Max_disciplinas].semestre);

	if(ListaDisciplinas[Max_disciplinas].semestre <= 0 || ListaDisciplinas[Max_disciplinas].semestre > 10) {
		printf("semestre invalido\n");
		return 0;
	}

	printf("digite o codigo da disciplina\n");
	scanf(" %7s", ListaDisciplinas[Max_disciplinas].codigo);

	if (ListaDisciplinas[Max_disciplinas].codigo[0] == '\0') {
		printf("codigo invalido\n");
		return 0;
	}

	for(int icont = 0; icont < *indexDisciplina; icont++) {
		if(strcmp(ListaDisciplinas[icont].codigo, ListaDisciplinas[Max_disciplinas].codigo) == 0 && icont != *excecao) {
			printf("codigo invalido\n");
			return 0;
		}
	}

	printf("professor(a) associado(a):\n");
	int icont = pesquisar_professor_por_matricula (ListaProfessores, indexProfessor, Vies);
	if(icont >= 0)
		ListaDisciplinas[Max_disciplinas].matriculaProfessor = ListaProfessores[icont].matricula;
	else
		return 0;

	scanf("%d", &ListaDisciplinas[Max_disciplinas].vagas);
	if(ListaDisciplinas[Max_disciplinas].vagas < 1) {
		printf("a disciplina deve ter alguma vaga");
		return 0;
	}

	if(*excecao >= 0) {
		int qtAlunos = 0;
		for(int icont = 0; icont < *indexAluno; icont++) {
			if(DisciplinaEAlunos[*excecao][icont] == 1)
				qtAlunos++;
		}
		if(ListaDisciplinas[Max_disciplinas].vagas>qtAlunos) {
			printf("existem mais alunos do que a vaga sugerida pode suportar");
		}
	}
	return 1;
}

int pesquisar_disciplina_por_codigo(disciplina ListaDisciplinas[], int *indexDisciplina, char Cvies[]) {
	char CodigoPesquisado[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int encontrado = 0;
	if (Cvies[0] == '\0') {
		printf("digite o codigo da disciplina que deseja selecionar\n");
		scanf(" %7s", CodigoPesquisado);
	}
	else
		strcpy(CodigoPesquisado, Cvies);
	if (CodigoPesquisado[0] != '\0') {
		for(int icont=0; icont<*indexDisciplina; icont++) {
			if(strcmp(CodigoPesquisado, ListaDisciplinas[icont].codigo) == 0) {
				return icont;
			}
		}
	}
	printf("disciplina não encontrada\n");
	return -1;
}

void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, int *indexAluno, int DisciplinaEAlunos[][Max_alunos]) {
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, "");
	if(icont >= 0) {
		printf("disciplina %s deletada\n", ListaDisciplinas[icont].nome);
		for(int jcont=icont; jcont<*indexDisciplina-1; jcont++) {
			ListaDisciplinas[jcont]=ListaDisciplinas[jcont + 1];
			for(int kcont = 0; kcont<*indexAluno; kcont++) {
				DisciplinaEAlunos [jcont] [kcont] = DisciplinaEAlunos [jcont+1] [kcont];
			}
		}
		for (int kcont = 0; kcont < Max_alunos; kcont++) {
			DisciplinaEAlunos[*indexDisciplina-1][kcont] = 0;
		}
		(*indexDisciplina)--;
	}
}
void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, long long int *Vies) {
	for(int icont=0; icont<*indexDisciplina; icont++) {
		*Vies = ListaDisciplinas[icont].matriculaProfessor;
		int jcont = pesquisar_professor_por_matricula(ListaProfessores, indexProfessor, Vies);
		printf("nome: %s\ncodigo: %s\nsemestre: %d\nprofessor associado: %s\n", ListaDisciplinas[icont].nome, ListaDisciplinas[icont].codigo, ListaDisciplinas[icont].semestre, ListaProfessores[jcont].nome);
	}
}
void listar_disciplinas_Detalhado(disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, int DisciplinaEAlunos[][Max_alunos], professor ListaProfessores[], int *indexProfessor, long long int *Vies, char Cvies[]) {
	int qtAlunos = 0;
	int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, Cvies);
	if(icont>=0) {
		*Vies = ListaDisciplinas[icont].matriculaProfessor;
		int jcont = pesquisar_professor_por_matricula(ListaProfessores, indexProfessor, Vies);
		printf("nome: %s\ncodigo: %s\nsemestre: %d\nprofessor associado: %s\n", ListaDisciplinas[icont].nome, ListaDisciplinas[icont].codigo, ListaDisciplinas[icont].semestre, ListaProfessores[jcont].nome);
		printf("alunos registrados:\n");
		for(int jcont=0; jcont < *indexAluno; jcont++) {
			if(DisciplinaEAlunos[icont][jcont] == 1) {
				printf("%s\n%lld\n", ListaAlunos[jcont].nome, ListaAlunos[jcont].matricula);
				qtAlunos++;
			}
		}
		printf("\n");
		if(qtAlunos == 0)
			printf("nenhum\n");
	}
}

void filtrar_disciplina_vagas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, long long int *Vies) {
	for(int icont=0; icont<*indexDisciplina; icont++) {
		if(ListaDisciplinas[icont].vagas >= 40) {
			*Vies = ListaDisciplinas[icont].matriculaProfessor;
			int jcont = pesquisar_professor_por_matricula(ListaProfessores, indexProfessor, Vies);
			printf("nome: %s\ncodigo: %s\nsemestre: %d\nprofessor associado: %s\n", ListaDisciplinas[icont].nome, ListaDisciplinas[icont].codigo, ListaDisciplinas[icont].semestre, ListaProfessores[jcont].nome);
		}
	}
}

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
	long long int matriculaProfessor;
} disciplina;

void menu_principal();

int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno, int *excecao);
void deletar_aluno(aluno ListaAlunos[], int *indexAluno, int *indexDisciplina, int DisciplinaEAlunos[][Max_alunos], long long int *Vies);
void listar_alunos(aluno ListaAlunos[], int *indexAluno);
void ordenar_alunos_nome(aluno ListaAlunos[], int *indexAluno);
void ordenar_alunos_nascismento(aluno ListaAlunos[], int *indexAluno);
int pesquisar_aluno_por_matricula(aluno ListaAlunos[], int *indexAluno, long long int *Vies);
void disciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno, long long int *Vies);
void desdisciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int*indexAluno, long long int *Vies);

int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor, int *excecao);
void deletar_professor(professor ListaProfessores[], int *indexProfessor, long long int *Vies);
void listar_professores(professor ListaProfessores[], int *indexProfessor);
int pesquisar_professor_por_matricula(professor ListaProfessores[], int *indexProfessor, long long int *Vies);

int inserir_dados_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, int *excecao, long long int *vies);
void deletar_disciplina(disciplina ListaDisciplinas[], int *indexDisciplina, int *indexAluno, int DisciplinaEAlunos[][Max_alunos]);
void listar_disciplinas(disciplina ListaDisciplinas[], int *indexDisciplina, professor ListaProfessores[], int *indexProfessor, long long int *vies);
void listar_disciplinas_Detalhado(disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, int DisciplinaEAlunos[][Max_alunos], professor ListaProfessores[], int *indexProfessor, long long int *Vies, char Cvies[]);
int pesquisar_disciplina_por_codigo(disciplina ListaDisciplinas[], int *indexDisciplina, char Cvies[]);

int main()
{
	int sair = 0;
	int opcao = -1;
	int excecao = 0;
	long long int Vies = 0;
	char Cvies[8];
	Cvies[0] = '\0';
	int indexAluno = 0;
	int indexProfessor = 0;
	int indexDisciplina = 0;
	aluno ListaAlunos[Max_alunos+1];
	professor ListaProfessores[Max_professores+1];
	disciplina ListaDisciplinas[Max_disciplinas+1];
	int DisciplinaEAlunos [Max_disciplinas] [Max_alunos];
	for(int icont = 0; icont < Max_disciplinas; icont++) {
		for(int jcont = 0; jcont < Max_alunos; jcont++) {
			DisciplinaEAlunos [icont] [jcont] = 0;
		}
	}
	while(!sair) {
		excecao = 0;
		menu_principal();
		scanf(" %d", &opcao);
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairAluno = 1;
					break;

				case 1:
					excecao = -1;
					if(indexAluno < Max_alunos) {
						if(inserir_dados_aluno(ListaAlunos, &indexAluno, &excecao) == 1) {
							ListaAlunos[indexAluno] = ListaAlunos[Max_alunos];
							indexAluno++;
							if(ListaAlunos[indexAluno-1].sexo == 'f')
								printf("aluna %s cadastrada com sucesso\n", ListaAlunos[indexAluno-1].nome);
							else
								printf("aluno %s cadastrado com sucesso\n", ListaAlunos[indexAluno-1].nome);
						}
					}
					else
						printf("maximo de alunos atingido\n");
					break;
				case 2:
					Vies = 0;
					deletar_aluno(ListaAlunos, &indexAluno, &indexDisciplina, DisciplinaEAlunos, &Vies);
					break;
				case 3:
					Vies=0;
					int icont = pesquisar_aluno_por_matricula (ListaAlunos, &indexAluno, &Vies);
					excecao = icont;
					if(icont >= 0) {
						printf("editando ");
						if(ListaAlunos[icont].sexo == 'f')
							printf("aluna");
						else
							printf("aluno");
						printf(" %s\n", ListaAlunos[icont].nome);

						if(inserir_dados_aluno(ListaAlunos, &indexAluno, &excecao) == 1) {
							ListaAlunos[icont] = ListaAlunos[Max_alunos];
							printf("alterações salvas");
						}
					}
					break;
				case 4:
					listar_alunos(ListaAlunos, &indexAluno);
					break;
				case 5:
					Vies = 0;
					disciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				case 6:
					Vies = 0;
					desdisciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				default:
					printf("opção inválida\n\n");
					break;
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairProfessor = 1;
					break;

				case 1:
					excecao = -1;
					if(indexProfessor < Max_professores) {
						if(inserir_dados_professor(ListaProfessores, &indexProfessor, &excecao) == 1) {
							ListaProfessores[indexProfessor] = ListaProfessores[Max_professores];
							indexProfessor++;
							if(ListaProfessores[indexProfessor-1].sexo == 'f')
								printf("professora %s cadastrada com sucesso\n", ListaProfessores[indexProfessor-1].nome);
							else
								printf("professor %s cadastrado com sucesso\n", ListaProfessores[indexProfessor-1].nome);
						}
					}
					else
						printf("maximo de professores atingido\n");
					break;
				case 2:
					deletar_professor(ListaProfessores, &indexProfessor, &Vies);
					break;
				case 3:
					Vies=0;
					int icont = pesquisar_professor_por_matricula (ListaProfessores, &indexProfessor, &Vies);
					excecao = icont;
					if(icont >= 0) {
						printf("editando ");
						if(ListaProfessores[icont].sexo == 'f')
							printf("professora");
						else
							printf("professor");
						printf(" %s\n", ListaProfessores[icont].nome);

						if(inserir_dados_professor(ListaProfessores, &indexProfessor, &excecao) == 1)
							ListaProfessores[icont] = ListaProfessores[Max_professores];
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

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				case 0:
					SairDisciplina = 1;
					break;

				case 1:
					excecao = -1;
					Vies = 0;
					if(indexDisciplina < Max_disciplinas) {
						if(inserir_dados_disciplina( ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, &excecao, &Vies) == 1) {
							ListaDisciplinas[indexDisciplina] = ListaDisciplinas[Max_disciplinas];
							indexDisciplina++;
							printf("disciplina %s cadastrada com sucesso\n", ListaDisciplinas[indexDisciplina-1].nome);
						}
					}
					else
						printf("maximo de disciplinas atingido\n");

					break;
				case 2:
					deletar_disciplina(ListaDisciplinas, &indexDisciplina, &indexAluno, DisciplinaEAlunos);
					break;
				case 3:
					Vies = 0;
					int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, &indexDisciplina, "");
					excecao = icont;
					if(icont >= 0) {
						printf("editando disciplína %s\n", ListaDisciplinas[icont].nome);

						if(inserir_dados_disciplina(ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, &excecao, &Vies) == 1)
							ListaDisciplinas[icont] = ListaDisciplinas[Max_disciplinas];
					}
					break;
				case 4:
					listar_disciplinas(ListaDisciplinas, &indexDisciplina, ListaProfessores, &indexProfessor, &Vies);
					break;
				case 5:
					listar_disciplinas_Detalhado(ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, DisciplinaEAlunos, ListaProfessores, &indexProfessor, &Vies, Cvies);
					break;
				case 6:
					Vies = 0;
					disciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					Vies = 0;
					break;
				case 7:
					Vies = 0;
					desdisciplinar_aluno(DisciplinaEAlunos, ListaDisciplinas, &indexDisciplina, ListaAlunos, &indexAluno, &Vies);
					break;
				default:
					printf("opção inválida\n\n");
					break;
				}
			}
			break;
		case 4:
			printf("listas e relatórios\n");
			int SairRelatorio = 0;
			while(!SairDisciplina) {
				opcao = -1;
				printf("0 - voltar\n");
				printf("1 - listar alunos ordenados\n"); //nome nascimento
				printf("2 - filtrar alunos\n"); //sexo poucas disciplinas
				printf("3 - listar professores ordenados\n"); //nome nascimento
				printf("4 - filtrar professores por sexo\n"); 
				printf("5 - pesquisar por nome\n"); //alunos e professores
				printf("6 - aniversariante do mês\n"); //alunos e professores
				printf("7 - listar disciplinas com mais de 40 vagas\n");

				scanf(" %d", &opcao);
				printf("\n");
				switch(opcao) {

				}
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

	int inserir_dados_aluno(aluno ListaAlunos[], int *indexAluno, int *excecao) {

		printf("digite a matrícula do aluno(a)\n");
		scanf(" %lld", &ListaAlunos[Max_alunos].matricula);

		if(ListaAlunos[Max_alunos].matricula <= 0) {
			printf("matricula invalida\n");
			return 0;
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			if(ListaAlunos[icont].matricula == ListaAlunos[Max_alunos].matricula && icont != *excecao) {
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
			if(ListaAlunos[icont].CPF == ListaAlunos[Max_alunos].CPF && icont != *excecao) {
				printf("CPF invalido\n");
				return 0;
			}
		}

		return 1;
	}

	int pesquisar_aluno_por_matricula (aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
		long long int MatriculaPesquisada = 0;
		int encontrado = 0;
		if(*Vies == 0) {
			printf("digite a matricula do(a) aluno(a) que deseja selecionar\n");
			scanf(" %lld", &MatriculaPesquisada);
		}
		else
			MatriculaPesquisada = *Vies;

		if(MatriculaPesquisada > 0) {
			for(int icont=0; icont<*indexAluno; icont++) {
				if(MatriculaPesquisada==ListaAlunos[icont].matricula) {
					return icont;
				}
			}
		}
		printf("aluno não encontrado\n");
		return -1;
	}
	void deletar_aluno(aluno ListaAlunos[], int *indexAluno, int *indexDisciplina, int DisciplinaEAlunos[][Max_alunos], long long int *Vies) {
		int icont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
		if(icont >= 0) {
			if(ListaAlunos[icont].sexo == 'f')
				printf("aluna %s deletada\n", ListaAlunos[icont].nome);
			else
				printf("aluno %s deletado\n", ListaAlunos[icont].nome);
			for(int jcont=icont; jcont<*indexAluno-1; jcont++) {
				ListaAlunos[jcont]=ListaAlunos[jcont + 1];
				for(int kcont = 0; kcont<*indexDisciplina; kcont++) {
					DisciplinaEAlunos [kcont] [jcont] = DisciplinaEAlunos [kcont] [jcont+1];
				}
			}
			for (int kcont = 0; kcont < Max_disciplinas; kcont++) {
				DisciplinaEAlunos[kcont][*indexAluno-1] = 0;
			}
			(*indexAluno)--;
		}
	}
	void listar_alunos(aluno ListaAlunos[], int *indexAluno) {
		for(int icont=0; icont<*indexAluno; icont++) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
		}
	}

	void filtrar_alunos_sexo(aluno ListaAlunos[], int *indexAluno) {
		char sexoPesquisado;
		scanf(" %c", sexoPesquisado);
		for(int icont=0; icont<*indexAluno; icont++) {
			if(ListaAlunos[icont].sexo == sexoPesquisado) {
				printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", ListaAlunos[icont].nome, ListaAlunos[icont].matricula, ListaAlunos[icont].sexo, ListaAlunos[icont].dia, ListaAlunos[icont].mes, ListaAlunos[icont].ano, ListaAlunos[icont].CPF);
			}
		}
	}

	void ordenar_alunos_nome(aluno ListaAlunos[], int *indexAluno) {
		aluno CopiaListaAlunos[Max_alunos];
		aluno tro_K;
		for (int kcont = 0; kcont < *indexAluno; kcont++) {
			CopiaListaAlunos[kcont] = ListaAlunos[kcont];
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			for(int jcont = icont; jcont < *indexAluno; jcont++) {
				if(strcmp(CopiaListaAlunos[jcont].nome, CopiaListaAlunos[jcont+1].nome) > 0) {
					tro_K = CopiaListaAlunos[jcont];
					CopiaListaAlunos[jcont] = CopiaListaAlunos[jcont+1];
					CopiaListaAlunos[jcont+1] = tro_K;
				}
			}
		}

		for(int kcont = 0; kcont < *indexAluno; kcont++) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaAlunos[kcont].nome, CopiaListaAlunos[kcont].matricula, CopiaListaAlunos[kcont].sexo, CopiaListaAlunos[kcont].dia, CopiaListaAlunos[kcont].mes, CopiaListaAlunos[kcont].ano, CopiaListaAlunos[kcont].CPF);
		}
	}

	void ordenar_alunos_nascismento(aluno ListaAlunos[], int *indexAluno) {
		aluno CopiaListaAlunos[Max_alunos];
		aluno tro_K;
		for (int kcont = 0; kcont < *indexAluno; kcont++) {
			CopiaListaAlunos[kcont] = ListaAlunos[kcont];
		}

		for(int icont = 0; icont < *indexAluno; icont++) {
			for(int jcont = icont; jcont < *indexAluno; jcont++) {
				if(CopiaListaAlunos[jcont].ano*10000+CopiaListaAlunos[jcont].mes*100+CopiaListaAlunos[jcont].dia < CopiaListaAlunos[jcont+1].ano*10000+CopiaListaAlunos[jcont+1].mes*100+CopiaListaAlunos[jcont+1].dia) {
					tro_K = CopiaListaAlunos[jcont];
					CopiaListaAlunos[jcont] = CopiaListaAlunos[jcont+1];
					CopiaListaAlunos[jcont+1] = tro_K;
				}
			}
		}

		for(int kcont = 0; kcont < *indexAluno; kcont++) {
			printf("nome: %s\nmatricula: %lld\nsexo: %c\ndata de nascimento: %d %d %d\nCPF: %lld\n\n", CopiaListaAlunos[kcont].nome, CopiaListaAlunos[kcont].matricula, CopiaListaAlunos[kcont].sexo, CopiaListaAlunos[kcont].dia, CopiaListaAlunos[kcont].mes, CopiaListaAlunos[kcont].ano, CopiaListaAlunos[kcont].CPF);
		}
	}

	void disciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
		int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, "");
		if(icont >= 0) {
			int jcont = 1;
			printf("digite -1 para sair ou ");
			while(jcont>=0) {
				jcont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
				if(icont >= 0 && jcont >= 0) {
					DisciplinaEAlunos [icont] [jcont] = 1;
				}
			}
		}
	}
	void desdisciplinar_aluno(int DisciplinaEAlunos [] [Max_alunos], disciplina ListaDisciplinas[], int *indexDisciplina, aluno ListaAlunos[], int *indexAluno, long long int *Vies) {
		int icont = pesquisar_disciplina_por_codigo(ListaDisciplinas, indexDisciplina, "");
		if(icont >= 0) {
			int jcont = 1;
			printf("digite -1 para sair ou ");
			while(jcont>=0) {
				jcont = pesquisar_aluno_por_matricula(ListaAlunos, indexAluno, Vies);
				if(icont >= 0 && jcont >=0) {
					DisciplinaEAlunos [icont] [jcont] = 0;
				}
			}
		}
	}
	//parte dos professores:______________________________________________________________________________________________________

	int inserir_dados_professor(professor ListaProfessores[], int *indexProfessor, int *excecao) {

		printf("digite a matrícula do professor(a)\n");
		scanf(" %lld", &ListaProfessores[Max_professores].matricula);

		if(ListaProfessores[Max_professores].matricula <= 0) {
			printf("matricula invalida\n");
			return 0;
		}

		for(int icont = 0; icont < *indexProfessor; icont++) {
			if(ListaProfessores[icont].matricula == ListaProfessores[Max_professores].matricula && icont != *excecao) {
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
			if((ListaProfessores[Max_professores].anomatricula) {
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
