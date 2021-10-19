
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <ctime>

using namespace std;


const long int   a1=0x5DEECE66D;
const  int       b1=0xB;
const  int       a2=0x8088405;
const  int       b2=1;


float buf[256];
long int seed1=-35;
long int seed2;


long int LCG1(long int );
long int LCG2(long int ); 
void Randomize();
double myrandom();


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  LCG 1  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

		long int LCG1(long int r)
			

			{                       
		        return ((a1*r+b1) & (((1ULL)<<48)-1));
			}





//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   LCG2  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 


		long int LCG2(long int r)


			{                         
			return ((a2*r+b2) & (((1ULL)<<32)-1));
			}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  Randomize@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		void  Randomize()

			{
			seed1=-time(NULL); 

                       

                	for(int i=0; i<256; i++)
				{
				

					seed1=LCG1(seed1);
        	        		buf[i]=seed1;



    		                 }



			seed1=LCG1(seed1);
	        	seed2=seed1;
			}







//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ myrandom@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		double myrandom()

			{
				seed2=LCG2(seed2);
				float x=(1.0 *seed2)/(((1ULL)<<32));
				 int i=(int)(x*256); 
				float temp=buf[i];
				seed1=LCG1(seed1);
				buf[i]=seed1;	
				return (temp)/(((1ULL)<<48));
			}

		



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   main   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		int main()

			{
	
				int N_rand;
				cout<<"Type the numder of randoms num (N_rand) and then press <Enter/Return>"<<endl;
				cin>>N_rand;

				Randomize();
	
				for(int i=0; i<N_rand ;i++)
					cout<<myrandom()<<endl;

			}








	
	


	

