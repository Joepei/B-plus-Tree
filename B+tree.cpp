#include "B+tree.h"
#include <stdlib.h>
#include <iostream>

itnlpt :: itnlpt ():son(nullptr){} // todo

itnlpt :: ~itnlpt(){}

tree :: tree(){}//root(nullptr){}// todo

tree:: ~tree(){}

bool tree:: insert(node **root, const Keytype key, const Valuetype value)
{
    if (lookup(root, key))
        return false;
    else
    {
        node* temp = *root;
        if(temp->array[0].son == nullptr)
        {
            std:: cout << "nihao"<< std:: endl;
            node* new_leaf = new leaf;
            std:: cout << new_leaf << std:: endl;
            temp->array[0].son =new_leaf;
            new_leaf->m_father = temp;
            new_leaf->m_mother = &(temp->array[0]);
            new_leaf->array[0].m_key = key;
            new_leaf->array[0].m_value = value;
            new_leaf->array[0].unchanged = false;
            return true;
        }
        while(temp->array[0].son != nullptr)
        {
            if(temp->array[1].son != nullptr)
            {
                if(key > temp->array[1].m_key)
                    temp = temp->array[1].son;
                else
                    temp = temp->array[0].son;
            }
            else
                temp = temp->array[0].son;
        }
        if(temp->array[1].unchanged == true)
        {
            if(key > temp->array[0].m_key)
            {
                std:: cout << "hello"<< std::endl;
                temp->array[1].m_key = key;
                temp->array[1].m_value = value;
                temp->array[1].unchanged = false;
            }
            else
                {
                    Keytype t1 = temp->array[0].m_key;
                    Valuetype t2 = temp->array[0].m_value;
                    temp->array[0].m_key = key;
                    temp->array[0].m_value= value;
                    temp->array[1].m_key = t1;
                    temp->array[1].m_value= t2;
                    temp->array[1].unchanged = false;
                    temp->full = true;
                    while(!temp->m_father->isroot() && temp->array[0].m_key != temp->m_mother->m_key)
                    {
                        temp->m_mother->m_key = temp->array[0].m_key;
                        temp = temp->m_father;
                    }
                }
        }
        else
        {
            leaf* new_leaf = new leaf;
            std::  cout << new_leaf << std:: endl;
            new_leaf->array[0].m_key = key;
            new_leaf->array[0].m_value = value;
            new_leaf->array[0].unchanged = false;
            split(temp, new_leaf);
        }
    return true;// todo
    }
}

bool tree:: erase(node **root, const Keytype key)
{
    if (!lookup(root, key))
        return false;
    else
    {
        node*temp = *root;
        while(temp->array[0].son != nullptr)
        {
            if (temp->array[1].son!= nullptr)
            {
                if(key >= temp->array[1].m_key)
                    temp = temp->array[1].son;
                else
                    temp = temp->array[0].son;
            }
            else
            {
                //if(temp->array[1].unchanged == false)
                if(temp->array[1].m_key == key)
                    break;
                temp = temp->array[0].son;
            }
        }
        if (temp->full)
        {
            if (key == temp->array[1].m_key)
            {
                temp->array[1].m_key = 0;
                temp->array[1].m_value = 0;
                temp->array[1].unchanged = true;
                temp->full = false;
                return true;
            }
            else
            {
                temp->array[0].m_key = temp->array[1].m_key;
                temp->array[0].m_value = temp->array[1].m_value;
                temp->array[1].unchanged = true;
                temp->full = false;
                while(!temp->m_father->isroot() && temp->array[0].m_key != temp->m_mother->m_key)
                {
                    temp->m_mother->m_key = temp->array[0].m_key;
                    temp = temp->m_father;
                }
            }
        }
        else
        {
//            node* temp2 = temp->m_father;
//            leaf* new_leaf = new leaf;
//            new_leaf->array[0].m_key = temp2->array[0].m_key;
//            new_leaf->array[1].m_key = temp2->array[1].m_key;
//            if(!temp2->array[1].unchanged)
//                new_leaf->array[1].unchanged = false;
//            new_leaf->m_mother= temp2->m_mother;
//            new_leaf->m_father=
            temp->m_mother->son = nullptr;
            delete temp;
            erase(root, key);
        }
    }
    return true;
}

Valuetype tree:: lookup(node **root, const Keytype key)
{
    
    node* temp = *root;
    if (temp->array[0].son == nullptr)
    {
        return false;
    }
    
    while(/*!temp->isleaf() ||*/ temp->array[0].son!= nullptr)
    {
        if(temp->array[1].son != nullptr)
        {
            if(key >= temp->array[1].m_key)
                temp = temp->array[1].son;
            else
                temp = temp->array[0].son;
        }
        else
        {
            //if(temp->array[1].unchanged == false)
            if(temp->array[1].m_key == key)
                return true;
            temp = temp->array[0].son;
            std:: cout << std:: endl;
        }
    }
    if(key == temp->array[0].m_key)
    {
        
        return temp->array[0].m_value;
        
    }
    else
        if(!temp->array[1].unchanged)
             if(key == temp->array[1].m_key)
                 return temp->array[1].m_value;
    std:: cout << "shazi" << std:: endl;
    return false;
}

