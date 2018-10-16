
//  Created by Mega Putra on 3/10/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class String
{
private:
    char* pointer;
    static unsigned countA; //to count the number of 'a's
    friend ostream& operator<< (ostream&, const String&);
public:
    String() {pointer = nullptr;} //default constructor
    String(const String &); //copy constructor
    String(const char * c); //'other' constructor
    String getPointer() { return pointer;}
    static unsigned a_count() { return countA;}
    void setCountA(unsigned A) { countA = A; }
    bool operator<(const String&) const;
    void operator=(const String &);
    bool operator==(const String &) const;
    unsigned long operator!(void) const;
    String operator*(void);
    friend String operator+(const String&, const String&);
    const String operator+=(const String&);
    char& operator[] (size_t index) {return pointer[index];}
    ~String() {pointer = nullptr;} //dtor, pointer released in ctor

};

unsigned String::countA = 0;

String::String(const char *c)
{
    pointer = new char[strlen(c) + 1];
    strcpy(pointer, c);
    
    for (int i = 0; i < strlen(c) + 1; i++)
    {
        if (pointer[i] == 'a')
            countA++;
        else countA += 0;
    }
}
String::String(const String &arg)
{
    pointer = new char[strlen(arg.pointer) + 1];
    strcpy(pointer, arg.pointer);
    for (int i = 0; i < strlen(pointer) + 1; i++){
        if (pointer[i] == 'a')
            countA++;
        else countA += 0;
    }
    delete []pointer; //release memory
}

ostream& operator<< (ostream& out, const String &fruit)
{
    if(fruit.pointer  != nullptr)
        {out << fruit.pointer;}
    
    return out;
}

bool String::operator< (const String& obj) const
{
    if(strcmp(pointer, obj.pointer) < 0) {
        return true;
    }
    else if(strcmp(pointer, obj.pointer) > 0) {
        return false;
    }
    else
        return false;
}
bool String::operator== (const String& obj) const
{
    if (strcmp(pointer, obj.pointer)==0)
        return true;
    else
        return false;
}

void String::operator=(const String& obj)
{
    pointer = obj.pointer;
}
unsigned long String::operator!(void) const
{
    unsigned long lettersCount = 0;
    if (pointer == nullptr)
        lettersCount = 0;
    else
        lettersCount = strlen(pointer);

    return lettersCount;
}
String String::operator* (void)
{
    setCountA(0);
    return *this;
}
String operator+(const String&obj1, const String&obj2)
{
    char buffer[24];
    strcpy(buffer, obj1.pointer);
    strcat(buffer, obj2.pointer);

    return buffer;
}

const String String:: operator+=(const String&obj)
{
    char* arr = strcat(pointer, obj.pointer);
    return arr;
}

int main()
{
    // Constructors
    String A("apple");
    String B("banana");
    String C("cantaloupe");
    String D(B);
    String E;
    
    // static member function
    cout << "Number of a's = " << String::a_count() << endl << endl;
    
    // Overloaded insertion operator
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;
    cout << "E = " << E << endl << endl;
    
    // Relational operators
    cout << boolalpha;
    cout << "A < B " << (A < B) << endl;
    cout << "B < A " << (B < A) << endl;
    cout << "A == B " << (A == B) << endl << endl;

    // Assignment operator
    A = B;
    cout << "A = " << A << endl;
    cout << "A == B " << (A == B) << endl << endl;
  
    // Size (bang) operator
    cout << "A size = " << !A << endl;
    cout << "E size = " << !E << endl << endl;

    // Unary * operator
    cout << "C text = " << *C << endl << endl;
    
    // Plus operator
    cout << "A + B = " << A + B << endl << endl;
    
    // Plus equal operator
    A += C;
    cout << "A = " << A << endl << endl;
    
    // Index operator
    cout << "A[3] = " << A[3] << endl << endl;
    
    // static member function
    cout << "Number of a's = " << String::a_count() << endl;
}

