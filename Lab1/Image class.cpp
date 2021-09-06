#include <iostream>
#include <vector>
#include <string>

typedef unsigned int ui;
typedef unsigned char uc;
using std::vector, std::cout, std::swap, std::string;

ui dig_count(int a)
{
    int c = 0;
    while (a >= 0){
        ++c;
        a /= 10;
        --a;
    }
    return c;
}

class Image{
private:
    ui height, width, depth;
    vector<vector<vector<ui>>> image;

public:
    Image(ui* raw, ui width, ui height, ui depth):
        height{height}, width{width}, depth{depth}, image{vector<vector<vector<ui>>> (height, vector<vector<ui>> (width, vector<ui> (depth, 0)))}
    {
            for(ui i=0; i<height; ++i){
                for(ui j=0; j<width; ++j){
                    for (ui k=0; k<depth; ++k){
                        image[i][j][k] = raw[k+depth*(j+i*width)];
                    }
                }
            }
    }
    Image(): Image(0, 0, 0){
        //std::vector<std::vector<std::vector<ui>>> image;
    }
    Image(ui width, ui height, ui depth){
        vector<vector<vector<ui>>> image(height, vector<vector<ui>> (width, vector<ui> (depth, 0)));
    }
    Image(Image & other){
        height = other.get_height();
        width = other.get_width();
        depth = other.get_depth();
        image = other.image;
    }

    void clear()
    {
        image.clear();
        height = 0;
        width = 0;
        depth = 0;
    }

    ui get_height()
    {
        return height;
    }

    ui get_width()
    {
        return width;
    }

    ui get_depth()
    {
        return depth;
    }

    int at(ui x, ui y, ui d)
    {
        if ((y<height)&&(x<width)&&(d<depth)){
            return image[y][x][d];
        }
        else{
            return -1;
        }
    }

    void image_crop(ui xi, ui yi, ui xf, ui yf)
    {
        ui new_height = yf-yi+1;
        ui new_width = xf-xi+1;
        vector<vector<vector<ui>>> new_image(yf-yi+1, vector<vector<ui>> (xf-xi+1, vector<ui> (depth, 0)));
        for(ui i=0; i<new_height; ++i){
            for(ui j=0; j<new_width; ++j){
                for (ui k=0; k<depth; ++k){
                    new_image[i][j][k] = image[i+yi][j+xi][k];
                }
            }
        }
        height = new_height;
        width = new_width;
        image = new_image;
    }

    void print()
    {
        ui s=0;
        for(ui i=0; i<height; ++i){
            for(ui j=0; j<width; ++j){
                for (ui k=0; k<depth; ++k){
                    s += image[i][j][k];
                }
                cout << s/depth<<' ';
                for (ui f=0; f<3-dig_count(s/depth); ++f){
                    cout <<' ';
                }
                s = 0;
            }
            cout << '\n';
        }
    }

    void to_gs()
    {
        vector<vector<vector<ui>>> new_image(height, vector<vector<ui>> (width, vector<ui> (1, 0)));
        ui s=0;
        for(ui i=0; i<height; ++i){
            for(ui j=0; j<width; ++j){
                for (ui k=0; k<depth; ++k){
                    s += image[i][j][k];
                }
                new_image[i][j][0] = s/depth;
                s = 0;
            }
        }
        image = new_image;
        depth = 1;
    }

    void to_bmp(const char* name)
    {
        FILE* f;
        uc* img = NULL;
        ui filesize = 54 + 3*width*height;
        img = new uc[3*width*height];
        for(ui i=0; i<height; ++i){
            for(ui j=0; j<width; ++j){
                for(ui k=0; k<3; ++k){
                    img[k+depth*(j+i*width)] = (uc)(image[i][j][k]);
                }
            }
        }

        uc bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
        uc bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
        uc bmppad[3] = {0,0,0};

        bmpfileheader[2] = (uc)(filesize);
        bmpfileheader[3] = (uc)(filesize>>8);
        bmpfileheader[4] = (uc)(filesize>>16);
        bmpfileheader[5] = (uc)(filesize>>24);

        bmpinfoheader[4] = (uc)(width);
        bmpinfoheader[5] = (uc)(width>>8);
        bmpinfoheader[6] = (uc)(width>>16);
        bmpinfoheader[7] = (uc)(width>>24);
        bmpinfoheader[8] = (uc)(height);
        bmpinfoheader[9] = (uc)(height>>8);
        bmpinfoheader[10] = (uc)(height>>16);
        bmpinfoheader[11] = (uc)(height>>24);

        f = fopen(name,"wb");
        fwrite(bmpfileheader, 1, 14, f);
        fwrite(bmpinfoheader, 1, 40, f);
        for(ui i=0; i<height; ++i){
            fwrite(img+(width*(height-i-1)*3), 3, width, f);
            fwrite(bmppad, 1, (4-(width*3)%4)%4, f);
        }

        delete [] img;
        fclose(f);

    }
};

int main()
{
    ui h, w, d;
    h = 100;
    w = 100;
    d = 3;
    ui* a = new ui[d*w*h];
    for(ui i=0; i<h; ++i){
        for(ui j=0; j<w; ++j){
            for (ui k=0; k<d; ++k){
                a[k+d*(j+i*w)] = (31*(i+j)*(k+1))%255;
            }
        }
    }

    Image img(a, w, h, d);
    /*
    cout<<img.at(2,4,1) <<'\n';
    img.print();
    Image img2 = img;
    cout<<img2.get_width()<<'\n';
    img2.image_crop(2,2,7,8);
    img2.print();
    cout<<img2.get_height()<<'\n';
    cout<<img2.get_depth()<<'\n';
    img2.to_gs();
    img2.print();
    cout << img2.get_depth()<<'\n';
    */
    img.to_bmp("image1.bmp");
    return 0;
}
