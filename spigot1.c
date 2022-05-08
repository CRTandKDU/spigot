/* Spigot Algorithm for \Pi */
/* See also: [[https://www.maa.org/sites/default/files/pdf/pubs/amm_supplements/Monthly_Reference_12.pdf]] */
/* See also: [[http://www.pi314.net/eng/goutte.php]] */

/* Questions: */
/* - What is the highest integer reached in the iterations? */
/* - How does the length of the initial array depend on the number of decimals? */

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
  int n		= 100;
  int top       = 0;
  int c;
  /* Parse command line */
  while ((c = getopt (argc, argv, "n:")) != -1){
    switch(c){
    case 'n':
      /* Use -n to specify the number of decimals to print, default = 33 */
      n = atoi(optarg);
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
  int len = (10*n / 3) + 2;
  int a[len];
  int i, j, q;
  int nines, pre;

  a[0] = 0;
  for( i=1; i<len; i++ ) a[i] = 2;
  nines = pre = 0;

  /* Iterations */
  for( j = 0; j < n; j++ ){
    a[len-1] *= 10;
    if( a[len-1] > top ) top = a[len-1];
    for( i=len-1; i>0; i-- ){
      q		= a[i] / (2*i - 1);
      a[i-1]	= 10*a[i-1] + q*(i-1);
      a[i]	= a[i] % (2*i - 1);
      if( a[i-1] > top ) top = a[i-1];
    }
    a[1]	= q % 10;
    q		= q / 10;
    /* printrow( a, len ); */
    if( 9 == q ){ nines += 1; }
    else if( 10 == q ){
      a[0] = pre + 1;
      printf( "%1d", a[0] );
      for( i=0; i<nines; i++ ) printf( "%1d", 0 );
      nines = pre = 0;
    }
    else{
      a[0] = pre;
      printf( "%1d", a[0] );
      for( i=0; i<nines; i++ ) printf( "%1d", 9 );
      pre = q;
      nines = 0;
    }

  }
  /* printrow( a, len ); */
  printf("\n");
  printf("Top integer: %6d\n", top );
  return 0;
}
