#include <stdio.h>

int volumeOfTriange2(int ax, int ay, int bx, int by, int cx, int cy) {
    // Find the volume using the cross product
    // Readjust c to origin
    if (cx) {
        ax -= cx;
        bx -= cx;
    }
    if (cy) {
        ay -= cy;
        by -= cy;
    }
    
    int result = (ax * by - ay * bx);
    return result < 0 ? -result : result;
}

int containsPoint(int ax, int ay, int bx, int by, int cx, int cy, int px, int py) {
    int sizeWithPoint = volumeOfTriange2(ax, ay, bx, by, px, py);
    sizeWithPoint += volumeOfTriange2(cx, cy, bx, by, px, py);
    sizeWithPoint += volumeOfTriange2(ax, ay, cx, cy, px, py);
    
    int normalSize = volumeOfTriange2(ax, ay, bx, by, cx, cy);
    return !(sizeWithPoint > normalSize);
}

int main (int argc, char **argv) {
    char buf[512];
    int sum = 0;
    while(gets(buf)) {
        int ax, ay, bx, by, cx, cy;
        sscanf(buf, "%d,%d,%d,%d,%d,%d", &ax, &ay, &bx, &by, &cx, &cy);
        sum += containsPoint(ax, ay, bx, by, cx, cy, 0, 0);
    }
    printf("%d\n", sum);
}