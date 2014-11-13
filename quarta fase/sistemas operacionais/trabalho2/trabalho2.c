/**
 * Trabalho 2 - Arquivos
 *
 * Alunos: Lucas jacques e Lucas Vieira
 * Professor: Márcio Castro
 * Disciplina INE5611 - Sistemas Operacionais
 */

#include <stdio.h>
#include <string.h>

struct funcionario {
	char nome[256];
	char datanasc[11];
	char sexo;
	float salario;
};

FILE *data;
struct funcionario buffer;

int menu();
void criaFuncionario();
void salvaFuncionario();
void removerFuncionario();
void mediaSalarialSexo();
void exportarDados();

int main(int argc, char *argv[]) {

	data = fopen("dados", "a+b");

	if (data == NULL) {
		printf("Erro ao abrir o arquivo de dados.\n");
		return 1;
	}

	int option = 5;
	do {
		option = menu();
		switch (option) {
		case 1:
			criaFuncionario();
			salvaFuncionario();
			break;
		case 2:
			removerFuncionario();
			break;
		case 3:
			mediaSalarialSexo();
			break;
		case 4:
			exportarDados();
			break;
		}
	} while (option != 5);

	fflush(data);
	fclose(data);

	return 0;
}

int menu() {
	int option = 5;
	printf("O que você deseja fazer?\n");
	printf("1. Inserir um novo funcionário.\n");
	printf("2. Remover um funcionário.\n");
	printf("3. Calcular a média de salários dos funcionários por sexo.\n");
	printf("4. Exportar dados dos funcionários.\n");
	printf("5. Sair.\n");
	scanf("%i", &option);
	return option;
}

void criaFuncionario() {
	printf("Insira o nome do novo funcionário: ");
	scanf("%s", buffer.nome);
	printf("Insira a data de nascimento do novo funcionário (ex. 01/01/1990): ");
	scanf("%s", buffer.datanasc);
	printf("Insira o sexo do novo funcionário (m ou f): ");
	char sexo;
	scanf("%s", &sexo);
	buffer.sexo = sexo;
	printf("Insira o salário do novo funcionário (ex. 100.59): ");
	float salario;
	scanf("%f", &salario);
	buffer.salario = salario;
}

void salvaFuncionario() {
	fseek(data, 0, SEEK_END);
	fwrite(&buffer, sizeof(struct funcionario), 1, data);
}

void removerFuncionario() {
	FILE *placeholder = fopen(".dados", "w+b");
	char nome[256];
	int status;
	printf("Insira o nome do funcionário que será removido: ");
	scanf("%s", nome);
	fseek(data, 0, SEEK_SET);
	fseek(placeholder, 0, SEEK_SET);
	fread(&buffer, sizeof(struct funcionario), 1, data);
	while (!feof(data)) {
		if (strcmp(nome, buffer.nome) != 0) {
			fwrite(&buffer, sizeof(struct funcionario), 1, placeholder);
		}
		fread(&buffer, sizeof(struct funcionario), 1, data);
	}
	remove("dados");
	rename(".dados", "dados");
	data = placeholder;
}

void mediaSalarialSexo() {
	float sumMasc = 0, sumFem = 0;
	int countMasc = 0, countFem = 0, status;
	fseek(data, 0, SEEK_SET);
	fread(&buffer, sizeof(struct funcionario), 1, data);
	while (!feof(data)) {
		if (buffer.sexo == 'm') {
			sumMasc += buffer.salario;
			countMasc++;
		} else {
			sumFem += buffer.salario;
			countFem++;
		}
		fread(&buffer, sizeof(struct funcionario), 1, data);
	}
	float mediaMasc = sumMasc / countMasc;
	float mediaFem = sumFem / countFem;
	printf("Média salarial:\nMasculina: %.2f\nFeminina: %.2f\n", mediaMasc, mediaFem);
}

void exportarDados() {
	FILE *output = fopen("dadosTexto", "w");
	int status;
	fseek(data, 0, SEEK_SET);
	fread(&buffer, sizeof(struct funcionario), 1, data);
	while (!feof(data)) {
		fprintf(output, "%s\n", buffer.nome);
		fprintf(output, " Data Nascimento: %s\n", buffer.datanasc);
		if(buffer.sexo == 'm') {
			fprintf(output, " Sexo: Masculino\n");
		} else {
			fprintf(output, " Sexo: Feminino\n");
		}
		fprintf(output, " Salário: %.2f\n", buffer.salario);
		fread(&buffer, sizeof(struct funcionario), 1, data);
	}
	printf("Dados exportados para dadosTexto\n");
	fclose(output);
}
