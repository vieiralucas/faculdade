/*
 * Alunos: Lucas Jacques e Lucas Vieira
 * Implementa��o de uma �rvore AVL utilizando aloca��o din�mica de mem�ria.
 * 
 * Obs:
 * Foram encontrados muitos problemas na implementa��o relacionados a "Null Pointer Exception"
 * e "Stack Overflows" principalmente devido a grande utiliza��o de recurs�o. Os m�todos de rota��o
 * foram os mais dif�ceis de implementar, foi necess�rio buscar c�digos prontos para tentar entender
 * como deve ser feito. Existe um problema na exclus�o, n�o conseguimos rebalancear a �rvore perfeitamente.
 * 
 * Principal fonte de pesquisa:
 * 	http://www.blackbam.at/blackbams-blog/2012/05/04/avl-tree-implementation-in-java/
 */

public class ArvoreAVL {
	
	//raiz da ArvoreAVL
	private NodoAVL raiz;

	/*
	 * Contrutor da ArvoreAVL
	 * Seta a raiz da arvore como null 
	 */
	public ArvoreAVL() {
		raiz = null;
	}
	
	/*
	 * Busca na ArvoreAVL
	 * Recebe um inteiro e retorna um boolean da busca na ArvoreAVL
	 */
	public boolean busca(int buscado) {
		NodoAVL nodoBuscado = busca(raiz, buscado);
		if(nodoBuscado == null) {
			return false;
		}
		return true;
	}
	
	/*
	 * Busca na ArvoreAVL
	 * Recebe um NodoAVL e um inteiro buscado
	 * Retorna true caso o inteiro esteja na �rvore que 
	 * possui como raiz o NodoAVL recebido e false caso o contr�rio 
	 */
	private NodoAVL busca(NodoAVL nodo, int buscado) {
		if(nodo == null) {
			return null;
		}
		if(nodo.codigo == buscado) {
			return nodo;
		} else if(nodo.codigo > buscado) {
			return busca(nodo.esquerda, buscado);
		} else {
			return busca(nodo.direita, buscado);
		}
	}
	
	/*
	 * Recebe um inteiro e insere um NodoAVL na ArvoreAVL
	 */
	public void inserir(int novo) {
		inserir(raiz, new NodoAVL(novo));
	}

	/*
	 * Recebe dois NodoAVL, o primeiro � um pai e o 
	 * segundo um nodo a ser inserido na subarvore que possui como raiz esse pai.  
	 */
	private void inserir(NodoAVL pai, NodoAVL novo) {
		if (pai == null) {
			raiz = novo;
		} else {
			if (novo.codigo > pai.codigo) {
				if (pai.direita == null) {
					pai.direita = novo;
					novo.pai = pai;
					//Nodo inserido, balancear
					balanceia(pai);
				} else {
					inserir(pai.direita, novo);
				}
			} else if (novo.codigo < pai.codigo) {
				if (pai.esquerda == null) {
					pai.esquerda = novo;
					novo.pai = pai;
					//Nodo inserido, balancear					
					balanceia(pai);
				} else {
					inserir(pai.esquerda, novo);
				}
			}
		}
	}
	
	/*
	 * Recebe um NodoAVL e balanceia a ArvoreAVL que ele � raiz
	 */
	private void balanceia(NodoAVL atual) {
		if (atual == null) {
			return;
		}
		//calcula fator de balanceamento do NodoAVL
		atual.fatorB = calculaFatorB(atual);
		if (atual.fatorB == -2) {
			//ArvoreAVL desbalanceada para direita
			if(atual.direita.fatorB <= 0) {
				//ArvoreAVL desbalanceada em "Zig-Zig" rota��o simples
				if (atual == raiz) {
					raiz = rotacaoEsquerda(atual);
				} else {
					atual = rotacaoEsquerda(atual);
				}
			}else {
				//ArvoreAVL desbalanceada em "Zig-Zag" rota��o dupla
				atual = rotacaoDireitaEsquerda(atual);
			}
		} else if (atual.fatorB == 2) {
			//ArvoreAVL desbalanceada para esquerda
			if (atual.esquerda.fatorB >= 0) {
				//ArvoreAVL desbalanceada em "Zig-Zig" rota��o simples
				if (atual == raiz) {
					raiz = rotacaoDireita(atual);
				} else {
					atual = rotacaoDireita(atual);
				}
			} else {
				//ArvoreAVL desbalanceada em "Zig-Zag" rota��o dupla
				atual = rotacaoEsquerdaDireita(atual);
			}
		} else {
			//NodoAVL n�o est� desbalanceado, balancear pai
			balanceia(atual.pai);
		}
	}

