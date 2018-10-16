//  The correct code
//  fruit_list.hpp
//  ass9
//
//  Created by Mega Putra on 3/16/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#ifndef fruit_list_h
#define fruit_list_h

#include <stdio.h>
#include "fruit.h"
#include <iostream>
#include <string>

class Fruit_List
{
   Fruit_Node* top;
public:
    Fruit_List();
    ~Fruit_List();
    void remove_fruit(int, string);
    void print_list();
    void input_transaction(int,string);
    void openFile(ifstream&, string);
    void getTransactions(ifstream &, int);
    Fruit_Node* get_top() const;
    Fruit_Node* find_fruit(string item) const;
};

ostream& operator<<(ostream&, const Fruit_List&);

#endif /* fruit_list_hpp */
