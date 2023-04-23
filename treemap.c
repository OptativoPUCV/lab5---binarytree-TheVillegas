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

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap *auxArbol = (TreeMap*)malloc(sizeof(TreeMap));
  if(auxArbol== NULL) return NULL;
  
  auxArbol->root = NULL;
  auxArbol->current = NULL;

  auxArbol->lower_than = lower_than;
  return auxArbol;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  Pair *ubicacion = searchTreeMap(tree, key);
  if(ubicacion != NULL) return;

  TreeNode *aux =(TreeNode*)malloc(sizeof(TreeNode));
  aux->pair = (Pair*)malloc(sizeof(Pair));
  aux->pair->key =key;
  aux->pair->value = value;
  aux->left = aux->right = aux->parent = NULL;

  if(aux ==NULL)
  {
    tree->root = aux;
    tree->current = aux;
  }

  TreeNode *padre = NULL;
  TreeNode *current = tree->root;
  while(current != NULL)
  {
    padre = current;
    if(tree->lower_than(key,current->pair->key))
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }
  
  if(tree->lower_than(key,padre->pair->key))
  {
    padre->left = aux;
  }
  else{
    padre->right =aux;
  }
  aux->parent = padre;
  tree->current = aux;


}

TreeNode * minimum(TreeNode * x)
{
  while(x->left != NULL) x=x->left;
  return x;

}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node == NULL) return;

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
  TreeNode * auxArbol = tree->root;
  while(auxArbol != NULL)
    {
      if(is_equal(tree, auxArbol->pair->key,key))
      {
        tree->current = auxArbol;
        return auxArbol->pair;
      }
      if(tree->lower_than(key,auxArbol->pair->key))
      {
        tree->current = auxArbol->left;
        auxArbol = auxArbol->left;
      }
      else
      {
        tree->current=auxArbol->right;
        auxArbol = auxArbol->right;
      }
    }
  return NULL;

  

}
Pair * upperBound(TreeMap * tree, void* key) {
  
  TreeNode *auxBase = tree->root;
  TreeNode *auxBuscado = NULL;
  while(auxBase != NULL)
    {
      if(is_equal(tree,auxBase->pair->key,key) == 1)
      {
        return auxBase->pair;
      }
      if(tree->lower_than(key,auxBase->pair->key)== 1)
      {
        auxBuscado = auxBase;
        auxBase = auxBase->left;
      }
      else{
        auxBase = auxBase->right;
      }
    }
  if(auxBuscado == NULL) return NULL;
  return auxBuscado->pair;
  
}

Pair * firstTreeMap(TreeMap * tree) {
  if(tree->root == NULL) return NULL;

  TreeNode *aux = tree->root;
  while(aux->left != NULL)
    {
      aux = aux->left;
    }

  tree->current = aux;
  return aux->pair;
   
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree->current == NULL) return NULL;

  if(tree->current->right != NULL)
  {
    TreeNode *aux = tree->current->right;
    while(aux->left!=NULL)
      {
        aux = aux->left;
      }
    tree->current = aux;
    return tree->current->pair;
  }
  else{
    TreeNode *current = tree->current;
    TreeNode *padre = tree->current->parent;
    while(padre !=NULL && current == padre->right)
      {
        current = padre;
        padre = padre->parent;
      }
    tree->current = padre;
    if(padre == NULL)
    {
      return NULL;
    }
    else{
      return padre->pair;
    }
    
    
  }
    
}
