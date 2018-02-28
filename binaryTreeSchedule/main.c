/**
#Universidade Federal de Pelotas#
#Unidade: CDTEC
#Curso: Ciênia da computação
#Disciplina: Algoritmos e Estruturas de Dados I
Profº: Raphael Peccin Torchelsen
#Aluno: Maicon de Menezes
#Projeto:Agenda de nomes com arvore binária
#Módulo: principal
#Descrição: O código a seguir descreve uma estrutura de arvore binária que armazena string de forma ordenada
**/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//Definindo o tamanho total da string
#define sizeOfName 30

//Definindo o tipo abstrato 'tree'
struct tree{
    char data[sizeOfName];//string armazenada
    struct tree *left;   //filho da esquerda
    struct tree *right;  //filho da direita
    struct tree *parent; //pai
};

/*
Função que cria uma nova subarvore contendo o valor de uma string
Parametros:
    root    :Folha/Nó Raiz
    thisTree:Folha/Nó que será inserido na estrutura
    data    :Dado pertencente à Folha/Nó que será incluída(o)
 * Algoritmo baseado no livro C completo e total
*/
struct tree *makeTree(struct tree *root, struct tree *thisTree, char *data){
    //Nova raiz
    if(!thisTree){
        //Aloca memória para a subarvores caso ainda não exista
        thisTree = (struct tree *) malloc(sizeof(struct tree));
        if(!thisTree){
            printf("Não foi possível alocar memória!");
            exit(0);
        }
        //Caso a subarvore ainda não exista então é criada uma arvore nova a partir deste(a) Folha/Nó
        thisTree->left = NULL;
        thisTree->right = NULL;
        thisTree->parent = NULL;
        strcpy(thisTree->data, data);
        //Retorna a subarvore atual como Folha/Nó Raiz, caso ela mesma não possua Raiz
        if(!root) return thisTree;
        //Posiciona a subarvore atual a esquerda da raiz caso a string seja menor que a string da raiz
        if(strcmp(data, root->data)<0){
            root->left = thisTree;
        }
        //Caso contrário posiciona a subarvore atual a direita da raiz
        else{
            root->right = thisTree;
        }
        return thisTree;
    }
    //Caso a já exista uma raiz são feitas as comparaçes para adicionar a subarvore no local correto
    if(strcmp(data, thisTree->data)<0) makeTree(thisTree, thisTree->left, data);
    else makeTree(thisTree, thisTree->right, data);
}

/* Percurso de arvore in-ordem
 * Algoritmo que imprime a chave da raiz de uma subarvore entre a impressão dos 
 * valores em em sua subarvore esquerda e a impressão dos valores em sua subarvore
 * direita
 * Algoritmo baseado no livro do Thomas Cormem*/
void inOrderTreeWalk(struct tree *root){
    if(!root) return;
    inOrderTreeWalk(root->left);
    if(root->data) printf("%s", root->data);
    inOrderTreeWalk(root->right);
}
void inOrderPrintTree(struct tree *thisTree, int l){ 
    inOrderPrintTree(thisTree->left, l+1);
    for(int i=0; i<l; ++i) printf("  ");
    printf("%s\n", thisTree->data);
    inOrderPrintTree(thisTree->right, l+1);    
}
/* Percurso de arvore em pré-ordem
 * Algoritmo que imprime a chave da raiz de uma subarvore antes dos valores das suas
 * subarvores
 * Algoritmo baseado no livro do Thomas Cormem*/
void preOrderTreeWalk(struct tree *root){
    if(!root) return;
    if(root->data) printf("%s", root->data);
    preOrderTreeWalk(root->left);
    preOrderTreeWalk(root->right);
}
void preOrderPrintTree(struct tree *thisTree, int l){ 
    for(int i=0; i<l; ++i) printf("  ");
    printf("%s\n", thisTree->data);
    preOrderPrintTree(thisTree->left, l+1);
    preOrderPrintTree(thisTree->right, l+1);       
}
/* Percurso de arvore em pós-ordem
 * Algoritmo que imprime a chave da raiz de uma subarvore depois dos valores das suas
 * subarvores
 * Algoritmo baseado no livro do Thomas Cormem*/
