#include "graphic_objects_header.h"
#include <iostream>

Set_of_objects::Set_of_objects(){
    Data = {};
}

Set_of_objects::Set_of_objects(layers &D){
    Data = D;
}

//===

Graphic_object* Graphic_object::dublicate(){
    return nullptr;
}

Graphic_object* Points::dublicate(){
    return new Points(data,r,g,b);
}

Graphic_object* Dyer::dublicate(){
    return new Dyer(data,r,g,b);
}

Graphic_object* Linear_gradient::dublicate(){
    return new Linear_gradient(data[0],data[1],data[2],
                               r1,g1,b1,r2,g2,b2);
}


Graphic_object* Circles::dublicate(){
    return new Circles(data,R,r,g,b,thickness);
}

Graphic_object* Circle_shapes::dublicate(){
    return new Circle_shapes(data,R,r,g,b);
}

Graphic_object* Polyline::dublicate(){
    return new Polyline(data,r,g,b,thickness);
}

Graphic_object* Polygon::dublicate(){
    return new Polygon(data,r,g,b,thickness);
}

Graphic_object* Regular_polygons::dublicate(){
    return new Regular_polygons(data,R,vertices,angle,r,g,b,thickness);
}

Graphic_object* Static_spline::dublicate(){
    return new Static_spline(data,r,g,b,thickness);
}

Graphic_object* Dynamic_spline::dublicate(){
    return new Dynamic_spline(data,r,g,b,thickness);
}






// Constructors:

Points::Points(vPoint inc_data, int red, int green, int blue){
    data = inc_data;
    r = red;
    g = green;
    b = blue;
}

Points::Points(Point single_point, int red, int green, int blue){
    data = { single_point };
    r = red;
    g = green;
    b = blue;
}



Dyer::Dyer(vPoint inc_data, int red, int green, int blue){
    data = inc_data;
    r = red;
    g = green;
    b = blue;
}

Dyer::Dyer(Point init, int red, int green, int blue){
    data = { init };
    r = red;
    g = green;
    b = blue;
}


Linear_gradient::Linear_gradient(Point initial, Point init1, Point init2,
                    int red1, int green1, int blue1,
                    int red2, int green2, int blue2){
    data.resize(3);
    data[0] = initial;
    data[1] = init1;
    data[2] = init2;
    r1 = red1;
    r2 = red2;
    g1 = green1;
    g2 = green2;
    b1 = blue1;
    b2 = blue2;
}


