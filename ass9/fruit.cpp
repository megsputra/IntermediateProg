//  The correct code
//  fruit.cpp
//  ass9
//
//  Created by Mega Putra on 3/15/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <stdio.h>
#include "fruit.h"
#include <iostream>


Fruit_Node::Fruit_Node(int c, string f, Fruit_Node*n)
: count(c), fruit(f), next(n)
{}

int Fruit_Node::get_count() const
{
    return count;
}

string Fruit_Node::get_fruit() const
{
    return fruit;
}

Fruit_Node* Fruit_Node::get_next() const
{
    return next;
}

void Fruit_Node::set_next(Fruit_Node* ptr)
{
    next = ptr;
}
void Fruit_Node::set_count(int a)
{
    count = a;
}

ostream& operator<<(ostream& out, const Fruit_Node& obj)
{
    out << obj.get_fruit();
    return out;
}
