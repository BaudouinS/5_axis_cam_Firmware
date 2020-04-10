/*
  Motion - 
  Created by B Saintyves, April 4, 2020.
*/

#ifndef Motion_h
#define Motion_h


class fclass
{
  public:
    fclass();
    void Cartesian(int & VX, int & VY, int & VZ, int & VP, int & VT, float V,int r,float LX, float LY, float LZ, float RX,float RY);
    void Spherical(long int X, long int Y, long int Z, int & VX, int & VY, int & VZ, int & VP, int & VT, float V,int r, int R, float LX, float LY, float LZ, float RX, float RY);
  };

  extern fclass Motion;

#endif
