#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}
/* 1.- Implemente la función *createTreeMap* en el archivo treemap.c. Esta función recibe la función de comparación de claves y crea un mapa (TreeMap) inicializando sus variables. 
El siguiente código muestra como inicializar la función de comparación. Reserve memoria, inicialice el resto de variables y retorne el mapa.

  */
TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* mapa= (TreeMap*)malloc(sizeof(TreeMap));
    if (mapa!=NULL){
      mapa->root=NULL;
      mapa->lower_than=lower_than;
      
      return mapa;
    
    }else{
      return NULL;
    }
}

/*Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).*/

void insertTreeMap(TreeMap * tree, void* key, void * value){
  if(tree==NULL || key==NULL||value==NULL){
    return;
  }
  
  TreeNode* nuevoNodo=createTreeNode(key,value);
  
  if (tree->root == NULL){
    tree->root= nuevoNodo;
  }
  TreeNode* temp=tree->root;
  
  while(1){
    if(is_equal(tree, key,temp->pair->key)){
      return;
    }else if(tree->lower_than(key,temp->pair->key)){
      if(temp->left==NULL){
        temp->left=nuevoNodo;
        tree->current=temp->left;
        return;
      }else{
        temp=temp->left;
      }
    }else{
      if(temp->right==NULL){
        temp->right=nuevoNodo;
        tree->current=temp->right;
        return;
      }else{
        temp=temp->right;
      }
    }
  } 

}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


/* 2.- Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el **Pair** asociado al nodo. Si no se encuentra la clave retorna NULL.
Recuerde hacer que el current apunte al nodo encontrado.
  */

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* temp = tree->root;
    while (temp!=NULL){
      if (is_equal(tree,key,temp->pair->key)){
        tree->current=temp;
        return temp->pair;
      }else if (tree->lower_than(key,temp->pair->key)){
        temp=temp->left;
      }else{
        temp=temp->right;
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
