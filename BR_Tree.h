/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-11-18 00:51:35
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-11-18 16:17:27
 * @FilePath: /black-red-tree/BR_Tree.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef BR_TREE_H
#define BR_TREE_H
#include"BR_Tree_Node.h"
#include <__config>
#include <utility>

template <typename K, typename V>
class BR_Tree{
private:
    BR_Tree_Node<K, V> *root_;

public:
    BR_Tree<K, V>(std::pair<K, V> data);
    ~BR_Tree<K, V>();

    //functional functions
    void LeftRotate(BR_Tree_Node<K, V> *cur);
    void RightRotate(BR_Tree_Node<K, V> *cur);
    void RLRotate(BR_Tree_Node<K, V> *cur);
    void LRRotate(BR_Tree_Node<K, V> *cur);
    bool Insert(const std::pair<K, V> &data);
    bool Remove(const K &key);
    BR_Tree_Node<K, V>* Search(const K &key);
    bool IsBRTree();
    
};

template<typename K, typename V>
void BR_Tree<K, V>::LeftRotate(BR_Tree_Node<K, V> *cur) {
    BR_Tree_Node<K, V> *right_child = cur->right_child_, *left_grandson = right_child->left_child_;
    BR_Tree_Node<K, V> *parent = cur->parent_;
    cur->right_child_ = left_grandson;
    if(left_grandson){
        left_grandson->parent_ = cur;
    }
    right_child->left_child_ = cur;
    cur->parent_ = right_child;

    if(parent == nullptr){
        this->root_ = right_child;
        this->root_->parent_ = nullptr;
    }else{
        if(cur == parent->left_child_){
            parent->left_child_ = right_child;
        }else{
            parent->right_child_ = right_child;
        }
        right_child->parent_ = parent;
    }
}

template <typename K, typename V>
void BR_Tree<K, V>::RightRotate(BR_Tree_Node<K, V> *cur){
    BR_Tree_Node<K, V> *parent = cur->parent_;
    BR_Tree_Node<K, V> *left_child = cur->left_child_;
    BR_Tree_Node<K, V> *right_grandson = left_child->right_child_;
    cur->left_child_ = right_grandson;
    if(right_grandson){
        right_grandson->parent_ = cur;
    }
    left_child->right_child_ = cur;
    cur->parent_ = left_child;

    if(parent == nullptr){
        this->root_ = left_child;
        this->root_->parent_ = nullptr;
    }else{
        if(cur == parent->left_child_){
            parent->left_child_ = left_child;
        }else{
            parent->right_child_ = left_child;
        }
        left_child->parent_ = parent;
    }
}

template <typename K, typename V>
void BR_Tree<K, V>::RLRotate(BR_Tree_Node<K, V> *cur){
    RightRotate(cur->right_child_);
    LeftRotate(cur);
}

template <typename K, typename V>
void BR_Tree<K, V>::LRRotate(BR_Tree_Node<K, V> *cur){
    LeftRotate(cur->left_child_);
    RightRotate(cur);
}

template <typename K, typename V>
bool BR_Tree<K, V>::Insert(const std::pair<K, V> &data){
    if(this->root_ == nullptr){
        this->root_ = new BR_Tree_Node<K, V>(data);
        this->root_->color_tag_ = BLACK;
        return true;
    }
    BR_Tree_Node<K, V> *cur = this->root_;
    BR_Tree_Node<K, V> *pre = nullptr;

    while(cur){
        if(data.first < cur->data_.first){
            pre = cur;
            cur = cur->left_child_;
        }else if (data.first > cur->data_.first) {
            pre = cur;
            cur = cur->right_child_;
        }else {
            return false;
        }
    }

    cur = new BR_Tree_Node<K, V>(data);
    BR_Tree_Node<K, V> *new_node_location = cur;

    if(data.first < pre->data_.first){
        pre->left_child_ = cur;
        cur->parent_ = pre;
    }else {
        pre->right_child_ = cur;
        cur->parent_ = pre;
    }

    //开始调整红黑树
    //1. 如果父节点是红色的
    while(pre && pre->color_tag_ == RED){
        BR_Tree_Node<K, V> *grandfather = pre->parent_;
        if(pre == grandfather->left_child_){
            BR_Tree_Node<K, V> *uncle = grandfather->right_child_;
            if(uncle->color_tag_ == RED && uncle){
                //如果叔叔结点为红色，调整颜色即可
                pre->color_tag_ = uncle->color_tag_ = BLACK;
                grandfather->color_tag_ = RED;
                //向上处理
                cur = grandfather;
                pre = cur->parent_;
            }else {
                //如果叔叔不存在，或者叔叔存在但是为黑色
                if(cur == pre->left_child_){
                    //如果祖孙三代为直线，旋转+染色
                    RightRotate(grandfather);
                    grandfather->color_tag_ = RED;
                    pre->color_tag_ = BLACK;
                }else {
                    //祖孙三代为折线，需要双旋+染色
                    LRRotate(grandfather);
                    grandfather->color_tag_ = RED;
                    cur->color_tag_ = BLACK;
                }
                //不用向上调整颜色了，因为此时根为黑色
                break;
            }
        }else {
            BR_Tree_Node<K, V> *uncle = grandfather->left_child_;
            if(uncle && uncle->color_tag_ == RED){
                uncle->color_tag_ = pre->color_tag_ = BLACK;
                grandfather->color_tag_ = RED;
                //向上处理
                cur = grandfather;
                pre = cur->parent_;
            }else {
                if(cur == pre->left_child_){
                    //祖孙三代为折线
                    RLRotate(grandfather);
                    cur->color_tag_ = BLACK;
                    grandfather->color_tag_ = RED;
                }else {
                    LeftRotate(grandfather);
                    pre->color_tag_ = BLACK;
                    grandfather->color_tag_ = RED;
                }
                break;
            }
        }
    }
    //根结点可能被子树向上调整颜色时变成红色，这里要改回来
    this->root_->color_tag_ = BLACK;
    return true;
}

