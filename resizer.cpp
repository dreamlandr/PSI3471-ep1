//pixels.cpp - 2016
#include <cekeikon.h>
int main(int argc, char** argv)
{
    ImgAtb<COR> a;
    le(a, argv[1]);

    ImgAtb<COR> b;
    int i = a.rows/2;
    int j = a.cols/2;

    resize(a,b,Size(a.cols/2,a.rows/2));

    imp(b,"reduzido.jpg");
}


