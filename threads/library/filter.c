//
// Created by radekkoziol on 20.05.18.
//

int max(int x, int y) {
    return x > y ? x : y;
}

void filter_pix(int x, int y) {

    float s = 0.0;
    int p1, p2;
    for (int i = 0; i < c; i++)
        for (int j = 0; j < c; j++) {
            p1 = max(1, (int) (x - ceil(c / 2.0) + i));
            p2 = max(1, (int) (y - ceil(c / 2.0) + j));
//                printf("p1 = %d p2 = %d\n",p1,p2);
            if (p1 < w && p2 < h){
                s += (filter[i][j] * in_pix[p1][p2]);
//                if(s == 0.0)
//                    printf("filtr %f pix %d\n",filter[i][j] ,in_pix[p1][p2]);
            }
        }


    out_pix[x][y] = (short) roundf(s);
    if(out_pix[x][y] == 0){
        out_pix[x][y] = 10;
    }
}

void filter_rect(int x1, int y1, int x2, int y2) {

    printf("[Thread] Filtering rectangle from (%d,%d) to (%d,%d)!\n", x1, y1, x2, y2);

    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++)
            filter_pix(i, j);

}

void *
filter_image(int N) {

    if (N == 0)
        filter_rect(N * w / th_num, 0, (N + 1) * w / th_num, h - 1);
    else if (N == th_num - 1)
        filter_rect(N * w / th_num + 1, 0, (N + 1) * w / th_num - 1, h - 1);
    else
        filter_rect(N * w / th_num + 1, 0, (N + 1) * w / th_num, h - 1);

}
