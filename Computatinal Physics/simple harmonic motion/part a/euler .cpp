// Numerical calculation of physical pendulum model using the Euler method
// adapted for C++ by Fateme Hafezian on 1396

#include <iostream>
#include<cstdlib>
#include <fstream>
#include <math.h>
//#define Max 100

using namespace std;

//@@@@@@@@@@@@@@ Global variables @@@@@@@@@@@@@@
double *w; 			// Declare angular velocity of pendulum
double *teta;			// declare angle of pendulum
double *E;			// declare total energy
double A=9.8;                   // declare constant A=g/l   g=l=9.8   (l= lenght)
double m=1.0; 			// declare mass of pendulum
double l=1.0;			// declare lenght
double *t;		        // store time value here
double dt= 0.04;                // time step
double tyme= 10;                 // total time
int n;				// =tyme/dt   number of step

int main()
{

n=int (tyme/dt);
t= new double[n];
teta=new double[n];
w=new double[n];
E= new double[n];


for(int i=0; i<n; i++){

t[i]=0.0;
teta[i]=0.0;
w[i]=0.0;
E[i]=0.0;
}



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@initial value  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



  teta[0]=0.2;
  E[0]=0.196;




//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

    
    for(int i = 0; i< n-1; i++)
    {
        w[i+1] = w[i] -A*teta[i]*dt;
	teta[i+1]=teta[i]+w[i]*dt;
	t[i+1] = t[i] + dt;
	E[i+1]=0.5*m*l*l*(w[i+1]*w[i+1]+A*teta[i+1]*teta[i+1]);
        
    }





    
    
   //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$   plot   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ 


 ofstream temp("euler-cromer-method.txt", ios::out | ios::trunc);
    temp << "set ylabel \"E(j)\"\n"
         << "set xlabel \"time(s)\"\n"
	<<"set terminal png\n"
	<<"set output\"euler-cromer-method.png\""<<endl
 << "set autoscale y" "\n"  	;  
        


    temp << "plot '-' using 2:1 title \"My Plot\" with lp" << endl;
    
    for( int i=0; i<n; i++)
        temp <<E[i] << '\t' << t[i] << endl;
    
    temp << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;

    temp.close();

    system("gnuplot euler-cromer-method.txt");  	 // Execute gnuplot software in main OS
    
    cout << "Finish" << endl;

    return 0;
}

