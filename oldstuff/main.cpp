#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include <ctime>
#include "graphic_objects_header.h"
#include <iostream>


// VER 01.12.2021
/// Add gradients
// test gradient as Graphic_object
/// Linear operators
/// Make more static shapes (most of them are dynamic now)
/// Add drawing numbers (and probably letters)

//using namespace std;

void demo0(){
    // Reading and writing some image
    Image Pic;
    Pic.read("input.png");
    // Writing its' heigh and width:
    std::cout<<Pic.H<<" "<<Pic.W<<"\n";
    Pic.output("output.png");
}

void demo1(){

    /// Creating the image 800x800:
    Image Pic(800,800);

    /// Initializing some vector of points:
    vPoint P = { {-300,-300}, {-250,0},
               {100,-100}, {300,150} };

    /// Drawing:
    //   drawing a circle with radius=5
    //   in the centre of the image (0,0)
    //   of red colour (255,0,0)
    Pic.draw_circle_shape(5,{0,0},255,0,0);

    //   polyline with vertices from vector P
    //   of the colour (0,240,0) (green)
    //   and thin
    Pic.draw_polyline(P,0,240,0,THIN);

    //   black spline through points from vector P
    Pic.draw_spline(P,0,0,0,THIN);

    //   dying the area that contains point (-275,-145)
    //   in grey colour (150,150,150)
    Pic.dye({-275,-145},150,150,150);

    //   dying another area
    Pic.dye({200,20},255,200,255);

    //   drawing a circle in each point of P
    //   with radius=10, blue colour and thick
    for(auto pt: P){
        Pic.draw_circle(10,pt,0,0,255,THICK);
    }

    //   connecting first and last points from P
    //   by thin black line
    Pic.draw_line(P[0],P[3],0,0,0,THIN);

    // Thickness has 3 options: THIN, THICK and FAT

    /// Output:
    Pic.output("demo1.png");
}

void demo2(){

    /// Creating the image:
    Image Pic(800,800);

    /// Drawing:

    // drawing circles with different centres, colours and thickness
    Pic.draw_circle(200,{0,0},0,0,0,FAT);
    Pic.draw_circle(180,{15,15},100,150,200,THICK);
    Pic.draw_circle(100,{-20,0},0,200,0,THICK);
    Pic.draw_circle(40,{0,-30},50,50,200,FAT);

    // drawing line between points (-200,130) and (250,0)
    // default parameters for colour and thickness are black and thin,
    // so the line with
    //   Pic.draw_line({-200, 130},{250,0})
    // is equivalent to the following:
    //   Pic.draw_line({-200, 130},{250,0},0,0,0,THICK);
    Pic.draw_line({-200, 130},{250,0});

    // dying some areas
    Pic.dye({0,15},55,200,200);
    Pic.dye({0,-195},200,200,100);

    /// Output:
    Pic.output("demo2.png");
}

void demo_spline(){

    /// Initializing the image:
    Image Pic(800,800);
    // the line above is equivalent to:
    //   Image Pic(800,800,255,255,255);
    // last 3 arguments are RGB of the initial colour of the image

    /// Initializing the vector of points
    //  reading their coordinates from console:

    vPoint P;
    std::cout<<"Enter the number of points for spline:\n";
    int n; std::cin>>n;
    for(int i=0; i<n; i++){
        std::cout<<"Enter the coordinates for point "<<i+1<<": ";
        int x,y; std::cin>>x>>y;
        P.push_back({x,y});
    }

    /// Drawing:
    // drawing a thick blue circle of R=5 in each given point
    for(int i=0; i<n; i++){
        Pic.draw_circle(5,P[i],0,0,255,THICK);
    }

    // drawing spline through points from P:
    Pic.draw_spline(P,0,0,0,THIN);
    // default parameters for spline: black colour, thickness=THIN
    // (the last 4 arguments would be the same even if they were not given)

    /// Output:
    Pic.output("demo_spline.png");
}

