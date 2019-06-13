#include <cekeikon.h>

ImgAtb<COR> pintaFundo(ImgAtb<COR> a, int ls, int cs)
{
    ImgAtb<COR> b = a.clone();
    b.backg = COR(0, 0, 0);
    queue<int> q;
    q.push(ls);
    q.push(cs);
    while (!q.empty())
    {
        int l = q.front();
        q.pop();
        int c = q.front();
        q.pop();
        if ((int)b(l, c)[0] >= 31 && (int)b(l, c)[0] < 120)
        {
            b(l, c) = COR(0, 0, 255);
            q.push(l - 1);
            q.push(c); //N
            q.push(l + 1);
            q.push(c); //S
            q.push(l);
            q.push(c + 1); //E
            q.push(l);
            q.push(c - 1); //W
        }
    }
    cout << b(-10, +1000) << endl;
    return b;
}

ImgAtb<COR> pintaMoeda(ImgAtb<COR> a, int ls, int cs)
{
    ImgAtb<COR> b = a.clone();
    b.backg = COR(0, 0, 0);
    queue<int> q;
    q.push(ls);
    q.push(cs);
    while (!q.empty())
    {
        int l = q.front();
        q.pop();
        int c = q.front();
        q.pop();
        if (b(l, c) not_eq COR(0, 0, 255) && b(l, c) not_eq COR(0, 0, 0))
        {
            b(l, c) = COR(0, 0, 0);
            q.push(l - 1);
            q.push(c); //N
            q.push(l + 1);
            q.push(c); //S
            q.push(l);
            q.push(c + 1); //E
            q.push(l);
            q.push(c - 1); //W
        }
    }
    // cout << b(-10,+1000) << endl;
    return b;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("ep1: Conta o numero de moedas em uma imagem\n");
        printf("ep1 arquivo_de_entrada.jpg arquivo_de_saida.jpg\n");
        printf("ep1 arquivo_de_entrada.jpg arquivo_de_saida.jpg\n");
        erro("Erro: Numero de argumentos invalido.");
        exit(0);
    }

    ImgAtb<COR> img;
    le(img, argv[1]);
    ImgAtb<COR> imgreduz;
    resize(img, imgreduz, Size(img.cols / 5, img.rows / 5));

    ImgAtb<COR> sai = imgreduz.clone();
    
    cvtColor(imgreduz, imgreduz, CV_BGR2HSV);
    imgreduz.backg = COR(0, 0, 0);
    ImgAtb<COR> tmp = imgreduz.clone();
    tmp = pintaFundo(imgreduz, 0, 0);
    for (int l = 0; l <= tmp.rows; l++)
    {
        for (int c = 0; c <= tmp.cols; c++)
        {
            if (tmp(l, c) not_eq COR(0, 0, 255) && tmp(l, c) not_eq COR(0, 0, 0))
            {
                tmp = pintaMoeda(tmp, l, c);
            }
        }
    }

    for (int l = 0; l <= tmp.rows; l++)
    {
        for (int c = 0; c <= tmp.cols; c++)
        {
            if (tmp(l, c - 1) not_eq tmp(l, c) || tmp(l - 1, c) not_eq tmp(l, c))
            {
                sai(l, c) = COR(0, 0, 0);
            }
        }
    }
    cvtColor(tmp, tmp, CV_HSV2BGR);
    imp(tmp,"tmp.jpg");
    
    Point ce;

    ImgAtb<COR> t0(40, 40, COR(128, 128, 128));
    ce.x = 20;
    ce.y = 20;
    circle(t0, ce, 20, 0, -1);
    ImgAtb<COR> t1(44, 44, COR(128, 128, 128));
    ce.x = 22;
    ce.y = 22;
    circle(t1, ce, 22, 0, -1);
    ImgAtb<COR> t2(50, 50, COR(128, 128, 128));
    ce.x = 25;
    ce.y = 25;
    circle(t2, ce, 25, 0, -1);
    ImgAtb<COR> t3(54, 54, COR(128, 128, 128));
    ce.x = 27;
    ce.y = 27;
    circle(t3, ce, 27, 0, -1);
    ImgAtb<COR> t4(60, 60, COR(128, 128, 128));
    ce.x = 30;
    ce.y = 30;
    circle(t4, ce, 30, 0, -1);
    ImgAtb<COR> t5(64, 64, COR(128, 128, 128));
    ce.x = 32;
    ce.y = 32;
    circle(t5, ce, 32, 0, -1);
    ImgAtb<COR> t6(70, 70, COR(128, 128, 128));
    ce.x = 35;
    ce.y = 35;
    circle(t6, ce, 35, 0, -1);
    ImgAtb<COR> t7(74, 74, COR(128, 128, 128));
    ce.x = 37;
    ce.y = 37;
    circle(t7, ce, 37, 0, -1);

    Mat_<FLT> te[8];
    matchTemplate(tmp, t0, te[0], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t1, te[1], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t2, te[2], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t3, te[3], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t4, te[4], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t5, te[5], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t6, te[6], CV_TM_CCOEFF_NORMED);
    matchTemplate(tmp, t7, te[7], CV_TM_CCOEFF_NORMED);
    
    te[0] = aumentaCanvas(te[0], tmp.rows, tmp.cols, (t0.rows - 1) / 2, (t0.cols - 1) / 2, 0.0);
    te[1] = aumentaCanvas(te[1], tmp.rows, tmp.cols, (t1.rows - 1) / 2, (t1.cols - 1) / 2, 0.0);
    te[2] = aumentaCanvas(te[2], tmp.rows, tmp.cols, (t2.rows - 1) / 2, (t2.cols - 1) / 2, 0.0);
    te[3] = aumentaCanvas(te[3], tmp.rows, tmp.cols, (t3.rows - 1) / 2, (t3.cols - 1) / 2, 0.0);
    te[4] = aumentaCanvas(te[4], tmp.rows, tmp.cols, (t4.rows - 1) / 2, (t4.cols - 1) / 2, 0.0);
    te[5] = aumentaCanvas(te[5], tmp.rows, tmp.cols, (t5.rows - 1) / 2, (t5.cols - 1) / 2, 0.0);
    te[6] = aumentaCanvas(te[6], tmp.rows, tmp.cols, (t6.rows - 1) / 2, (t6.cols - 1) / 2, 0.0);
    te[7] = aumentaCanvas(te[7], tmp.rows, tmp.cols, (t7.rows - 1) / 2, (t7.cols - 1) / 2, 0.0);

    Mat_<GRY> teg[8];
    queue<int> cnd;
    // Gera imagem com os candidatos a centro
    for(int i = 0; i < 8; i++)
    {  
        converte(te[i],teg[i]);
    }
    Mat_<GRY> temax(tmp.rows, tmp.cols);

    for (int l = 0; l < tmp.rows; l++)
    {
        for (int c = 0; c < tmp.cols; c++)
        {
            if(teg[0](l, c) > 190 || teg[1](l, c) > 190 || teg[2](l, c) > 190 || teg[3](l, c) > 190 || teg[4](l, c) > 190 || teg[5](l, c) > 190 || teg[6](l, c) > 190 || teg[7](l, c) > 190)
            {
                temax(l, c) = teg[0](l, c);
                for(int i = 1; i < 8; i++)
                {  
                    if(teg[i](l, c) > temax(l, c))
                    { 
                        temax(l, c) = teg[i](l, c);
                    }
                }
            }
        }
    }

    // cria uma lista com os candidatos a centro
    for (int l = 0; l < tmp.rows; l++)
    {
        for (int c = 0; c < tmp.cols; c++)
        {
            if(teg[0](l, c) > 190 || teg[1](l, c) > 190 || teg[2](l, c) > 190 || teg[3](l, c) > 190 || teg[4](l, c) > 190 || teg[5](l, c) > 190 || teg[6](l, c) > 190 || teg[7](l, c) > 190)
            {
                if(temax(l,c) >= temax(l-1,c-1) && temax(l,c) >= temax(l-1,c) && temax(l,c) >= temax(l-1,c+1) && temax(l,c) >= temax(l,c-1) && temax(l,c) >= temax(l,c+1) && temax(l,c) >= temax(l+1,c-1) && temax(l,c) >= temax(l+1,c) && temax(l,c) >= temax(l+1,c+1))
                {  
                    cnd.push(l);
                    cnd.push(c);
                    cnd.push(temax(l,c));
                }
            }
        }
    }
    // Resto
    int x1=0,y1=0,v1=0,x2=0,y2=0,v2=0;
    queue<int> cnt;
    while(!cnd.empty())
    {
        queue<int> temp;
        for(int i = 0; i < cnd.size(); i++)
        {
            cnd.push(cnd.front());
            temp.push(cnd.front());
            cnd.pop();
            cnd.push(cnd.front());
            temp.push(cnd.front());
            cnd.pop();
            cnd.push(cnd.front());
            temp.push(cnd.front());
            cnd.pop();
        }
        x1 = cnd.front();
        cnd.pop();
        y1 = cnd.front();
        cnd.pop();
        v1 = cnd.front();
        cnd.pop();
        while(!temp.empty())
        {
            x2 = temp.front();
            temp.pop();
            y2 = temp.front();
            temp.pop();
            v2 = temp.front();
            temp.pop();

            double wot = sqrt(double(elev2(x1 - x2) + elev2(y1 - y2)));
            if(wot < 15)
            {
                if(v1 > v2)
                {
                    cnd.push(x1);
                    cnd.push(y1);
                    cnd.push(v1);
                }
                else if(v1 < v2)
                {
                    cnd.push(x2);
                    cnd.push(y2);
                    cnd.push(v2);
                }
                else
                {
                    int x = (x1+x2)/2;
                    int y = (y1+y2)/2;
                    int z = (v1+v2)/2;
                    cnt.push(x);
                    cnt.push(y);
                    cnt.push(z);
                }
                break;
            }
            else
            {
                cnt.push(x1);
                cnt.push(y1);
                cnt.push(v1);
            }
        }
    }
    imp(temax,"temax.jpg");
    Mat_<GRY> centros(tmp.rows, tmp.cols, GRY(0));
    while(!cnt.empty())
    {
        x1 = cnt.front();
        cnt.pop();
        y1 = cnt.front();
        cnt.pop();
        v1 = cnt.front();
        cnt.pop();
        centros(x1,y1) = v1;
    }
    imp(centros,"centros.jpg");



    // cout << x.front() << endl;
    // cout << y.front() << endl;
    // cout << v.front() << endl;
    //         if (te1g(l, c) < 200 && te1g(l, c) not_eq 0)
    //         {
    //             te1g(l, c) = GRY(0);
    //         }
    //         if (te2g(l, c) < 200 && te2g(l, c) not_eq 0)
    //         {
    //             te2g(l, c) = GRY(0);
    //         }
    //         if (te3g(l, c) < 200 && te3g(l, c) not_eq 0)
    //         {
    //             te3g(l, c) = GRY(0);
    //         }
    //         
    //     }
    // }
    // imp(te1g,"te1g.jpg");
    // imp(te2g,"te2g.jpg");
    // imp(te3g,"te3g.jpg");
    // imp(total,"total.jpg");

}
