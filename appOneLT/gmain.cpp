#define _CATMULL_ROM

#ifdef _CATMULL_ROM
#include"libOne.h"
#include"moveWithMouse.h"
#include"CATMULL_ROM.h"
void gmain()
{
    window(1920, 1080, full);
    //Colors
    colorMode(HSV, 100);
    angleMode(DEGREES);
    COLOR black(0, 0, 0);
    COLOR white(0, 0, 100);
    COLOR gray(0, 0, 50);
    COLOR red(330, 100, 100);
    COLOR yellow(65, 100, 80);
    COLOR rainbow;
    //Catmull-Rom Spline
    CATMULL_ROM path;
    int sw = 0;
    if (sw == 0) {
        //line point 等間隔に並べる
        float ofst = 400;//説明用に右にずらす値
        float w = width - ofst;
        int num = 5;
        float divW = w / num;
        for (int i = 0; i < num; i++) {
            path.setPoint(ofst + divW * i, height / 2);
        }
    }
    else if (sw == 1) {
        float cx = width / 2;
        float cy = height / 2;
        float ofst = 200;
        path.setPoint(cx - ofst, cy + ofst);//0==4

        path.setPoint(cx - ofst, cy - ofst);//1
        path.setPoint(cx + ofst, cy - ofst);//2
        path.setPoint(cx + ofst, cy + ofst);//3
        path.setPoint(cx - ofst, cy + ofst);//4
        path.setPoint(cx - ofst, cy - ofst);//5==1
        
        path.setPoint(cx + ofst, cy - ofst);//6==2
    }
    else if(sw==2){
        //star point
        int numCorners = 10;//点の数ではない
        float divAng = 360.0f / numCorners;
        for (int i = -1; i <= numCorners + 1; i++) {
            float radius = 200;
            if (i % 2 == 0)radius += 200;
            float x = Sin(divAng * i) * radius + width / 2;
            float y = -Cos(divAng * i) * radius + height / 2;
            path.setPoint(x, y);
        }
    }
    //Prepare for Mouse dragging
    for (size_t i = 0; i < path.numPoints(); i++) {
        addPointToMoveWithMouse(&path.points[i]);
    }

    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.01f;
    size_t idx=1;

    float tension = 0.5f;

    //Main Loop
    while (notQuit) {
        if (isTrigger(KEY_W))dt += 0.01f;
        if (isTrigger(KEY_S))dt -= 0.01f;
        if (isPress(KEY_D))tension += 0.01f;
        if (isPress(KEY_A))tension -= 0.01f;
        movePointWithMouse();
        clear(90, 100, 0);
        //Draw curve
        for (size_t i = 1; i <= path.numPoints()-3; i++) {
            VECTOR sp = path.compute(i, 0, tension);
            VECTOR v = path.derivative(i, 0, tension);
            VECTOR ep;
            if(sw!=2)arrow(sp, sp + v, red, 3);
            float dt = 0.05f;
            for (float t = dt; t <= 1.000001f; t += dt) {
                ep = path.compute(i, t, tension);
                rainbow.set(360 * t, 50, 100);
                line(sp, ep, rainbow, 5);
                //point(sp, rainbow, 10);
                v = path.derivative(i, t, tension);
                //if (sw != 2)arrow(ep, ep + v, red, 3);
                sp = ep;
            }
            //ここは２回重なって書くこともあるが、よしとする。
            v = path.derivative(i, 1, tension);
            if(sw!=2)arrow(ep, ep + v, red, 3);
        }
        //Draw control points
        for (size_t i = 0; i < path.numPoints(); i++) {
            VECTOR p = path.points[i];
            circle(p, 14, black, white, 6);
            fill(yellow);
            textMode(BCENTER);
            textSize(30);
            text((let)"p" + (int)i, p.x, p.y+25);
        }
        //Character motion
        static int sw = 0;
        if (isTrigger(KEY_SPACE))++sw %= 4;
        if (sw == 0||sw==2) {
            //アニメーション
            t += dt;
            if (t >= 1.0f) {
                if (idx < path.numPoints() - 3) {
                    idx++;
                    t -= 1.0f;
                }
                else {
                    idx = 1;
                    t = 0;
                }
            }
        }
        else if (sw == 1) {
            //スタート地点で固定
            idx = 1;
            t = 0;
            arrow(path.points[0], path.points[2], gray, 3);
        }
        else if (sw == 3) {
            //終点で固定
            idx = path.numPoints() - 3;
            t = 1;
            size_t n = path.numPoints();
            arrow(path.points[n - 3], path.points[n - 1], gray, 3);
        }
        VECTOR p = path.compute(idx, t, tension);
        VECTOR v = path.derivative(idx, t, tension);
        float angle = Atan2(v.y, v.x);
        image(img, p, angle, 1, CENTER);

        fill(white);
        print((let)"t=" + t);
        print((let)"tension=" + tension);
    }
}
#endif
