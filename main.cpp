#include<iostream>
#include<random>
#include<chrono>
#include<fstream>
#include"opt_alg.h"
#include"ode_solver.h"

using namespace std;

int main()
{
	try
	{
		cout << "LAB NUMBER " << LAB_NO << endl;
		cout << "LAB PART " << LAB_PART << endl << endl;

#if LAB_NO == 1

#endif
#if LAB_NO == 2
		double x0 = -10.; //punkt startowy
		double d = 2.;
		double epsilon, gamma, alfa;
		int Nmax = 100;;
		random_device r;

		epsilon = 0.00001;
		gamma = 0.0000001;
		alfa = 3;      //wspolczynnik ekspansji
#if LAB_PART == 1

		ofstream E("..//expansion.csv");
		ofstream F("..//fibonacci.csv");
		ofstream L("..//lagrange.csv");

		double temp_0[100];
		double temp_1[100];

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			x0 = 200.0 * r() / r.max() - 100;
			double* p = expansion(x0, d, alfa, Nmax);
			E << x0 << "," << p[0] << "," << p[1] << "," << solution::f_calls << endl;
			temp_0[i] = p[0];
			temp_1[i] = p[1];
		}
		E.close();

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			solution x_fib = fib(temp_0[i], temp_1[i], epsilon);
			F << x_fib.x << x_fib.y << solution::f_calls << endl;
		}
		F.close();

		for (int i = 0; i < 100; i++) {
			solution::clear_calls();
			solution x_lag = lag(temp_0[i], temp_1[i], epsilon, gamma, Nmax);
			L << x_lag.x << x_lag.y << solution::f_calls << endl;
		}
		L.close();

		//pojedyncze obliczenie dla (-100,100)
		solution::clear_calls();
		solution x_fib = fib(-100, 100, epsilon);
		cout << x_fib << endl;

		solution::clear_calls();
		solution x_lag = lag(-100, 100, epsilon, gamma, Nmax);
		cout << x_lag << endl;

#endif
#if LAB_PART == 2
		/*
		cout << "Fibonacci" << endl;
		solution::clear_calls();
		solution x_fib = fib(0.001, 0.01, epsilon);

		cout << "Lagrange" << endl;
		solution::clear_calls();
		solution x_lag = lag(0.001, 0.01, epsilon,gamma,Nmax);

		cout << x_fib << endl;
		cout << x_lag << endl;
		 */

		 //solution x_fib = fib(0.00241337, 0.00241337, epsilon);
		solution x_lag = lag(0.00241337, 0.00241337, epsilon, gamma, Nmax);

#endif
#endif
	}
	catch (char* EX_INFO)
	{
		cout << EX_INFO << endl;
	}
	//system("pause");
	return 0;
}
