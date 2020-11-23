//
//  main.cpp
//  B+tree
//
//  Created by Zixiang  Pei on 9/5/18.
//  Copyright © 2018 Zixiang  Pei. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "B+tree.h"

using namespace std;

int main()
{
    node * new_node  = new root;
    cout << new_node << std::endl;
    tree* new_tree = new tree;
    for(int a = 1; a <=1000; a++)
    {
        new_tree->insert(&new_node, a, a);
        //cout << new_tree->lookup(&new_node, a ) << endl;
    }
    
    for(int a = 1000; a >=1; a--)
    {
        //new_tree->insert(&new_node, a, a);
        cout << new_tree->lookup(&new_node, a)<< " no"<< endl;
    }
    
//    for(int a = 10; a >=1; a--)
//    {
//
//        //new_tree->insert(&new_node, a, a);
//        new_tree->erase(&new_node, a);
//    }
//    for(int a = 10; a >=1; a--)
//    {
//        //new_tree->insert(&new_node, a, a);
//        cout << new_tree->lookup(&new_node, a)<< " no"<< endl;
//        if(a == 10)
//            cout << endl;
//    }
    
    
//    for(int a = 0; a <= 50; a+=2)no
//    {
//        new_tree->erase(&new_node, a);
//        cout << new_tree->lookup(&new_node,a) << a << endl;
//    }
//    for(int a = 50; a <= 100; a+=2)
//    {
//       // new_tree->insert(&new_node, a, a);
//        cout << new_tree->lookup(&new_node, a )  << endl;
//    }
//    for(int a = 50; a <= 100; a+=2)
//    {
//        new_tree->update(&new_node, a, 2*a);
//        cout << new_tree->lookup(&new_node, a )  << "yes" << endl;
//    }
    //new_tree->erase(&new_node, 2);
//    cout << new_tree->lookup(&new_node, 2 ) << "happy"<< endl;
//    //new_tree->erase(&new_node, 4);
//    cout << new_tree->lookup(&new_node, 4 ) << "happy"<< endl;
//    //new_tree->erase(&new_node, 4);
//    cout << new_tree->lookup(&new_node, 76 ) << "happy"<< endl;
}
