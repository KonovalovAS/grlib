#include "demonstration_header.h"
#include <cstdlib>
#include <queue>

#include <iostream>

const vint dx_near = {-1,1,0,0};
const vint dy_near = {0,0,-1,1};

const vint dx_3by3 = {-1,0,1,-1,0,1,-1,0,1};
const vint dy_3by3 = {-1,-1,-1,0,0,0,1,1,1};

const vint dx_5by5 = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,0,1,2};
const vint dy_5by5 = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,0,1,1,1,1,1,2,2,2,2,2};

bool Point::visible(int H, int W){
    return ( (x<W/2)&&(x>=-W/2)
            &&(y<=H/2)&&(y>-H/2) );
}

Point::Point(){
    x = 0;
    y = 0;
}
Point::Point(int x_crd, int y_crd){
    x = x_crd;
    y = y_crd;
}

void Point::replace_for_visibility(int H, int W){
    x = std::max(-W/2,x);
    x = std::min(W/2-1,x);
    y = std::max(1-H/2,y);
    y = std::min(H/2,y);
}
void Point::set_color(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
}

///============

void Reading::Read_the_image(Vint& New_image, std::string filename){
    int H,W,CHANNELS;
    unsigned char *data = stbi_load(filename.c_str(),&W,&H,&CHANNELS,3);
    Vint Image (H,vvint(W,vint(CHANNELS)));
    convert_char_to_Vint( data, Image );
    New_image = Image;
}

void Reading::convert_char_to_Vint( const unsigned char* data, Vint& Image ){
    int h = Image.size(),
        w = Image[0].size();

    for(int row=0; row<h; row++) {
        for(int col=0; col<w; col++) {
            for(int comp=0; comp<3; comp++){
                Image[row][col][comp] =
                    data[(row*w*3)
                    +(col*3)+comp];
            }
        }
    }
}

///============

void Drawing::convert_Vint_to_char(char * data, const Vint &Pic){
    int H = Pic.size(),
        W = Pic[0].size(),
        CHANNELS = Pic[0][0].size();

    for(int row=0; row<H; row++){
        for(int col=0; col<W; col++){
            //std::cout<<"fine!\n";
            for(int c=0; c<3; c++){
                data[(row*W*CHANNELS)+(col*CHANNELS)+c] = Pic[row][col][c];
            }
        }
    }
}

void Drawing::output(std::string filename, Vint &Pic){
    int H = Pic.size(),
        W = Pic[0].size(),
        CHANNELS = Pic[0][0].size();
    char *data = (char*)malloc(H*W*CHANNELS*sizeof(char));
    convert_Vint_to_char( data, Pic );
    stbi_write_png(filename.c_str(),W,H,CHANNELS,data,W*CHANNELS);
}

bool Drawing::visible(int x, int y, int H, int W){
    return ( (x>=-W/2)&&(x<W/2)&&(y<=H/2)&&(y>-H/2) );
}

void Drawing::set_single_pixel(Vint &canvas, int x, int y, int r, int g, int b){
    int H = canvas.size(),
        W = canvas[0].size();

    if( visible(x,y,H,W) ){
        canvas[H/2-y][x+W/2][0] = r;
        canvas[H/2-y][x+W/2][1] = g;
        canvas[H/2-y][x+W/2][2] = b;
    }
}

void Drawing::set_pixel(Vint &canvas, int x, int y, int r, int g, int b, Thickness thickness){
    switch(thickness){
    case THIN:
        set_single_pixel(canvas,x,y,r,g,b);
        break;
    case THICK:
        for(int i=0; i<9; i++){
            set_single_pixel(canvas,x+dx_3by3[i],y+dy_3by3[i],r,g,b);
        }
        break;
    case FAT:
        for(int i=0; i<25; i++){
            set_single_pixel(canvas,x+dx_5by5[i],y+dy_5by5[i],r,g,b);
        }
        break;
    }
}

// DRAWING:
// all lines are drawn with Brezenham's algorithm
void Drawing::line_x(Vint &canvas, int x1, int x2, int y1, int y2, int r, int g, int b, Thickness thickness){

    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int error = 0;
    int deltaerr = (deltay + 1);
    int y = y1;
    int diry = y2 - y1;

    if(diry > 0)
        diry = 1;
    else if(diry < 0)
        diry = -1;

    int dx = (x2-x1>0) ? 1 : -1;

    for(int x=x1; x!=x2; x=x+dx){
        set_pixel(canvas,x,y,r,g,b,thickness);
        error = error + deltaerr;
        if( error >= (deltax+1) ){
            y = y + diry;
            error = error - (deltax + 1);
        }
    }
}