template <typename K, typename V>
bool BR_Tree<K, V>::IsBRTree(){
    if(this->root_ == nullptr)
        return true;
    if(this->root_->color_tag_ == RED)
        throw "根结点为红色";
    BR_Tree_Node<K, V> *cur = this->root_;
    int count = 0;
    while(cur){
        if(cur->color_tag_ == BLACK)
            count++;
        cur = cur->left_child_;
    }
    int black_count = 0;
    return IsBRTreeHelper(this->root_, count, black_count);
}

template <typename K, typename V>
bool IsBRTreeHelper(BR_Tree_Node<K, V> *cur, int count, int black_count){
    if(cur == nullptr){
        if(count != black_count){
            return false;
        }
        return true;
    }
    if(cur->color_tag_ == RED && cur->parent_->color_tag_ == RED){
        return false;
    }
    if(cur->color_tag_ == BLACK)
        black_count++;
    return IsBRTreeHelper(cur->left_child_, count, black_count) && IsBRTreeHelper(cur->right_child_, count, black_count);
}

template <typename K,typename V>
BR_Tree_Node<K, V>* BR_Tree<K, V>::Search(const K &key){
    BR_Tree_Node<K, V>* cur = this->root_;
    while(cur){
        if(key < cur->data_.first)
            cur = cur->left_child_;
        else if (key > cur->data_.first) {
            cur = cur->right_child_;
        }else {
            return cur;
        }
    }
    return nullptr;
}

