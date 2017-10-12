
/**************************************************

file: demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

compile with the command: gcc demo_tx.c rs232.c -Wall -Wextra -o2 -o test_tx

**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"


int main()
{
  int i=0,
      cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=9600; /* 9600 baud */
char buffer[10000];
      

  char mode[]={'8','N','1',0},
       str[2][512];

 FILE *f;
     f=fopen("newinput.txt","r");

if (f)
{
  fseek (f, 0, SEEK_END);
  int length=ftell (f);
  fseek (f, 0, SEEK_SET);
    fread (buffer, 1, length, f);
}
  /*strcpy(str[0], "The quick brown fox jumped over the lazy grey dog.\n");

  strcpy(str[1], "Happy serial programming!\n");*/

  if(RS232_OpenComport(cport_nr, bdrate, mode))
  {
    printf("Can not open comport\n");

    return(0);
  }

    RS232_cputs(cport_nr, buffer);

    printf("sent: %s\n", buffer);

    usleep(1000000);  /* sleep for 1 Second */

  return(0);
}

