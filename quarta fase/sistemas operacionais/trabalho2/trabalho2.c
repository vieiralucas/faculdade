#include <stdio.h>

struct funcionario {
	char nome[256];
	char datanasc[11];
	char sexo[3];
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

void ler() {
	fseek(data, 0, SEEK_SET);
	struct funcionario lido;
	fread(&lido, sizeof(struct funcionario), 1, data);
	fwrite(&lido.salario, sizeof(float), 1, stdout);
}

int main(int argc, char *argv[]) {

	data = fopen("dados", "wb");
	criaFuncionario();
	ler();
	return 0;


	if(data == NULL) {
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
			ler();
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
	} while(option != 5);

	return 0;
}

int menu() {
	int option = 5;
	printf("O que você deseja fazer?\n");
	printf("1. Inserir um funcionário no arquivo\n");
	printf("2. Remover um funcionário do arquivo\n");
	printf("3. Calcular a média de salários dos funcionários por sexo\n");
	printf("4. Exportar dados dos funcionários\n");
	printf("5. Sair\n");
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
	printf("Insira o salário do novo funcionário (ex. 100.59): ");
	float salario;
	scanf("%f", &salario);
}

void salvaFuncionario() {
	fseek(data, 0, SEEK_SET);
	fwrite(&buffer, sizeof(struct funcionario), 1, data);
}

void removerFuncionario() {

}

void mediaSalarialSexo() {

}

void exportarDados() {

}
