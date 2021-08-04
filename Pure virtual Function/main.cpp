#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const double PI = 3.141592653589793238 ;

/* A derived class object aggregates a base class object for the purpose of inheritance. A base class object contains a
virtual table containing a derived class functions addresses which are assigned during creation of a derived class object.*/


/// Shapes.
/// base class.
struct ShapeVTable;
struct Shape
{
    ShapeVTable* vtable;
};
struct ShapeVTable
{
    double (*GetArea)(Shape*);
};

double GetArea(Shape* shape)
{
    shape->vtable->GetArea(shape);
}
/// ------------------------------------------------------------------------------------------------------------------///

/// Circle.
/// Derived class
struct Circle  /// create struct with the name of shape and init shape from base class and make new variables
{
    Shape parent;
    double radius;
};

double GetArea_Circle(Circle* circle)
{
    return  PI* circle->radius * circle->radius;
}

ShapeVTable circle_vtable = {
        (double(*)(Shape*)) GetArea_Circle
};

void CircleInitialize(Circle* circle,double radius)
{
    circle->parent.vtable=&circle_vtable;
    circle->radius=radius;
}
/// ------------------------------------------------------------------------------------------------------------------///

/// Rectangle
/// Derived class
struct Rectangle   /// create struct with the name of shape and init shape from base class and make new variables
{
    Shape parent;
    double height;
    double width;
};

double GetArea_Rectangle(Rectangle* rectangle)
{
    return rectangle->height * rectangle->width;
}

ShapeVTable rectangle_vtable = {
        (double(*)(Shape*)) GetArea_Rectangle
};

void RectangleInitialize(Rectangle* rectangle,double width,double  height)
{
    rectangle->parent.vtable=&rectangle_vtable;
    rectangle->height=height;
    rectangle->width=width;
}
/// -------------------------------------------------------------------------------------------------------------------///

/// Triangle
/// Derived class
struct Triangle    /// create struct with the name of shape and init shape from base class and make new variables
{
    Shape parent;
    double a;
    double b;
    double c;
};

double GetArea_Triangle(Triangle* triangle)
{
    /// Heron's Formula. area = 0.25 * √( (a + b + c) * (-a + b + c) * (a - b + c) * (a + b - c) )
   /// I know all sides of the triangle.
    return  0.25 * sqrt( ( (triangle->a + triangle->b + triangle->c) * ( - triangle-> a  + triangle-> b + triangle->c) * (triangle->a - triangle->b + triangle->c) * (triangle->a + triangle->b - triangle->c) )  );
}

ShapeVTable triangle_vtable = {
        (double(*)(Shape*)) GetArea_Triangle
};

void TriangleInitialize(Triangle* triangle,double a,double b,double c)
{
    triangle->parent.vtable=&triangle_vtable;
    triangle->a=a;
    triangle->b=b;
    triangle->c=c;
}
/// ------------------------------------------------------------------------------------------------------------------///


int main()
{

    Circle circle;
    CircleInitialize(&circle, 10); /// circle with radius 10
    ///CircleInitialize(&circle, 20); /// circle with radius 20
    ///CircleInitialize(&circle, 30); /// circle with radius 30

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); /// rectangle with width 3 and height 5
    /// RectangleInitialize(&rectangle, 6, 7); /// rectangle with width 6 and height 9
    /// RectangleInitialize(&rectangle, 9, 11); /// rectangle with width 9 and height 11

    Triangle triangle;
    TriangleInitialize(&triangle, 7, 4, 12); /// triangle with side lengths: 7, 4, 12     (This is Wrong test Case because 4+7 < 12 )  Output is nan
    /// TriangleInitialize(&triangle, 5, 8, 9); /// triangle with side lengths: 5, 8, 9
    ///TriangleInitialize(&triangle, 15, 14, 13); /// triangle with side lengths: 15, 14, 13

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&triangle;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        /// cout << d << endl;
        total_area+=d;
    }
    cout<<total_area<<endl; /// check if the value is correct
    return 0;
}
