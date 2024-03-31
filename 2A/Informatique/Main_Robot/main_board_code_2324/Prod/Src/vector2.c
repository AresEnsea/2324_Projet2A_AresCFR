#include "vector2.h"


Vector2 vector2_new(float x, float y) {
    Vector2 u = { x, y };
    return u;
}


void vector2_display(Vector2 u) {
    printf("{ x: %f, y: %f }\r\n", u.x, u.y);
}


float vector2_norm(Vector2 u) {
    return sqrt(u.x*u.x + u.y*u.y);
}


float vector2_angle(Vector2 u) {
    return atan2(u.y, u.x);
}


float vector2_dist(Vector2 u, Vector2 v) {
    Vector2 diff = { v.x - u.x, v.y - u.y };
    return vector2_norm(diff);
}


float vector2_dist2(Vector2 u, Vector2 v) {
    Vector2 diff = { v.x - u.x, v.y - u.y };
    return diff.x*diff.x + diff.y*diff.y;
}


Vector2 vector2_sum(Vector2 u, Vector2 v) {
    Vector2 sum = { v.x + u.x, v.y + u.y };
    return sum;
}


Vector2 vector2_diff(Vector2 u, Vector2 v) {
    Vector2 diff = { u.x - v.x, u.y - v.y };
    return diff;
}


float vector2_dot(Vector2 u, Vector2 v) {
    return u.x * v.x + u.y * v.y;
}


float vector2_cross(Vector2 u, Vector2 v) {
    return u.x * v.y - u.y * v.x;
}


/* Fonctions à effet de bord */

void vector2_normalize(Vector2* u) {
    float l = vector2_norm(*u);
    if (l != 0) {
        u->x /= l;
        u->y /= l;
    } else {
        u->x = 1;
        u->y = 0;
    }
}


void vector2_scale(Vector2* u, float k) {
    u->x *= k;
    u->y *= k;
}


void vector2_rotate(Vector2* u, float a) {
    float cos_a = cos(a);
    float sin_a = sin(a);
    float newX = cos_a*u->x - sin_a*u->y;
    u->y = sin_a*u->x + cos_a*u->y;
    u->x = newX;
}


void vector2_rotate90(Vector2* u) {
    float newX = -u->y;
    u->y = u->x;
    u->x = newX;
}
