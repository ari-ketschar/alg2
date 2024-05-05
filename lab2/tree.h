#pragma once
#include <memory>
#define STRUCT typedef struct

// Определение ключа для красно-черного дерева
typedef long long TreeKeyType;

// Структура узла красно-черного дерева
STRUCT TreeNode TreeNode;

struct TreeNode {
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    unsigned long long color: 1, key: 63;
};

// Определение красно-черного дерева
STRUCT Tree Tree;

struct Tree {
    TreeNode* root;
};

// Перечисление для цвета узла
enum Color {black = 0, red = 1};

// Создание фиктивного узла для красно-черного дерева
void Tree_create_null_node();
// Уничтожение фиктивного узла для красно-черного дерева
void Tree_destroy_null_node();
// Создание нового экземпляра красно-черного дерева
Tree* Tree_construct();
// Удаление красно-черного дерева
void Tree_destroy(Tree* tree);
// Вставка нового узла в красно-черное дерево
TreeNode* Tree_insert(Tree* tree, TreeKeyType key);
// Восстановление свойств красно-черного дерева после вставки
void Tree_insert_fixup(Tree* tree, TreeNode* z);
// Левый поворот
void Tree_left_rotate(Tree* tree, TreeNode* z);
// Правый поворот
void Tree_right_rotate(Tree* tree, TreeNode* z);
// Удаление узла из красно-черного дерева
void Tree_delete(Tree* tree, TreeNode* z);
// Восстановление свойств красно-черного дерева после удаления
void Tree_delete_fixup(Tree* tree, TreeNode* x);
// Замена узла в красно-черном дереве
void Tree_transplant(Tree* tree, TreeNode* z, TreeNode* v);
// Поиск минимального узла в поддереве
TreeNode* Tree_minimum(TreeNode* root);
// Поиск узла по ключу
TreeNode* Tree_find(Tree* tree, TreeKeyType key);

// Глобальный фиктивный узел
TreeNode* Tree_null_node;

void Tree_create_null_node()
{
    TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));
    res->color = black;
    res->key = 0;
    res->parent = NULL;
    res->left = NULL;
    res->right = NULL;
    Tree_null_node = res;
}

void Tree_destroy_null_node()
{
    free(Tree_null_node);
}

Tree* Tree_construct()
{
    Tree* res = (Tree*)malloc(sizeof(Tree));
    res->root = Tree_null_node;
    return res;
}

void Tree_destroy(Tree* tree)
{
    TreeNode* current = tree->root;
    TreeNode* prev;
    while (current != Tree_null_node)
    {
        if(current->left == Tree_null_node){
            if(current->right == Tree_null_node){
                prev = current;
                current = current->parent;
                free(prev);
            } else{
                prev = current;
                current = current->right;
                current->parent = prev->parent;
                free(prev);
            }
        } else{
            if(current->right == Tree_null_node){
                prev = current;
                current = current->left;
                current->parent = prev->parent;
                free(prev);
            } else{
                prev = current;
                current = current->left;
                current->parent = prev->right;
                prev->right->parent = prev->parent;
                free(prev);
            }
        }
    }
    free(tree);
}

TreeNode* Tree_insert(Tree* tree, TreeKeyType key)
{
    TreeNode* z = (TreeNode*)malloc(sizeof(TreeNode));
    z->key = key;
    TreeNode* y = Tree_null_node;
    TreeNode* x = tree->root;
    while (x != Tree_null_node)
    {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;}
    z->parent = y;
    if (y == Tree_null_node) tree->root = z;
    else if(z->key < y->key) y->left = z;
    else y->right = z;
    z->left = Tree_null_node;
    z->right = Tree_null_node;
    z->color = red;
    Tree_insert_fixup(tree, z);
    return z;
}

void Tree_insert_fixup(Tree* tree, TreeNode* z)
{
    while (z->parent->color == red)
    {
        if (z->parent == z->parent->parent->left){
            TreeNode* y = z->parent->parent->right;
            if(y->color == red){
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->right){
                z = z->parent;
                Tree_left_rotate(tree, z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                Tree_right_rotate(tree, z->parent->parent);
            }
        }
        else{
            TreeNode* y = z->parent->parent->left;
            if(y->color == red){
                z->parent->color = black;
                y->color = black;
                z->parent->parent->color = red;
                z = z->parent->parent;
            }
            else{
                if (z == z->parent->left){
                z = z->parent;
                Tree_right_rotate(tree, z);
                }
                z->parent->color = black;
                z->parent->parent->color = red;
                Tree_left_rotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = black;
}

void Tree_left_rotate(Tree* tree, TreeNode* z)
{
    TreeNode* y = z->right;
    z->right = y->left;