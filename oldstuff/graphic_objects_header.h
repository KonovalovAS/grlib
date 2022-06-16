#ifndef GRAPHIC_OBJECTS_HEADER_H_INCLUDED
#define GRAPHIC_OBJECTS_HEADER_H_INCLUDED

#include "demonstration_header.h"

class Graphic_object{
public:
    vPoint data;
    int r,g,b;

    virtual void set_color(int red=0, int green=0, int blue=0);
    void relocate(int delta_x, int delta_y);
    void rotation(double angle, Point center);
    void transformation( vvdb &lop, Point center );

    virtual void draw(Vint &canvas);

    // virtual Graphic_object& operator=(const Graphic_object& right);

    virtual Graphic_object* dublicate();

};

//=

class Points : public Graphic_object{
public:
    Points(vPoint inc_data, int red=255, int green=255, int blue=255);
    Points(Point single_point, int red=255, int green=255, int blue=255);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

class Dyer : public Graphic_object{
public:
    Dyer(vPoint inc_data, int red=255, int green=255, int blue=255);
    Dyer(Point init, int red=255, int green=255, int blue=255);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

class Linear_gradient : public Graphic_object{
public:
    int r1,g1,b1,
        r2,g2,b2;

    Linear_gradient(Point initial, Point init1, Point init2,
                    int red1=255, int green1=255, int blue1=255,
                    int red2=255, int green2=255, int blue2=255);
    virtual void draw(Vint &canvas);
    virtual void set_color(int red=0, int green=0, int blue=0);
    virtual Graphic_object* dublicate();
};



class Circles : public Graphic_object{
public:
    int R;
    Thickness thickness;

    Circles(vPoint inc_data, int radius, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    Circles(Point centre, int radius, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

/*
class Static_Circles : public Graphic_object{
public:

    Static_Circles(vPoint inc_data, int radius, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
};
*/
class Circle_shapes : public Graphic_object{
public:
    int R;

    Circle_shapes(vPoint inc_data, int radius, int red=0, int green=0, int blue=0);
    Circle_shapes(Point centre, int radius, int red=0, int green=0, int blue=0);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};


/*
class Static_Circle_shapes : public Graphic_object{
public:

    Static_Circle_shapes(vPoint inc_data, int radius, int red=0, int green=0, int blue=0);
    virtual void draw(Vint &canvas);
};
*/
class Polyline : public Graphic_object{
public:
    Thickness thickness;

    Polyline(vPoint inc_data, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

class Polygon : public Graphic_object{
public:
    Thickness thickness;

    Polygon(vPoint inc_data, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

class Regular_polygons : public Graphic_object{
public:
    int R;
    int vertices;
    double angle;
    Thickness thickness;

    Regular_polygons(vPoint inc_data, int radius, int num_of_vertices=3,
                     double first_angle=PI/2, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    Regular_polygons(Point centre, int radius, int num_of_vertices=3,
                     double first_angle=PI/2, int red=0, int green=0, int blue=0, Thickness thns=THIN);


    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};
/*
class Static_Regular_polygons : public Graphic_object{
public:
    int R;
    int vertices;
    double angle;
    Thickness thickness;

    Static_Regular_polygons(vPoint &inc_data, int radius, int num_of_vertices=3,
                     double first_angle=PI/2, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
};
*/
class Static_spline : public Graphic_object{
public:
    Thickness thickness;

    Static_spline(vPoint inc_data, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

class Dynamic_spline : public Graphic_object{
public:
    Thickness thickness;

    Dynamic_spline(vPoint inc_data, int red=0, int green=0, int blue=0, Thickness thns=THIN);
    virtual void draw(Vint &canvas);
    virtual Graphic_object* dublicate();
};

//===

typedef std::vector<Graphic_object*> layers;

class Set_of_objects{

public:
    layers Data;

    Set_of_objects();
    Set_of_objects(layers &D);

    void draw(Vint &canvas);

    void add_object(Graphic_object &newone);
    void unify_color(int red=0, int green=0, int blue=0);
    void relocate( int delta_x, int delta_y );
    void rotation( double angle, Point center = grid_center );
    void transformation( vvdb &lin_operator, Point center = grid_center );

    Set_of_objects& operator=(const Set_of_objects &right);

};

/// IMAGE

class Image{
public:
    int H,W,CHANNELS;
    Image(int h=100, int w=100, int r=255, int g=255, int b=255);
    Image(int h, int w, Vint &initial_image);

    Vint data;

    void read(std::string filename);
    void output(std::string filename = "my_image");

    void clear_all(int r=255, int g=255, int b=255);

    void set_pixel(int x, int y, int r=255, int g=255, int b=255, Thickness thickness = THIN);

    void draw_circle(int R, Point center = grid_center,
                     int r=0, int g=0, int b=0, Thickness thickness=THIN);
    void draw_circle_shape(int R, Point center = grid_center,
                     int r=0, int g=0, int b=0);
    void draw_line(Point pt1, Point pt2,
                   int r=0, int g=0, int b=0, Thickness thickness =THIN);
    void draw_polygon(vPoint &Points,
                      int r=0, int g=0, int b=0, Thickness thickness =THIN);
    void draw_polyline(vPoint &Points,
                       int r=0, int g=0, int b=0, Thickness thickness =THIN);
    void draw_regular_polygon(int R, Point center = grid_center, int vertices=3, double angle=PI/2,
                              int r=0, int g=0, int b=0, Thickness thickness=THIN);
    void draw_spline(vPoint &Points, int r=0, int g=0, int b=0, Thickness thickness = THIN);

    void dye(Point init, int r=255, int g=255, int b=255);
    void linear_gradient(Point init, Point init1, Point init2, int r1, int g1, int b1, int r2, int g2, int b2 );

    //

    void draw(Set_of_objects &set_of_gobj);
    void draw(Graphic_object &gobj);

    //

    Image& operator=(const Image &right);

};


#endif // GRAPHIC_OBJECTS_HEADER_H_INCLUDED
