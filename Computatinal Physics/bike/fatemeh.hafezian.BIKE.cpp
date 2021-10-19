// Numerical calculation of radioactive alpha decay using the Euler method
// Nicholas Giordano's C code
// adapted for C++ by Bahman Farnudi on  2003

#include <iostream>
#include<cstdlib>
#include <fstream>
#define Max 100

using namespace std;

//@@@@@@@@@@@@@@ Global variables @@@@@@@@@@@@@@
double v[Max];  // Declare n_uranium[] to track the number of the nuclei
double p;
double m;
double t[Max];          // store time value here
double dt;              // time step
int n; //= Max;            // number of steps
double tau = 1.0;       // decay time constant
double N0 = Max;
double tyme ;      // total time

int main()
{


    cout << "Type the mass (m) and then press <Enter/Return>" << "\n\n";
    cin >> m;
      cout << '\n';
	


    cout << "Type the time (tyme) and then press <Enter/Return>" << "\n\n";
    cin >> tyme;
      cout << '\n';
	

dt=tyme/Max;
  cout << "Type the power (p) and then press <Enter/Return>" << "\n\n";
    cin >> p;
      cout << '\n';


  cout << "Type the initial velocity (v0) and then press <Enter/Return>" << "\n\n";
    cin >> v[0];
      cout << '\n';


    t[0] = 0.0;
    n = min(int(tyme/dt),Max);     //To prevent memory overflow
    int i; //, n;
    for(i = 0; i<= n-1; i++)
    {
        v[i+1] = v[i] + (p/(m*v[i]))*dt;
        t[i+1] = t[i] + dt;
    }
    ofstream fout;      // Declare 'fout' to be an object of ofstream class
      fout.open ("bike_v1.dat");  // Access the member 'open' of object 'fout'
                                   // that opens the file 'decay_v1.dat'
      fout << '\n';                // Write to the file 'decay_v1.dat'
    
    for(i = 0; i < n; i++)
    {
        cout << t[i] << '\t' << v[i] << endl; //Prints to display
        fout << t[i] << '\t' << v[i] << endl; //Prints to file
    }
    cout << endl;
    fout << endl;
    
    fout.close();              // Close file 'decay_v1.dat'
    


 ofstream temp("temp.txt", ios::out | ios::trunc);
    temp << "set ylabel \"y\"\n"
         << "set xlabel \"x\"\n"
	<<"set terminal png\n"
	<<"set output\"temp.png\""<<endl;  
        


    temp << "plot '-' using 2:1 title \"My Plot\" with lp" << endl;
    
    for( i=0; i<n; i++)
        temp <<v[i] << '\t' << t[i] << endl;
    
    temp << "EOF\n"
         << "pause -1 \"Hit any key to continue\"" << endl;

    temp.close();

    system("gnuplot temp.txt");   // Execute gnuplot software in main OS
    
    cout << "Finish" << endl;

    return 0;
}

