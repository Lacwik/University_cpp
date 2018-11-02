#include <iostream>
#include <ctime>


float** cholesky(float** matrix, int matrix_N, int matrix_M) {
	float** resultMatrix = new float*[matrix_N];
	for (int i = 0; i < matrix_N; i++) {
		resultMatrix[i] = new float[matrix_M];
	}
	float** secondMatrix = new float*[matrix_N];
	for (int i = 0; i < matrix_N; i++) {
		secondMatrix[i] = new float[matrix_M];
	}

	for (int i = 0; i < matrix_N; i++) {
		for (int j = 0; j < matrix_M; j++) {
			resultMatrix[i][j] = 0;
			secondMatrix[i][j] = 0;
		}
	}

	float sum1 = 0;
	float sum2 = 0;


	for (int i = 0; i < matrix_N; i++) {
		for (int j = 0; j < matrix_M; j++) {
			if (i == j) {
				for (int k = 0; k < i - 1; k++) {
					sum1 = sum1 + resultMatrix[i][k] * resultMatrix[i][k];
				}
				resultMatrix[i][j] = sqrt((matrix[i][j] - sum1));
			}
			else {
				for (int k = 0; k < i - 1; k++) {
					sum2 = sum2 + resultMatrix[j][k] * resultMatrix[i][k];
				}
				resultMatrix[i][j] = (matrix[i][j] - sum2) / resultMatrix[i][i];
			}
		}
	}

	for (int i = 0; i < matrix_N; i++) {
		for (int j = 0; j < matrix_M; j++) {
			std::cout << resultMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return resultMatrix;
}

//=====================================================================================
int main() {

	srand(time(NULL));
	int matrixSize = 2;

	float** tmpMatrix = new float*[2];
	for (int i = 0; i < 2; i++) {
		tmpMatrix[i] = new float[2];
	}
	tmpMatrix[0][0] = 4;
	tmpMatrix[0][1] = 1;
	tmpMatrix[1][0] = 1;
	tmpMatrix[1][1] = 2;

	cholesky(tmpMatrix, 2, 2);


	system("PAUSE");
	return 0;
}