	/*
	 * Recebe a raiz de uma sub�rvore desbalanceada e faz
	 * um giro para a direita
	 * Retorna a raiz da nova subarvore, agora balanceada
	 */
	private NodoAVL rotacaoDireita(NodoAVL raizVelha) {
		NodoAVL novaRaiz = raizVelha.esquerda;
		novaRaiz.pai = raizVelha.pai;
		raizVelha.esquerda = novaRaiz.direita;
		if (raizVelha.esquerda != null) {
			raizVelha.esquerda.pai = raizVelha;
		}
		novaRaiz.direita = raizVelha;
		raizVelha.pai = novaRaiz;
		if (novaRaiz.pai != null) {
			if (novaRaiz.pai.direita == raizVelha) {
				novaRaiz.pai.direita = novaRaiz;
			} else if (novaRaiz.pai.esquerda == raizVelha) {
				novaRaiz.pai.esquerda = novaRaiz;
			}
		}
		raizVelha.fatorB = calculaFatorB(raizVelha);
		novaRaiz.fatorB = calculaFatorB(novaRaiz);
		return novaRaiz;
	}

	/*
	 * Recebe a raiz de uma sub�rvore desbalanceada e faz
	 * um giro para a esquerda
	 * Retorna a raiz da nova subarvore, agora balanceada
	 */
	private NodoAVL rotacaoEsquerda(NodoAVL raizVelha) {
		NodoAVL novaRaiz = raizVelha.direita;
		novaRaiz.pai = raizVelha.pai;
		raizVelha.direita = novaRaiz.esquerda;
		if (raizVelha.direita != null) {
			raizVelha.direita.pai = raizVelha;
		}
		novaRaiz.esquerda = raizVelha;
		raizVelha.pai = novaRaiz;
		if (novaRaiz.pai != null) {
			if (novaRaiz.pai.esquerda == raizVelha) {
				novaRaiz.pai.esquerda = novaRaiz;
			} else if (novaRaiz.pai.direita == raizVelha) {
				novaRaiz.pai.direita = novaRaiz;
			}
		}
		raizVelha.fatorB = calculaFatorB(raizVelha);
		novaRaiz.fatorB = calculaFatorB(novaRaiz);
		return novaRaiz;
	}

	/*
	 * Recebe a raiz de uma sub�rvore desbalanceada em "Zig-Zag",
	 * faz um giro para a esquerda na sub�rvore imediata a essa subarvore.
	 * Retorna a rotacao para a direita da sub�rvore desbalanceada agora em "Zig-Zig"
	 */
	private NodoAVL rotacaoEsquerdaDireita(NodoAVL raizVelha) {
		raizVelha.esquerda = rotacaoEsquerda(raizVelha.esquerda);
		return rotacaoDireita(raizVelha);
	}

	/*
	 * Recebe a raiz de uma sub�rvore desbalanceada em "Zig-Zag",
	 * faz um giro para a direita na sub�rvore imediata a essa subarvore.
	 * Retorna a rotacao para a esquerda da sub�rvore desbalanceada agora em "Zig-Zig"
	 */
	private NodoAVL rotacaoDireitaEsquerda(NodoAVL raizVelha) {
		raizVelha.direita = rotacaoDireita(raizVelha.direita);
		return rotacaoEsquerda(raizVelha);
	}

	/*
	 * Recebe um NodoAVL
	 * Calcula a altura desse NodoAVL recursivamente
	 * Retorna a altura
	 */
	private int calculaAltura(NodoAVL nodo) {
		if (nodo == null) {
			return -1;
		}
		if (nodo.esquerda == null && nodo.direita == null) {
			return 0;
		} else if (nodo.esquerda == null) {
			return 1 + calculaAltura(nodo.direita);
		} else if (nodo.direita == null) {
			return 1 + calculaAltura(nodo.esquerda);
		} else {
			return 1 + Math.max(calculaAltura(nodo.esquerda),
					calculaAltura(nodo.direita));
		}
	}
	
	/*
	 * Recebe um NodoAVL
	 * Calcula as alturas dos filhos
	 * Retorna a diferen�a das alturas como fator de balanceamento
	 */
	private int calculaFatorB(NodoAVL nodo) {
		int alturaEsquerda = calculaAltura(nodo.esquerda);
		int alturaDireita = calculaAltura(nodo.direita);
		return alturaEsquerda - alturaDireita;
	}

