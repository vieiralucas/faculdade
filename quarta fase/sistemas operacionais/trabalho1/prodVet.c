/*
* Trabalho 1
* Produto escalar concorrente usando threads
* INE5611 - Sistemas Operacionais
* Prof. Márcio Castro
* 2014/2
* Grupo: Lucas Jacques, Lucas Vieira
* 
* Enunciado:
* 
* O primeiro trabalho da disciplina de Sistemas Operacionais consiste em implementar
* o produto escalar entre dois vetores de inteiros (obrigatoriamente do
* mesmo tamanho) de forma concorrente utilizando a linguagem C e a biblioteca
* POSIX Threads. Os dois parâmetros de entrada são o número de threads
* trabalhadoras – worker threads (NTHREADS) e o tamanho dos veto-
* res (VECSIZE).
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

// struct para passar os argumentos para as threads
typedef struct pthread_args {
    int id;
    int start;
    int end;
} pthread_args;

int *vet1, *vet2; // vetores de tamanho dinamico ainda não alocados
pthread_t *threads; // vetor de threads dinamico ainda não alocado
int vetSize, nThreads, produtoEsc = 0; // variaveis de controle globais

pthread_mutex_t mutex;  // mutex necessário pois diferentes threads vão ler e escrever na variável produtoEsc

// assinatura das funcoes definidas após o main, feito dessa maneira para deixar o main no começo
void askUser(bool explicar);
void populaVets();
void printVets();
void *goThread(void *arg);
int prodEscalarParc(int start, int end);

int main(int argc, char *argv[]) {
    // Validando argumentos
    if(argc <= 1) { // se não existirem argumentos
        askUser(false); // apenas pede ao usuario
    } else if(argc <= 2){ // se estiverem faltando argumentos
        askUser(true); // pede ao usuario
    } else { // não estao faltando argumentos
        if(sscanf (argv[1], "%i", &nThreads) != 1 || sscanf (argv[2], "%i", &vetSize) != 1) {
            // não foi possível converter todos os argumentos para inteiro
            askUser(true);
        }
    }

    vet1 = malloc(vetSize * sizeof(int)), vet2 = malloc(vetSize * sizeof(int)); // alocando memoria para os vetores dinamicos 
    
    populaVets(); // populando vetores com inteiros aleatorios
    printVets(); // imprimindo os vetores

    pthread_mutex_init(&mutex, NULL); // inicia mutex

    // codigo para criar as threads e calcular suas posicoes
    int nValPerThr = vetSize / nThreads; // numero de valores por thread
    int resto = vetSize % nThreads; // posicoes que sobram 
    pthread_args args[nThreads]; // instanciando a struct pthread_args

    if(nThreads > vetSize) { // se forem solicitadas mais threads que posições nos vetores
        nThreads = vetSize; // limita a quantidade de threads pro tamanho do vetor
        resto = 0; // zera resto para impedir atribuição de mais posicoes desnecessarias para threads
        nValPerThr = 1; // como foram solicitadas mais threads que posicoes, serao criadas 1 thread para cada posicao
    }

    threads = malloc(nThreads * sizeof(pthread_t)); // alocando memoria para o vetor de threads
    int start = 0; // variavel que marca a posicao de start
    for(int i = 0; i < nThreads; i++) {
        args[i].id = i + 1; // define o id da thread
        args[i].start = start; // atribui a args.start a posicao de start
        args[i].end = args[i].start + nValPerThr; // atribui a args.end a posicao de end que a principio devera ser start + numero de valores por thread 
        start += nValPerThr;
        if(resto > 0) { // se existir resto 
            args[i].end++; // atribui mais uma posicao para essa thread
            resto--; // decrementa resto, pois agora resta uma posicao a menos
            start++; // incrementa start para que a proxima thread comece da proxima posicao
        }
        pthread_create(&threads[i], NULL, goThread, (void *) &args[i]); // cria a thread
    }
    // termino do codigo que cria as threads

    // espera todas as threads finalizarem
    for(int i = 0; i < nThreads; i++)
        pthread_join(threads[i], NULL);

    printf("Produto escalar = %d\n", produtoEsc); // imprime produto escalar

    return 0; // termina programa com status 0 (sucesso)
}

/*
* Recebe um bool para explicar ou não o modo correto
* de passar argumentos pela linha de comando
* Pega os dados necessários
*/
void askUser(bool explicar) {
    if(explicar) {
        printf("Para passar os argumentos pela linha de comando execute da seguinte forma:\n./prodVet numero_threads tamanho_vetores\n\n");
    }
    printf("Insira o número de threads utilizadas: ");
    scanf("%d", &nThreads);
    printf("Insira o tamanho dos vetores: ");
    scanf("%d", &vetSize);
}

/*
* Popula os vetores com inteiros aleatórios de 0 a 9
*/
void populaVets() {
    srand(time(NULL));
    for(int i = 0; i < vetSize; i++) {
        vet1[i] = rand() % 10;
        vet2[i] = rand() % 10;
    }
}

/*
* Imprime os dois vetores no formato:
* A - 0, 3, 4, 5
* B - 3, 5, 0, 7
*/
void printVets() {
    printf("A = ");
    for(int i = 0; i < vetSize; i++) {
        if(i == vetSize - 1) {
            printf("%d\n", vet1[i]);
        } else {
            printf("%d, ", vet1[i]);
        }
    }
    printf("B = ");
    for(int i = 0; i < vetSize; i++) {
        if(i == vetSize - 1) {
            printf("%d\n", vet2[i]);
        } else {
            printf("%d, ", vet2[i]);
        }
    }
}

/*
* Código a ser executado pelas threads que são
* responsáveis pelo calculo do produto escalar
*
* Calcula o produto escalar da faixa dos vetores
* que são responsáveis chamando a função "prodEscalarParc"
* adiciona seu produto escalar parcial a soma total;
*/
void *goThread(void *arg) {
    pthread_args *args = (pthread_args *) arg;
    int prod = prodEscalarParc(args->start, args->end);
    printf("Thread %d calculou de %d a %d: produto escalar parcial = %d\n", args->id, args->start, args->end - 1, prod);
    pthread_mutex_lock(&mutex); // espera para acessar váriavel critica
    // regiao critica
    produtoEsc += prod; // soma produto escalar parcial junto ao total
    pthread_mutex_unlock(&mutex); // libera acesso a variável critica
}

/*
* Recebe dois inteiros:
*   start -> indica a posição inicial dos vetores
*   end   -> indica a posição final dos vetores
* Retorna o produto escalar parcial dos vetores levando
* em consideração as seguintes posições:
*   end > posicao_levada_consideracao <= start
*/
int prodEscalarParc(int start, int end) {
    int sum = 0;
    int prod;
    for(int i = start; i < end; i++) {
        prod = vet1[i] * vet2[i];
        sum += prod;
    }
    return sum;
}
