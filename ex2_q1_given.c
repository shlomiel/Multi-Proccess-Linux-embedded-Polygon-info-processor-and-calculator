#include "ex2_q1_given.h"

//-----------------------------------------------
void my_exception(int line, const char* function, char* msg)
{
			fprintf(stderr, "ERROR (line %d function: %s) !!!%s\n", line, function, msg);
      exit(1);
}

//-----------------------------------------------
void print_point(struct point pt)
{
	printf("{%d, %d} ", pt.x, pt.y);
}

//-----------------------------------------------
void print_polygon_name(enum POLY_TYPE poly, char* poly_name)
{
  switch (poly)
  {
    case QUADRI:  sprintf(poly_name, "quadrilateral"); break;
    case HEXAGON: sprintf(poly_name, "hexagon"); break;
    case OCTAGON: sprintf(poly_name, "octagon"); break;
    default: my_exception(__LINE__, __func__, "bad-polygon_type");
  }
}

//-----------------------------------------------
void print_helper_end_msg(int created, int printed, enum POLY_TYPE poly)
{
  char poly_name[20];
  print_polygon_name(poly, poly_name);
  int pid = getpid();
  fprintf(stdout, "==> process %d created %d %s and printed %d times\n",
          pid, created, poly_name, printed);
  fflush(stdout);
  fprintf(stderr, "==> process %d created %d %s and printed %d times\n",
          pid, created, poly_name, printed);
}

