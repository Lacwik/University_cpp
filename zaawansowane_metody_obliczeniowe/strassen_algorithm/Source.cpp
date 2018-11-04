
#include <iostream>
#include <ctime>


void fillMatrixes(float **firstMatrix, float **secondMatrix, int matrixSize)
{
	int i, j;
	//firstMatrix
	for (i = 0; i < matrixSize; ++i) {
		for (j = 0; j < matrixSize; ++j) {
			firstMatrix[i][j] = rand() % 10;
		}
	}

	//secondMatrix
	for (i = 0; i < matrixSize; ++i) {
		for (j = 0; j < matrixSize; ++j) {
			secondMatrix[i][j] = rand() % 10;
		}
	}
}

float **allocateAndFillMatrix(int matrixSize) {
	float** matrix = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		matrix[i] = new float[matrixSize];
	}

	for (int x = 0; x < matrixSize; x++) {
		for (int y = 0; y < matrixSize; y++) {
			matrix[x][y] = 0;
		}
	}

	return matrix;
}

void sum(float **firstMatrix, float **secondMatrix, float **resultMatrix, int matrixSize) {

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
		}
	}
}

void subtract(float **firstMatrix, float **secondMatrix, float **resultMatrix, int tam) {
	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			resultMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];
		}
	}
}


void deleteAllocatedMatrixSpace(float **matrix, int matrixSize) {
	//deleting each subarray in main array
	for (int i = 0; i < matrixSize; ++i) {
		delete[] matrix[i];
	}
	//deleting main array
	delete[] matrix;
}

void strassen(float **firstMatrix, float **secondMatrix, float **resultMatrix, int matrixSize, int &multiplificationCounter) {

	int newMatrixSize = matrixSize / 2;
	if (newMatrixSize == 1) {
		resultMatrix[0][0] = firstMatrix[0][0] * secondMatrix[0][0];
		multiplificationCounter++;
		return;
	}
	float **firstMatrix_11, **firstMatrix_12, **firstMatrix_21, **firstMatrix_22;
	float **secondMatrix_11, **secondMatrix_12, **secondMatrix_21, **secondMatrix_22;
	float **resultMatrix_11, **resultMatrix_12, **resultMatrix_21, **resultMatrix_22;
	float **M1, **M2, **M3, **M4, **M5, **M6, **M7;

	firstMatrix_11 = allocateAndFillMatrix(newMatrixSize);
	firstMatrix_12 = allocateAndFillMatrix(newMatrixSize);
	firstMatrix_21 = allocateAndFillMatrix(newMatrixSize);
	firstMatrix_22 = allocateAndFillMatrix(newMatrixSize);

	secondMatrix_11 = allocateAndFillMatrix(newMatrixSize);
	secondMatrix_12 = allocateAndFillMatrix(newMatrixSize);
	secondMatrix_21 = allocateAndFillMatrix(newMatrixSize);
	secondMatrix_22 = allocateAndFillMatrix(newMatrixSize);

	resultMatrix_11 = allocateAndFillMatrix(newMatrixSize);
	resultMatrix_12 = allocateAndFillMatrix(newMatrixSize);
	resultMatrix_21 = allocateAndFillMatrix(newMatrixSize);
	resultMatrix_22 = allocateAndFillMatrix(newMatrixSize);

	M1 = allocateAndFillMatrix(newMatrixSize);
	M2 = allocateAndFillMatrix(newMatrixSize);
	M3 = allocateAndFillMatrix(newMatrixSize);
	M4 = allocateAndFillMatrix(newMatrixSize);
	M5 = allocateAndFillMatrix(newMatrixSize);
	M6 = allocateAndFillMatrix(newMatrixSize);
	M7 = allocateAndFillMatrix(newMatrixSize);

	float **firstMatrix_result = allocateAndFillMatrix(newMatrixSize);
	float **secondMatrix_result = allocateAndFillMatrix(newMatrixSize);

	//rewriting smaller matrixes
	for (int i = 0; i < newMatrixSize; i++) {
		for (int j = 0; j < newMatrixSize; j++) {
			firstMatrix_11[i][j] = firstMatrix[i][j];
			firstMatrix_12[i][j] = firstMatrix[i][j + newMatrixSize];
			firstMatrix_21[i][j] = firstMatrix[i + newMatrixSize][j];
			firstMatrix_22[i][j] = firstMatrix[i + newMatrixSize][j + newMatrixSize];

			secondMatrix_11[i][j] = secondMatrix[i][j];
			secondMatrix_12[i][j] = secondMatrix[i][j + newMatrixSize];
			secondMatrix_21[i][j] = secondMatrix[i + newMatrixSize][j];
			secondMatrix_22[i][j] = secondMatrix[i + newMatrixSize][j + newMatrixSize];
		}
	}

	sum(firstMatrix_11, firstMatrix_22, firstMatrix_result, newMatrixSize);
	sum(secondMatrix_11, secondMatrix_22, secondMatrix_result, newMatrixSize);
	strassen(firstMatrix_result, secondMatrix_result, M1, newMatrixSize, multiplificationCounter); // M1 = (a11+a22) * (b11+b22)


	sum(firstMatrix_21, firstMatrix_22, firstMatrix_result, newMatrixSize);
	strassen(firstMatrix_result, secondMatrix_11, M2, newMatrixSize, multiplificationCounter); // M2 = (a21+a22) * (b11)


	subtract(secondMatrix_12, secondMatrix_22, secondMatrix_result, newMatrixSize);
	strassen(firstMatrix_11, secondMatrix_result, M3, newMatrixSize, multiplificationCounter); // M3 = (a11) * (b12 - b22)


	subtract(secondMatrix_21, secondMatrix_11, secondMatrix_result, newMatrixSize);
	strassen(firstMatrix_22, secondMatrix_result, M4, newMatrixSize, multiplificationCounter); // M4 = (a22) * (b21 - b11)


	sum(firstMatrix_11, firstMatrix_12, firstMatrix_result, newMatrixSize);
	strassen(firstMatrix_result, secondMatrix_22, M5, newMatrixSize, multiplificationCounter); // M5 = (a11+a12) * (b22)


	subtract(firstMatrix_21, firstMatrix_11, firstMatrix_result, newMatrixSize);
	sum(secondMatrix_11, secondMatrix_12, secondMatrix_result, newMatrixSize);
	strassen(firstMatrix_result, secondMatrix_result, M6, newMatrixSize, multiplificationCounter); // M6 = (a21-a11) * (b11+b12)


	subtract(firstMatrix_12, firstMatrix_22, firstMatrix_result, newMatrixSize);
	sum(secondMatrix_21, secondMatrix_22, secondMatrix_result, newMatrixSize);
	strassen(firstMatrix_result, secondMatrix_result, M7, newMatrixSize, multiplificationCounter); // M7 = (a12-a22) * (b21+b22)


	//M
	sum(M3, M5, resultMatrix_12, newMatrixSize);
	sum(M2, M4, resultMatrix_21, newMatrixSize);
	sum(M1, M4, firstMatrix_result, newMatrixSize);
	sum(firstMatrix_result, M7, secondMatrix_result, newMatrixSize);
	subtract(secondMatrix_result, M5, resultMatrix_11, newMatrixSize);
	sum(M1, M3, firstMatrix_result, newMatrixSize);
	sum(firstMatrix_result, M6, secondMatrix_result, newMatrixSize);
	subtract(secondMatrix_result, M2, resultMatrix_22, newMatrixSize);

	//END RESULT
	for (int i = 0; i < newMatrixSize; i++) {
		for (int j = 0; j < newMatrixSize; j++) {
			resultMatrix[i][j] = resultMatrix_11[i][j];
			resultMatrix[i][j + newMatrixSize] = resultMatrix_12[i][j];
			resultMatrix[i + newMatrixSize][j] = resultMatrix_21[i][j];
			resultMatrix[i + newMatrixSize][j + newMatrixSize] = resultMatrix_22[i][j];
		}
	}

	deleteAllocatedMatrixSpace(firstMatrix_11, newMatrixSize);
	deleteAllocatedMatrixSpace(firstMatrix_12, newMatrixSize);
	deleteAllocatedMatrixSpace(firstMatrix_21, newMatrixSize);
	deleteAllocatedMatrixSpace(firstMatrix_22, newMatrixSize);
	deleteAllocatedMatrixSpace(secondMatrix_11, newMatrixSize);
	deleteAllocatedMatrixSpace(secondMatrix_12, newMatrixSize);
	deleteAllocatedMatrixSpace(secondMatrix_21, newMatrixSize);
	deleteAllocatedMatrixSpace(secondMatrix_22, newMatrixSize);
	deleteAllocatedMatrixSpace(resultMatrix_11, newMatrixSize);
	deleteAllocatedMatrixSpace(resultMatrix_12, newMatrixSize);
	deleteAllocatedMatrixSpace(resultMatrix_21, newMatrixSize);
	deleteAllocatedMatrixSpace(resultMatrix_22, newMatrixSize);
	deleteAllocatedMatrixSpace(M1, newMatrixSize);
	deleteAllocatedMatrixSpace(M2, newMatrixSize);
	deleteAllocatedMatrixSpace(M3, newMatrixSize);
	deleteAllocatedMatrixSpace(M4, newMatrixSize);
	deleteAllocatedMatrixSpace(M5, newMatrixSize);
	deleteAllocatedMatrixSpace(M6, newMatrixSize);
	deleteAllocatedMatrixSpace(M7, newMatrixSize);
	deleteAllocatedMatrixSpace(firstMatrix_result, newMatrixSize);
	deleteAllocatedMatrixSpace(secondMatrix_result, newMatrixSize);
}

