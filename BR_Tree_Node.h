/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-11-17 23:10:11
 * @LastEditors: Ziguan Jin 18917950960@163.com
 * @LastEditTime: 2023-11-18 19:49:42
 * @FilePath: /black-red-tree/BR_Tree_Node.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef BR_TREE_NODE_H
#define BR_TREE_NODE_H

#include <__config>
#include <utility>

typedef enum{
    RED,
    BLACK,
} Color;

template<typename K, typename V>
class BR_Tree_Node{
public:
    Color color_tag_;
    BR_Tree_Node<K, V> *left_child_, *right_child_, *parent_;
    std::pair<K, V> data_;

public:
    BR_Tree_Node(){
        this->color_tag_ = RED;
        this->left_child_ = this->right_child_ = this->parent_ = nullptr;
        this->data_ = std::pair<K, V>();
    }

    BR_Tree_Node(const std::pair<K, V> &data) : data_(data){
        this->color_tag_ = RED;
        this->left_child_ = this->right_child_ = this->parent_ = nullptr;
    }

    ~BR_Tree_Node() {
        this->left_child_ = this->right_child_ = this->parent_ = nullptr;
    }
};


#endif