#include "bezier.h"


Bezier* bezier_new(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int lutLength) {
    Bezier* b = (Bezier*) malloc(sizeof(Bezier));
    bezier_set(b, x1, y1, x2, y2, x3, y3, x4, y4, lutLength);
    return b;
}


Bezier* bezier_newEmpty() {
    Bezier* b = (Bezier*) malloc(sizeof(Bezier));
    return b;
}


void bezier_set(Bezier* b, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int lutLength) {
    b->p1 = vector2_new(x1, y1);
    b->p2 = vector2_new(x2, y2);
    b->p3 = vector2_new(x3, y3);
    b->p4 = vector2_new(x4, y4);
    b->lutLength = lutLength;
    b->lut = (Vector2*) malloc(sizeof(Vector2) * b->lutLength);
    for (int i=0; i<b->lutLength; i++) {
        float t = (float) i/(b->lutLength-1);
        Vector2 eval = bezier_eval(b, t);
        b->lut[i] = eval;
    }
}


void bezier_display(Bezier* b) {
    printf("Bezier {\r\n    ");
    vector2_display(b->p1);
    printf("    ");
    vector2_display(b->p2);
    printf("    ");
    vector2_display(b->p3);
    printf("    ");
    vector2_display(b->p4);
    printf("}\r\n");
}


Vector2 bezier_eval(Bezier* b, float t) {
    float u = 1-t;
    float x = b->p1.x * u*u*u + b->p2.x * 3*u*u*t + b->p3.x * 3*u*t*t + b->p4.x * t*t*t;
    float y = b->p1.y * u*u*u + b->p2.y * 3*u*u*t + b->p3.y * 3*u*t*t + b->p4.y * t*t*t;
    Vector2 eval = { x, y };
    return eval;
}


Vector2 bezier_evalLut(Bezier* b, float t) {
    int i = round(t*(b->lutLength-1));
    return b->lut[i];
}


Vector2 bezier_deriv1(Bezier* b, float t) {
    float u = 1-t;
    float x = (b->p2.x - b->p1.x) * 3*u*u + (b->p3.x - b->p2.x) * 6*u*t + (b->p4.x - b->p3.x) * 3*t*t;
    float y = (b->p2.y - b->p1.y) * 3*u*u + (b->p3.y - b->p2.y) * 6*u*t + (b->p4.y - b->p3.y) * 3*t*t;
    Vector2 eval = { x, y };
    return eval;
}


Vector2 bezier_deriv2(Bezier* b, float t) {
    float u = 1-t;
    float x = (b->p3.x - 2*b->p2.x + b->p1.x) * 6*u + (b->p4.x - 2*b->p3.x + b->p2.x) * 6*t;
    float y = (b->p3.y - 2*b->p2.y + b->p1.y) * 6*u + (b->p4.y - 2*b->p3.y + b->p2.y) * 6*t;
    Vector2 eval = { x, y };
    return eval;
}


float bezier_curvature(Bezier* b, float t) {
    Vector2 diff1 = bezier_deriv1(b, t); // B'(t)
    Vector2 diff2 = bezier_deriv2(b, t); // B''(t)
    float num = vector2_cross(diff1, diff2);
    float den = vector2_norm(diff1);
    if (den == 0)
        return INFINITY;
    return num/(den*den*den);
}


float bezier_projectLut(Bezier* b, Vector2 p) {
    float minDist = INFINITY;
    float minIndex = 0;
    for (int i=0; i<b->lutLength; i++) {
        float dist = vector2_dist2(p, b->lut[i]);
        if (dist < minDist) {
            minDist = dist;
            minIndex = i;
        }
    }
    float tLut = (float) minIndex/(b->lutLength-1);
    return tLut;
}


float bezier_project(Bezier* b, Vector2 p, float precision) {
    float tLut = bezier_projectLut(b, p);

    float halfWidth = 1.0/(b->lutLength-1);

    float t_a = tLut - halfWidth;
    t_a = (t_a<0)?0:t_a;

    float t_b = tLut + halfWidth;
    t_b = (t_b>1)?1:t_b;

    Vector2 p_a, p_b;

    while (t_b - t_a > precision) {
        p_a = bezier_eval(b, t_a);
        p_b = bezier_eval(b, t_b);
        if (vector2_dist2(p, p_a) < vector2_dist2(p, p_b))
            t_b = (t_a + t_b)/2;
        else
            t_a = (t_a + t_b)/2;
    }
    return (t_a + t_b)/2;
}
