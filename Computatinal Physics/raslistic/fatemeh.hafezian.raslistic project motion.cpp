//ver 0.1
//code : implemented in GNU c++ copiler
//os : linux ubuntu
// adapted for C++ by fateme hafezian on 1396

#include <iostream>
#include<cstdlib>
#include <fstream>
#define n 1000

using namespace std;

//                                         @@@@@@@@@@@@@@ Global variables @@@@@@@@@@@@@@




double vy[n];  // declar vy[] to track the velocity

double vx[n];    // declar vx[] to track the velocity
 
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

	
   	     x[i+1] = x[i] + (vx[i])*dt;
   	     vx[i+1]=vx[i];
		y[i+1]=y[i] + vy[i]*dt; 
		vy[i+1]=vy[i] - g*dt;
	
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
    


		 ofstream temp1("temp1.txt", ios::out | ios::trunc);
  	  temp1 << "set ylabel \"y\"\n"
        	 << "set xlabel \"x\"\n"
		<<"set terminal png\n"
		<<"set output\"temp1.png\""<<endl 
        	 << "set autoscale y" "\n"  						
  			 << "set autoscale x""\n"  ; 
        
        


    temp1 << "plot '-' using 2:1 title \"My Plot\" with lp" << endl;
    
    for( int j=0; j<n-1; j++)
        temp1 <<y[j] << '\t' << x[j] << endl;
    
    temp1 << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;

    temp1.close();

    system("gnuplot temp1.txt");   // Execute gnuplot software in main OS
    
    cout << "Finish" << endl;

    return 0;
}

