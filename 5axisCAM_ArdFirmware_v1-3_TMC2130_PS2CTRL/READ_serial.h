/*
  READ_serial - 
  Created by B Saintyves, April 4, 2020.
*/

#ifndef READ_serial_h
#define READ_serial_h

class fclass3
{
  public:
    fclass3();
    void CreateString(char RXCHAR, char (&RXTEXT)[50], int & RXN);
    void GAMEPAD(char (&RXTEXT)[50], int RXN, int & St_local, int & L3_local, float & LX, float & LY, float & LZ, float & RX,float & RY, int & R3_local, int MAX_SPEED, int MIN_SPEED, float & V, long int & r, long int r_max);
    void SERIAL_MONITOR(char (&RXTEXT)[50], int RXN, int MAX_SPEED, int MIN_SPEED, float & V, int & SWITCH);
  };

  extern fclass3 READ_serial;


#endif
