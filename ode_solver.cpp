//Do not edit the code below (unless you know what you are doing)

#include "ode_solver.h"
#include <math.h>
#define M_PI 3.14159265358979323846

matrix *solve_ode(double t0, double dt, double tend, const matrix &Y0, matrix P)
{
	int N = static_cast<int>(floor((tend - t0) / dt) + 1);
	if (N < 2)
		throw "The time interval is defined incorrectly";
	int *s = get_size(Y0);
	if (s[1] != 1)
		throw "Initial condition must be a vector";
	int n = s[0];
	delete[]s;
	matrix *S = new matrix[2]{ matrix(N), matrix(n,N) };
	S[0](0) = t0;
	for (int i = 0; i < n; ++i)
		S[1](i, 0) = Y0(i);
	matrix k1(n), k2(n), k3(n), k4(n);
	//cout << "b1 = " << P(0, 0) << ", b2 = " << P(1, 0) << endl;
	for (int i = 1; i < N; ++i)
	{
		S[0](i) = S[0](i - 1) + dt;
		k1 = dt*diff(S[0](i - 1), S[1][i - 1], P);
		k2 = dt*diff(S[0](i - 1) + 0.5*dt, S[1][i - 1] + 0.5*k1, P);
		k3 = dt*diff(S[0](i - 1) + 0.5*dt, S[1][i - 1] + 0.5*k2, P);
		k4 = dt*diff(S[0](i - 1) + dt, S[1][i - 1] + k3, P);
		for (int j = 0; j < n; ++j)
			S[1](j, i) = S[1](j, i - 1) + (k1(j) + 2 * k2(j) + 2 * k3(j) + k4(j)) / 6;
	}
	S[1] = trans(S[1]);
	return S;
}



//You can edit the following code

matrix diff(double t, const matrix &Y, matrix P)
{
#if LAB_NO == 2
	matrix dY(Y);
	double a=0.98, b=0.63, g=9.81, PA=1, PB=1, DB= 0.00365665, Fin = 0.01, Tin=10, TA=90, TB =10;
	double DA = P(0); //P[1][1]

	double FAout = Y(0) > 0 ? a * b * DA * sqrt(2 * g * Y(0) / PA) : 0;
	double FBout = Y(1) > 0 ? a * b * DB * sqrt(2 * g * Y(1) / PB) : 0;
	
	dY(0) = -FAout;
	dY(1) = FAout + Fin - FBout;

	double T1 = Y(2) > 0 ? Fin / Y(1) * (Tin - Y(2)) : 0;
	double T2 = Y(2) > 0 ? FAout / Y(1) * (TA - Y(2)) : 0;
	dY(2) = T1 + T2; 

	return dY;
#endif
}
