//#include <omp.h>
//#include <cmath>
//#include <stdio.h>
//#include <time.h>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//using namespace std;
//
//
//#define ITERATION_LIMIT 333
//#define EPSILON 0.0000001
//#define NUM_OF_THREADS 12
//
//bool check_diagoanally_dominant_sequential(float** matrix, int matrix_size);
//bool check_diagoanally_dominant_parallel(float** matrix, int matrix_size);
//void solve_jacobi_sequential(float** matrix, int matrix_size, float* right_hand_side);
//void solve_jacobi_parallel(float** matrix, int matrix_size, float* right_hand_side);
//void init_array_sequential(float array[], int array_size);
//float* clone_array_sequential(float array[], int array_length);
//void init_array_parallel(float array[], int array_size);
//float* clone_array_parallel(float array[], int array_length);
//void delete_matrix(float** matrix, int matrix_size);
//int readMatrixSize();
//void readMatrix(float**, float*, int);
//
//int main() {
//	// Just to simulate a real program
//	int user_choice = 1;
//	while (user_choice == 1)
//	{
//		// Get the matrix size .. 
//		int matrix_size = readMatrixSize();
//
//		// Initializing the main structures .. 
//		float** matrix = new float* [matrix_size];
//		for (int i = 0; i < matrix_size; i++) matrix[i] = new float[matrix_size];
//		float* right_hand_side = new float[matrix_size];
//
//		// Getting the matrix elements ..
//		cout << "Size: " << matrix_size << "x" << matrix_size << endl;
//		readMatrix(matrix, right_hand_side, matrix_size);
//
//
//		// Printing the matrix (As a confirmation for the user) .. 
//		/*printf("The matrix in its final shape: \n");
//		for (int i = 0; i < matrix_size; i++) {
//			for (int j = 0; j < matrix_size; j++) {
//				printf("%f ", matrix[i][j]);
//			}
//			printf("\n");
//		}*/
//
//		// Checking if the matrix is diagonally dominant or not ..
//		// I prefered to use the parallel dominant check version here .. 
//		// It won't affact the comparison between the 2 modes as we are using the same function in the 2 modes.
//		omp_set_num_threads(NUM_OF_THREADS);
//		if (!check_diagoanally_dominant_parallel(matrix, matrix_size)) {
//			printf("The matrix is not dominant, please enter another matrix.\n");
//			// We don't need the matrix if it's not diagonally dominant .. 
//			// Cleaning the chaos
//			delete_matrix(matrix, matrix_size);
//			delete[] right_hand_side;
//			printf("Do you want to continue? 1/0\n");
//			scanf_s("%d", &user_choice);
//			continue;
//		}
//
//		// Entering the running mode .. 
//		int run_mode_choice = -1;
//
//		while (run_mode_choice != 2) {
//			printf("Choose: Serial Mode -> 0, Parallel Mode -> 1, Exit -> 2 :\nYour Choice: \n");
//			scanf_s("%d", &run_mode_choice);
//
//			switch (run_mode_choice)
//			{
//				// Serial run..
//			case 0:
//			{
//				// Computing the time
//				const clock_t serial_starting_time = clock();
//				solve_jacobi_sequential(matrix, matrix_size, right_hand_side);
//				printf("Elapsed time: %f ms\n", float(clock() - serial_starting_time));
//			}
//			break;
//			// Parallel run
//			case 1:
//			{
//				// Computing the time
//				const clock_t parallel_starting_time = clock();
//				// Initializing the parallel mode in case of it was chosen ..
//				omp_set_num_threads(NUM_OF_THREADS);
//				solve_jacobi_parallel(matrix, matrix_size, right_hand_side);
//				printf("Elapsed time: %f ms\n", float(clock() - parallel_starting_time));
//			}
//			break;
//			}
//
//		}
//
//		
//		// Cleaning the chaos
//		delete_matrix(matrix, matrix_size);
//		delete[] right_hand_side;
//
//		printf("Do you want to continue? 1/0\n");
//		scanf_s("%d", &user_choice);
//	}
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
//		float i = 0.0f;
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
//			float i = 0.0f;
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
//
//bool check_diagoanally_dominant_parallel(float** matrix, int matrix_size) {
//	// This is to validate that all the rows applies the rule .. 
//	int check_count = 0;
//#pragma omp parallel 
//	{
//		// For each row
//		// Each thread will be assigned to run on a row.
//#pragma omp for schedule (guided, 1)
//		for (int i = 0; i < matrix_size; i++) {
//			float row_sum = 0;
//			// Summing the other row elements .. 
//			for (int j = 0; j < matrix_size; j++) {
//				if (j != i) row_sum += abs(matrix[i][j]);
//			}
//
//			if (abs(matrix[i][i]) >= row_sum) {
//#pragma omp atomic 
//				check_count++;
//			}
//		}
//	}
//	return check_count == matrix_size;
//}
//
//bool check_diagoanally_dominant_sequential(float** matrix, int matrix_size) {
//	int check_count = 0;
//	// For each row ..
//	for (int i = 0; i < matrix_size; i++) {
//		float row_sum = 0;
//		// Summing the other row elements .. 
//		for (int j = 0; j < matrix_size; j++) {
//			if (j != i) row_sum += abs(matrix[i][j]);
//		}
//
//		if (abs(matrix[i][i]) >= row_sum) {
//			check_count++;
//		}
//	}
//	return check_count == matrix_size;
//}
//
//void solve_jacobi_sequential(float** matrix, int matrix_size, float* right_hand_side) {
//	float* solution = new float[matrix_size];
//	float* last_iteration = new float[matrix_size];
//
//	// Just for initialization ..
//	printf("Iterations:----------------------------------------- \n");
//	init_array_sequential(solution, matrix_size);
//
//	for (int i = 0; i < ITERATION_LIMIT; i++) {
//		last_iteration = clone_array_sequential(solution, matrix_size);
//		for (int j = 0; j < matrix_size; j++) {
//			float sigma_value = 0;
//			for (int k = 0; k < matrix_size; k++) {
//				if (j != k) {
//					sigma_value += matrix[j][k] * solution[k];
//				}
//			}
//			solution[j] = (right_hand_side[j] - sigma_value) / matrix[j][j];
//		}
//
//		// Checking for the stopping condition ...
//		int stopping_count = 0;
//		for (int s = 0; s < matrix_size; s++) {
//			if (abs(last_iteration[s] - solution[s]) <= EPSILON) {
//				stopping_count++;
//			}
//		}
//
//		if (stopping_count == matrix_size) break;
//
//		printf("Iteration #%d: ", i + 1);
//		for (int l = 0; l < matrix_size; l++) {
//			printf("%f ", solution[l]);
//		}
//		printf("\n");
//	}
//}
//
//void solve_jacobi_parallel(float** matrix, int matrix_size, float* right_hand_side) {
//	float* solution = new float[matrix_size];
//	float* last_iteration = new float[matrix_size];
//
//	// Just for initialization ..
//	printf("Iterations:--------------------------------------------------\n");
//	init_array_parallel(solution, matrix_size); // dump the array with zeroes
//
//	// NOTE: we don't need to parallelize this as the iterations are dependent. However, we may parallelize the inner processes 
//	for (int i = 0; i < ITERATION_LIMIT; i++) {
//		// Make a deep copy to a temp array to compare it with the resulted vector later
//		last_iteration = clone_array_parallel(solution, matrix_size);
//
//		// Each thread is assigned to a row to compute the corresponding solution element
//#pragma omp parallel for schedule(dynamic, 1)
//		for (int j = 0; j < matrix_size; j++) {
//			float sigma_value = 0;
//			for (int k = 0; k < matrix_size; k++) {
//				if (j != k) {
//					sigma_value += matrix[j][k] * solution[k];
//				}
//			}
//			solution[j] = (right_hand_side[j] - sigma_value) / matrix[j][j];
//		}
//
//		// Checking for the stopping condition ...
//		int stopping_count = 0;
//#pragma omp parallel for schedule(dynamic, 1) 
//		for (int s = 0; s < matrix_size; s++) {
//			if (abs(last_iteration[s] - solution[s]) <= EPSILON) {
//#pragma atomic
//				stopping_count++;
//			}
//		}
//
//		if (stopping_count == matrix_size) break;
//
//		printf("Iteration #%d: ", i + 1);
//		for (int l = 0; l < matrix_size; l++) {
//			printf("%f ", solution[l]);
//		}
//		printf("\n");
//	}
//}
//
//void init_array_sequential(float array[], int array_size) {
//	for (int i = 0; i < array_size; i++) {
//		array[i] = 0;
//	}
//}
//
//float* clone_array_sequential(float array[], int array_length) {
//	float* output = new float[array_length];
//	for (int i = 0; i < array_length; i++) {
//		output[i] = array[i];
//	}
//	return output;
//}
//
//void init_array_parallel(float array[], int array_size) {
//#pragma omp parallel for schedule (dynamic, 1)
//	for (int i = 0; i < array_size; i++) {
//		array[i] = 0;
//	}
//}
//
//float* clone_array_parallel(float array[], int array_length) {
//	float* output = new float[array_length];
//#pragma omp parallel for schedule (dynamic, 1)
//	for (int i = 0; i < array_length; i++) {
//		output[i] = array[i];
//	}
//	return output;
//}
//
//void delete_matrix(float** matrix, int matrix_size) {
//	for (int i = 0; i < matrix_size; i++) {
//		delete[] matrix[i];
//	}
//	delete[] matrix;
//}