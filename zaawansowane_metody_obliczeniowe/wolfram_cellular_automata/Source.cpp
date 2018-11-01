#include <iostream>
#include <cstdio>
#include <string>


std::string toBinary(int n)
{
	std::string r;
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	if (r.length() < 8) {
		for (int i = r.length(); i < 8; i++) {
			r = "0" + r;
		}
	}
	return r;
}

int* nextGeneration(int tab[], int rule, int size) {
	int left, right, current;
	char tmp_char;
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


		//if (left == 1 && current == 1 && right == 1) {
		//	if (binRule[0] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 1 && current == 1 && right == 0) {
		//	if (binRule[1] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 1 && current == 0 && right == 1) {
		//	if (binRule[2] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 1 && current == 0 && right == 0) {
		//	if (binRule[3] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 0 && current == 1 && right == 1) {
		//	if (binRule[4] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 0 && current == 1 && right == 0) {
		//	if (binRule[5] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 0 && current == 0 && right == 1) {
		//	if (binRule[6] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
		//if (left == 0 && current == 0 && right == 0) {
		//	if (binRule[7] == '1') tab[i] = 1;
		//	else tab[i] = 0;
		//}
	}
	return newTab;
}




int main()
{
	int rule = 104;
	int numberOfGenerations = 30;
	const int width = 60;
	int *tmp_tab;
	int row[width] = { 0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 };

	std::cout << "RULE: " << toBinary(rule) << std::endl;

	for (int i = 0; i < numberOfGenerations; i++) {
		for (int j = 0; j < width; j++) {
			if (row[j] == 1) std::cout << (char)(219);
			else std::cout << " ";
		}
		std::cout << std::endl;
		tmp_tab = nextGeneration(row, rule, width);
		for (int x = 0; x < width; x++) {
			row[x] = tmp_tab[x];
		}
	}
	system("PAUSE");
	return 0;
}