void demo_lingrad(){

    /// Linear gradient
    // Arguments:
    // initial_point -- the one which is located in the area
    //                  that you need to dye
    // initial_point_1 -- the first "knot"
    // initial_point_2 -- the second "knot"
    // r1,g1,b1        -- components of the first colour
    // r2,g2,b2        -- components of the second colour
    //
    // The method will draw linear gradient from colour 1 (in the initial_point_1)
    // to the colour 2 (in the initial_point_2).
    // Only the are that contains initial_point will be dyed!

    /// Creating the image with blue background-colour:
    Image Pic(800,800,255,255,180);

    /// Reading colours:
    int r1,g1,b1,
        r2,g2,b2;
    std::cout<<"Enter the first colour (r,g,b):\n";
    std::cin>>r1>>g1>>b1;

    std::cout<<"Enter the second colour (r,g,b):\n";
    std::cin>>r2>>g2>>b2;

    /// Drawing:
    // drawing thin black circle, R=100, centre in the point (0,0)
    Pic.draw_circle(100,{0,0});

    // the linear gradient will be created between these points:
    Point init1 = Point(-200,-100),
          init2 = Point(200,150);
    // drawing little black thick circles in these knots:
    Pic.draw_circle(5,init1,0,0,0,THICK);
    Pic.draw_circle(5,init2,0,0,0,THICK);

    // drawing linear gradient:
    Pic.linear_gradient({0,0},init1,init2,r1,g1,b1,r2,g2,b2);

    // drawing it's initial point:
    Pic.draw_circle(5,{0,0},255,0,0,THICK);

    /// Output:
    Pic.output("demo_linear_gradient.png");
}

void demo_objects(){

    /// The image we're gonna draw on:
    Image Pic(800,800);

    /// Creating the set of objects

    // Initializing some vectors of points:
    vPoint p1 = { {0,0}, {100,140}, {-120,130}, {-30,-30}, {20,-50} },
           p2 = { {-200,70}, {-150, 45}, {70,60}, {130,30} },
           p3 = {{0,80}};

    /// Initializing some objects (splines);
    //    Arguments: vector of points,
    //               RGB -- default 0,0,0
    //               thickness -- default thin
    Static_spline s_spl1 (p1);
    Static_spline s_spl2 (p2);
    Dynamic_spline d_spl (p1,255);

    // The point that will dye the area around:
    Dyer dyer (p3,160,200,230);

    // Circles:
    Circles cir1 (p1,6,0,255,0,THICK),
            cir2 (p2,6,0,0,255,THICK);

    // Putting all these objects into special vector:
    layers L1 = {&s_spl1,&s_spl2,&dyer,&d_spl,&cir1,&cir2};

    /// Finally, creating the set:
    //  The argument -- that very vector of objects
    Set_of_objects MySet(L1);

    /// Drawing:
    // drawing this set on our image
    Pic.draw(MySet);
    // output with current condition:
    Pic.output("demo_objects_1.png");

    /// A couple of tricks

    // Linear transformations:
    //      initialising the operator:
    vvdb oper = { {2,0},
                  {0,2} };
    //      applying transformation:
    MySet.transformation(oper,{0,0});
    // the second argument is the point,
    // which is considered as the centre of the transformation (kind of (0,0))
    // its' default value is (0,0), so the last argument here is unnecessary

    // Output over the previous image:
    Pic.draw(MySet);
    Pic.output("demo_objects_2.png");



    // Shift by -100 and -200
    // Rotation counterclockwise
    MySet.rotation(PI/4);
    MySet.relocate(-100,-200);
    // arguments for "rotation"
    // angle, the centre-point (default={0,0})

    // Output:
    Pic.clear_all();
    Pic.draw(MySet);
    Pic.output("demo_objects_3.png");

    // Quick colour change for all data inside our set:
    //          Arguments -- R,G,B-values of the new common colour
    MySet.unify_color(100,100,200);
    MySet.rotation(-PI/2,{-100,-200});

    Pic.clear_all(255,255,255);
    Pic.draw(MySet);
    Pic.output("demo_objects_3.png");
}

void demo_objects__(){

    Image Pic(800,800);

    vPoint p1 = { {0,0}, {100,140}, {-120,130}, {-30,-30}, {20,-50} },
           p2 = { {-200,70}, {-150, 45}, {70,60}, {130,30} };

    Static_spline s_spl1 (p1);
    Static_spline s_spl2 (p2);
    Dynamic_spline d_spl (p1,255);

    Linear_gradient ling({0,80},{-200,0},{100,0},160,200,230,230,0,100);

    Circles cir1 (p1,6,0,255,0,THICK),
            cir2 (p2,6,0,0,255,THICK);

    layers L1 = {&s_spl1,&s_spl2,&ling,&d_spl,&cir1,&cir2};

    Set_of_objects MySet(L1);

    Pic.draw(MySet);
    Pic.output("demo_objects_with_lingrad.png");
}

int main(){

    demo_objects__();


    return 0;
}
