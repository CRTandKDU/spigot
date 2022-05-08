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

/* Ancillaries */
void printrow( int *arr, int len ){
  int i;
  for( i=0; i<len; i++ ) printf("%3d ", arr[i]);
  printf("\n");
}

/* Reverse Iterators */
static int g_num;
int num_init(int last);    /* returns init element in numerators */
int num_done(int val);     /* returns 1 if val is past end */
int num_next(int val);     /* returns next value after val */

static int g_den;
int den_init(int last);    /* returns init element in denominators */
int den_done(int val);     /* returns 1 if val is past end */
int den_next(int val);     /* returns next value after val */

/* int num_init( int last ){ return last; } */
/* int num_done( int val ) { return val <= 0; } */
/* int num_next( int val ) { return val - 1; } */

/* int den_init( int last ){ return last; } */
/* int den_done( int val ) { return val <= 0; } */
/* int den_next( int val ) { return val - 2; } */

int num_core(int n ){
  switch(n){
  case 1: return 1;
    break;
  case 2: return 1;
    break;
  case 3: return 2;
    break;
  case 4: return 15;
    break;
  }
  return (2*n+1)*(n+1);
}
int num_init( int last ){ g_num = last; return num_core(g_num); }
int num_done( int val ) { return g_num <= 0; }
int num_next( int val ) { g_num -= 1; return g_num < 0 ? 0 : num_core(g_num); }

int den_core(int n ){
  switch(n){
  case 1: return 28;
    break;
  case 2: return 22;
    break;
  case 3: return 39;
    break;
  case 4: return 272;
    break;
  }
  return 3*(3*n+4)*(3*n+5);
}
int den_init( int last ){ g_den = last; return den_core( g_num ); }
int den_done( int val ) { return g_den <= 0; }
int den_next( int val ) { g_den -= 1; return g_den < 0 ? 1 : den_core( g_num ); }

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
  int i, j, q;
  int nines, pre;
  int num, den;
  int bprint = 1;

  /* int len = (10*n / 3) + 2; */
  /* int a[len]; */
  /* a[0] = 0; */
  /* for( i=1; i<len; i++ ) a[i] = 2; */

  int len = n+1;
  int a[len];

  a[0] = 0;
  for( i=1; i<len; i++ ) a[i] = 5*i-2;

  /* a[0] = 0; */
  /* a[1] = 3; */
  /* a[2] = 8; */
  /* a[3] = 13; */
  /* a[4] = 18; */
  /* a[5] = 0; */

  nines = pre = 0;

  /* Iterations */
  for( j = 0; j < n; j++ ){
    /* printrow( a, len ); */
    /* num = num_init( len - 1 ); */
    /* den = den_init( 2*len - 1 ); */
    num = num_init( len-2 );
    den = den_init( len-2 );
    a[len-1] *= 10;
    if( a[len-1] > top ) top = a[len-1];

    for( i=len-1; i>0; i-- ){
      num = num_next( num );
      den = den_next( den );
      /* printf( "\t<%2d> %3d %3d %3d (top=%3d pre=%3d)\n", i, num, den, a[i], top, pre ); */
      q		= a[i] / den;
      a[i-1]	= 10*a[i-1] + q*num;
      a[i]	= a[i] % den;
      if( a[i-1] > top ) top = a[i-1];
    }
    a[1]	= q % 10;
    q		= q / 10;

    if( 9 == q ){ nines += 1; }
    else if( 10 == q ){
      a[0] = pre + 1;
      if( bprint) printf( "%1d", a[0] );
      if( bprint ) for( i=0; i<nines; i++ ) printf( "%1d", 0 );
      nines = pre = 0;
    }
    else{
      a[0] = pre;
      if( bprint ) printf( "%1d", a[0] );
      if( bprint ) for( i=0; i<nines; i++ ) printf( "%1d", 9 );
      pre = q;
      nines = 0;
    }

  }
  
  /* printrow( a, len ); */
  printf("\n");
  printf("For len = %3d - Top integer: %6d\n", len, top );
  return 0;
}
