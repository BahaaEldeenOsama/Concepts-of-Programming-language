#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const double PI = 3.141592653589793238 ;

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


struct Circle
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

struct Rectangle
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


struct Triangle
{
    Shape parent;
    double a;
    double b;
    double c;
};

double GetArea_Triangle(Triangle* triangle)
{
    return (triangle->a + triangle->b  + triangle->c) / 2 ;
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


int main()
{

    Circle circle;
    CircleInitialize(&circle, 10); /// circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); /// rectangle with width 3 and height 5

    Triangle triangle;
    TriangleInitialize(&triangle, 7, 4, 12); /// triangle with side lengths: 7, 4, 12


    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&triangle;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
    }
    cout<<total_area<<endl; /// check if the value is correct
    return 0;
}
