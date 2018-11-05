#include <iostream>

void printMatrix(float** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void cholesky(float** matrix, int rows, int cols) {
	float** resultMatrix = new float*[rows];
	for (int i = 0; i < rows; i++) {
		resultMatrix[i] = new float[cols];
	}
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			resultMatrix[i][j] = 0.0;
		}
	}
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <= i; j++) {
			float sum = 0.0;
			if (j == i){
				for (int k = 0; k < j; k++) {
					sum = sum + pow(resultMatrix[j][k], 2)*1.0;
				}
				resultMatrix[j][j] = sqrt(matrix[j][j] - sum)*1.0;
			}
			else {
				for (int k = 0; k < j; k++) {
					sum = sum + (resultMatrix[i][k] * resultMatrix[j][k]);
				}
				resultMatrix[i][j] = 1.0*((matrix[i][j] - sum) / resultMatrix[j][j]);
			}
		}
	}
	printMatrix(resultMatrix, rows, cols);
}

//=====================================================================================
int main() {

	int rows = 3;
	int cols = 3;

	float** tmpMatrix = new float*[rows];
	for (int i = 0; i < rows; i++) {
		tmpMatrix[i] = new float[cols];
	}
	tmpMatrix[0][0] = 4;
	tmpMatrix[0][1] = 12;
	tmpMatrix[0][2] = -16;

	tmpMatrix[1][0] = 12;
	tmpMatrix[1][1] = 37;
	tmpMatrix[1][2] = -43;

	tmpMatrix[2][0] = -16;
	tmpMatrix[2][1] = -43;
	tmpMatrix[2][2] = 98;

	cholesky(tmpMatrix, rows, cols);

	system("PAUSE");
	return 0;
}

