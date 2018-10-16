//  The correct code
//  fruit_list.cpp
//  ass9
//
//  Created by Mega Putra on 3/16/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include "fruit_list.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

Fruit_List::Fruit_List() : top(nullptr)
{ }

Fruit_List::~Fruit_List()
{
    Fruit_Node* temp = top;
    while (temp != nullptr)
    {
        top = top -> get_next();
        delete temp;
        temp = top;
    }
}

Fruit_Node* Fruit_List::get_top() const
{
    return top;
}

Fruit_Node* Fruit_List::find_fruit(string item) const
{
    Fruit_Node* temp = top;
    while (temp != nullptr)
    {
        if (temp->get_fruit() == item)
            return temp;
        else
            temp = temp -> get_next();
    }
    return 0;
}

void Fruit_List::print_list()
{
    
    cout << "\n" << setw(11) << fixed << left << "Item" << setw(8) << " Quantity" << endl;
    
    Fruit_Node* temp1 = get_top();
    while(temp1 != nullptr)
    {
        cout << setw(16) << fixed << left << (temp1)->get_fruit() << setw(8) << (temp1)->get_count() << endl;
        temp1 = temp1->get_next();
    }
    cout << endl;
}

void Fruit_List::input_transaction(int c,string f)
{
    Fruit_Node* newFruit = new Fruit_Node(c, f, top);
    
    if(newFruit->get_fruit() == "") return; //if read blank line dont input
    
    if(top == NULL) //list is empty
    {
        top = newFruit;
    }
    else
    {
        Fruit_Node* current = top;
        Fruit_Node* trail = nullptr;
        
        while(current != nullptr) //Find insert location
        {
            if(current->get_fruit() > newFruit->get_fruit())
            {
                break;
            }
            else if(current->get_fruit() == newFruit->get_fruit()) //if duplicate fruit
            {
                current->set_count(current->get_count()+1);
                return;
            }
            else
            {
                trail = current;
                current = current->get_next();
            }
        }
        if (current == top)//insert at head (not empty)
        {
            newFruit->set_next(top);
            top = newFruit;
        }
        else //insert after head (not empty)
        {
            newFruit->set_next(current);
            trail->set_next(newFruit);
        }
    }
}

void Fruit_List::remove_fruit(int line_count, string f)
{
    if (!find_fruit(f))
    {
        cerr << "Unable to remove " << f << " on in line #" << line_count << endl;
        return;
    }
    else
    {
        Fruit_Node* temp1 = top;
        Fruit_Node* temp2 = temp1->get_next();
        if(top->get_fruit() == f) //if first fruit
        {
            if (temp1->get_count() == 1) //if last of first fruit
            {
                top = top->get_next();
                temp1->set_count(temp1->get_count()-1);
                delete temp1;
                return;
            }
            else
            {
                temp1->set_count(temp1->get_count()-1);
            }
        }
        else if (temp1->get_next()== NULL) //if tail fruit
        {
            temp2 = temp1 -> get_next();
            
            if (temp2->get_count() ==1) //if last fruit
            {
                temp2->set_count(temp2->get_count()-1);
                temp1->set_next(temp2->get_next());
                delete temp2;
            }
            else
            {
                temp2->set_count(temp2->get_count()-1);
                temp1->set_next(temp2);
            }
        }
        else //fruit not located at head/tail, locate
        {
            while (temp1->get_next()->get_fruit() != f)
            {
                temp1 = temp1->get_next();
            }
            temp2 = temp1 -> get_next();
            
            if (temp2->get_count() ==1) //if only 1 fruit left
            {
                temp2->set_count(temp2->get_count()-1);
                temp1->set_next(temp2->get_next());
                delete temp2;
            }
            else //not last fruit, decrement
            {
                temp2->set_count(temp2->get_count()-1);
                temp1->set_next(temp2);
            }
        }
    }
}

void Fruit_List:: openFile(ifstream& inFile, string fileName)
{
    inFile.open(fileName.c_str());
    if (!inFile)
    {
        cerr << "Error opening the file: " << fileName << endl;
        exit(1);
    }
    else
    {
        cout << "File "<< fileName << " is opened successfully!" << endl;
    }
    cout << endl;
}

void Fruit_List::getTransactions(ifstream &inFile, int lineCount)
{
    string buffer = "", command = "", tempFruit = "";
    size_t firstSpacePos = 0;
    
    while(!inFile.eof())
    {
        if (buffer[buffer.size()-1] == '\r') buffer.resize(buffer.size()-1);
        
        getline(inFile, buffer);
        lineCount++;
        
        //get command
        firstSpacePos = buffer.find_first_of(" ");
        command = buffer.substr(0, firstSpacePos);
        
        //get fruit
        tempFruit = buffer.substr(firstSpacePos+1, buffer.length());
    
        if (command == "add")
        {
            input_transaction(1, tempFruit);
        }
        else if (command == "remove")
        {
            remove_fruit(lineCount, tempFruit);
        }
        else if(command == "print")
        {
            print_list();
        }
        else if(command == "")
        {
            continue;
        }
        else //misspelled command
        {
            cout <<"Bad transaction: " << command << " in line #" << lineCount << endl;
        }
    }
    inFile.close();
}

ostream& operator<<(ostream& out, const Fruit_List& object)
{
    Fruit_Node* temp = object.get_top();
    
    while (temp != nullptr)
    {
        out << *temp << " ";
        temp = temp -> get_next();
    }
    return out;
}
