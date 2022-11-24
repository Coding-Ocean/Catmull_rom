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
    CATMULL_ROM spline;
    int numCorners = 4;//点の数ではない
    float divAng = 360.0f / numCorners;
    for (int i = -1; i <= numCorners + 1; i++) {
        float radius = 200;
        float x = Sin(divAng * i) * radius + width / 2;
        float y = -Cos(divAng * i) * radius + height / 2;
        spline.setPoint(x, y);
    }
    //Prepare for Mouse dragging
    for (size_t i = 0; i < spline.numPoints(); i++) {
        addPointToMoveWithMouse(&spline.points[i]);
    }
    //for character motion
    int img = loadImage("car.png");
    float t = 0;
    float dt = 0.005f;
    size_t idx = 1;

    //接線ベクトルの長さ調整
    float tension = 0.5f;

    //Main Loop
    while (notQuit) {
        if (isPress(KEY_W))tension += 0.01f;
        if (isPress(KEY_S))tension -= 0.01f;
        movePointWithMouse();
        clear(90, 100, 0);
        //Draw curve
        for (size_t i = 1; i <= spline.numPoints() - 3; i++) {
            VECTOR sp = spline.compute(i, 0, tension);
            float dt = 0.025f;
            for (float t = dt; t <= 1.000001f; t += dt) {
                VECTOR ep = spline.compute(i, t, tension);
                rainbow.set(360 * t, 50, 100);
                line(sp, ep, rainbow, 10);
                sp = ep;
            }
        }
        //Draw tangent vectors
        for (size_t i = 1; i <= spline.numPoints() - 3; i++) {
            VECTOR p = spline.compute(i, 0, tension);
            VECTOR v = spline.derivative(i, 0, tension);
            arrow(p, p + v, yellow, 3);
            //最後の接線ベクトル
            if (i == spline.numPoints() - 3) {
                p = spline.compute(i, 1, tension);
                v = spline.derivative(i, 1, tension);
                arrow(p, p + v, yellow, 3);
            }
        }
        //Draw control points
        VECTOR ofst(0, 25);
        for (size_t i = 0; i < spline.numPoints(); i++) {
            VECTOR p = spline.points[i];
            circle(p, 14, black, white, 6);
            text((let)"p" + (int)i, p + ofst, BCENTER, white, 30);
        }
        //Character motion
        t += dt;
        if (t >= 1.0f) {
            if (idx < spline.numPoints() - 3) {
                idx++;
                t -= 1.0f;
            }
            else {
                idx = 1;
                t = 0;
            }
        }
        VECTOR p = spline.compute(idx, t, tension);
        VECTOR v = spline.derivative(idx, t, tension);
        float angle = Atan2(v.y, v.x);
        image(img, p, angle, 1, CENTER);

        fill(white);
        print((let)"t=" + t);
        print((let)"tension=" + tension);
    }
}