void Drawing::line_y(Vint &canvas, int x1, int x2, int y1, int y2, int r, int g, int b, Thickness thickness){

    int deltax = abs(x2 - x1);
    int deltay = abs(y2 - y1);
    int error = 0;
    int deltaerr = (deltax + 1);
    int x = x1;
    int dirx = x2 - x1;

    if(dirx > 0)
        dirx = 1;
    else if(dirx < 0)
        dirx = -1;

    int dy = (y2-y1>0) ? 1 : -1;

    for(int y=y1; y!=y2; y=y+dy){
        set_pixel(canvas,x,y,r,g,b,thickness);
        error = error + deltaerr;
        if( error >= (deltay+1) ){
            x = x + dirx;
            error = error - (deltay + 1);
        }
    }
}

void Drawing::draw_line(Vint &canvas, Point pt1, Point pt2, int r, int g, int b, Thickness thickness){

    int x1 = pt1.x,
        x2 = pt2.x,
        y1 = pt1.y,
        y2 = pt2.y;

    if( x2==x1 && y2==y1 ){
        set_pixel(canvas,x1,y1,r,g,b,thickness);
    }
    else if(abs(x2-x1)>abs(y2-y1)){
        line_x(canvas,x1,x2,y1,y2,r,g,b,thickness);
    }
    else{
        line_y(canvas,x1,x2,y1,y2,r,g,b,thickness);
    }
}

void Drawing::draw_polygon(Vint &canvas, vPoint &Points, int r, int g, int b, Thickness thickness){
    int n = Points.size();
    for(int i=0; i<n; i++)
        draw_line( canvas, Points[i], Points[ (i+1)%n ], r,g,b, thickness );
}

void Drawing::draw_polyline(Vint &canvas, vPoint &Points, int r, int g, int b, Thickness thickness){
    int n = Points.size();
    for(int i=0; i<n-1; i++)
        draw_line( canvas, Points[i], Points[i+1], r,g,b, thickness );
}

void Drawing::draw_circle(Vint &canvas, int R, Point center, int r, int g, int b, Thickness thickness){
    int x0 = center.x,
        y0 = center.y;

    int x = 0,
        y = R;
    int delta = 1-2*R;
    int error = 0;

    while( y>=x ){
        set_pixel(canvas,x0+x,y0+y,r,g,b,thickness);
        set_pixel(canvas,x0+x,y0-y,r,g,b,thickness);
        set_pixel(canvas,x0-x,y0+y,r,g,b,thickness);
        set_pixel(canvas,x0-x,y0-y,r,g,b,thickness);
        set_pixel(canvas,x0+y,y0+x,r,g,b,thickness);
        set_pixel(canvas,x0+y,y0-x,r,g,b,thickness);
        set_pixel(canvas,x0-y,y0+x,r,g,b,thickness);
        set_pixel(canvas,x0-y,y0-x,r,g,b,thickness);
        error = 2 * (delta + y) - 1;
        if((delta < 0) && (error <= 0)){
            x++;
            delta += 2*x+1;
            continue;
        }
        error = 2*(delta-x)-1;
        if((delta > 0) && (error > 0)){
            y--;
            delta += 1-2*y;
            continue;
        }
        x++;
        delta += 2 * (x-y);
        y--;
    }
}

void Drawing::draw_circle_shape(Vint &canvas, int R, Point center, int r, int g, int b){
    int H = canvas.size(),
        W = canvas[0].size();

    int x0 = center.x,
        y0 = center.y;

    int x_beg = std::max(x0-R,-W/2),
        x_end = std::min(x0+R,W/2-1),
        y_beg, y_end;

    for(int x=x_beg; x<=x_end; x++){
        int delta_y = round( sqrt( pow(R,2)-pow(x0-x,2) ) );
        y_beg = y0-delta_y;
        y_end = y0+delta_y;
        y_beg = std::max(y_beg,1-H/2);
        y_end = std::min(H/2,y_end);
        for(int y=y_beg; y<=y_end; y++){
            set_single_pixel(canvas,x,y,r,g,b);
        }
    }
}

void Drawing::draw_regular_polygon(Vint &canvas, int R, Point center, int vertices, double angle, int r, int g, int b, Thickness thickness){
    int xc = center.x,
        yc = center.y;

    vPoint Points;
    for( int t=0; t<vertices; t++){
        double arg = angle + PI*2*t/vertices;
        int x = xc + round( R*cos(arg) ),
            y = yc + round( R*sin(arg) );
        Points.push_back( Point(x,y) );
    }
    draw_polygon(canvas, Points, r, g, b, thickness);
}