void postOrderTreeWalk(struct tree *root){
    if(!root) return;
    postOrderTreeWalk(root->left);
    postOrderTreeWalk(root->right);
    if(root->data) printf("%s", root->data);
}
void postOrderPrintTree(struct tree *thisTree, int l){ 
    postOrderPrintTree(thisTree->left, l+1);
    postOrderPrintTree(thisTree->right, l+1);        
    for(int i=0; i<l; ++i) printf("  ");
    printf("%s\n", thisTree->data);
}
/*Imprimir arvore
 * Imprimi uma arvore de forma hierarquica de acordo com a ordem de percurso
 * definida, as opções são:
 * 0- in-ordem
 * 1- pré-ordem
 * 2- pós-ordem */
void printTree(struct tree *thisTree, int l, int orderWalk){
    if(thisTree==NULL) return;    
    if(orderWalk == 0)
        inOrderPrintTree(thisTree, l);       
    else if (orderWalk == 1)
        preOrderPrintTree(thisTree, l);         
    else if (orderWalk == 2)
        postOrderPrintTree(thisTree, l);       
    else return;    
}
/*Função que percorre a arvore procurando de forma recursiva um nó que contém a 
 * string pesquisada e retorna NULL caso não encontre*/
struct tree *recursiveSearchInTree(struct tree *thisTree, char keySearch[sizeOfName]){
    if (thisTree == NULL || strcmp(keySearch ,thisTree->data) == 0){
        return thisTree;
    }
    if(strcmp(keySearch ,thisTree->data) < 0){
        return recursiveSearchInTree(thisTree->left, keySearch);
    }else{
        return recursiveSearchInTree(thisTree->right, keySearch);
    }
}
/*Função que percorre a arvore procurando de forma iterativa um nó que contém a 
 * string pesquisada e retorna NULL caso não encontre, esta versão é mais eficiente*/
struct tree *iterativeSearchInTree(struct tree *thisTree, char keySearch[sizeOfName]){
    while (thisTree != NULL || strcmp(keySearch ,thisTree->data) != 0){
         if(strcmp(keySearch ,thisTree->data) < 0)
             thisTree = thisTree->left;
         else
             thisTree = thisTree->right;
    }
    return thisTree;
}
/* Função que permite selecionar qual o algoritmo utilizado para  realizar as buscas
 * de uma arvore binária as opções são:
 * 0- algoritmo recursivo
 * 1- algoritmo iterativo
 **/
struct tree *SearchInTree(struct tree *thisTree, char keySearch[sizeOfName], int searchMode){
    if(searchMode == 0)
        return recursiveSearchInTree(thisTree, keySearch);
    else if(searchMode == 1)
        return iterativeSearchInTree(thisTree, keySearch);
    else
        return NULL;
}
/*Função que retorna o menor nó da arvore*/
struct tree *minimumNode(struct tree *thisTree){
    while (thisTree->left != NULL){
        thisTree=thisTree->left;
    return thisTree;
    }
}
/*Função que retorna o maior nó da arvore*/
struct tree *maximumNode(struct tree *thisTree){
    while (thisTree->right != NULL){
        thisTree=thisTree->right;
    return thisTree;
    }
}
/*Função que retorna o sucessor de um nó da arvore*/
struct tree *sucessorNode(struct tree *thisTree){
    struct tree *sucessor;
    
    if(thisTree->right != NULL)
        return minimumNode(thisTree->right);
    sucessor=thisTree->parent;
    while(sucessor != NULL && thisTree == sucessor->left){
        thisTree = sucessor;
        sucessor = sucessor->parent;
    }
    return sucessor;
}
/*Função que retorna o antecessor de um nó da arvore*/
struct tree *predecessorNode(struct tree *thisTree){
    struct tree *predecessor;    
    if(thisTree->left != NULL)
        return thisTree->left;
    predecessor=thisTree->parent;
    while(predecessor != NULL && thisTree == predecessor->right){
        thisTree = predecessor;
        predecessor = predecessor->parent;
    }
    return predecessor;
}
/*Função que adiciona um novo nó a arvore, assumindo que o argumento thisTree é
 a raiz da árvore*/
