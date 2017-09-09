#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <cmath>

class Pixel
{

  int x;
  int y;
  double red;
  double green;
  double blue;
  double alpha;

public:

  Pixel(int X_coord, int Y_coord, int R_comp,
        int G_comp, int B_comp, int A_comp):
        x(X_coord), y(Y_coord), red(R_comp),
        green(G_comp), blue(B_comp), alpha(A_comp) {}

  int get_X() {return x;}
  int get_Y() {return y;}
  double get_R() {return red;}
  double get_G() {return green;}
  double get_B() {return blue;}
  double get_A() {return alpha;}

  void set_X(int new_x) {x = new_x;}
  void set_Y(int new_y) {y = new_y;}
  void set_RGBA(double new_r, double new_g, double new_b, double new_a)
  {

    red = new_r;
    green = new_g;
    blue = new_b;
    alpha = new_a;

  }

};

class Distances
{

  double hypotenuse;
  int r_distance;
  int g_distance;
  int b_distance;
  int a_distance;

public:

  int get_Hypo(){return hypotenuse;}
  int get_RDist(){return r_distance;}
  int get_GDist(){return g_distance;}
  int get_BDist(){return b_distance;}
  int get_ADist(){return a_distance;}

  void setDistances(Pixel, Pixel);

};

void Distances::setDistances(Pixel start, Pixel end)
{

  int dx = abs(end.get_X() - start.get_X());
  int dy = abs(end.get_Y() - start.get_Y());

  double hypo = sqrt(dx*dx + dy*dy); // hypotenuse

  int r_dist = end.get_R() - start.get_R();
  int g_dist = end.get_G() - start.get_G();
  int b_dist = end.get_B() - start.get_B();
  int a_dist = end.get_A() - start.get_A();

  hypotenuse = hypo;
  r_distance = r_dist;
  g_distance = g_dist;
  b_distance = b_dist;
  a_distance = a_dist;

}

void Interpolate(Pixel *p, Distances dist)
{

  double hypo = dist.get_Hypo();
  double new_red = p->get_R() + (dist.get_RDist()/hypo);
  double new_green = p->get_G() + (dist.get_GDist()/hypo);
  double new_blue = p->get_B() + (dist.get_BDist()/hypo);
  double new_alpha = p->get_A() + (dist.get_ADist()/hypo);

  p->set_RGBA(new_red, new_green, new_blue, new_alpha);

}

void PutPixel(Pixel *pxl)
{

  if(pxl->get_X()>IMAGE_WIDTH || pxl->get_X()<0 || pxl->get_Y()>IMAGE_HEIGHT || pxl->get_Y()<0) // exceeded limits
    return;

  else
  {

    int index = pxl->get_X()*4 + pxl->get_Y()*4*IMAGE_WIDTH;  // coordinates
    FBptr[index + 0] = pxl->get_R();  // red
    FBptr[index + 1] = pxl->get_G();  // green
    FBptr[index + 2] = pxl->get_B();  // blue
    FBptr[index + 3] = pxl->get_A();  // alpha

  }

}

void DrawLine(Pixel pxl_initial, Pixel pxl_final)
{

  std::cout<<"DrawLine Called"<<std::endl;
  int x = pxl_initial.get_X();
  int y = pxl_initial.get_Y();
  int xf = pxl_final.get_X();
  int yf = pxl_final.get_Y();
  int dx = abs(xf - x);      // delta x
  int dy = abs(yf - y);      // delta y
  int d = 0;                 // decision variable
  int inc_x = 0;             // direction on x
  int inc_y = 0;             // direction on y
  int incr1 = 0;
  int incr2 = 0;
  Distances all_distances;
  all_distances.setDistances(pxl_initial, pxl_final);


  (xf > x) ? (inc_x = 1) : (inc_x = -1);  // if true then x increases, else decreases
  (yf > y) ? (inc_y = 1) : (inc_y = -1);  // if true then y increases, else decreases

  Pixel *pix = new Pixel(x, y, pxl_initial.get_R(), pxl_initial.get_G(), pxl_initial.get_B(), pxl_initial.get_A());
  PutPixel(pix);  // First pixel
  
  if(dx == 0) // Line above axis y
  {

    if(inc_y > 0) // positive axis y
    {

      while(y != yf)
      {

        pix->set_Y(++y);
        Interpolate(pix, all_distances);
        PutPixel(pix);

      }

    }
    else  // negative axis y
    {

      while(y != yf)
      {

        pix->set_Y(--y);
        Interpolate(pix, all_distances);
        PutPixel(pix);

      }

    }

  }
  else if(dy == 0)
  {

    if(inc_x > 0) // positive axis x
    {

      while(x != xf)
      {

        pix->set_X(++x);
        Interpolate(pix, all_distances);
        PutPixel(pix);

      }

    }
    else  // negative axis x
    {

      while(y != yf)
      {

        pix->set_X(--x);
        Interpolate(pix, all_distances);
        PutPixel(pix);

      }

    }

  }
  else
  {

    if(dx >= dy)
    {

      d = 2*dy - dx;
      incr1 = 2 * dy;
      incr2 = 2 * (dy - dx);

      while(x != xf)
      {

        if (d <= 0)
        {

          d += incr1;
          x += inc_x;

        }
        else
        {

          d += incr2;
          x += inc_x;
          y += inc_y;

        }

        pix->set_X(x);
        pix->set_Y(y);
        Interpolate(pix, all_distances);
        PutPixel(pix);
      }

    }
    else
    {
      d = 2 * dx - dy;
      incr1 = 2 * dx;
      incr2 = 2 * (dx - dy);

      std::cout<<"X: "<<x<<std::endl;
      std::cout<<"Y: "<<y<<std::endl;

      while(y != yf)
      {

        if (d <= 0)
        {

          d += incr1;
          y += inc_y;

        }
        else
        {

          d += incr2;
          y += inc_y;
          x += inc_x;

        }

        pix->set_Y(y);
        pix->set_X(x);
        Interpolate(pix, all_distances);
        PutPixel(pix);
      }

    }

  }

}

void DrawTriangle(Pixel p1, Pixel p2, Pixel p3)
{

  DrawLine(p1, p2);
  DrawLine(p2, p3);
  DrawLine(p3, p1);

}
#endif // _MYGL_H_
