#include <iostream>
#include <cstdio>
#include <string>

int hamming_distance(int next[], int prev[], int size) {
	int distance = 0;
	for (int i = 0; i < size; i++) {
		if (next[i] != prev[i]) {
			distance++;
		}
	}
	return distance;
}

int count_m_spins(int generation[], int size) {
	int m = 0;
	for (int i = 0; i < size; i++) { if (generation[i] == 1) { m++; } }
	return m;
}


std::string toBinary(int n)
{
	std::string r;
	std::string u = "00000000";
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	if (r.length() < 8) {
		for (int i = r.length(); i < 8; i++) {
			r = "0" + r;
		}
	}
	for (int i = 0; i < r.length(); i++) {
		u[i] = r[7 - i];
	}
	return u;
}

int* nextGeneration(int tab[], int rule, int size) {
	int left, right, current;
	char tmp_char;
	int tmp_int;
	int* newTab = new int[size];
	std::string binRule = toBinary(rule);
	for (int i = 0; i < size; i++) {
		if (i - 1 < 0) {
			left = tab[size - 1];
			right = tab[i + 1];
			current = tab[i];
		}
		else if (i + 1 > size - 1) {
			right = tab[0];
			left = tab[i - 1];
			current = tab[i];
		}
		else {
			right = tab[i + 1];
			left = tab[i - 1];
			current = tab[i];
		}
		tmp_char = binRule[left * 4 + current * 2 + right * 1];
		if (tmp_char == '0') newTab[i] = 0;
		else newTab[i] = 1;
	}
	return newTab;
}

float standard_deviation(int m[], float avg, int size, int delta) {
	float result;
	float sumUP = 0.0;
	float sumDOWN = 0.0;
	for (int j = delta; j < size; j += delta) {
		sumUP += (m[j] - avg)*(m[j - delta] - avg);
	}
	for (int i = 0; i < size; i++) {
		sumDOWN += (m[i] - avg)*(m[i] - avg);
	}
	result = sumUP / sumDOWN;
	return result;
}



int main()
{
	int rule = 90;
	int numberOfGenerations = 50;
	const int width = 80;
	int *tmp_tab;
	int row[width] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int h_distance;
	int m_avg;
	float deviation;
	int *h_distances = new int[numberOfGenerations];
	int *gen_spins = new int[numberOfGenerations];

	std::cout << "RULE: " << toBinary(rule) << " " << rule << std::endl;

	int m_sum = 0;
	for (int i = 0; i < numberOfGenerations; i++) {
		for (int j = 0; j < width; j++) {
			if (row[j] == 1) std::cout << (char)(219);
			else std::cout << " ";
		}

		tmp_tab = nextGeneration(row, rule, width);

		gen_spins[i] = count_m_spins(tmp_tab, width);
		m_sum += gen_spins[i];

		if (tmp_tab != NULL) {
			h_distance = hamming_distance(tmp_tab, row, width);
			std::cout << "           H: " << h_distance;
			h_distances[i] = h_distance;
		}
		std::cout << std::endl;
		for (int x = 0; x < width; x++) {
			row[x] = tmp_tab[x];
		}
	}
	m_avg = m_sum / numberOfGenerations;
	deviation = standard_deviation(gen_spins, m_avg, numberOfGenerations, 1);
	std::cout << "m average: " << m_avg << std::endl;
	std::cout << "deviation: " << deviation << std::endl;

	int m_tmp[5] = { 1, 3, 5, 7, 9 };
	float m_tmp_avg = 5;
	std::cout << "deviation TEMP: " << standard_deviation(m_tmp, m_tmp_avg, 5, 1) << std::endl;
	system("PAUSE");
	return 0;
}