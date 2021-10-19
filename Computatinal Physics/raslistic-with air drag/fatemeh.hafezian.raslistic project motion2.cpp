//ver 0.1
//code : implemented in GNU c++ copiler
//os : linux ubuntu
// adapted for C++ by fateme hafezian on 1396

#include <iostream>
#include<cstdlib>
#include <fstream>
#include<cmath>
#define n 1000

using namespace std;

//                                         @@@@@@@@@@@@@@ Global variables @@@@@@@@@@@@@@


double v[n];   // declar v[] to track the velocity

double vy[n];  // declar vy[] to track the velocity

double vx[n];    // declar vx[] to track the velocity

double fx[n];   // declar fx[] to track the air drag force

double fy[n];   // declar fy[] to track the air drag force

double B=0.04 ;       // constant  =  B2/m*m
    
double g=9.8;
      
double x[n];          // store x value here

double y[n];          // store y value here

double dt;              // time step

double tyme;



//                           $$$$$$$$$$$$$$$$$$$$$$$$$$  main   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$




int main()
{


   
    cout << "Type the time  (time) and then press <Enter/Return>" << "\n\n";
    cin >> tyme;
      cout << '\n';



	
	

x[0]=0.0;
y[0]= 0.0;

dt= tyme/n;	

 
  cout << "Type the initial velocity (vx0) and then press <Enter/Return>" << "\n\n";
    cin >> vx[0];
      cout << '\n';


  cout << "Type the initial velocity (vy0) and then press <Enter/Return>" << "\n\n";
    cin >> vy[0];
      cout << '\n';

   
    
   
    
	for(int i=0; i<n-1 ; i++)
	{

		v[i]= sqrt((vx[i]*vx[i])+(vy[i]*vy[i]));




 	     x[i+1] = x[i] + (vx[i])*dt;

		fx[i]= -B*v[i]*vx[i];

   	     vx[i+1]=vx[i] + fx[i]*dt;




		y[i+1]=y[i] + vy[i]*dt;

		fy[i]= -B*v[i]*vy[i]; 

		vy[i+1]=vy[i] + (-g+fy[i])*dt ;
	
		if (y[i+1]<0)  y[i+1]=0;
    
	}





    ofstream fout;      // Declare 'fout' to be an object of ofstream class
      fout.open ("realistic project motion_v1.dat");  // Access the member 'open' of object 'fout'
                                   
      fout << '\n'; 

              
    
    for(int j = 0; j < n-1; j++)


    {
        cout << x[j] << '\t' << vx[j] <<'\t'<<y[j]<<'\t'<<vy[j]<< endl; //Prints to display
        fout << x[j] << '\t' << vx[j] <<'\t'<<y[j]<<'\t'<<vy[j]<< endl; //Prints to file
    }



    cout << endl;
    fout << endl;
    
    fout.close();              // Close file realistic project motion_v1.dat
    


		 ofstream temp2("temp2.txt", ios::out | ios::trunc);
  	  temp2 << "set ylabel \"y\"\n"
        	 << "set xlabel \"x\"\n"
		<<"set terminal png\n"
		<<"set output\"temp2.png\""<<endl 
        	 << "set autoscale y" "\n"  						
  			 << "set autoscale x""\n"  ; 
        
        


    temp2 << "plot '-' using 2:1 title \"My Plot\" with lp" << endl;
    
    for( int j=0; j<n-1; j++)
        temp2 <<y[j] << '\t' << x[j] << endl;
    
    temp2 << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;

    temp2.close();

    system("gnuplot temp2.txt");   // Execute gnuplot software in main OS
    
    cout << "Finish" << endl;

    return 0;
}

