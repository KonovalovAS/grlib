#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "myheader.h"

#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

typedef vector<pixel> line;
typedef vector<line> mat;
typedef vector<double> vdb;
typedef vector<vdb> vvdb;

void run(string inname) {
    inname += ".png";
    unsigned char *data = stbi_load(inname.c_str(),&W,&H,&CHANNELS,3);
    unsigned char *buf = data;

    vvdb P (H+2, vdb (W+2,0));
    convert_uc_to_vvdb(data,P);

    show_progress(P,"01_bw.png");

    cout<<"\nEnter desired values of parameters of anti-alaising\n(recommended: 5-100 for first, 1-10 for second; both > 0!):\nFirst parameter:\t";
    double t,k; cin>>t; cout<<"Second parameter:\t"; cin>>k;
    cout<<"\n";
        vvdb_Perona_n_Malik(P,t,k);
    show_progress(P,"02_anti-alaising.png");

    //const vvdb buf = P;
    //P = buf;

    cout<<"How to highlight the borders?\n1: Sobel's filter, 2: Previtt't filter.\nEnter 1 or 2:\n\t";
    int det; cin>>det;
    cout<<"\nApplying...\n";
        if(det==1) vvdb_draw_borders(P,Sobel);
        else vvdb_draw_borders(P,Previtt);
    show_progress(P,"03_borders_1.png");

    int level;
    cout<<"\nEnter the desired level of border-selection (recommended: 15-40):\n\t";
    cin>>level;
    cout<<"\nDrawing borders...\n";
        vvdb_highlight_borders(P,level);
    show_progress(P,"04_borders_2.png");

    cout<<"\nColorizing segments...\n";
    mat M (H+2,line(W+2,{0,0,0,255}));
    convert_vvdb_to_mat(P,M);
        dye_pic(P,M);
    convert_mat_to_uc( data, M );
    stbi_write_png("05_RESULT.png",W,H,CHANNELS,data,W*CHANNELS);

    cout<<"\nAlmost ready...";

    //Erasing borders:
    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++){
            if(M[i][j].r==255 && M[i][j].g==255 && M[i][j].b==255){
                M[i][j].r=0;
                M[i][j].g=0;
                M[i][j].b=0;
            }
        }

    mat R (H+2,line(W+2,{0,0,0,255}));
    data = stbi_load(inname.c_str(),&W,&H,&CHANNELS,3);
    convert_uc_to_mat(data,R);

    for(int i=1; i<H+1; i++)
        for(int j=1; j<W+1; j++){
                if(M[i][j].r+M[i][j].g+M[i][j].b!=0){
                    R[i][j].r = ( 4*R[i][j].r + 6*M[i][j].r ) /10;
                    R[i][j].g = ( 4*R[i][j].g + 6*M[i][j].g ) /10;
                    R[i][j].b = ( 4*R[i][j].b + 6*M[i][j].b ) /10;
                }
        }

    convert_mat_to_uc( data, R );
    stbi_write_png("06_OVERLAYER.png",W,H,CHANNELS,data,W*CHANNELS);

    cout<<"\nDONE!";
}

int main() {
    cout<<"Type file's name (without \".png\"):\n";
    string name; cin>>name;
    cout<<"\nReading your file...\n";
    run(name);

    return 0;
}