// DYING:

void Drawing::dye( Vint &canvas, Point init, int r, int g, int b ){
    int H = canvas.size(),
        W = canvas[0].size();

    if( init.visible(H,W) ){
        int r_init = canvas[H/2-init.y][init.x+W/2][0],
            g_init = canvas[H/2-init.y][init.x+W/2][1],
            b_init = canvas[H/2-init.y][init.x+W/2][2];

        std::queue<Point> Q;
        Q.push(init);

        while(!Q.empty()){
            Point cur_pt = Q.front();
            int x = cur_pt.x,
                y = cur_pt.y;
            Q.pop();
            for(int i=0; i<4; i++){
                int cur_x = x + dx_near[i],
                    cur_y = y + dy_near[i];
                if(visible(cur_x,cur_y,H,W)){
                    bool available = ( canvas[H/2-cur_y][cur_x+W/2][0]==r_init )
                                  && ( canvas[H/2-cur_y][cur_x+W/2][1]==g_init )
                                  && ( canvas[H/2-cur_y][cur_x+W/2][2]==b_init );
                    if( available ){
                        set_single_pixel(canvas,cur_x,cur_y,r,g,b);
                        Point checkit = Point(cur_x,cur_y);
                        Q.push(checkit);
                    }
                }
            }
        }
    }
}

void Drawing::linear_gradient( Vint &canvas, Point init, Point init1, Point init2, int r1, int g1, int b1, int r2, int g2, int b2 ){
    int H = canvas.size(),
            W = canvas[0].size();
    if( init.visible(H,W) ){
        vvbool DYED (H,vbool(W,false));

        int r_init = canvas[H/2-init.y][init.x+W/2][0],
            g_init = canvas[H/2-init.y][init.x+W/2][1],
            b_init = canvas[H/2-init.y][init.x+W/2][2];

        double vec_x = init2.x-init1.x,
               vec_y = init2.y-init1.y,
               len = sqrt(pow(vec_x,2)+pow(vec_y,2));

        std::queue<Point> Q;
        Q.push(init);

        while(!Q.empty()){
            Point cur_pt = Q.front();
            int x = cur_pt.x,
                y = cur_pt.y;
            Q.pop();
            for(int i=0; i<4; i++){
                int cur_x = x + dx_near[i],
                    cur_y = y + dy_near[i];
                if(!DYED[H/2-cur_y][cur_x+W/2] && visible(cur_x,cur_y,H,W)){
                    bool available = ( canvas[H/2-cur_y][cur_x+W/2][0]==r_init )
                                  && ( canvas[H/2-cur_y][cur_x+W/2][1]==g_init )
                                  && ( canvas[H/2-cur_y][cur_x+W/2][2]==b_init );
                    if( available ){
                        double dist1 = ((cur_x-init1.x)*vec_x+(cur_y-init1.y)*vec_y)/len;
                        int r,g,b;
                        if(dist1<0){
                            r = r1;
                            g = g1;
                            b = b1;
                        }
                        else if(dist1<len){
                            r = r1 + round((r2-r1)*dist1/len),
                            g = g1 + round((g2-g1)*dist1/len),
                            b = b1 + round((b2-b1)*dist1/len);
                        }
                        else{
                            r = r2;
                            g = g2;
                            b = b2;
                        }
                        set_single_pixel(canvas,cur_x,cur_y,r,g,b);
                        Point checkit = Point(cur_x,cur_y);
                        DYED[H/2-cur_y][cur_x+W/2] = true;
                        Q.push(checkit);
                    }
                }
            }
        }
    }
}



//===

void Drawing::solve_system(vvdb &system, vdb &m){
    int n = system.size();

    for(int i=1; i<n; i++){
        double coef = system[i][i-1]/system[i-1][i-1];
        for(int j=i-1; j<std::min(i+1,n-1); j++){
            system[i][j] -= coef*system[i-1][j];
        }
        system[i][n] -= coef*system[i-1][n];
    }

    m.resize(0);
    m.resize(n+2,0);
    m[0] = 0;
    m[n+1] = 0;
    m[n-1] = system[n-1][n]/system[n-1][n-1];
    for(int i=0; i<n; i++){
        m[n-i] = ( system[n-1-i][n] - m[n-i+1]*system[n-1-i][n-i] ) / system[n-1-i][n-1-i];
    }
}

