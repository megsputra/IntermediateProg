//
//  CIS 22B / Mega Putra / Assignment 10
//  Compiler: Xcode on MacBookPro
//
//  Created by Mega Putra on 3/23/17.
//  Copyright © 2017 Mega Putra. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
using namespace std;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~BASE-QUADRILATERAL~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Quadrilateral 
{
protected:
    int side1;
    int side2;
    string type;
public:
    Quadrilateral(int, int);
    virtual ~Quadrilateral(){}
    int get_side1() const {return side1; }
    int get_side2() const {return side2; }
    virtual void set_type(string s) = 0;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string get_type() const = 0;

};

Quadrilateral::Quadrilateral(int a, int b) : side1(a), side2(b)
{}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~RECTANGLE~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Rectangle: public Quadrilateral
{
public:
    Rectangle(int, int);
    void set_type(string s){type = s;}
    double area(void) const;
    double perimeter(void) const;
    string get_type() const {return type;}

};

Rectangle::Rectangle(int a, int b) : Quadrilateral(a, b)
{}

double Rectangle::area(void) const
{
    return side1 * side2;
}

double Rectangle::perimeter(void) const
{
    return (2. * side1) + (2. * side2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARALLELOGRAM~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Parallelogram: public Quadrilateral
{
private:
    int height;
public:
    Parallelogram(int a, int b, int h);
    int get_height() const { return height;}
    void set_type(string s){type = s;}
    string get_type() const {return type;}
    double area(void) const;
    double perimeter(void) const;
};

Parallelogram::Parallelogram(int a, int b, int h) : Quadrilateral(a,b), height(h)
{}

double Parallelogram::area(void) const
{
    return side1 * height;
}
double Parallelogram::perimeter(void) const
{
    return (2. * side1) + (2. * side2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~SQUARE~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Square: public Rectangle
{
public:
    Square(int);
    string get_type() const {return type;}
    void set_type(string s){type = s;}
   // void set_type(string s) {s = type;}
    double area(void) const;
    double perimeter(void) const;
};

Square::Square(int a) : Rectangle(a, a)
{}

double Square::area(void) const
{
    return side1 * side2;
}
double Square::perimeter(void) const
{
    return 4 * side1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~RHOMBUS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Rhombus: public Parallelogram
{
public:
    Rhombus(int, int);
    string get_type() const {return type;}
    void set_type(string s){type = s;}
   // void set_type(string s) {s = type;}
    double area(void) const;
    double perimeter(void) const;
};

Rhombus::Rhombus(int s1, int h) : Parallelogram(s1, s1, get_height())
{}

double Rhombus::area(void) const
{
    return side1 * get_height();
}
double Rhombus::perimeter(void) const
{
    return 4 * side1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~NON-MEMBER FUNCTIONS~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
Quadrilateral* createQuadrilateralFromString(string buffer)
{
    if (buffer[buffer.size()-1] == '\r') buffer.resize(buffer.size()-1);
    
    string shape = ""; size_t pos = 0;
    int side1 =0, side2 =0, side3 = 0;
    Quadrilateral* ptr = NULL;

    pos = buffer.find_first_of(" ");
    buffer[0] = toupper(buffer[0]);
    shape = buffer.substr(0, pos);
    
    side1 = stoi(buffer.substr(pos, pos + 1));
    
    if (shape == "Rectangle")
    {
        side2 = stoi(buffer.substr(pos + 2, pos + 3));
        ptr = new Rectangle(side1, side2);
        ptr->set_type(shape);
    }
    else if (shape == "Square")
    {
        ptr = new Square(side1);
        ptr->set_type(shape);
    }
    else if ( shape == "Parallelogram")
    {
        side2 = stoi(buffer.substr(pos+2, pos+3));
        side3 = stoi(buffer.substr(pos+4, pos + 5));
        ptr = new Parallelogram(side1, side2, side3);
        ptr->set_type(shape);
    }
    else
    {
        side2 = stoi(buffer.substr(pos+2, pos+3));
        ptr = new Rhombus(side1, side2);
        ptr->set_type(shape);
    }
    return ptr;
}

ostream& operator <<(ostream& out, const Quadrilateral& q)
{
    out << q.get_type() << ":  ";
    if (q.get_type() == "Rhombus" || q.get_type() == "Square")
    {
        out << "side " << q.get_side1();
    }
    else
        out << "sides " << q.get_side1() << " and " << q.get_side2();
    
    out << "  area=" << q.area() << "  perimeter=" << q.perimeter();
    return out;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~MAIN~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
    const string filename = "ass10_data.txt";
    ifstream fin(filename.c_str());
    if (!fin)
    {
        cerr << "Unable to open " << filename << endl;
        exit(1);
    }
    string buffer;
    Quadrilateral* ptrQuad;
    while (getline(fin,buffer))
    {
        if (buffer.size() > 1)
        {
            ptrQuad = createQuadrilateralFromString(buffer);
            cout << *ptrQuad << endl;
            delete ptrQuad;
        }
    }
    fin.close();
}

