#ifndef MYHEADER_H_INCLUDED
#define MYHEADER_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int CHANNELS = 3; // rgba
int W; // width
int H; // height

struct pixel
{
    double r,g,b,a;
};

struct point
{
    int h,w;
};

typedef vector<pixel> line;
typedef vector<line> mat;
typedef vector<double> vdb;
typedef vector<vdb> vvdb;
typedef vector<int> vint;
typedef vector<vint> vvint;
typedef queue<point> qp;


struct core{
    vint core1;
    vint core2; // if operator (filter) contains only 1 matrix, core2 will remain NULL (use only core1 in such case)
    int div;
};


const core Previtt = { {-1,-1,-1,0,0,0,1,1,1}, {-1,0,1,-1,0,1,-1,0,1}, 1 },
      Sobel = { {-1,-2,-1,0,0,0,1,2,1}, {-1,0,1,-2,0,2,-1,0,1}, 1 },
      Gauss3 = {  { 54901,  111345, 54901,
                    111345, 225821, 111345,
                    54901,  111345, 54901 },
                    {0}, 1000000 },
      sharp = { {-1,-1,-1,-1,9,-1,-1,-1,-1},{0},1 };


// FOR COLORED:
pixel new_pixel( unsigned char * data, int row, int col ) {
    if( CHANNELS == 4 )
        return { data[(row*W*CHANNELS)+(col*CHANNELS)+0],
                 data[(row*W*CHANNELS)+(col*CHANNELS)+1],
                 data[(row*W*CHANNELS)+(col*CHANNELS)+2],
                 data[(row*W*CHANNELS)+(col*CHANNELS)+3] };
    else
        return { data[(row*W*CHANNELS)+(col*CHANNELS)+0],
                 data[(row*W*CHANNELS)+(col*CHANNELS)+1],
                 data[(row*W*CHANNELS)+(col*CHANNELS)+2],
                 255 };
}

// attention: matrix must have two empty black rows ( 0 and H+1 ) and two black columns ( 0 and W+1 );
void convert_uc_to_mat( unsigned char * data, mat &G ) {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            G[i+1][j+1] = new_pixel(data,i,j);
        }
    }
}

void convert_mat_to_uc( unsigned char * data, mat &G ) {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            data[CHANNELS*i*W+CHANNELS*j] = G[i+1][j+1].r;
            data[CHANNELS*i*W+CHANNELS*j+1] = G[i+1][j+1].g;
            data[CHANNELS*i*W+CHANNELS*j+2] = G[i+1][j+1].b;

            if(CHANNELS==4)
                data[CHANNELS*i*W+CHANNELS*j+3] = G[i+1][j+1].a;
        }
    }
}

void set_pixel( mat &Pic, int i, int j, double r, double g, double b ) {
    Pic[i][j].r = r;
    Pic[i][j].g = g;
    Pic[i][j].b = b;
}

double HF_apply_col(mat &P, const vint &core, int a, int b, int div, int col) {
    vint da = {-1,-1,-1,0,0,0,1,1,1},
         db = {-1,0,1,-1,0,1,-1,0,1};
    double ret(0);
    for(int i=0; i<9; i++){
        double add;
        if(col==0) add = ceil(P[a+da[i]][b+db[i]].r*core[i]/div);
        else if(col==1) add = ceil(P[a+da[i]][b+db[i]].g*core[i]/div);
        else add = ceil(P[a+da[i]][b+db[i]].b*core[i]/div);
        ret += add;
    }
    return ret;
}

mat filter( mat &P, const core &Core ) {
    mat res = P;
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++) {
            double r = HF_apply_col(P,Core.core1,i,j,Core.div,0),
                   g = HF_apply_col(P,Core.core1,i,j,Core.div,1),
                   b = HF_apply_col(P,Core.core1,i,j,Core.div,2);
            set_pixel(res,i,j,r,g,b);
        }
    return res;
}

