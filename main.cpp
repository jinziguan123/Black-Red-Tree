/*
 * @Author: Ziguan Jin 18917950960@163.com
 * @Date: 2023-11-18 19:28:15
 * @LastEditors: Ziguan Jin 18917950960@163.com
 * @LastEditTime: 2023-11-18 19:56:43
 * @FilePath: /black-red-tree/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
 #include<iostream>
#include"BR_Tree.h"

using namespace std;

int main(){
    BR_Tree<char, int> brt;
    brt.Insert(make_pair('A', 1));
    cout<<(*brt.Search('A')).data_.second<<endl;
    brt.Remove('A');
    cout<<(*brt.Search('A')).data_.second<<endl;

    return 0;
}