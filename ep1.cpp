#include <cekeikon.h>
#include <queue>

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
    return b;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("ep1: Conta o numero de moedas em uma imagem\n");
        printf("Uso\n");
        printf("ep1 arquivo_de_entrada.jpg arquivo_de_saida.jpg\n");
        erro("Erro: Numero de argumentos invalido.");
        exit(0);
    }

    ImgAtb<COR> img;
    le(img, argv[1]);
    ImgAtb<COR> imgreduz;
    resize(img, imgreduz, Size(img.cols / 5, img.rows / 5));
    imp(imgreduz, "imgreduz.jpg");
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
    cvtColor(tmp, tmp, CV_HSV2BGR);
    imp(tmp, "tmp.jpg");

    Point ce;
    ImgAtb<COR> t0(40, 40, COR(255, 255, 255));
    ce.x = 20;
    ce.y = 20;
    circle(t0, ce, 20, 0, -1);
    ImgAtb<COR> t1(44, 44, COR(255, 255, 255));
    ce.x = 22;
    ce.y = 22;
    circle(t1, ce, 22, 0, -1);
    ImgAtb<COR> t2(50, 50, COR(255, 255, 255));
    ce.x = 25;
    ce.y = 25;
    circle(t2, ce, 25, 0, -1);
    ImgAtb<COR> t3(54, 54, COR(255, 255, 255));
    ce.x = 27;
    ce.y = 27;
    circle(t3, ce, 27, 0, -1);
    ImgAtb<COR> t4(60, 60, COR(255, 255, 255));
    ce.x = 30;
    ce.y = 30;
    circle(t4, ce, 30, 0, -1);
    ImgAtb<COR> t5(64, 64, COR(255, 255, 255));
    ce.x = 32;
    ce.y = 32;
    circle(t5, ce, 32, 0, -1);
    ImgAtb<COR> t6(70, 70, COR(255, 255, 255));
    ce.x = 35;
    ce.y = 35;
    circle(t6, ce, 35, 0, -1);
    ImgAtb<COR> t7(74, 74, COR(255, 255, 255));
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
    // Gera imagem com os candidatos a centro
    for (int i = 0; i < 8; i++)
    {
        converte(te[i], teg[i]);
    }
    Mat_<COR> temax(tmp.rows, tmp.cols, COR(0, 0, 0));
    for (int l = 0; l < tmp.rows; l++)
    {
        for (int c = 0; c < tmp.cols; c++)
        {
            temax(l, c)[0] = teg[0](l, c);
            temax(l, c)[1] = 0;
            for (int i = 1; i < 8; i++)
            {
                if (teg[i](l, c) > temax(l, c)[0])
                {
                    temax(l, c)[0] = teg[i](l, c);
                    temax(l, c)[1] = i;
                }
            }
        }
    }
    imp(temax, "temax.jpg");
    // cria uma lista com os candidatos a centro
    queue<int> cnd;
    for (int l = 0; l < tmp.rows; l++)
    {
        for (int c = 0; c < tmp.cols; c++)
        {
            if (temax(l, c)[0] > 190)
            {
                if (temax(l, c)[0] >= temax(l - 1, c - 1)[0] && temax(l, c)[0] >= temax(l - 1, c)[0] && temax(l, c)[0] >= temax(l - 1, c + 1)[0] && temax(l, c)[0] >= temax(l, c - 1)[0] && temax(l, c)[0] >= temax(l, c + 1)[0] && temax(l, c)[0] >= temax(l + 1, c - 1)[0] && temax(l, c)[0] >= temax(l + 1, c)[0] && temax(l, c)[0] >= temax(l + 1, c + 1)[0])
                {
                    cnd.push(l);
                    cnd.push(c);
                    cnd.push(temax(l, c)[0]);
                    cnd.push(temax(l, c)[1]);
                }
            }
        }
    }
    queue<int> cnt;
    int x1 = 0, y1 = 0, v1 = 0, s1 = 0, x2 = 0, y2 = 0, v2 = 0, s2 = 0;
    while (!cnd.empty())
    {
        int isgood;
        queue<int> temp;
        for (int i = 0; i < cnd.size(); i++)
        {
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
        s1 = cnd.front();
        cnd.pop();
        temp.pop();
        temp.pop();
        temp.pop();
        temp.pop();
        if (!temp.empty())
        {
            while (!temp.empty())
            {
                isgood = 1;
                x2 = temp.front();
                temp.pop();
                y2 = temp.front();
                temp.pop();
                v2 = temp.front();
                temp.pop();
                s2 = temp.front();
                temp.pop();
                double dist = sqrt(double(elev2(x1 - x2) + elev2(y1 - y2)));
                if (dist < 15)
                {
                    if (v1 > v2)
                    {
                        cnd.push(x1);
                        cnd.push(y1);
                        cnd.push(v1);
                        cnd.push(s1);
                    }
                    else if (v1 < v2)
                    {
                        cnd.push(x2);
                        cnd.push(y2);
                        cnd.push(v2);
                        cnd.push(s2);
                    }
                    else
                    {
                        if (x1 != x2 || y1 != y2)
                        {
                            int x = (x1 + x2) / 2;
                            int y = (y1 + y2) / 2;
                            int v = (v1 + v2) / 2;
                            int s = (s1 + s2) / 2;
                            cnd.push(x);
                            cnd.push(y);
                            cnd.push(v);
                            cnd.push(s);
                        }
                    }
                    isgood = 0;
                    break;
                }
            }
            if (isgood == 1)
            {
                cnt.push(x1);
                cnt.push(y1);
                cnt.push(v1);
                cnt.push(s1);
            }
        }
        else
        {
            cnt.push(x1);
            cnt.push(y1);
            cnt.push(v1);
            cnt.push(s1);
        }
    }
    int num = 0;
    Point_<int> p;
    Mat_<COR> centros(tmp.rows, tmp.cols, COR(255, 255, 255));
    while (!cnt.empty())
    {
        p.y = cnt.front();
        cnt.pop();
        p.x = cnt.front();
        cnt.pop();
        v1 = cnt.front();
        cnt.pop();
        s1 = cnt.front();
        cnt.pop();
        if (s1 == 0)
            s1 = 20;
        if (s1 == 1)
            s1 = 22;
        if (s1 == 2)
            s1 = 25;
        if (s1 == 3)
            s1 = 27;
        if (s1 == 4)
            s1 = 30;
        if (s1 == 5)
            s1 = 32;
        if (s1 == 6)
            s1 = 35;
        if (s1 == 7)
            s1 = 37;
        circle(imgreduz, p, s1, 128, 1);
        circle(imgreduz, p, 1, 128, -1);
        num++;
    }
    cvtColor(imgreduz, imgreduz, CV_HSV2BGR);
    p.x = 5;
    p.y = 20;
    char s[100];
    sprintf(s, "Ha %d moeda(s)", num);
    putText(imgreduz, s, p, FONT_HERSHEY_SIMPLEX, 0.75, 0, 2.5);
    resize(imgreduz, imgreduz, Size(imgreduz.cols * 5, imgreduz.rows * 5));
    cout << num << endl;
    imp(imgreduz, argv[2]);
}
