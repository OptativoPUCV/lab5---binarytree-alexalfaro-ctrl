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
        nuevoNodo->parent=temp;
        tree->current=temp->left;
      }else{
        temp=temp->left;
      }
    }else{
      if(temp->right==NULL){
        temp->right=nuevoNodo;
        nuevoNodo->parent=temp;
        tree->current=temp->right;
      }else{
        temp=temp->right;
      }
    }
  } 

}


TreeNode * minimum(TreeNode * x){
  while(x->left!=NULL){
    x=x->left;
  }
    return x;
}

/*5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo *node* del árbol *tree*. Recuerde que para eliminar un node existen 3 casos:
**Nodo sin hijos:** Se anula el puntero del padre que apuntaba al nodo
**Nodo con un hijo:** El padre del nodo pasa a ser padre de su hijo
**Nodo con dos hijos:** Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value) de *node* con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función *removeNode*).*/
void removeNode(TreeMap * tree, TreeNode* node) {
  
  if(node!=NULL||tree!=NULL){
    if(node->left==NULL&&node->right==NULL){
      if(node->parent==NULL){
        tree->root=NULL;
        
      }else if(node->parent->left==node){
        node->parent->left=NULL;
      }else{
        node->parent->right=NULL;
      }
      free(node);
      
      
    }else if(node->left==NULL||node->right==NULL){
      TreeNode* bendicion = (node->left != NULL) ? node->left : node->right;
      if (node->parent==NULL){
        tree->root=bendicion;
      }else if(node->parent->left==node){
        node->parent=bendicion;
        
      }else{
        node->parent->right=bendicion;
      }
      bendicion->parent=node->parent;
      free(node);
      
    }else{
      TreeNode* minimo = minimum(node->right);
      node->pair->key = minimo->pair->key;
      node->pair->value = minimo->pair->value;
      removeNode(tree,minimo);
      
    }
    
  }

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
/*6.- Implemente las funciones para recorrer la estructura: Pair* firstTreeMap(TreeMap* tree) retorna el primer **Pair** del mapa (el menor). Pair* nextTreeMap(TreeMap* tree)  retornar el siguiente **Pair** del mapa a partir del puntero TreeNode* current. Recuerde actualizar este puntero.*/
Pair * firstTreeMap(TreeMap * tree) {
  if(tree!=NULL){
    TreeNode* minimo=minimum(tree->root);
    tree->current=minimo;
    return minimo->pair;
  }
 return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree!=NULL&&tree->current!=NULL){
    if(tree->current->right!=NULL){
      tree->current=minimum(tree->current->right);
      return tree->current->pair;
    }
    TreeNode* temp=tree->current;
    TreeNode* padre=temp->parent;
    while(padre!=NULL&& temp==padre->right){
      temp=padre;
      padre=padre->parent;
    }
    tree->current=padre;
    if(padre!=NULL){
      return padre->pair;
    }
  }
  return NULL;
}
