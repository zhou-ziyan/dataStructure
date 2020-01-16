//
// Created by qixuecheng on 2019/9/19.
//

#ifndef CIRLINKEDLIST_CIRLINKEDLIST_H
#define CIRLINKEDLIST_CIRLINKEDLIST_H

#include <iostream>
using namespace std;

typedef int Node_entry;

struct Node{

    Node(){};
    Node(Node_entry entry, Node *next = NULL) : entry(entry), next(next) {}
    Node_entry  entry;
    Node *next;
};

class CirLinkedList {
public:
    CirLinkedList();
    ~CirLinkedList();

    void create_cirlinkedlist(int n);//创建长度为n的循环链表
    void append(Node_entry entry);//在头部插入一个节点
    Node *get_node(int m);//获得第m个节点
    void del_node(Node* node, int m);  //从节点node开始删除第m个节点
    int get_length();//获得循环链表的长度
    void print();//从头部打印循环链表

private:
    Node * head;
};

#endif //CIRLINKEDLIST_CIRLINKEDLIST_H
