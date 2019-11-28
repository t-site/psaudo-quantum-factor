#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<gmp.h>

#define THRESH 8192
#define TIMEOUT 512

gmp_randstate_t randomfp;

void qf2( mpz_t x  )
{
	mpz_t diff , out , cx ,s,ff,tmp,r,sr,two,zero,xhalf;
	mpz_init_set_ui(diff,2);
	mpz_init_set(out,x);
	mpz_init_set_ui(cx,1);
	mpz_init_set_ui(s,2);
	mpz_init_set_ui(two,2);
	mpz_init_set_ui(zero,0);
	mpz_init(tmp);
	int i;
	int facflag=1;
	int times=0;
	int ml=0;
	for( i = 2 ; i < THRESH ; i++ )
	{
		while( mpz_tdiv_r_ui(tmp ,out , i ) == 0 )
		{
			printf("%d ",i);
			mpz_tdiv_q_ui(out,out,i);
			mpz_mul_ui(cx,cx,i);
		}
	}
	mpz_set_ui(diff,THRESH);
	mpz_init_set_ui(ff,THRESH);
	mpz_init(r);
	mpz_init(sr);
	mpz_init(xhalf);
	mpz_tdiv_q(xhalf,x,two);
	while( mpz_cmp(x,cx) != 0 )
	{
		mpz_urandomm(r,randomfp,diff);
		mpz_tdiv_q(xhalf,diff,two);
		mpz_sub(r,r,xhalf);
		mpz_tdiv_r(sr,r,diff);
		mpz_add(s,s,sr);
		if( mpz_cmp(s,two) < 0 )
			mpz_set(s,two);
		else if( mpz_cmp(out,s) < 0 )
		{
			mpz_set( s,out);
			ml=0;
		}
		
		mpz_tdiv_r(diff,out,s);
		facflag=mpz_cmp(diff,zero);
		while( facflag == 0 )
		{
			mpz_out_str(stdout,10,s);
			puts("");
			mpz_tdiv_q(out,out,s);
			mpz_mul(cx,cx,s);
			mpz_tdiv_r(diff,out,s);
			facflag=mpz_cmp(diff,zero);
			mpz_tdiv_q(ff,s,two);
			times=0;
			ml=0;
		}
		mpz_sub(tmp,s,diff);
		if ( mpz_cmp(tmp,diff) < 0 )
			mpz_set(diff,tmp);
		if ( mpz_cmp_ui(diff,THRESH ) < 0 )
			mpz_set_ui(diff,THRESH);
		if( times < TIMEOUT )
			times++;
		else
		{
			ml++;
			mpz_add_ui(diff,diff,ml*ml);
			times=0;
		}

	}
}


int main( int argc , char **argv)
{
	mpz_t base;
	gmp_randinit_mt(randomfp);
	if( argc != 2 )
		return 3;
	if ( mpz_init_set_str(base , argv[1] , 10) != 0 )
		return 1;
	if( mpz_cmp_ui( base,0) < 0 )
		return 2;
	qf2(base);
	return 0;
}