bool tree:: update(node**root, const Keytype key, const Valuetype value)
{
    node* temp = *root;
    if (temp->array[0].son == nullptr)
    {
        return false;
    }
    
    while(/*!temp->isleaf() ||*/ temp->array[0].son!= nullptr)
    {
        if(temp->array[1].son != nullptr)
        {
            if(key >= temp->array[1].m_key)
                temp = temp->array[1].son;
            else
                temp = temp->array[0].son;
        }
        else
        {
            temp = temp->array[0].son;
        }
    }
    if(temp->array[0].m_key == key)
    {
        temp->array[0].m_value = value;
    }
    else
        temp->array[1].m_value = value;
    return true;
}

void tree:: split(node *ptr, node *nodee)
{
    if(ptr->array[1].m_key > nodee->array[0].m_key && ptr->array[0].m_key < nodee->array[0].m_key)
    {
        std:: cout << "what"<< std:: endl;
        Keytype ktemp  = nodee->array[0].m_key;
        Valuetype vtemp = nodee->array[0].m_value;
        nodee->array[0].m_key = ptr->array[1].m_key;
        nodee->array[0].m_value = ptr->array[1].m_value;
        ptr->array[1].m_key = ktemp;
        ptr->array[1].m_value = vtemp;
        if(ptr->array[0].son!= nullptr)//not sure
        {
            node* temp1 = nodee->array[0].son;
            nodee->array[0].son = ptr->array[1].son;
            nodee->array[0].son->m_mother = &nodee->array[0]; //&ptr->array[1];
            nodee->array[0].son->m_father = nodee;//ptr;
            ptr->array[1].son = temp1;
            ptr->array[0].son->m_mother = &ptr->array[0];//&nodee->array[0];
            ptr->array[0].son->m_father = ptr;//nodee;
        }
    }
    else if (ptr->array[0].m_key > nodee->array[0].m_key)
    {
        std:: cout << "shenme" << std:: endl;
        Keytype ktemp  = nodee->array[0].m_key;
        Valuetype vtemp = nodee->array[0].m_value;
        nodee->array[0].m_key = ptr->array[1].m_key;
        nodee->array[0].m_value = ptr->array[1].m_value;
        ptr->array[1].m_key = ptr->array[0].m_key;
        ptr->array[1].m_value =ptr->array[0].m_value;
        ptr->array[0].m_key =ktemp;
        ptr->array[0].m_value =vtemp;
        if(ptr->array[0].son!= nullptr)
        {
            node* temp2 = nodee->array[0].son;
            nodee->array[0].son = ptr->array[1].son;
            nodee->array[0].son->m_mother = &nodee->array[0];// &ptr->array[1];
            nodee->array[0].son->m_father = nodee;//ptr;
            ptr->array[1].son = ptr->array[0].son;
            ptr->array[1].son->m_mother = &ptr->array[1];// &ptr->array[0];
            ptr->array[1].son->m_father = ptr;
            ptr->array[0].son = temp2;
            ptr->array[0].son->m_mother = &ptr->array[0];
            ptr->array[0].son->m_father = ptr;
        }
    }
    if (ptr->m_father->isroot())
    {
        std:: cout << "wodema" << std::endl;
        struct node* new_parent = new struct node;
        std:: cout << new_parent << std:: endl;
        new_parent->array[0].m_key = ptr->array[0].m_key;
        new_parent->array[0].m_value = ptr->array[0].m_value;
        new_parent->array[1].m_key = nodee->array[0].m_key;
        new_parent->array[1].m_value = nodee->array[0].m_value;
        new_parent->m_father = ptr->m_father;
        new_parent->m_mother = ptr->m_mother;
        (*ptr->m_mother).son = new_parent;
        new_parent->array[0].son = ptr;
        new_parent->array[1].son = nodee;
        ptr->m_mother = &new_parent->array[0];
        ptr->m_father = new_parent;
        nodee->m_mother =&new_parent->array[1];
        nodee->m_father = new_parent;
        new_parent->full = true;
        if (ptr->isleaf())
        {
            std:: cout << "909090" << std:: endl;
            ptr->m_next = nodee;
        }
    }
    else
    {
        if(!ptr->m_father->full)
        {
            ptr->m_father->array[1].m_key = nodee->array[0].m_key;
            ptr->m_father->array[1].m_value = nodee->array[0].m_value;
            nodee->m_father = ptr->m_father;
            nodee->m_mother = &ptr->m_father->array[1];
            nodee->m_mother->son = nodee;
            ptr->m_father->full = true; 
            node* temp = ptr;
            if (ptr->isleaf())
            {
                std:: cout << "909090" << std:: endl;
                if (ptr->m_next != nullptr)
                {
                    nodee->m_next = ptr->m_next;
                }
                ptr->m_next = nodee;
            }
            while(!temp->m_father->isroot() && temp->array[0].m_key != temp->m_mother->m_key)
            {
                temp->m_mother->m_key = temp->array[0].m_key;
                temp = temp->m_father;
            }
            
        }
        else
        {
            node* new_node = new node;
            new_node->array[0].m_key = nodee->array[0].m_key;
            new_node->array[0].m_value = nodee->array[0].m_value;
            nodee->m_mother = &new_node->array[0];
            nodee->m_father = new_node;
            new_node->array[0].son = nodee;
            if (ptr->m_next != nullptr)
            {
                nodee->m_next = ptr->m_next;
            }
            ptr->m_next = nodee;
            split(ptr->m_father, new_node);
        }
    }
}

