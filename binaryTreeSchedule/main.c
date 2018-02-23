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
    struct tree *left;    //Folha/Nó da esquerda
    struct tree *right;   //Folha/Nó da direita
    struct tree *root; //raiz do nó
    int  height;
};

/*
Função que cria uma nova subarvore contendo o valor de uma string
Parametros:
    root    :Folha/Nó Raiz
    thisTree:Folha/Nó que será inserido na estrutura
    data    :Dado pertencente à Folha/Nó que será incluída(o)
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
        thisTree->root = NULL;
        strcpy(thisTree->data, data);
        //Retorna a subarvore atual como Folha/Nó Raiz, caso ela mesma não possua Raiz
        if(!root) return thisTree;
        //Posiciona a subarvore atual a esquerda da raiz caso a string seja menor que a string da raiz
        if(strcmp(data, root->data)<0){
            root->left = thisTree;
            thisTree->root = root;
        }
        //Caso contrário posiciona a subarvore atual a direita da raiz
        else{
            root->right = thisTree;
            thisTree->root = root;
        }
        return thisTree;
    }
    //Caso a já exista uma raiz são feitas as comparaçes para adicionar a subarvore no local correto
    if(strcmp(data, thisTree->data)<0) makeTree(thisTree, thisTree->left, data);
    else makeTree(thisTree, thisTree->right, data);
}

void inOrderTree(struct tree *root){
    if(!root) return;
    inOrderTree(root->left);
    if(root->data) printf("%s", root->data);
    inOrderTree(root->right);
}

void preOrderTree(struct tree *root){
    if(!root) return;
    if(root->data) printf("%s", root->data);
    preOrderTree(root->left);
    preOrderTree(root->right);
}

void postOrderTree(struct tree *root){
    if(!root) return;
    postOrderTree(root->left);
    postOrderTree(root->right);
    if(root->data) printf("%s", root->data);
}

void printTree(struct tree *thisTree, int l){
    if(thisTree==NULL) return;

    printTree(thisTree->left, l+1);
    for(int i=0; i<l; ++i) printf("  ");
    printf("%s\n", thisTree->data);
    printTree(thisTree->right, l+1);
}
/*Função que percorre a arvore procurando um nó que contém a string pesquisada
 retorna NULL caso não encontre*/
struct tree *searchInTree(struct tree *thisTree, char keySearch[sizeOfName]){
    if (thisTree == NULL || strcmp(keySearch ,thisTree->data) == 0){
        return thisTree;
    }
    if(strcmp(keySearch ,thisTree->data) < 0){
        return searchInTree(thisTree->left, keySearch);
    }else{
        return searchInTree(thisTree->right, keySearch);
    }
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
    struct tree *root;
    
    if(thisTree->right != NULL){
        return minimumNode(thisTree->right);
    }
    root=thisTree->root;
    while(root != NULL && thisTree == root->left){
        thisTree = root;
        root = root->root;
    }
    return thisTree;
}
/*Função que retorna o antecessor de um nó da arvore*/
struct tree *predecessorNode(struct tree *thisTree){
    struct tree *root;
    
    if(thisTree->left != NULL){
        return thisTree->left;
    }
    root=thisTree->root;
    while(root != NULL && thisTree == root->right){
        thisTree = root;
        root = root->root;
    }
    return thisTree;
}


/*Função que equilibra uma subarvore*/
void balanceTree(struct tree *root){
    
    
}

struct tree *root;
void main(void){
    char nome[sizeOfName];

    root=NULL;
    do{
        printf("Digite um nome ou '0' para sair:");
        scanf("%s", nome);
        if(!root) root=makeTree(root, root, nome);
        else makeTree(root, root, nome);
    } while(strcmp(nome,"0")!=0);
    printTree(root, 0);
}
