#ifndef TEMP_H_INCLUDED
#define TEMP_H_INCLUDED

#include <ctime>
#include <iostream>




void demo1(){
    // vector of points:
    vPoint P = { {-300,-300}, {-250,0},
               {100,-100}, {300,150} };

    // creating image:
    Vint image (IMAGE_CONST::H,vvint(IMAGE_CONST::W,vint(3,255)));

    // drawing:
    Drawing::draw_circle_shape(image,5,{0,0},255,0,0);
    Drawing::draw_polyline(image,P,0,240,0,THIN);
    Drawing::draw_spline(image,P,0,0,0,THIN);
    Drawing::dye(image,{-275,-145},150,150,150);
    Drawing::dye(image,{200,20},255,200,255);
    for(auto pt: P){
        Drawing::draw_circle(image,10,pt,0,0,255,THICK);
    }
    Drawing::draw_line(image,P[0],P[3],0,0,0,THIN);

    // output:
    std::string filename = "demo1";
    filename += ".png";
    Drawing::output(filename,image);
}

void demo2(){

// creating image:
Vint image (IMAGE_CONST::H,vvint(IMAGE_CONST::W,vint(3,255)));

// drawing:
Drawing::draw_circle(image,200,{0,0},0,0,0,FAT);
Drawing::draw_circle(image,180,{15,15},100,150,200,THICK);
Drawing::draw_circle(image,100,{-20,0},0,200,0,THICK);
Drawing::draw_circle(image,40,{0,-30},50,50,200,FAT);

Drawing::draw_line(image,{-200, 130},{250,0});
Drawing::dye(image,{0,15},55,200,200);
Drawing::dye(image,{0,-195},200,200,100);

// output:
std::string filename = "demo2";
filename += ".png";
Drawing::output(filename,image);
}

void obj_demo1(){

    vPoint p1 = { {0,0}, {100,140}, {-120,130}, {-30,-30}, {20,-50} },
           p2 = { {-200,70}, {-150, 45}, {70,60}, {130,30} },
           p3 = {{0,80}};
    Static_spline s_spl1 (p1);
    Static_spline s_spl2 (p2);
    Dynamic_spline d_spl (p1,255);

    Dyer dyer (p3,160,200,230);

    Circles cir1 (p1,6,0,255,0,THICK),
            cir2 (p2,6,0,0,255,THICK);

    layers L1 = {&s_spl1,&s_spl2,&dyer,&d_spl,&cir1};
    Set_of_objects MySet(L1);
    MySet.add_object(cir2);

    vvdb oper = {{1,0},{1,1}};
    MySet.transformation(oper);
    //MySet.relocate(-100,-200);
    //MySet.rotation(PI/4);
    //MySet.unify_color(255,0,0);

    Vint image (IMAGE_CONST::H,vvint(IMAGE_CONST::W,vint(3,255)));

    MySet.draw(image);

    std::string filename = "obj1";
    filename += ".png";
    Drawing::output(filename,image);
}

void demo_lingrad(){
    Vint image (IMAGE_CONST::H,vvint(IMAGE_CONST::W,vint(3,255)));

    int r1,g1,b1,
        r2,g2,b2;
    std::cout<<"Enter end-colors:\n";
    std::cin>>r1>>g1>>b1>>r2>>g2>>b2;

    Drawing::draw_circle(image,100,{0,0});

    Point init1 = Point(-200,-100),
          init2 = Point(200,-100);
    Drawing::draw_circle(image,5,init1,0,0,0,THICK);
    Drawing::draw_circle(image,5,init2,0,0,0,THICK);

    Drawing::linear_gradient(image,{0,0},init1,init2,r1,g1,b1,r2,g2,b2);
    Drawing::draw_circle(image,5,{0,0},255,0,0,THICK);

    std::string filename = "grad0";
    filename += ".png";
    Drawing::output(filename,image);
}

void users_spline(){
    vPoint P;
    int n; std::cin>>n;
    for(int i=0; i<n; i++){
        int x,y; std::cin>>x>>y;
        P.push_back({x,y});
    }

    Vint image (IMAGE_CONST::H,vvint(IMAGE_CONST::W,vint(3,255)));

    for(int i=0; i<n; i++){
        Drawing::draw_circle(image,5,P[i],0,0,255,THICK);
    }

    Drawing::draw_spline(image,P);

    std::string filename;
    std::cin>>filename;
    filename += ".png";
    Drawing::output(filename,image);
}

#endif // TEMP_H_INCLUDED
