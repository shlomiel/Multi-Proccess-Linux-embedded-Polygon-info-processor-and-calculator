#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <signal.h>

// *****   declarations of types and constants   *****

typedef long long unsigned int lluint;

#define MAX_VERT   8 // maximum number of vertices (8 is for octagon)
#define QUAD_IN   "quad_in.tmp"
#define HEX_IN    "hex_in.tmp"
#define OCT_IN    "oct_in.tmp"
#define ALL_OUT   "all_out.tmp"
#define CHARS_IN  "chars_in.txt"
#define HELPER    "ex2_q1_helper"
#define NANO_SLEEP 300 * 1000 * 1000 // 0.3 second


enum POLY_TYPE {QUADRI = 4, PENTAGON, HEXAGON = 6, 
                OCTAGON = 8, BAD_POLY};
enum WHOM_TO_OUTPUT {CURRENT, ALL_POLY, NONE};

struct point {
   int x, y;
};

struct polygon {
     enum POLY_TYPE poly_type;
     struct point vertices[MAX_VERT];
}; 

struct Node {
    struct polygon* poly;
    struct Node* next;
};

// *****   declarations of function prototypes   *****
void my_exception(int line, const char* function, char* msg);
// the following are not needed for this exercise. Left over from ex1_q1
// double calc_side(struct point pt1, struct point pt2);
// double calc_triangle_area(struct point p1, struct point p2, struct point p3);
void print_point(struct point pt);
void print_polygon_name(enum POLY_TYPE poly, char* poly_name);
void print_helper_end_msg(int created, int printed, enum POLY_TYPE poly);