	/*
	 * M�todo utilizado para "printar" a arvore em pre-order e poder
	 * reconstrui-la verificando se os balanceamentos funcionaram
	 * como esperado
	 */
	public void printPreOrder() {
		printPreOrder(raiz);
	}

	/*
	 * M�todo que "printa" os NodoAVL's em pre-order recursivamente
	 */
	private void printPreOrder(NodoAVL nodo) {
		if (nodo != null) {
			System.out.printf(nodo.codigo + " ");
			printPreOrder(nodo.esquerda);
			printPreOrder(nodo.direita);
		}
	}
	
	/*
	 * Recebe um inteiro para excluir da ArvoreAVL
	 * Procura o inteira na �rvore, caso esteja presente
	 * chama o metodo de exclusao enviando o NodoAVL a excluir
	 */
	public void excluir(int excluido) {
		NodoAVL aExcluir = busca(raiz, excluido);
		if(aExcluir != null) {
			excluir(aExcluir);
		}
	}
	
	/*
	 * Recebe um NodoAVL a excluir
	 * Observa todos os casos de "status" de um nodo e procede com a exclus�o do mesmo
	 */
	private void excluir(NodoAVL aExcluir) {
		if(aExcluir.esquerda == null && aExcluir.direita == null) {
			if(aExcluir.pai == null) {
				//Arvore s� possui raiz
				raiz = null;
				aExcluir = null;
			} else {
				//aExcluir � folha
				int codigo = aExcluir.codigo;
				if(aExcluir.pai.codigo > codigo) {
					aExcluir.pai.esquerda = null;
					aExcluir = null;
				} else {
					aExcluir.pai.direita = null;
					aExcluir = null;
				}
			}
		} else if(aExcluir.esquerda == null) {
			//N�o possui filho � esquerda
			if(aExcluir.pai == null) {
				//aExcluir � raiz
				raiz = aExcluir.direita;
				raiz.pai = null;
			} else {				
				aExcluir.direita.pai = aExcluir.pai;
				aExcluir.pai.direita = aExcluir.direita;
			}
			aExcluir = null;
		} else if(aExcluir.direita == null) {
			if(aExcluir.pai == null) {
				//aExcluir � raiz
				raiz = aExcluir.esquerda;
				raiz.pai = null;
			} else {
				aExcluir.esquerda.pai = aExcluir.pai;
				aExcluir.pai.esquerda = aExcluir.esquerda;
			}
			aExcluir = null;
		} else {
			if(aExcluir.pai == null) {
				//raiz
				raiz = aExcluir.direita;
				NodoAVL ultimoEsquerda = buscarUltimoNodoEsquerda(aExcluir.direita);
				ultimoEsquerda.esquerda = aExcluir.esquerda;
				aExcluir = null;
				raiz.pai = null;
			} else {
				int codigo = aExcluir.codigo;
				if(codigo > aExcluir.pai.codigo) {
					//"Ligar" na direita do pai do aExcluir
					aExcluir.pai.direita = aExcluir.direita;
					aExcluir.direita.pai = aExcluir.pai;
					NodoAVL ultimoEsquerda = buscarUltimoNodoEsquerda(aExcluir.direita);
					ultimoEsquerda.esquerda = aExcluir.esquerda;
				} else {
					//"Ligar" na esquerda do pai do aExcluir
					aExcluir.pai.esquerda = aExcluir.direita;
					aExcluir.direita.pai = aExcluir.pai;
					NodoAVL ultimoEsquerda = buscarUltimoNodoEsquerda(aExcluir.direita);
					ultimoEsquerda.esquerda = aExcluir.esquerda;
				}
				aExcluir = null;
			}
		}
		//Tentativa de balanceamento, n�o � perfeita
		balanceia(buscarUltimoNodoEsquerda(raiz));
	}
	
	/*
	 * Recebe um NodoAVL raiz de uma sub �rvore
	 * Retorna o ultimo filho da esquerda dessa sub �rvore
	 */
	private NodoAVL buscarUltimoNodoEsquerda(NodoAVL raizSubArvore) {
		if(raizSubArvore.esquerda == null) {
			return raizSubArvore;
		} else {
			return buscarUltimoNodoEsquerda(raizSubArvore.esquerda);
		}
	}
}