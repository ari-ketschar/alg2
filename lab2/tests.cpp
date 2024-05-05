#include "tree.h"
#include <gtest/gtest.h>

// Проверка: корень черный
bool is_root_black(tree* tree)
{
    return tree->root->color == black;
}

// Проверка: все красные потомки черного узла черные
bool are_red_children_black(tree* tree)
{
    node* cur = tree->root;
    node* prev;
    while (cur != tree_null_node)
    {
        if(cur->left == tree_null_node){
            if(cur->color == red){
                if(!(cur->left->color == black) || !(cur->right->color == black)) return false;
            }
            cur = cur->right;
        } else{
            prev = cur->left;
            while ((prev->right != tree_null_node) && (prev->right != cur))
            {
                prev = prev->right;
            }
            if(prev == tree_null_node){
                prev->right = cur;
                cur = cur->left;
            } else{
                prev->right = tree_null_node;
                if(cur->color == red){
                if(!(cur->left->color == black) || !(cur->right->color == black)) return false;
                }
                cur = cur->right;
            }
        }
    }
    return true;
}

// Проверка: черные высоты всех путей одинаковы
int black_height(node* root){
    if(root == tree_null_node) return 1;
    else if(root->color == red){
        int x = black_height(root->left);
        if(x == black_height(root->right)) return x;
        else return -1;
    } else{
        int x = black_height(root->left);
        if(x == black_height(root->right)) return x + 1;
        else return -1;
    }
}

bool are_black_heights_consistent(tree* tree)
{
    return (black_height(tree->root) != -1);
}

TEST(tree_insert, root_is_black)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    tree_insert(tree, 1);
    tree_insert(tree, 2);
    tree_insert(tree, 3);
    tree_insert(tree, 4);
    tree_insert(tree, 5);

    EXPECT_TRUE(is_root_black(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}

TEST(tree_insert, red_child_is_black)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    tree_insert(tree, 1);
    tree_insert(tree, 2);
    tree_insert(tree, 3);
    tree_insert(tree, 4);
    tree_insert(tree, 5);

    EXPECT_TRUE(are_red_children_black(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}

TEST(tree_insert, black_height_consistent)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    tree_insert(tree, 1);
    tree_insert(tree, 2);
    tree_insert(tree, 3);
    tree_insert(tree, 4);
    tree_insert(tree, 5);

    EXPECT_TRUE(are_black_heights_consistent(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}

TEST(tree_delete, root_is_black)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    for(int i = 1; i < 15; ++i){
        tree_insert(tree, i);
    }
    tree_delete(tree, tree_find(tree, 4));

    EXPECT_TRUE(is_root_black(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}

TEST(tree_delete, red_child_is_black)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    for(int i = 1; i < 15; ++i){
        tree_insert(tree, i);
    }
    tree_delete(tree, tree_find(tree, 4));

    EXPECT_TRUE(are_red_children_black(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}

TEST(tree_delete, black_height_consistent)
{
    tree_create_null_node();
    tree* tree = tree_construct();
    for(int i = 1; i < 15; ++i){
        tree_insert(tree, i);
    }
    tree_delete(tree, tree_find(tree, 4));

    EXPECT_TRUE(are_black_heights_consistent(tree));

    tree_destroy(tree);
    tree_destroy_null_node();
}