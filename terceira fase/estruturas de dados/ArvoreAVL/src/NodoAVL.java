/*
 * Alunos: Lucas Jacques e Lucas Vieira
 * Implementação de uma árvore AVL utilizando alocação dinâmica de memória.
 * 
 * Obs:
 * Foram encontrados muitos problemas na implementação relacionados a "Null Pointer Exception"
 * e "Stack Overflows" principalmente devido a grande utilização de recursão. Os métodos de rotação
 * foram os mais difíceis de implementar, foi necessário buscar códigos prontos para tentar entender
 * como deve ser feito. 
 * 
 * Principal fonte de pesquisa:
 * 	http://www.blackbam.at/blackbams-blog/2012/05/04/avl-tree-implementation-in-java/
 */

public class NodoAVL {
	
	public int codigo, fatorB;
	public NodoAVL pai, esquerda, direita;
	
	public NodoAVL(int codigo) {
		this.codigo = codigo;
		fatorB = 0;
		pai = null;
		esquerda = null;
		direita = null;
	}
	
}