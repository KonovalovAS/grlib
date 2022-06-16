#ifndef DEMONSTRATION_HEADER_H_INCLUDED
#define DEMONSTRATION_HEADER_H_INCLUDED
#include "stb_image_write.h"
#include "stb_image.h"
#include <cmath>
#include <vector>
#include <string>


const double PI = 3.14159265;

typedef std::vector<int> vint;
typedef std::vector<vint> vvint;
typedef std::vector<vvint> Vint;
typedef std::vector<double> vdb;
typedef std::vector<vdb> vvdb;
typedef std::vector<bool> vbool;
typedef std::vector<vbool> vvbool;


enum Thickness{
    THIN,
    THICK,
    FAT,
};

class Point{
public:
    int x,y;
    int r,g,b;
    Point();
    Point(int x_crd,int y_crd);
    bool visible(int H, int W);
    void replace_for_visibility(int H, int W);
    void set_color(int red=255, int green=255, int blue=255);
};

static Point grid_center = Point();

typedef std::vector<Point> vPoint;

class Reading{
private:
    static void convert_char_to_Vint( const unsigned char* data, Vint& Image );
public:
    static void Read_the_image(Vint& New_image,std::string filename);
};

class Drawing{
private:
    static void convert_Vint_to_char(char * data, const Vint &Pic);
    static bool visible(int x, int y, int H, int W);
    static void line_x(Vint &canvas, int x1, int x2, int y1, int y2, int r, int g, int b, Thickness thickness);
    static void line_y(Vint &canvas, int x1, int x2, int y1, int y2, int r, int g, int b, Thickness thickness);
    static void solve_system(vvdb &system, vdb &m);
    static void spline(vvdb &data, vvdb &spline);
    static void q_spline(vvdb &data, vdb &spline);
    static double dist(Point &A, Point &B);
    static void spline_parametrization(vPoint &Points, vvdb &x_t, vvdb &y_t);
    static void make_curve(vvdb &x_t, vvdb &y_t, vvdb &x_spline, vvdb &y_spline, vPoint &final_curve );

public:
    static std::string int_to_string(int k);

    static void output(std::string filename, Vint &Pic);
    static void set_single_pixel(Vint &canvas, int x, int y, int r, int g, int b);
    static void set_pixel(Vint &canvas, int x, int y, int r=255, int g=255, int b=255, Thickness thickness = THIN);


    static void draw_circle(Vint &canvas, int R, Point center = grid_center,
                     int r=0, int g=0, int b=0, Thickness thickness=THIN);
    static void draw_circle_shape(Vint &canvas, int R, Point center = grid_center,
                     int r=0, int g=0, int b=0);
    static void draw_line(Vint &canvas, Point pt1, Point pt2,
                   int r=0, int g=0, int b=0, Thickness thickness =THIN);
    static void draw_polygon(Vint &canvas, vPoint &Points,
                      int r=0, int g=0, int b=0, Thickness thickness =THIN);
    static void draw_polyline(Vint &canvas, vPoint &Points,
                       int r=0, int g=0, int b=0, Thickness thickness =THIN);
    static void draw_regular_polygon(Vint &canvas, int R, Point center = grid_center, int vertices=3, double angle=PI/2,
                              int r=0, int g=0, int b=0, Thickness thickness=THIN);
    static void make_spline(vPoint &Points, vPoint &final_curve);
    static void draw_spline(Vint &canvas, vPoint &Points, int r=0, int g=0, int b=0, Thickness thickness = THIN);

    static void dye(Vint &canvas, Point init, int r=255, int g=255, int b=255);
    static void linear_gradient( Vint &canvas, Point init, Point init1, Point init2, int r1, int g1, int b1, int r2, int g2, int b2 );
};

#endif // DEMONSTRATION_HEADER_H_INCLUDED
