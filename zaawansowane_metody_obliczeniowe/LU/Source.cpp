#include <iostream>

void printMatrix(float** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void lu_decomposition(float** matrix_A, int rows, int cols) {
	float** matrix_L = new float*[rows];
	for (int i = 0; i < rows; i++) {
		matrix_L[i] = new float[cols];
	}
	float** matrix_U = new float*[rows];
	for (int i = 0; i < rows; i++) {
		matrix_U[i] = new float[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i == j) { 
				matrix_L[i][j] = 1.0;
				matrix_U[i][j] = 0.0;
			}
			else {
				matrix_L[i][j] = 0.0;
				matrix_U[i][j] = 0.0;
			}
		}
	}

	for (int i = 0; i < rows; i++) {
			for (int k = i; k < rows; k++) {
				float sum = 0.0;
				for (int j = 0; j < i; j++) {
					sum += (matrix_L[i][j] * matrix_U[j][k]);
				}
				matrix_U[i][k] = matrix_A[i][k] - sum;
			}
			for (int k = i; k < cols; k++) {
				if (i == k) {
					matrix_L[i][i] = 1.0;
				}
				else {
					float sum = 0.0;
					for (int j = 0; j < i; j++) {
						sum += (matrix_L[k][j] * matrix_U[j][i]);
					}
					matrix_L[k][i] = (matrix_A[k][i] - sum) / matrix_U[i][i];
				}
			}
	}

	std::cout << "MAIN: " << std::endl;
	printMatrix(matrix_A, rows, cols);
	std::cout << "LEFT: " << std::endl;
	printMatrix(matrix_L, rows, cols);
	std::cout << "UPPER: " << std::endl;
	printMatrix(matrix_U, rows, cols);
}


//=====================================================================================
int main() {

	int rows = 3;
	int cols = 3;

	float** test_matrix = new float*[rows];
	for (int i = 0; i < rows; i++) {
		test_matrix[i] = new float[cols];
	}

	test_matrix[0][0] = 2.0;
	test_matrix[0][1] = -1.0;
	test_matrix[0][2] = -2.0;

	test_matrix[1][0] = -4.0;
	test_matrix[1][1] = 6.0;
	test_matrix[1][2] = 3.0;

	test_matrix[2][0] = -4.0;
	test_matrix[2][1] = -2.0;
	test_matrix[2][2] = 8.0;

	lu_decomposition(test_matrix, rows, cols);

	system("PAUSE");
	return 0;
}