double HF_bord_pixel(mat &P, const core &Core, int i, int j, int col){
    double a = HF_apply_col(P,Core.core1,i,j,Core.div,col),
           b = HF_apply_col(P,Core.core2,i,j,Core.div,col);
    return sqrt(pow(a,2)+pow(b,2));
}

// core: Previtt or Sobel
void borders(mat &P, const core &Core){
    mat newpic (H,line(W));
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++){
            double r = HF_bord_pixel(P,Core,i,j,0),
                   g = HF_bord_pixel(P,Core,i,j,1),
                   b = HF_bord_pixel(P,Core,i,j,2);
            set_pixel(newpic,i,j,r,g,b);
        }
    P = newpic;
}







//FOR BLACK-WHITE:
// attention: bw-matrix must have two empty black rows ( 0 and H+1 ) and two black columns ( 0 and W+1 );
void convert_uc_to_vvdb( const unsigned char * data, vvdb &G ) {
    for(int row=0; row<H; row++) {
        for(int col=0; col<W; col++) {
            int r = data[(row*W*CHANNELS)+(col*CHANNELS)+0],
                g = data[(row*W*CHANNELS)+(col*CHANNELS)+1],
                b = data[(row*W*CHANNELS)+(col*CHANNELS)+2];
            G[row+1][col+1] = (36*r+53*g+11*b)/100;
        }
    }
}

// empty rows and columns are not included into the final output;
void convert_vvdb_to_uc( unsigned char * data, const vvdb &G ) {
    for(int i=0; i<H; i++) {
        for(int j=0; j<W; j++) {
            data[CHANNELS*i*W+CHANNELS*j+0] = floor(G[i+1][j+1]);
            data[CHANNELS*i*W+CHANNELS*j+1] = floor(G[i+1][j+1]);
            data[CHANNELS*i*W+CHANNELS*j+2] = floor(G[i+1][j+1]);
        }
    }
}

void bw_set_pixel(vvdb &P, int i, int j, double x){
    P[i+1][j+1] = x;
}

double HF_apply(vvdb &P, const vint &core, int a, int b, int div){
    vint da,db;
        da = {-1,-1,-1,0,0,0,1,1,1};
        db = {-1,0,1,-1,0,1,-1,0,1};
    double ret(0);
    for(int i=0; i<9; i++)
        ret += P[a+da[i]][b+db[i]]*core[i];
    return ret/div;
}

double HF_bw_bord_pixel(vvdb &P, const core &Core, int i, int j){
    double a = HF_apply(P,Core.core1,i,j,Core.div),
           b = HF_apply(P,Core.core2,i,j,Core.div);
    return sqrt(pow(a,2)+pow(b,2));
}

void vvdb_draw_borders(vvdb &P, const core &Core){
    vvdb newpic (H+2,vdb(W+2));
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++){
            newpic[i][j]=HF_bw_bord_pixel(P,Core,i,j);
        }
    P = newpic;
}

void vvdb_highlight_borders(vvdb &P, int level){
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++)
            if(P[i][j]<level) P[i][j]=0;
            else P[i][j] = 255;
}

void convert_vvdb_to_mat(const vvdb &P, mat &M){
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++){
            M[i][j].r = P[i][j];
            M[i][j].g = P[i][j];
            M[i][j].b = P[i][j];
            M[i][j].a = 255;
        }
}

//for the filter of Perona and Malik:
double HF_h(double s, double k){
    return 1.0/( 1.0 + pow(s/k,2) );
}

