#include <iostream>
#include <math.h>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

double suma(int n);

float potega(float x, int k);

void zad4(double a, double h, int M);

void zad5(int p, int k);

int main()
{
	srand(time(NULL));
	/*
	//zadanie 1
	cout<<"Obliczanie sumy"<<endl;
	double s;
	int N;
	cout<<"Podaj N";
	cin>>N;
	s=suma(N);
	cout<<s;
	//zadanie 2
	unsigned int silnia, N1;
	cout<<"podaj z jakiej liczby liczyc silnie"<<endl;
	cin>>N1;
	silnia = 1;
	for(int i=1; i<=N1; i++)
		silnia=silnia*i;
	cout<<"silnia = "<<silnia<<endl;
	//zadanie 3
	float x;
	cout<<"podaj x: ";
	cin>>x;
	int k;
	cout<<"podaj k: ";
	cin>>k;
	cout<<potega(x,k);
	//zadanie 4
	
	double a;
	double h;
	int M;
	cout << "podaj a: ";
	cin >> a;
	cout << "podaj h: ";
	cin >> h;
	cout << "podaj M: ";
	cin >> M;
	zad4(a, h, M);
	*/

	int p;
	int k;
	cout << "podaj p: ";
	cin >> p;
	cout << "podaj k: ";
	cin >> k;
	zad5(p, k);

	system("PAUSE");

	return 0;
}

double suma(int n)
{
	int i;
	double s = 0;
	for (i = 2; i <= n; i++)
		s = s + (2 * i + 3.0) / (i + 1.0);
	return s;
}

float potega(float x, int k)
{
	float p = 1;
	for (int i = 1; i <= k; i++)
		p = p * x;
	return p;
}

void zad4(double a, double h, int M)
{
	double x, y;
	for (int i = 0; i <= M; i++)
	{
		x = a + i * h;
		if (x >= -12 && x <= 5)
		{
			y = (1 / 2)*x*x;
			cout << y << endl;
		}
		else if (x > 5)
		{
			y = sin(x);
			cout << y << endl;
		}
		else if (x < -12)
		{
			y = (1 / x);
			cout << y << endl;
		}
	}
}

void zad5(int p, int k)
{
	int suma = 0;
	int y;
	int l=0;
	for (int i = 0; i < 100; i++)
	{
		y = rand() % ((k + 1) - p) + p;
		cout << y << endl;
		suma += y;
		if (y % 3 == 0)
		{
			l++;
		}
	}
	cout << suma << endl;
	cout << l << endl;
}