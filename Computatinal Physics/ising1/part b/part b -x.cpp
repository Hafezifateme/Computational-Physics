/******************************************************************************/
/*** Ver 0.11                                                                ***/
/*** Date: 13960308                                                         ***/
/*** This code implemented in GNU C++ compiler (v. 4.6.3),                  ***/
/*** OS: Linux 3.16.7-21-desktop (x86_64)                                   ***/
/*** Run under a Intel® Core™ i3-2330M CPU @ 2.20GHz × 4 machine with 4 GB  ***/
/*** RAM.                                                                   ***/
/******************************************************************************/

// You can compile this code by following command in shell:
// > g++ -o Ising.out Ising.cpp -Ofast
// , then execute it in shell by
// > ./Ising.out

/* This is a sample code. It is not complete and it may contain some errors. 
 * So you can try it with your own risk! */

/* Random number generator in the following code is based on the random number generator function

   double ran2(long *idum);
   
implemented in the Numerical recipes in C, chapter 7 (ran2)

Long period (> 2 × 10^{18}) random number generator of L. Ecuyer with Bays-Durham shuffle
and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of
the endpoint values). 

***!!! Call with idum a negative integer to initialize; !!!*** thereafter, do not alter
idum between successive deviates in a sequence. RNMX should approximate the largest floating
value that is less than 1.

Visit www.nr.com for the licence.*/

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>

using namespace std;

//BEGIN_FOLD - Random number generator section
//------------------------------------------------------------------------------

/* following routine based on Random number generator

   double ran2(long *idum);
   
implemented in the Numerical recipes in C, chapter 7 (ran2)

Long period (> 2 × 10^{18}) random number generator of L. Ecuyer with Bays-Durham shuffle
and added safeguards. Returns a uniform random deviate between 0.0 and 1.0 (exclusive of
the endpoint values). 

***!!! Call with idum a negative integer to initialize; !!!*** thereafter, do not alter
idum between successive deviates in a sequence. RNMX should approximate the largest floating
value that is less than 1.

Visit www.nr.com for the licence.*/