void insertNewNode(struct tree *thisTree, struct tree *newNode){
    struct tree *temporaryNode=NULL;
    if(!thisTree)
        thisTree = newNode;
    else{
        while (thisTree != NULL){
            temporaryNode = thisTree;
            if(strcmp(newNode->data,thisTree->data)<0)
                thisTree = thisTree->left;
            else
                thisTree = thisTree->right;        
        }
        newNode->parent = temporaryNode;
        if(temporaryNode == NULL)
            thisTree = newNode;
        else if(strcmp(newNode->data, temporaryNode->data)<0)
            temporaryNode->left = newNode;
        else
            temporaryNode->right = newNode;
    }
}
    
/*Função que aloca espaço na memória e cria um novo nó com a informação da chave*/
struct tree *createNewNode(struct tree *newNode, char *data){
    newNode = (struct tree *) malloc(sizeof(struct tree));
    if(!newNode){
        printf("Não foi possível alocar memória!");
        exit(0);
    }else
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        strcpy(newNode->data, data);        
        return newNode;
}
/*Função que subistitui uma arvore por outra*/
void transplantNode(struct tree *thisTree, struct tree *currentNode, struct tree *newNode){
    if(currentNode->parent == NULL)
        thisTree = newNode;
    else if(currentNode == currentNode->parent->left)
        currentNode->parent->left = newNode;
    else
        currentNode->parent->right = newNode;
    if(newNode != NULL)
        newNode->parent = currentNode->parent;
}

void deleteNode(struct tree *thisTree, struct tree *deletedNode){
    struct tree *temporaryNode;
    if(deletedNode->left == NULL)
        transplantNode(thisTree, deletedNode, deletedNode->right);
    else if(deletedNode->right == NULL)
        transplantNode(thisTree, deletedNode, deletedNode->left);
    else
        temporaryNode = minimumNode(deletedNode->right);
    if(temporaryNode->parent != deletedNode){
        transplantNode(thisTree, temporaryNode, temporaryNode->right);
        temporaryNode->right = deletedNode->right;
        temporaryNode->right->parent = temporaryNode;
    }
    transplantNode(thisTree, deletedNode, temporaryNode);
    temporaryNode->left = deletedNode->left;
    temporaryNode->left->parent = temporaryNode;
}

/*Função que gira um nó para direita*/
void rightRotation(struct tree *thisTree){
    struct tree *temporaryTree;
    struct tree *qTree;
    
    qTree = thisTree->left;
    temporaryTree= qTree->right;
    qTree->right = thisTree;
    thisTree->left=temporaryTree;
    thisTree=qTree;
}
/*Função que gira um nó para esquerda*/
void leftRotation(struct tree *thisTree){
    struct tree *temporaryTree;
    struct tree *qTree;
    
    qTree = thisTree->right;
    temporaryTree= qTree->left;
    qTree->left = thisTree;
    thisTree->right=temporaryTree;
    thisTree=qTree;
}
/*Função que gira um nó da direita para esquerda*/
void rightToLeftRotation(struct tree *thisTree){
   
    rightRotation(thisTree->right);
    leftRotation(thisTree);
}
/*Função que gira um nó da esquerda para direita*/
void leftToRightRotation(struct tree *thisTree){
    leftRotation(thisTree->right);
    rightRotation(thisTree);
}
/*Função que equilibra uma subarvore*/
void balanceTree(struct tree *root){
    //https://www.cs.usfca.edu/~galles/visualization/AVLtree.html
    
}

void main(void){
    struct tree *node=NULL;
    struct tree *root=NULL;
    char nome[sizeOfName];

    do{
        printf("Digite um nome ou '0' para sair:");
        scanf("%s", nome);
        node = createNewNode(node, nome);
        insertNewNode(root, node);
    } while(strcmp(nome,"0")!=0);
    printTree(node, 0, 1);
}