template <typename K, typename V>
bool BR_Tree<K, V>::Remove(const K &key){
    BR_Tree_Node<K, V> *cur = this->root_, *pre = nullptr;
    //标记需要删除的结点以及他的父节点
    BR_Tree_Node<K, V> *delete_pre = nullptr, *delete_node = nullptr;

    while(cur){
        if(key < cur->data_.first){
            pre = cur;
            cur = cur->left_child_;
        }else if (key > cur->data_.first) {
            pre = cur;
            cur = cur->right_child_;
        }else {
            //找到结点后进行判断
            if(cur->left_child_ == nullptr){
                if(cur == this->root_){
                    //如果当前为根结点
                    this->root_ = this->root_->right_child_;
                    if(this->root_){
                        this->root_->parent_ = nullptr;
                        this->root_->color_tag_ = BLACK;
                    }
                    delete cur;
                    return true;
                }else {
                    //如果不是根结点
                    delete_pre = pre;
                    delete_node = cur;
                }
                break;
            }else if (cur->right_child_ == nullptr) {
                if(cur == this->root_){
                    this->root_ = this->root_->left_child_;
                    if(this->root_){
                        this->root_->parent_ = nullptr;
                        this->root_->color_tag_ = BLACK;
                    }
                    delete cur;
                    return true;
                }else {
                    delete_node = cur;
                    delete_pre = pre;
                }
                break;
            }else {
                //左右子树均不为空
                //将右子树中最小的结点替换到cur结点中，这样只需要删除末端结点即可
                BR_Tree_Node<K, V> *min_parent = cur, *min_right = cur->right_child_;
                while(min_right->left_child_){
                    //寻找最小的右子树结点
                    min_parent = min_right;
                    min_right = min_right->left_child_;
                }
                //进行替换，更新删除标记
                cur->data_.first = min_right->data_.first;
                cur->data_.second = min_right->data_.second;
                delete_node = min_right;
                delete_pre = min_parent;
                break;
            }
        }
    }
    if(delete_node == nullptr){
        //没找到需要删除的结点
        return false;
    }

    //在删除之前需要调整红黑树的颜色
    //这里保存删除结点的相关信息方便在调整完颜色之后的删除操作
    cur = delete_node;
    pre = delete_pre;

    if(delete_node->color_tag_ == BLACK){
        if(delete_node->left_child_){
            delete_node->left_child_->color_tag_ = BLACK;
        }else if (delete_node->right_child_) {
            delete_node->right_child_->color_tag_ = BLACK;
        }else {
            //左右子树都空
            while(delete_node != this->root_){
                //可能需要调整到根结点
                //一共有四种可能的情况
                if(delete_node == delete_pre->left_child_){
                    //如果待删除结点为左孩子
                    BR_Tree_Node<K, V> *brother = delete_pre->right_child_;
                    if(brother->color_tag_ == RED){
                        //1. 如果brother结点为红色
                        delete_pre->color_tag_ = RED;
                        brother->color_tag_ = BLACK;
                        LeftRotate(delete_pre);
                        brother = delete_pre->right_child_;
                    }
                    if((brother->left_child_ == nullptr || brother->left_child_->color_tag_ == BLACK) &&
                            (brother->right_child_ == nullptr || brother->right_child_->color_tag_ == BLACK)){
                        //2.如果brother结点为黑色，并且其左右孩子要么为黑色要么为空
                        brother->color_tag_ = RED;
                        if(delete_pre->color_tag_ == RED){
                            //如果父结点的颜色为红色，说明不需要继续调整，直接跳出循环
                            delete_pre->color_tag_ = BLACK;
                            break;
                        }
                        //否则说明这是调整中的某一个情况，需要继续向上调整
                        delete_node = delete_pre;
                        delete_pre = delete_node->parent_;
                    }else {
                        if(brother->right_child_ == nullptr || brother->right_child_->color_tag_ == BLACK){
                            //3.brother为黑色，并且左孩子为红色，右孩子为黑色或者为空
                            brother->left_child_->color_tag_ = BLACK;
                            brother->color_tag_ = RED;
                            RightRotate(brother);
                            //这样就进入了情况4
                            brother = delete_pre->right_child_;
                        }else {
                            //4.brother为黑色，并且右孩子为红色
                            brother->color_tag_ = delete_pre->color_tag_;
                            delete_pre->color_tag_ = BLACK;
                            brother->right_child_->color_tag_ = BLACK;
                            LeftRotate(delete_pre);
                            break;
                        }
                    }
                }else {
                    //待删除结点为父节点的右孩子
                    BR_Tree_Node<K, V> *brother = delete_pre->left_child_;
                    if(brother->color_tag_ == RED){
                        //1.brother结点为红色
                        delete_pre->color_tag_ = RED;
                        brother->color_tag_ = BLACK;
                        RightRotate(delete_pre);
                        brother = delete_pre->left_child_;
                    }
                    if((brother->left_child_ == nullptr || brother->left_child_->color_tag_ == BLACK) &&
                            (brother->right_child_ == nullptr || brother->right_child_->color_tag_ == BLACK)){
                        //2.如果brother为黑色，并且其左右孩子为黑色或者为空
                        brother->color_tag_ = RED;
                        if(delete_pre->color_tag_ == RED){
                            delete_pre->color_tag_ = BLACK;
                            break;
                        }
                        delete_node = delete_pre;
                        delete_pre = delete_node->parent_;
                    }else {
                        //3.如果brother为黑色，并且右孩子为红色，左孩子为黑色或者为空
                        if(brother->left_child_ == nullptr || brother->left_child_->color_tag_ == BLACK){
                            brother->color_tag_ = RED;
                            brother->right_child_->color_tag_ = BLACK;
                            LeftRotate(brother);
                            //更新brother，进入情况4
                            brother = delete_pre->left_child_;
                        }else {
                            //4.brother为黑色，并且左孩子为红色
                            brother->color_tag_ = delete_pre->color_tag_;
                            delete_pre->color_tag_ = BLACK;
                            brother->left_child_->color_tag_ = BLACK;
                            RightRotate(delete_pre);
                            break;
                        }
                    }
                }
            }
        }
    }

    //开始正式删除结点
    //由于之前的染色操作把删除结点的相关结点都变成了情况4，所以操作方便许多
    delete_node = cur;
    delete_pre = pre;

    if(delete_node->left_child_ == nullptr){
        //删除结点没有左子树
        if(delete_node == delete_pre->left_child_){
            //如果删除结点为左孩子
            delete_pre->left_child_ = delete_node->right_child_;
            if(delete_node->right_child_){
                //如果有右孩子
                delete_node->right_child_->parent_ = delete_pre;
            }
        }else {
            //删除结点为右孩子
            delete_pre->right_child_ = delete_node->right_child_;
            if(delete_node->right_child_)
                delete_node->right_child_->parent_ = delete_pre;
        }
    }else {
        //删除结点没有右子树
        if(delete_node == delete_pre->left_child_){
            //如果为左结点
            delete_pre->left_child_ = delete_node->left_child_;
            if(delete_node->left_child_){
                delete_node->left_child_.parent_ = delete_pre;
            }
        }else {
            //为右结点
            delete_pre->right_child_ = delete_node->left_child_;
            if(delete_node->left_child_)
                delete_node->left_child_->parent_ = delete_pre;
        }
    }
    
    delete delete_node;
    return true;
}

#endif