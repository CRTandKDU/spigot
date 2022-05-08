/* Spigot Algorithm for \Pi */
/* See also: [[https://www.maa.org/sites/default/files/pdf/pubs/amm_supplements/Monthly_Reference_12.pdf]] */
/* See also: [[http://www.pi314.net/eng/goutte.php]] */

/* Missing handling of 9/10 quotients! See also: `spigot1.c' */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

void printrow( int *arr, int len ){
  int i;
  for( i=0; i<len; i++ ) printf("%3d ", arr[i]);
  printf("\n");
}

int main( int argc, char **argv ){
  const int K	= 3;
  int n		= 100;
  int c;
  /* Parse command line */
  while ((c = getopt (argc, argv, "n:")) != -1){
    switch(c){
    case 'n':
      /* Use -n to specify the number of decimals to print, default = 33 */
      n = K*atoi(optarg);
      break;
    case '?':
      if (optopt == 'c')
	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint (optopt))
	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
      else
	fprintf (stderr,
		 "Unknown option character `\\x%x'.\n",
		 optopt);
      return 1;
    default:
      abort ();     
    }
  }

  /* Init */
  int len = n+2;
  int a[len], carry[len];
  int i, j, q;

  a[0] = 0;
  for( i=1; i<len; i++ ) a[i] = 2;
  for( i=0; i<len; i++ ) carry[i] = 0;

  /* Iterations */
  for( j = 0; j < n/K; j++ ){
    for( i=len-1; i>0; i-- ){
      a[i] 	       *= 10;
      q			= (a[i] + carry[i]) / (2*i - 1);
      carry[i-1]	= q*(i-1);
      /* printf("\ta[%2d] = %3d; q = %3d; c[%2d] = %3d;", i, a[i], q, i-1, carry[i-1] );  */
      a[i]		= (a[i] + carry[i]) % (2*i - 1);
      /* printf("\ta[%2d] = %3d;\n", i, a[i] ); */
    }
    a[0] = q / 10; a[1] = q % 10;
    printf( "%1d", a[0] );
  }
  /* printrow( carry, len ); */
  /* printrow( a, len ); */
  printf("\n");
  return 0;
}