void Drawing::spline(vvdb &data, vvdb &spline){
    int n = data[0].size()-1;
    vdb h;
    vdb d;
    for(int i=0; i<n; i++){
        h.push_back(data[0][i+1]-data[0][i]);
        d.push_back( (data[1][i+1]-data[1][i]) /h[i] );
    }
    vdb u;
    for(int i=0; i<n-1; i++){
        u.push_back( 6*(d[i+1]-d[i]) );
    }

    vvdb system(n-1,vdb(n,0));

    system[0][n-1] = u[0];
    system[n-2][n-1] = u[n-2];
    system[0][0] = 2*(h[0]+h[1]);
    system[n-2][n-2] = 2*(h[n-2]+h[n-1]);
    system[0][1] = h[1];
    system[n-2][n-3] = h[n-1];

    for(int i=1; i<n-2; i++){
        system[i][n-1] = u[i];
        system[i][i-1] = h[i];
        system[i][i] = 2*(h[i]+h[i+1]);
        system[i][i+1] = h[i+1];
    }

    vdb m;
    solve_system(system,m);

    spline.resize(0);
    spline.resize(n,vdb(4));

    for(int i=0; i<n; i++){
        spline[i][0] = data[1][i];
        spline[i][1] = d[i] - h[i]*( 2*m[i] + m[i+1] )/6;
        spline[i][2] = m[i]/2;
        spline[i][3] = ( m[i+1] - m[i] )/(6*h[i]);
    }
}

double Drawing::dist(Point &A, Point &B){
    return sqrt( pow( A.x-B.x, 2 ) + pow( A.y-B.y, 2 ) );
}

void Drawing::spline_parametrization(vPoint &Points, vvdb &x_t, vvdb &y_t){
int n = Points.size();
    double t = 0;
    // 0 for t, 1 for x/y
    x_t[0][0] = t;
    x_t[1][0] = Points[0].x;
    y_t[0][0] = t;
    y_t[1][0] = Points[0].y;

    for(int i=1; i<n; i++){
        t += dist( Points[i], Points[i-1] );
        x_t[0][i] = t;
        y_t[0][i] = t;
        x_t[1][i] = Points[i].x;
        y_t[1][i] = Points[i].y;
    }
}

void Drawing::make_curve(vvdb &x_t, vvdb &y_t, vvdb &x_spline, vvdb &y_spline, vPoint &final_curve ){
    int K = 20,
        n = x_t[0].size();
    for(int i=0; i<n-1; i++){
        double step = ( x_t[0][i+1] - x_t[0][i] )/(double)(K);
        double arg0 = x_t[0][i];
        double arg = arg0;
        double x_value, y_value;
        for(int j=0; j<K; j++){
            arg += step;
            x_value = 0;
            y_value = 0;
            for(int s=0; s<4; s++){
                x_value += pow(arg-arg0,s)*x_spline[i][s];
                y_value += pow(arg-arg0,s)*y_spline[i][s];
            }
            int temp_x = round(x_value),
                temp_y = round(y_value);
            final_curve.push_back( { temp_x, temp_y } );
        }
    }
}

void Drawing::make_spline(vPoint &Points, vPoint &final_curve){
    int n = Points.size();
    vvdb x_t (2,vdb(n,0));
    vvdb y_t (2,vdb(n,0));

    spline_parametrization(Points,x_t,y_t);

    vvdb x_spline;
    vvdb y_spline;
    spline(x_t,x_spline);
    spline(y_t,y_spline);

    final_curve.resize(0);
    final_curve.push_back( Points[0] );
    make_curve(x_t,y_t,x_spline,y_spline,final_curve);
}

void Drawing::draw_spline(Vint &canvas, vPoint &Points, int r, int g, int b, Thickness thickness){

    int n = Points.size();
    vPoint curve;
    if(n>3){
        make_spline(Points,curve);
    }
    else if(n==3){
        int dx = Points[n-1].x - Points[n-2].x,
            dy = Points[n-1].y - Points[n-2].y;
        Points.push_back({ Points[0].x+2*dx, Points[0].y+2*dy });
        make_spline(Points,curve);
        for(int i=0; i<20; i++){
            curve.pop_back();
        }
    }
    else{
        curve = Points;
    }

    Drawing::draw_polyline(canvas,curve,r,g,b,thickness);
}




//=========================
//=========================


// MIGHT BE USED LATER:
std::string Drawing::int_to_string(int k){
    int th = k/1000;
        k -= th*1000;
    int h = k/100,
        t = (k%100)/10,
        u = k%10;
    std::string res("0000");
    res[0] = th+48;
    res[1] = h+48;
    res[2] = t+48;
    res[3] = u+48;
    return res;
}
