
#ifndef B_tree_h
#define B_tree_h

#include <stdio.h>

using Keytype = double;
using Valuetype = double;

class bptimpl;

struct node;

struct itnlpt
{
public:
    Keytype m_key = 0;
    Valuetype m_value =0 ;
    node* son;
    bool unchanged = true;
    itnlpt();
    ~itnlpt();
};

typedef struct node
{
    node() {m_father = nullptr;m_next = nullptr; m_mother = nullptr;}
    ~node() {}
    itnlpt array[2];
    itnlpt* m_mother;
    node* m_father;
    node* m_next;
    bool full = 0 ;
    virtual bool isroot() {return false;}
    virtual bool isleaf(){return false;}
}Node;


struct leaf: public node
{
    node* m_next;
    virtual bool isleaf(){return true;}
};

struct root: public node
{
    bool isroot(){return true;}
};

class tree
{
public:
    tree();
    ~tree();
    bool insert(node** root, const Keytype key, const Valuetype value);
    bool erase(node**root, const Keytype key);
    bool update(node**root,const Keytype key, const Valuetype value);
    Valuetype lookup(node** root, const Keytype key);
    void split(node* ptr,node* nodee);
};

#endif /* B_tree_h */
