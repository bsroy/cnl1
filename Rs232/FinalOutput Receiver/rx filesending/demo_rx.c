
/**************************************************

file: demo_rx.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_rx.c rs232.c -Wall -Wextra -o2 -o test_rx

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"



int main()
{
  int i, n,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600;       /* 9600 baud */

  unsigned char buf[10000];

  char mode[]={'8','N','1',0};


  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
 
  }
 

 while(1)
 {
   n = RS232_PollComport(cport_nr, buf, 10000);

    if(n > 0)
    {
      buf[n] = 0;   

      for(i=0; i < n; i++)
      {
        if(buf[i] < 32)  
        {
          buf[i] = '.';
        }
      }

      printf("received %i bytes: %s\n", n, (char *)buf);
      
     
FILE *f;
f=fopen("input.txt","a");
  
 
  fprintf(f,buf);
fclose(f);

    }

    usleep(100000); 
 }

  return(0);
}

