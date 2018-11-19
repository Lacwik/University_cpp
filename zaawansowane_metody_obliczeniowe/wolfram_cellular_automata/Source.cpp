#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

const int width = 80;

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
	if (sumUP == 0) result = 0;
	else result = sumUP / sumDOWN;
	if (result < 0) result = abs(result);
	return result;
}
void start(int rule, int generations, int start_row[], bool draw) {
	int row[width];
	int h_distance;
	int m_avg;
	int *tmp_tab;
	float deviation;
	int *h_distances = new int[generations];
	int *gen_spins = new int[generations];
	std::vector<int*> rows_vector;


	for (int i = 0; i < width; i++) {
		row[i] = start_row[i];
	}

	int m_sum = 0;
	rows_vector.push_back(row);
	for (int i = 0; i < generations; i++) {
		for (int j = 0; j < width; j++) {
			if (draw) {
				if (row[j] == 1) std::cout << (char)(219);
				else std::cout << " ";
			}
		}

		tmp_tab = nextGeneration(row, rule, width);
		rows_vector.push_back(tmp_tab);

		gen_spins[i] = count_m_spins(tmp_tab, width);
		m_sum += gen_spins[i];

		if (tmp_tab != NULL && draw) {
			h_distance = hamming_distance(tmp_tab, row, width);
			std::cout << "           H: " << h_distance;
			h_distances[i] = h_distance;

			std::cout << std::endl;
		}
		for (int x = 0; x < width; x++) {
			row[x] = tmp_tab[x];
		}
	}
	m_avg = m_sum / generations;
	if (draw) {
		std::cout << "m average: " << m_avg << std::endl;
		deviation = standard_deviation(gen_spins, m_avg, generations, 1);
		std::cout << "deviation 1, delta=1  | " << deviation << std::endl;
		deviation = standard_deviation(gen_spins, m_avg, generations, 2);
		std::cout << "deviation 2, delta=2  | " << deviation << std::endl;
		deviation = standard_deviation(gen_spins, m_avg, generations, 3);
		std::cout << "deviation 3, delta=3  | " << deviation << std::endl;
		deviation = standard_deviation(gen_spins, m_avg, generations, 4);
		std::cout << "deviation 4, delta=4  | " << deviation << std::endl;
	}

	int m_tmp[5] = { 1, 3, 5, 7, 9 };
	float m_tmp_avg = 5;
	if (draw) {
		std::cout << "Hdistance 1:2 |    " << hamming_distance(rows_vector[2], rows_vector[1], width) << std::endl;
		std::cout << "Hdistance 2:4 |    " << hamming_distance(rows_vector[4], rows_vector[2], width) << std::endl;
		std::cout << "Hdistance 3:6 |    " << hamming_distance(rows_vector[6], rows_vector[3], width) << std::endl;
		std::cout << std::endl << std::endl;
	}

	delete h_distances;
	delete gen_spins;
}



int main()
{
	int numberOfGenerations = 20;

	int row[width] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int row_2[width] = { 1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };

	bool standard = true; // examples with single point active
	bool advance = false; // emaples with many active points at start

	std::cout << "=================== RULE: " << toBinary(60) << " | 60" << std::endl << std::endl;
	start(60, numberOfGenerations, row, standard);
	start(60, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(61) << " | 61" << std::endl << std::endl;
	start(61, numberOfGenerations, row, standard);
	start(61, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(62) << " | 62" << std::endl << std::endl;
	start(62, numberOfGenerations, row, standard);
	start(62, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(63) << " | 63 " << std::endl << std::endl;
	start(63, numberOfGenerations, row, standard);
	start(63, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(64) << " | 64 " << std::endl << std::endl;
	start(64, numberOfGenerations, row, standard);
	start(64, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(65) << " | 65 " << std::endl << std::endl;
	start(65, numberOfGenerations, row, standard);
	start(65, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(66) << " | 66 " << std::endl << std::endl;
	start(66, numberOfGenerations, row, standard);
	start(66, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(67) << " | 67 " << std::endl << std::endl;
	start(67, numberOfGenerations, row, standard);
	start(67, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(68) << " | 68 " << std::endl << std::endl;
	start(68, numberOfGenerations, row, standard);
	start(68, numberOfGenerations, row_2, advance);
	std::cout << "=================== RULE: " << toBinary(69) << " | 69 " << std::endl << std::endl;
	start(69, numberOfGenerations, row, standard);
	start(69, numberOfGenerations, row_2, advance);

	system("PAUSE");
	return 0;
}