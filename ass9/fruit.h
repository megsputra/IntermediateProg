//  The correct code
//  fruit.h
//  ass9
//
//  Created by Mega Putra on 3/15/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#ifndef fruit_h
#define fruit_h

#include <iostream>
#include <string>
using namespace std;

class Fruit_Node
{
    int	count;
    string fruit;
    Fruit_Node*	next;
public:
    Fruit_Node(int c, string f, Fruit_Node* n);
    int get_count() const;
    Fruit_Node* get_next() const;
    string get_fruit() const;
    void set_next(Fruit_Node* ptr);
    void set_count(int a);
};

ostream& operator<<(ostream&, const Fruit_Node&);
#endif /* fruit_h */
