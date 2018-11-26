#include <iostream>
#include <time.h>
#include <fstream>

const int width = 10;
const int height = 10;


void do_nothing() { }

void first_fill(int **tab, int value) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tab[i][j] = value;
		}
	}
}

int count_energy(int **tab, int x, int y) {
	int energy;
	int sum = 0;
	int UP, DOWN, LEFT, RIGHT, CENTER;
	CENTER = tab[x][y];
	UP = y - 1 > 0 ? tab[x][y - 1] : tab[x][height - 1];
	DOWN = y + 1 > height ? tab[x][y + 1] : tab[x][0];
	LEFT = x - 1 > 0 ? tab[x - 1][y] : tab[width-1][y];
	RIGHT = x + 1 < width ? tab[x + 1][y] : tab[0][y];

	sum += CENTER * UP;
	sum += CENTER * DOWN;
	sum += CENTER * LEFT;
	sum += CENTER * RIGHT;
	sum = sum / -2;

	return sum;
}

int count_energy_inversed(int **tab, int x, int y) {
	int energy;
	int sum = 0;
	int UP, DOWN, LEFT, RIGHT, CENTER;
	CENTER = tab[x][y] == 1 ? -1 : 1;
	UP = y - 1 > 0 ? tab[x][y - 1] : tab[x][height - 1];
	DOWN = y + 1 > height ? tab[x][y + 1] : tab[x][0];
	LEFT = x - 1 > 0 ? tab[x - 1][y] : tab[width - 1][y];
	RIGHT = x + 1 < width ? tab[x + 1][y] : tab[0][y];

	sum += CENTER * UP;
	sum += CENTER * DOWN;
	sum += CENTER * LEFT;
	sum += CENTER * RIGHT;
	sum = sum * -0.5;

	return sum;
}

int get_random() {
	return rand() % (0 - 9 + 1) + 0;
}

void display(int **tab) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << tab[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
}

int count_system_energy(int **tab) {
	int sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			sum += count_energy(tab, i, j);
		}
	}
	return sum;
}

int count_magnitude(int **tab) {
	int sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			sum += tab[i][j];
		}
	}
	return sum;
}

int main() {
	srand(time(NULL));
	int demon_energy_start = 50;
	int iterations = 500;
	int demon_energy = demon_energy_start;
	bool console_display = false;
	std::fstream demon_energy_file;
	std::fstream system_energy_file;
	std::fstream magnitude_file;
	demon_energy_file.open("demon_energy.txt", std::ios::in | std::ios::out);
	system_energy_file.open("system_energy.txt", std::ios::in | std::ios::out);
	magnitude_file.open("magnitude.txt", std::ios::in | std::ios::out);


	int** main_tab = new int*[height];
	for (int i = 0; i < height; ++i)
		main_tab[i] = new int[width];

	int* demon_hist = new int[demon_energy_start];
	for (int i = 0; i < demon_energy_start; i++) {
		demon_hist[i] = 0;
	}
	
	first_fill(main_tab, 1);

	int magnitude_sum = 0;
	int x_rand, y_rand, difference, system_energy;
	for (int i = 0; i < iterations; i++) {
		x_rand = get_random();
		y_rand = get_random();
		difference = count_energy(main_tab, x_rand, y_rand) - count_energy_inversed(main_tab, x_rand, y_rand);
		if (demon_energy + difference > 0) {
			demon_energy += difference ;
			main_tab[x_rand][y_rand] == 1 ? main_tab[x_rand][y_rand] = -1 : main_tab[x_rand][y_rand] = 1;
		}
		system_energy = count_system_energy(main_tab);
		std::cout << "DEMON ENERGY | " << demon_energy << std::endl;
		std::cout << "SYSTEM ENERGY | " << system_energy << std::endl;
		if(console_display) display(main_tab);
		if (demon_energy_file.good() == true && system_energy_file.good() == true)
		{
			demon_energy_file << demon_energy << std::endl;
			system_energy_file << system_energy << std::endl;
		}
		demon_hist[demon_energy] += 1;
		std::cout << std::endl;
		magnitude_sum += count_magnitude(main_tab);
	}

	for (int i = 0; i < demon_energy_start; i++) {
		if (demon_hist[i] != 0) {
			std::cout << i << ": ";
			for (int j = 0; j < demon_hist[i]; j++) {
				std::cout << (char)(219);
			}
			std::cout << std::endl;
		}
	}


	float magnitude_avg = magnitude_sum*1.0 / iterations*1.0;

	for (int i = 0; i < height; ++i) { delete[] main_tab[i]; }
	delete[] main_tab;
	demon_energy_file.close();
	system_energy_file.close();
	magnitude_file.close();
	system("PAUSE");
	return 0;
}