void strassen_execute(int matrixSize) {
	float** firstMatrix = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		firstMatrix[i] = new float[matrixSize];
	}
	float** secondMatrix = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		secondMatrix[i] = new float[matrixSize];
	}
	float** thirdMatrix = new float*[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		thirdMatrix[i] = new float[matrixSize];
	}

	fillMatrixes(firstMatrix, secondMatrix, matrixSize);
	int multiplificationCounter = 0;
	strassen(firstMatrix, secondMatrix, thirdMatrix, matrixSize, multiplificationCounter);
	std::cout << std::endl << std::endl;
	std::cout << "N: " << multiplificationCounter << std::endl;

	deleteAllocatedMatrixSpace(firstMatrix, matrixSize);
	deleteAllocatedMatrixSpace(secondMatrix, matrixSize);
	deleteAllocatedMatrixSpace(thirdMatrix, matrixSize);
}

//=====================================================================================
int main() {

	srand(time(NULL));
	int matrixSize = 2;

	matrixSize = 2;
	strassen_execute(matrixSize);
	matrixSize = 8;
	strassen_execute(matrixSize);
	matrixSize = 16;
	strassen_execute(matrixSize);
	matrixSize = 64;
	strassen_execute(matrixSize);
	matrixSize = 128;
	strassen_execute(matrixSize);
	matrixSize = 256;
	strassen_execute(matrixSize);
	matrixSize = 512;
	strassen_execute(matrixSize);
	matrixSize = 1024;
	strassen_execute(matrixSize);


	system("PAUSE");
	return 0;
}

