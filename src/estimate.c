#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** multiply(double **matrix1, double **matrix2, int row1, int row2, int col);
double* y_multiply(double **matrix1, double *matrix2, int row, int col);
double** transpose(double **X, int row, int col);
double** invert(double **M, int len);


int main(int argc, char **argv) {

    char trainFile[6];
	char dataFile[5];
    int t_row;
	int t_col;
	int d_row;
	int d_col;
	double **XT;
	double **XTX;
	double **X_inv;
	double **XT_inv;
	double *w;
	double *result;

    // If input is invalid, return error
    if (argc < 3) {
        printf("Error: Invalid Input\n");
		exit(1);
    }
    
	// Read training file
	FILE *t = fopen(argv[1], "r");

	// Read data file
	FILE *d = fopen(argv[2], "r");

    // If files are empty, return error
	if(t == NULL || d == NULL) {
		printf("Error: File Empty\n");
		exit(1);
	}

    // Scan first line of train file, up to 5 characters
	fscanf(t, "%5s\n", trainFile);
	// Scan next line of train file and set equal to t_col for k attributes, add 1 for column 0
	fscanf(t, "%d\n", &t_col);
	t_col += 1;
	// Scan next line of train file and set equal to t_row for n number of houses
	fscanf(t, "%d\n", &t_row);

	// Scan first line of data file, up to 4 characters
	fscanf(d, "%4s\n", dataFile);
	// Scan next line of data file and set equal to d_col for k attributes, add 1 for column 0
	fscanf(d, "%d\n", &d_col);
	d_col += 1;
	// Scan next line of data file and set equal to d_row for m number of houses
	fscanf(d, "%d\n", &d_row);

	// If k values do not match, return error
	if (t_col != d_col) {
		printf("error\n");
		exit(1);
	}

	// Allocate memory for 2-D matrix train
	double **train = (double **)malloc(sizeof(double*) * t_row);
	// allocate memory for 2-D matrix copy
	double **copy = (double **)malloc(sizeof(double*) * t_row);
	// allocate memory for 1-D matrix y column prices
	double *y_col = (double *)malloc(sizeof(double) * t_row);
	//allocate memory for 2-D matric data
	double **data = (double **)malloc(sizeof(double*) * d_row);

	// Allocate memory for rows of each 2-D matrix, set column 0 in train/data to 1
	for(int i = 0; i < t_row; i++){
		train[i]= (double *)malloc(sizeof(double) * t_col);
		copy[i]= (double *)malloc(sizeof(double) * t_col);
	}
	for(int i = 0; i < d_row; i++) {
		data[i] = (double *)malloc(sizeof(double) * d_col);
	}

	// Input values from train file into matrix copy
	for(int i = 0; i < t_row; i++) {
		for(int j = 0; j < t_col; j++) {
			fscanf(t, "%lf", &copy[i][j]);
		}
		fscanf(t,"\n");
	}

	// Copy values from copy matrix into matrix train starting at column 1
	for (int i = 0; i < t_row; i++) {
		train[i][0] = 1;
		for(int j = 1; j < t_col; j++) {
			train[i][j] = copy[i][j-1];
		}
	}

	// Copy values from copy matrix into matrix y prices
	for(int i = 0; i < t_row; i++) {
		y_col[i] = copy[i][t_col - 1];
	}

	//Input values from data file into matrix data starting at column 1
	for(int i = 0; i < d_row; i++) {
		for(int j = 1; j < d_col; j++) {
			data[i][0] = 1;
			fscanf(d, "%lf", &data[i][j]);
		}
		fscanf(t,"\n");
	}

	// Call matrix manipulation functions to find X^T transpose
	XT = transpose(train, t_row, t_col);
	//X^TX multiply
	XTX = multiply(XT, train, t_col, t_row, t_col);
	// // //(X^TX)^-1 inverse
	X_inv = invert(XTX, t_col);
	// // //(X^TX)^-1X^T
	XT_inv = multiply(X_inv, XT, t_col, t_col, t_row);
	// // // // Final equation for w
	w = y_multiply(XT_inv, y_col, t_col, t_row);
	// // // // Final equation for result
	result = y_multiply(data, w, d_row, d_col);

	//Print result
	for(int i = 0; i < d_row; i++){
		printf("%.0f\n", result[i]);
	}

	// Free array memory
	for(int i = 0; i < t_row; i++){
		free(train[i]);
		free(copy[i]);
	}
	for(int i = 0; i < d_row; i++) {
		free(data[i]);
	}
	
	free(train);
	free(copy);
	free(y_col);
	free(data);

    exit(0);
}

