//#include <stdio.h>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//using namespace std;
//
//int readMatrixSize();
//void readMatrix(float**, float*, int);
//
//int main() {
//	
//	int matrix_size = readMatrixSize();
//	cout << "Size: " << matrix_size << "x" << matrix_size << endl;
//
//	// Initializing the main structures .. 
//	float** matrix = new float* [matrix_size];
//	for (int i = 0; i < matrix_size; i++) matrix[i] = new float[matrix_size];
//	float* right_hand_side = new float[matrix_size];
//
//	readMatrix(matrix, right_hand_side, matrix_size);
//
//	printf("The matrix in its final shape: \n");
//	for (int i = 0; i < matrix_size; i++) {
//		for (int j = 0; j < matrix_size; j++) {
//			printf("%.2f ", matrix[i][j]);
//		}
//		printf("\n");
//	}
//	printf("RHS/Solution: \n");
//	for (int i = 0; i < matrix_size; i++) {
//		printf("%.2f ", right_hand_side[i]);
//	}
//	printf("\n");
//}
//
//void readMatrix(float** matrix, float* rhs, int matrix_size) {
//	string lineText;
//	// Read from file
//	ifstream matrixFile("matrix.txt");
//
//	int lineCount = 0;
//	while (getline(matrixFile, lineText)) {
//
//		//if (lineCount == matrix_size) break;
//
//		float i = 0;
//		int index = 0;
//		istringstream s(lineText);
//		while (s >> i || !s.eof()) {
//			if (s.fail()) {
//				s.clear();
//				string temp;
//				s >> temp;
//				continue;
//			}
//			else {
//				if (lineCount != matrix_size) { // if not last line of matrix
//					matrix[lineCount][index++] = i;
//				}
//				else { // last line matrix is the solution / RHS matrix
//					rhs[index++] = i;
//				}
//			}
//		}
//		lineCount++;
//	}
//}
//
//int readMatrixSize() {
//	string lineText;
//
//	// Read from file
//	ifstream matrixFile("matrix.txt");
//
//	int size = 0;
//	int lineCount = 0;
//	while (getline(matrixFile, lineText)) {
//		lineCount++;
//
//		if (lineCount == 1) {
//			float i = 0;
//			istringstream s(lineText);
//			while (s >> i || !s.eof()) {
//				if (s.fail()) {
//					s.clear();
//					string temp;
//					s >> temp;
//					continue;
//				}
//				else {
//					size++;
//				}
//			}
//		}
//		else {
//			break;
//		}
//	}
//	return size;
//}