// This is a internal, 32 bit random number generator with uniform Distribution in range [0..1)
/* note #undef's at end of file */
#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran2(long *idum) {
    int j;
    long k;
    static long idum2=123456789;
    static long iy=0;
    static long iv[NTAB];
    double temp;

    if (*idum <= 0) {
        if (-(*idum) < 1) *idum=1;
        else *idum = -(*idum);
        idum2=(*idum);
        for (j=NTAB+7;j>=0;j--) {
            k=(*idum)/IQ1;
            *idum=IA1*(*idum-k*IQ1)-k*IR1;
            if (*idum < 0) *idum += IM1;
            if (j < NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }
    k=(*idum)/IQ1;
    *idum=IA1*(*idum-k*IQ1)-k*IR1;
    if (*idum < 0) *idum += IM1;
    k=idum2/IQ2;
    idum2=IA2*(idum2-k*IQ2)-k*IR2;
    if (idum2 < 0) idum2 += IM2;
    j=iy/NDIV;
    iy=iv[j]-idum2;
    iv[j] = *idum;
    if (iy < 1) iy += IMM1;
    if ((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

//------------------------------------------------------------------------------

// My interface 

// Random number generator seed
long iseed = -36;

// You can initializing random number generator seed by usin following routine
void Randomize() {
  iseed = -time(NULL);  
}

// return random number with uniform distribution in range [0..1).
inline double Random() { return ran2(&iseed); }

// return integer random number with uniform distribution in range 0 to N.
inline int Random(int N) { return int(ran2(&iseed)*N); }
//END_FOLD

const int L = 256;                // Lattice size; L = 2^n
const int LMask = L - 1;          // Mask used to perfom periodic boundary condition in a Perid() function
int** s;
int *M;
double *deltaM;
double *x;
int G;
int G2;
const int step=100;                          // Spins lattice; s[i][j] shows spin of cellm (i,j)
// All the following parameters are in the reduced unit system
double h = 0.0;                    // external field
double J = +1;                     // spin-spin coupling constant
int T = 50.0;                    // Tempreture
ofstream snapshot("snapshot.txt", // Keeps model snapshot
                  ios::out | ios::trunc);  


void Init();
void InitdeltaM2();
void Initx();
void InitM();                      // Initialize model, alocate dynamic memory, ...
void Execute();                   // Simulate Ising model
void PostProcess();               // Perform post statistical analysis
void DonedeltaM2();
void Donex();
void DoneM();
void Done();                      // Dealocate dynamic memory, ...

// Initialize model, alocate dynamic memory, ...
void Init() {
    cout << "Init ..." << endl;
    Randomize();
    s = new int*[L];
    for (int i = 0; i<L; i++) {
      s[i] = new int[L];
      for (int j = 0; j<L; j++)
        s[i][j] = 1;
    }
    
    snapshot << L << endl;
}

// Dealocate dynamic memory, ...
void Done() {
    cout << "Done ..." << endl;

    snapshot.close();

    for (int i = 0; i<L; i++)
      delete[] s[i];
    delete[] s;
}





// Initialize model, alocate dynamic memory, ...
void InitdeltaM() {
       deltaM = new double[T];
   
      for (int j = 0; j<T; j++)
        deltaM[j]=0.0;
    
    
    }

// Dealocate dynamic memory, ...
void DonedeltaM() {
    
    

       delete[] deltaM;
}





// Initialize model, alocate dynamic memory, ...
void Initx() {
       x = new double[T];
   
      for (int j = 0; j<T; j++)
        x[j]=0.0;
    
    
    }

// Dealocate dynamic memory, ...
void Donex() {
    
    

       delete[] x;
}


void InitM() {
       M = new int[L];
   
      for (int j = 0; j<L; j++)
        M[j]=0.0;
    
    
    }

// Dealocate dynamic memory, ...
void DoneM() {
    
    

       delete[] M;
}


// Export single snapshot to snapshot.txt
void Export_Single_Snapshot() {
    for (int i = 0; i<L; i++)
      for (int j = 0; j<L; j++)
          if ( s[i][j] > 0 )  
              snapshot << "1" << endl;
          else
              snapshot << "0" << endl;
}

// Rotate i if cross the boundary vs the periodic boundary condition
inline int Period(int i) {
    return i & LMask;
    // or equivalently use: return (i+L) % L;
}

// Calculate Delta E if s(i,j) flipped
double Delta_E_Flip(int i, int j) {
    double sum = 0.0;
    sum = s[i][Period(j+1)] + s[i][Period(j-1)] + s[Period(i-1)][j] + s[Period(i+1)][j];
    return 2*s[i][j]* (h + J * sum);
}

// Perfom single Monte Carlo step
void Single_Monte_Carlo_Step(double t) {
    for (int c = 0; c < L*L; c++) { // L^2 infinitesimate step
        int i = Random(L);        // Select random row between [0..L-1]
        int j = Random(L);        // Select random column between [0..L-1]
        double dE = Delta_E_Flip(i, j);
        if ( dE < 0 ) {           // If the total energy decreases after spin-flip, accept the infinitesimal step
            s[i][j] = -s[i][j];
        } else if ( Random() < exp(-dE/t) ) {
            s[i][j] = -s[i][j];
        }
    }
    
    // Export_Single_Snapshot();  // Activate this line if you want the snapshot.txt file is being generated during run
}

// Simulate Ising model
void Execute(double t) {


for (int b=0; b<step ; b++)
{

Single_Monte_Carlo_Step(t);

		for(int i=0; i<L ; i++)
		{
			for(int j=0; j<L; j++)
			{

			M[b]+= s[i][j];


			}



	


		}

}

	





}

// Perform post statistical analysis
void PostProcess() {
   ofstream temp("temp.txt", ios::out | ios::trunc);
    temp << "set ylabel \"X(magnet)\"\n"
         << "set xlabel \"t(time)\"\n"
	<<"set terminal png\n"
	<<"set output\"temp.png\""<<endl
<< "set autoscale y" "\n"  ;




 temp << "plot '-' using 2:1 title \"My Plot\" with lp" << endl;
    
    for( int b=0; b<T; b++)
        temp << x[b] << '\t' << b*(1.0/5) << endl;
    
    temp << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;

    temp.close();

    system("gnuplot temp.txt");   // Execute gnuplot software in main OS 
}

// Main routine
int main (int argc, char *argv[]) {
     

InitdeltaM();

Initx();


for(int m=0; m<T ; m++){
Init();
double t = m*(1.0/5);
InitM();
G=0.0;

    Execute(t);

	for(int b=10; b<step; b++)

	{
		G+=M[b];
	

	}


	 
deltaM[m]=((G*1.0)/((step-10)*(L*L)));
x[m]= (1-(deltaM[m]*deltaM[m]))/t;
Done();
DoneM();
}




    PostProcess();
    
DonedeltaM();   
Donex();

    cout << "Finish" << endl;
    
    return 0;
}