// Transpose matrix function
double** transpose(double **X, int row, int col) {

	double** result = (double**)malloc(col * sizeof(double*));

	for(int i = 0; i < col; i++) {
		result[i] = (double*)malloc(row * sizeof(double));
	}

	// Set result indices to 0
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++){
			result[j][i] = 0;
		}
	}

	// Copy matrix X values to result values
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			result[j][i] = X[i][j];
		}
	}

	// Test - print input matrix
	// for (int i = 0; i < row; i++) {
	// 	for (int j = 0; j < col; j++) {
	// 		printf("%.0f ", X[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// printf("\n");

	// Test - print transposed matrix
	// for(int i = 0; i < col; i++) {
	// 	for(int j = 0; j < row; j++){
	// 		printf("%.0f ", result[i][j]);
	// 	}
	// 	printf("\n");
	// }

	return result;
}

// Matrix multiplication function
double** multiply(double **matrix1, double **matrix2, int row1, int row2, int col) {

	double** result = (double**)malloc(row1 * sizeof(double*));

	// Set result indices to 0
	for(int i = 0; i < row1; i++) {
		result[i] = (double*)malloc(col * sizeof(double));
		for(int j = 0; j < col; j++){
			result[i][j] = 0;
		}
	}

	// Populate result with matrix 1 and matrix 2 product
	for(int i = 0; i < row1; i++) {
		for(int j = 0; j < col; j++){
			for(int x = 0; x < row2; x++){
				result[i][j] += matrix1[i][x] * matrix2[x][j];
				if (result[i][j] == -0){
					result[i][j] = 0;
				}
			}
		}
	}

	// // Test - print product matrix
	// for(int i = 0; i < row1; i++) {
	// 	for(int j = 0; j < col; j++){
	// 		printf("%0.f ", result[i][j]);
	// 	}
	// 	printf("++\n");
	// }

	// printf("\n");

	// // Test - print product matrix
	// for(int i = 0; i < row1; i++) {
	// 	for(int j = 0; j < col; j++){
	// 		printf("%f ", result[i][j]);
	// 	}
	// 	printf("\n");
	// }

	return result;
}

// Invert matrix function
double** invert(double **M, int len){

	double** result = (double**)malloc(len * sizeof(double*));
	double piv;

	// Set values for result as identity matrix
	for(int i = 0; i < len; i++) {
		result[i] = (double*)malloc(len * sizeof(double));
		for(int j = 0; j < len; j++){
			if(i == j) {
				result[i][j] = 1;
			}
			else {
				result[i][j] = 0;
			}
		}
	}

	// Transform M into upper triangular matrix
	for(int p = 0; p < len; p++) {
		// pivot element
		piv = M[p][p];

		for(int j = 0; j < len; j++) {
			// Divide each row of M and result by its respective pivot element
			M[p][j] /= piv;
			result[p][j] /= piv;
			if(result[p][j] == -0){
				result[p][j] = 0;
			}
		}

		// Subtracting or adding pivot row from rows beneath it in M and result
		for(int i = p+1; i < len; i++) {
			piv = M[i][p];

			for(int k = 0; k < len; k++) {
				// Subtract value from row
				M[i][k] -= (piv * M[p][k]);
				result[i][k] -= (piv * result[p][k]);  
				if(result[i][k] == -0) {
					result[i][k] = 0;
				}
		    }
        }		
	}

	// for(int i = 0; i < len; i++) {
	// 	for(int j = 0; j < len; j++){
	// 		printf("%f ", M[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// for(int i = 0; i < len; i++) {
	// 	for(int j = 0; j < len; j++){
	// 		printf("%f ", result[i][j]);
	// 	}
	// 	printf("\n");
	// }


	// Transform M into identity matrix
	for(int p = len - 1; p >= 0; p--) {
		for(int i = p - 1; i >= 0; i--) {
			piv = M[i][p];
			for(int j = 0; j < len; j++) {
				M[i][j] -= (piv * M[p][j]);
				result[i][j] -= (piv * result[p][j]);
				if(result[i][j] == -0) {
					result[i][j] = 0;
				}
			}
		}
	}

	// Test - print inverted matrix
	// for(int i = 0; i < len; i++) {
	// 	for(int j = 0; j < len; j++){
	// 		printf("%f ", result[i][j]);
	// 	}
	// 	printf("\n");
	// }

	return result;
}

// 1-D matrix multiplication function
double* y_multiply(double **matrix1, double *matrix2, int row, int col) {

	double* result = (double*)malloc(row * sizeof(double));

	// Set result indices to 0
	for (int i = 0; i < row; i++) {
		result[i] = 0;
	}

	// Populate result with mat1 and mat2 product
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++){
			result[i] += matrix1[i][j] * matrix2[j];
			if (result[i] == -0) {
				result[i] = 0;
			}
		}
	}

	// // Test - print 1D matrix
	// for(int i = 0; i < row; i++){
	// 	printf("%lf\n", result[i]);
	// }

	// printf("\n");

	// // Test - print 1D matrix
	// for(int i = 0; i < row; i++){
	// 	printf("%.0f\n", result[i]);
	// }

	return result;
}