void vvdb_Perona_n_Malik(vvdb &P,double t,double k){
    // this will be our result:
    vvdb Fin (H+2, vdb (W+2,0));

    double delta = 0.2,
           level = 0;
    double n,s,e,w; // north, south, east, west;

    // main process:
    while( level<t ){
        cout<<"Anti-aliasing: "<<100*level/t<<"%\n";
        for(int i=1; i<H+1; i++){
            for(int j=1; j<W+1; j++){
                n = P[i-1][j]-P[i][j];
                s = P[i+1][j]-P[i][j];
                e = P[i][j+1]-P[i][j];
                w = P[i][j-1]-P[i][j];
                double add = delta*( n*HF_h(n,k) + s*HF_h(s,k) + w*HF_h(w,k) + e*HF_h(e,k) );
                Fin[i][j] = P[i][j] + add;
                //cout<<add<<" ";
            }
        }
        for(int i=0; i<H; i++)
            for(int j=0; j<W; j++)
                P[i+1][j+1] = Fin[i+1][j+1];
        //show(P);
        level += delta;
    }
}



void show_progress(vvdb &P, char* name){
    unsigned char * data = (unsigned char*)malloc(H*W*CHANNELS*sizeof(unsigned char));
    convert_vvdb_to_uc(data,P);
    stbi_write_png(name,W,H,CHANNELS,data,W*CHANNELS);
}



// COLORING SECTION:

// returns vector<vector<int>> (H+2)*(W+2) with all elements =-1 except first and last rows and columns (they contain 0)
vvint make_vvint(){
    vvint vis (H+2,(vint(W+2,-1)));
    for(int i=0; i<W+2; i++){
        vis[0][i] = 0;
        vis[H+1][i] = 0;
    }
    for(int j=0; j<H+2; j++){
        vis[j][0] = 0;
        vis[j][W+1] = 0;
    }
    return vis;
}

qp update_front_line(qp &Q, vvdb &P, vvint &comp, int num){
    qp R;
    while(!Q.empty()){
        point p = Q.front();
        Q.pop();
        int x = p.h,
            y = p.w;
        if(x<H+1)
            if(P[x+1][y]==0){
                P[x+1][y]=100;
                R.push({x+1,y});
                comp[x+1][y] = num;
            }
        if(y<W+1)
            if(P[x][y+1]==0){
                P[x][y+1]=100;
                R.push({x,y+1});
                comp[x][y+1] = num;
            }
        if(x>1)
            if(P[x-1][y]==0){
                P[x-1][y]=100;
                R.push({x-1,y});
                comp[x-1][y] = num;
            }
        if(y>1)
            if(P[x][y-1]==0){
                P[x][y-1]=100;
                R.push({x,y-1});
                comp[x][y-1] = num;
            }

    }
    return R;
}

void dye(vvint &comp, mat &M, int num){
    double r = (33*num)%255,
           g = (57*num)%210,
           b = (98*num)%160;
    if(num==1){
        r=0; g=0; b=0;
    }

    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++)
            if(comp[i][j]==num)
                M[i][j] = {r,g,b,255};
}

void mark_comp(vvdb &P, int h, int w, vvint &comp, int num){
    qp Q;
    Q.push({h,w});
    comp[h][w]=num;
    while(!Q.empty()){
        Q = update_front_line(Q,P,comp,num);
    }
}

void dye_pic(vvdb &P, mat &M){

    vvint comp = make_vvint();
    int num = 1;
    bool run = true;
    while(run){
        bool found = false;
        int ibeg(1),jbeg(1);
        for(int i=ibeg; i<H+1; i++){
            for(int j=jbeg; j<W+1; j++){
                if(P[i][j]==0 && comp[i][j]<0){
                    found = true;
                    ibeg = i;
                    jbeg = j;
                    break;
                }
            }
            if(found)
                break;
        }
        if(found){
            mark_comp(P,ibeg,jbeg,comp,num);
            cout<<"Colorizing segment "<<num<<"\n";
            dye(comp,M,num);
            num++;
        }
        else run = false;
    }
}







// Unused:
vvdb bw_filter( vvdb &P, const core &Core ) {
    vvdb res (H+2, vdb (W+2,0));
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++) {
            res[i][j] = HF_apply(P,Core.core1,i,j,Core.div);
        }
    return res;
}


#endif // MYHEADER_H_INCLUDED
