#include "library.h"

#include <stdio.h>


struct complex {
    int x;
    int y;
};
struct complex SumComp(struct complex c1,struct complex c2) {
    double x = c1.x+c2.x;
    double y = c1.y+c2.y;
    struct complex c;
    c.x = x;
    c.y = y;
    return c;
}
struct complex SubComp(struct complex c1,struct complex c2) {
    double x = c1.x-c2.x;
    double y = c1.y-c2.y;
    struct complex c;
    c.x = x;
    c.y = y;
    return c;
}
struct complex MulComp(struct complex c1,struct complex c2){
    double x = c1.x * c2.y - c1.x * c2.y;
    double y = c1.y * c2.x + c1.y * c2.y;
    struct complex c;
    c.x = x;
    c.y = y;
    return c;
}
