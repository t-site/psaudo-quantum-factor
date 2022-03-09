#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define THRESH 8192

FILE *randomfp;

void qf2( long long x  )
{
	long long diff=2;
	long long out=x;
	long long cx=1;
	long long s=2;
	int i;
	for( i = 2 ; i < THRESH ; i++ )
	{
		while( out % i == 0 )
		{
			printf("%d ",i);
			out /= i;
			cx *= i;
		}
	}
	diff = THRESH;
	while( x != cx )
	{
		long long r;
		long long up,down;
		long long i;
		fread(&r , sizeof(long long) , 1 , randomfp);
		s +=( r %  diff );
		if( s < THRESH )
			s = THRESH;
		up = out % s;
		down = out % s;
		for ( i = up ; i >= 2 && i <= out ; i++ )
		{
			int t = out % i;
			if ( t >= up )
			{
				break;
			}else
			{
				up = t;
			}
			while( out % i == 0 )
			{
				printf("%lld ",i);
				out /= i;
				cx *= i;
				s = i;
				diff = THRESH;
			}
		}
		diff += (i - up ) * 3;
		for ( i = down ; i >= THRESH ; i-- )
		{
			int t = out % i;
			if ( t >= down )
			{
				break;
			}else
			{
				down = t;
			}
			while( out % i == 0 )
			{
				printf("%lld ",i);
				out /= i;
				cx *= i;
				s = i;
				diff = THRESH;
			}
		}
		diff += ( i - down ) * 3;
		if ( diff < THRESH )
			diff = THRESH;

	}
}


int main( int argc , char **argv)
{
	long long base;
	randomfp=fopen("/dev/urandom","rb");
	if( argc != 2 )
		return 3;
	base = strtoll(argv[1],NULL,0);
	if( base < 0 )
		return 2;
	qf2(base);
	fclose(randomfp);
	return 0;
}