Circles::Circles(vPoint inc_data, int radius, int red, int green, int blue, Thickness thns){
    data = inc_data;
    R = radius;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

Circles::Circles(Point centre, int radius, int red, int green, int blue, Thickness thns){
    data = { centre };
    R = radius;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}



/*
Static_Circles::Static_Circles(vPoint &inc_data, int radius, int red, int green, int blue, Thickness thns){

    data = inc_data;
    r = red;
    g = green;
    b = blue;

}
*/

Circle_shapes::Circle_shapes(vPoint inc_data, int radius, int red, int green, int blue){
    data = inc_data;
    R = radius;
    r = red;
    g = green;
    b = blue;
}

Circle_shapes::Circle_shapes(Point centre, int radius, int red, int green, int blue){
    data = { centre };
    R = radius;
    r = red;
    g = green;
    b = blue;
}



Polyline::Polyline(vPoint inc_data, int red, int green, int blue, Thickness thns){
    data = inc_data;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

Polygon::Polygon(vPoint inc_data, int red, int green, int blue, Thickness thns){
    data = inc_data;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

Regular_polygons::Regular_polygons(vPoint inc_data, int radius, int num_of_vertices, double first_angle, int red, int green, int blue, Thickness thns){
    data = inc_data;
    R = radius;
    angle = first_angle;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

Regular_polygons::Regular_polygons(Point centre, int radius, int num_of_vertices, double first_angle, int red, int green, int blue, Thickness thns){
    data = { centre };
    R = radius;
    angle = first_angle;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}



Static_spline::Static_spline(vPoint inc_data, int red, int green, int blue, Thickness thns){
    data = {};
    Drawing::make_spline(inc_data,data);
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

Dynamic_spline::Dynamic_spline(vPoint inc_data, int red, int green, int blue, Thickness thns){
    data = inc_data;
    thickness = thns;
    r = red;
    g = green;
    b = blue;
}

//===
// Drawing:

void Graphic_object::draw(Vint &canvas){
    std::cout<<"wrong function is called\n";
}

void Points::draw(Vint &canvas){
    int n = data.size();
    for(int i=0; i<n; i++){
        Drawing::set_single_pixel(canvas,data[i].x,data[i].y,r,g,b);
    }
}

void Dyer::draw(Vint &canvas){
    int n = data.size();
    for(int i=0; i<n; i++){
        Drawing::dye(canvas,data[i],r,g,b);
    }
}

void Linear_gradient::draw(Vint &canvas){
    Drawing::linear_gradient(canvas,data[0],data[1],data[2],r1,g1,b1,r2,g2,b2);
}

void Circles::draw(Vint &canvas){
    int n = data.size();
    for(int i=0; i<n; i++){
        Drawing::draw_circle(canvas,R,data[i],r,g,b,thickness);
    }
}

void Circle_shapes::draw(Vint &canvas){
    int n = data.size();
    for(int i=0; i<n; i++){
        Drawing::draw_circle_shape(canvas,R,data[i],r,g,b);
    }
}

void Polyline::draw(Vint &canvas){
    Drawing::draw_polyline(canvas,data,r,g,b,thickness);
}

void Polygon::draw(Vint &canvas){
    Drawing::draw_polygon(canvas,data,r,g,b,thickness);
}

void Regular_polygons::draw(Vint &canvas){
    int n = data.size();
    for(int i=0; i<n; i++){
        Drawing::draw_regular_polygon(canvas,R,data[i],vertices,angle,r,g,b,thickness);
    }
}

void Static_spline::draw(Vint &canvas){
    Drawing::draw_polyline(canvas,data,r,g,b,thickness);
}

void Dynamic_spline::draw(Vint &canvas){
    Drawing::draw_spline(canvas,data,r,g,b,thickness);
}


//===

void Set_of_objects::draw(Vint &canvas){
    int H_tmp = canvas.size();
    int W_tmp = canvas[0].size();
    Vint im_temp (H_tmp, vvint(W_tmp, vint(3,-1)));
    int n = Data.size();
    for(int i=0; i<n; i++){
        Graphic_object *temp = Data[i];
        temp->draw(im_temp);
    }
    for(int i=0; i<H_tmp; i++){
        for(int j=0; j<W_tmp; j++){
            if(im_temp[i][j][0]>=0){
                canvas[i][j] = im_temp[i][j];
            }
        }
    }
}

void Set_of_objects::add_object(Graphic_object &newone){
    Data.push_back(&newone);
}


//===

void Set_of_objects::unify_color(int red, int green, int blue){
    int n = Data.size();
    for(int i=0; i<n; i++){
        Data[i]->set_color(red,green,blue);
    }
}

void Graphic_object::set_color(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
}

void Linear_gradient::set_color(int red, int green, int blue){
    r1 = red;
    r2 = red;
    g1 = green;
    g2 = green;
    b1 = blue;
    b2 = blue;
}

//===

void Graphic_object::relocate(int delta_x, int delta_y){
    int n = data.size();
    for(int i=0; i<n; i++){
        data[i].x += delta_x;
        data[i].y += delta_y;
    }
}

void Set_of_objects::relocate( int delta_x, int delta_y ){
    int n = Data.size();
    for(int i=0; i<n; i++){
        Data[i]->relocate(delta_x,delta_y);
    }
}

//===

void Graphic_object::rotation( double arg, Point center ){
    double x0,y0,
    xc = center.x,
    yc = center.y;
    double sinus = sin(arg),
           cosinus = cos(arg);
    int n = data.size();
    for(int i=0; i<n; i++){
        x0 = data[i].x;
        y0 = data[i].y;
        data[i].x = round(xc + cosinus*(x0-xc) + sinus*(yc-y0));
        data[i].y = round(yc + cosinus*(y0-yc) + sinus*(x0-xc));
    }
}

void Set_of_objects::rotation( double arg, Point center ){
    int n = Data.size();
    for(int i=0; i<n; i++){
        Data[i]->rotation(arg,center);
    }
}

//===

void Graphic_object::transformation( vvdb &lop, Point center ){
    double delta_x, delta_y,
    xc = center.x,
    yc = center.y;
    int n = data.size();
    for(int i=0; i<n; i++){
        delta_x = data[i].x-xc;
        delta_y = data[i].y-yc;
        data[i].x = round( xc + delta_x*lop[0][0] + delta_y*lop[0][1] );
        data[i].y = round( yc + delta_x*lop[1][0] + delta_y*lop[1][1] );
    }
}

void Set_of_objects::transformation( vvdb &lin_operator, Point center ){
    bool everything_all_right =
    (lin_operator.size()==2) && (lin_operator[0].size()==2) && (lin_operator[1].size()==2);
    if(everything_all_right){
        int n = Data.size();
        for(int i=0; i<n; i++){
            Data[i]->transformation(lin_operator,center);
        }
    }
}

//===

Set_of_objects& Set_of_objects::operator=(const Set_of_objects &right){
    Data.clear();
    for(int i=0; i<right.Data.size(); i++){
        Data.push_back( right.Data[i]->dublicate() );
    }
    return *this;
}

/// IMAGE


Image::Image(int h, int w, int r, int g, int b){
    H = h;
    W = w;
    CHANNELS = 3;
    data = Vint(H,vvint(W,{r,g,b}));
}

Image::Image(int h, int w, Vint &initial_image){
    H = initial_image.size();
    W = initial_image[0].size();
    CHANNELS = initial_image[0][0].size();
    data = initial_image;
}

void Image::read(std::string filename){
    std::cout<<"in Image::read\n";
    Reading::Read_the_image(data,filename);
    H = data.size();
    W = data[0].size();
    CHANNELS = data[0][0].size();

}

void Image::output(std::string filename){
    Drawing::output(filename,data);
}

void Image::clear_all(int r, int g, int b){
    data = Vint(H,vvint(W,{r,g,b}));
}

void Image::set_pixel(int x, int y, int r, int g, int b, Thickness thickness){
    Drawing::set_pixel(data,x,y,r,g,b,thickness);
}

void Image::draw_circle(int R, Point center, int r, int g, int b, Thickness thickness){
    Drawing::draw_circle(data,R,center,r,g,b,thickness);
}

void Image::draw_circle_shape(int R, Point center, int r, int g, int b){
    Drawing::draw_circle_shape(data,R,center,r,g,b);
}

void Image::draw_line(Point pt1, Point pt2, int r, int g, int b, Thickness thickness){
    Drawing::draw_line(data,pt1,pt2,r,g,b,thickness);
}

void Image::draw_polygon(vPoint &Points, int r, int g, int b, Thickness thickness){
    Drawing::draw_polygon(data, Points, r,g,b, thickness);
}

void Image::draw_polyline(vPoint &Points, int r, int g, int b, Thickness thickness){
    Drawing::draw_polyline(data, Points, r,g,b, thickness);
}

void Image::draw_regular_polygon(int R, Point center, int vertices, double angle, int r, int g, int b, Thickness thickness){
    Drawing::draw_regular_polygon(data,R,center,vertices,angle,r,g,b,thickness);
}

void Image::draw_spline(vPoint &Points, int r, int g, int b, Thickness thickness){
    Drawing::draw_spline(data,Points,r,g,b,thickness);
}

void Image::dye(Point init, int r, int g, int b){
    Drawing::dye(data,init,r,g,b);
}

void Image::linear_gradient(Point init, Point init1, Point init2, int r1, int g1, int b1, int r2, int g2, int b2 ){
    Drawing::linear_gradient(data,init,init1,init2,r1,g1,b1,r2,g2,b2);
}

Image& Image::operator=(const Image &right){
    H = right.H;
    W = right.W;
    CHANNELS = right.CHANNELS;
    data = right.data;

    return *this;
}

void Image::draw(Set_of_objects &set_of_gobj){
    set_of_gobj.draw(data);
}

void Image::draw(Graphic_object &gobj){
    gobj.draw(data);
}

