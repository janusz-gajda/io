#include "pch.h"

/*TEST(Rank, CheckRankInitializerFunc) {
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) {return (double)i; });
	ASSERT_EQ(A.rank(), 1);
}*/

double initializer(int i, int j)
{
	return 2 * i - j / 2.0;
}

double initializer_floor(int i, int j)
{
	return floor(2 * i - j / 2.0);
}

class Constructor_Dimensions : public::testing::TestWithParam<tuple<int, int>> {};;


TEST_P(Constructor_Dimensions, Check_Constructor_Dimensions) {
	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	if (rows < 1 || colls < 1)
		ASSERT_ANY_THROW(Matrix A(rows, colls));
	else
		ASSERT_NO_THROW(Matrix A(rows, colls));
}

INSTANTIATE_TEST_CASE_P(Constructor_Dimensions, Constructor_Dimensions,
	::testing::Values(
		make_tuple(1, 1),
		make_tuple(2, 2),
		make_tuple(3, 3),
		make_tuple(4, 4),
		make_tuple(5, 5),
		make_tuple(5, 4),
		make_tuple(5, 3),
		make_tuple(5, 2),
		make_tuple(5, 1),
		make_tuple(5, 0),
		make_tuple(0, 5),
		make_tuple(1, 5),
		make_tuple(2, 5),
		make_tuple(3, 5),
		make_tuple(4, 5),
		make_tuple(0, 0),
		make_tuple(0, -1),
		make_tuple(0, -2),
		make_tuple(-1, 5),
		make_tuple(-2, 5),
		make_tuple(-2, -2),
		make_tuple(-1, -1)
		));

class Constructor_Copy : public::testing::TestWithParam<tuple<Matrix>> {};

TEST_P(Constructor_Copy, Check_Constructor_Copy) {
	Matrix A = get<0>(GetParam());
	Matrix B(A);
	ASSERT_TRUE(A == B);
}

INSTANTIATE_TEST_CASE_P(Constructor_Copy, Constructor_Copy,
	::testing::Values(
		make_tuple(Matrix(2, 4.0)),
		make_tuple(Matrix(4, 2, 2.0)),
		make_tuple(Matrix(3, 5, -2.0)),
		make_tuple(Matrix(8, 10, -2.98))
	));


class Constructor_Square_InitializerDouble : public::testing::TestWithParam<tuple<int, double>> {};


TEST_P(Constructor_Square_InitializerDouble, Check_Constructor_Square_InitializerDouble) {
	int rows_colls = get<0>(GetParam());
	double init = get<1>(GetParam());
	Matrix A(rows_colls, init);
	ASSERT_TRUE(A.columns == rows_colls);
	ASSERT_TRUE(A.rows == rows_colls);
	for (int i = 0; i < rows_colls * rows_colls; i++) {
		ASSERT_EQ(A.data[i], init);
	}
}

INSTANTIATE_TEST_CASE_P(Constructor_Square_InitializerDouble, Constructor_Square_InitializerDouble,
	::testing::Values(
		make_tuple(2, 4.0),
		make_tuple(3, 3.0),
		make_tuple(1, -4.0),
		make_tuple(6, 0.0),
		make_tuple(8, 3.95),
		make_tuple(9, 56565.55),
		make_tuple(12, 565656.0),
		make_tuple(65, 989.545)
	));


class Constructor_Square_InitializerFunction : public::testing::TestWithParam<tuple<int>> {};



TEST_P(Constructor_Square_InitializerFunction, Constructor_Square_InitializerFunction) {
	int rows_colls = get<0>(GetParam());
	Matrix A(rows_colls, initializer);
	ASSERT_TRUE(A.columns == rows_colls);
	ASSERT_TRUE(A.rows == rows_colls);
	for (int i = 0; i < rows_colls; i++) {
		for (int j = 0; j < rows_colls; j++) {
			ASSERT_EQ(A.data[i* rows_colls + j], initializer(i, j));
		}
		
	}
}

INSTANTIATE_TEST_CASE_P(Constructor_Square_InitializerFunction, Constructor_Square_InitializerFunction,
	::testing::Values(
		make_tuple(2),
		make_tuple(3),
		make_tuple(1),
		make_tuple(6),
		make_tuple(8),
		make_tuple(9),
		make_tuple(12),
		make_tuple(65)
	));


class Constructor_Square_InitializerVector : public::testing::TestWithParam<tuple<int, vector<double>>> {};

TEST_P(Constructor_Square_InitializerVector, Constructor_Square_InitializerVector) {
	int rows_colls = get<0>(GetParam());
	vector<double> vec = get<1>(GetParam());
	if (vec.size() < rows_colls * rows_colls) {
		ASSERT_ANY_THROW(Matrix A(rows_colls, vec));

	}
	else {
		Matrix A(rows_colls, vec);
		ASSERT_TRUE(A.columns == rows_colls);
		ASSERT_TRUE(A.rows == rows_colls);
		for (int i = 0; i < rows_colls; i++) {
			for (int j = 0; j < rows_colls; j++) {
				ASSERT_EQ(A.data[i * rows_colls + j], vec[i * rows_colls + j]);
			}

		}
	}
	
}

INSTANTIATE_TEST_CASE_P(Constructor_Square_InitializerVector, Constructor_Square_InitializerVector,
	::testing::Values(
		make_tuple(2, vector<double>({2.0, 1.0, 4.0, 6.0})),
		make_tuple(3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 4.0, 6.0, 7.0 })),
		make_tuple(1, vector<double>({ 1.0, 2.0})),
		make_tuple(2, vector<double>({ 1.0, 2.0 }))
	));

class Constructor_NotSquare_InitializerDouble : public::testing::TestWithParam<tuple<int, int, double>> {};


TEST_P(Constructor_NotSquare_InitializerDouble, Check_Constructor_NotSquare_InitializerDouble) {
	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	double init = get<2>(GetParam());
	Matrix A(rows, colls, init);
	ASSERT_TRUE(A.columns == colls);
	ASSERT_TRUE(A.rows == rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colls; j++) {
			ASSERT_EQ(A.data[i*colls + j], init);
		}
	}
}

INSTANTIATE_TEST_CASE_P(Constructor_NotSquare_InitializerDouble, Constructor_NotSquare_InitializerDouble,
	::testing::Values(
		make_tuple(2, 3, 4.0),
		make_tuple(3, 4, 3.0),
		make_tuple(1, 5, -4.0),
		make_tuple(6, 7, 0.0),
		make_tuple(8, 11, 3.95),
		make_tuple(9, 34, 56565.55),
		make_tuple(12, 5, 565656.0),
		make_tuple(65, 1, 989.545)
	));


class Constructor_NotSquare_InitializerFunction : public::testing::TestWithParam<tuple<int, int>> {};



TEST_P(Constructor_NotSquare_InitializerFunction, Check_Constructor_NotSquare_InitializerFunction) {
	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	Matrix A(rows, colls, initializer);
	ASSERT_TRUE(A.columns == colls);
	ASSERT_TRUE(A.rows == rows); 
	double expected_value;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colls; j++){
			ASSERT_EQ(A.data[i * colls + j], initializer(i, j));
		}
	}
}

INSTANTIATE_TEST_CASE_P(Constructor_NotSquare_InitializerFunction, Constructor_NotSquare_InitializerFunction,
	::testing::Values(
		make_tuple(2, 5),
		make_tuple(3, 7),
		make_tuple(1, 5),
		make_tuple(6, 3),
		make_tuple(8, 1),
		make_tuple(9, 43),
		make_tuple(12, 65),
		make_tuple(65, 90)
	));


class Constructor_NotSquare_InitializerVector : public::testing::TestWithParam<tuple<int, int, vector<double>>> {};

TEST_P(Constructor_NotSquare_InitializerVector, Constructor_NotSquare_InitializerVector) {
	int rows = get<0>(GetParam());
	int colls = get<0>(GetParam());
	vector<double> vec = get<2>(GetParam());
	if (vec.size() < rows * colls) {
		ASSERT_ANY_THROW(Matrix A(rows, colls, vec));

	}
	else {
		Matrix A(rows, colls, vec);
		ASSERT_TRUE(A.columns == colls);
		ASSERT_TRUE(A.rows == rows);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colls; j++) {
				ASSERT_EQ(A.data[i * colls + j], vec[i * colls + j]);
			}

		}
	}
	
}

INSTANTIATE_TEST_CASE_P(Constructor_NotSquare_InitializerVector, Constructor_NotSquare_InitializerVector,
	::testing::Values(
		make_tuple(1, 4, vector<double>({ 2.0, 1.0, 4.0, 6.0 })),
		make_tuple(2, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0 })),
		make_tuple(3, 2, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 4.0, 6.0, 7.0 })), //too long
		make_tuple(2, 3, vector<double>({ 1.0, 2.0 })) //too short
	));

class LoadData_DynamicArray : public::testing::TestWithParam<tuple<int, int, int, int ,vector<double>>> {};

TEST_P(LoadData_DynamicArray, Check_LoadData_DynamicArray) {
	
	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	int array_rows = get<2>(GetParam());
	int array_colls = get<3>(GetParam());
	vector<double> vec = get<4>(GetParam());

	//Create dynamic array
	double** dynamic_array = new double* [array_rows];
	for (int i = 0; i < array_rows; i++) {
		dynamic_array[i] = new double[array_colls];
		for (int j = 0; j < array_colls; j++) {
			dynamic_array[i][j] = vec[i * array_colls + j];
		}
	}

	Matrix A(rows, colls);

	if (array_rows != rows || array_colls != colls) {
		ASSERT_FALSE(A.load_data(dynamic_array));
	}
	else {
		ASSERT_TRUE(A.load_data(dynamic_array));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colls; j++) {
				ASSERT_EQ(A.data[i * colls + j], dynamic_array[i][j]);
			}
		}
	}


	//Destroy dynamic array
	for (int i = 0; i < array_rows; i++) {
		delete[] dynamic_array[i];
	}
	delete[] dynamic_array;

}

INSTANTIATE_TEST_CASE_P(LoadData_DynamicArray, LoadData_DynamicArray,
	::testing::Values(
		make_tuple(1, 4, 1, 4 ,vector<double>({ 2.0, 1.0, 4.0, 6.0 })),
		make_tuple(2, 3, 2, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0 })),
		make_tuple(3, 2, 4, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 4.0, 6.0, 7.0, 4.0, 6.0, 2.0 })), //too long
		make_tuple(2, 3, 1, 2, vector<double>({ 1.0, 2.0 })), //too short
		make_tuple(2, 2, 2, 2, vector<double>({ 2.0, 1.0, 4.0, 6.0 })),
		make_tuple(2, 2, 3, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 6.0, 2.0, 1.0 })), // too long
		make_tuple(4, 4, 3, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 6.0, 2.0, 1.0 })) // too short

	));


class LoadData_Function : public::testing::TestWithParam<tuple<int, int>> {};

TEST_P(LoadData_Function, Check_LoadData_Function) {

	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());

	Matrix A(rows, colls);

	
	ASSERT_TRUE(A.load_data(initializer));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colls; j++) {
			ASSERT_EQ(A.data[i * colls + j], initializer(i, j));
		}
	}
}

INSTANTIATE_TEST_CASE_P(LoadData_Function, LoadData_Function,
	::testing::Values(
		make_tuple(1, 4),
		make_tuple(2, 3),
		make_tuple(3, 2),
		make_tuple(2, 3),
		make_tuple(2, 2),
		make_tuple(2, 2),
		make_tuple(4, 4)

	));


class LoadData_Vector : public::testing::TestWithParam<tuple<int, int, int, int, vector<double>>> {};

TEST_P(LoadData_Vector, Check_LoadData_Vector) {

	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	int vector_rows = get<2>(GetParam());
	int vector_colls = get<3>(GetParam());
	vector<double> vec = get<4>(GetParam());

	Matrix A(rows, colls);

	if (vector_rows != rows || vector_colls != colls) {
		ASSERT_FALSE(A.load_data(vec, vector_rows, vector_colls));
	}
	else {
		ASSERT_TRUE(A.load_data(vec, vector_rows, vector_colls));
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < colls; j++) {
				ASSERT_EQ(A.data[i * colls + j], vec[i * colls + j]);
			}
		}
	}

	
}

INSTANTIATE_TEST_CASE_P(LoadData_Vector, LoadData_Vector,
	::testing::Values(
		make_tuple(1, 4, 1, 4, vector<double>({ 2.0, 1.0, 4.0, 6.0 })),
		make_tuple(2, 3, 2, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0 })),
		make_tuple(3, 2, 4, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 4.0, 6.0, 7.0, 4.0, 6.0, 2.0 })), //too long 
		make_tuple(2, 3, 1, 2, vector<double>({ 1.0, 2.0 })), //too short
		make_tuple(2, 2, 2, 2, vector<double>({ 2.0, 1.0, 4.0, 6.0 })),
		make_tuple(2, 2, 3, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 6.0, 2.0, 1.0 })), // too long
		make_tuple(4, 4, 3, 3, vector<double>({ 2.0, 1.0, 4.0, 6.0, 2.0, 1.0, 6.0, 2.0, 1.0 })) // too short

	));



class Operator_Multiply_Matrix : public::testing::TestWithParam<tuple<int, int, int, int>> {};
TEST_P(Operator_Multiply_Matrix, Check_Multiply_Operator_Matrix) {
	int a_rows = get<0>(GetParam());
	int a_colls = get<1>(GetParam());
	int b_rows = get<2>(GetParam());
	int b_colls = get<3>(GetParam());

	Matrix A(a_rows, a_colls, initializer);
	Matrix B(b_rows, b_colls, initializer);
	if (a_colls != b_rows) {
		ASSERT_ANY_THROW(Matrix C(A * B));
	}
	else {
		Matrix C(A * B);
		Matrix refrence_multiply(a_rows, b_colls, 0.0);
		for (int i = 0; i < a_rows; i++) {
			for (int j = 0; j < b_colls; j++) {
				for (int k = 0; k < b_rows; k++) {
					refrence_multiply.data[i * b_colls + j] += A.data[i * a_colls + k] * B.data[k * b_colls + j];
				}
			}
		}
		ASSERT_TRUE(C == refrence_multiply);
	}
}

TEST_P(Operator_Multiply_Matrix, Check_Multiply_Operator_Matrix_Floor) {
	int a_rows = get<0>(GetParam());
	int a_colls = get<1>(GetParam());
	int b_rows = get<2>(GetParam());
	int b_colls = get<3>(GetParam());

	Matrix A(a_rows, a_colls, initializer_floor);
	Matrix B(b_rows, b_colls, initializer_floor);
	if (a_colls != b_rows) {
		ASSERT_ANY_THROW(Matrix C(A * B));
	}
	else {
		Matrix C(A * B);
		Matrix refrence_multiply(a_rows, b_colls, 0.0);
		for (int i = 0; i < a_rows; i++) {
			for (int j = 0; j < b_colls; j++) {
				for (int k = 0; k < b_rows; k++) {
					refrence_multiply.data[i * b_colls + j] += A.data[i * a_colls + k] * B.data[k * b_colls + j];
				}
			}
		}
		ASSERT_TRUE(C == refrence_multiply);
	}
	

	
}

//floor w mnożeniu
//standardowo out of scope
INSTANTIATE_TEST_CASE_P(Operator_Multiply_Matrix, Operator_Multiply_Matrix,
	::testing::Values(
		make_tuple(1, 4, 4, 1),
		make_tuple(2, 3, 3, 7),
		make_tuple(3, 2, 3, 2), // out of scope
		make_tuple(2, 3, 1, 6), // out of scope
		make_tuple(2, 2, 2, 2),
		make_tuple(2, 2, 2, 8),
		make_tuple(4, 4, 10, 2) // out of scope

	));


class Operator_Multiply_Intiger : public::testing::TestWithParam<tuple<int, int, int>> {};

TEST_P(Operator_Multiply_Intiger, Check_Multiply_Operator_Intiger) {
	int rows = get<0>(GetParam());
	int colls = get<1>(GetParam());
	int multiplier = get<2>(GetParam());

	Matrix A(rows, colls, initializer);
	Matrix C(A * multiplier);
	double expected = 0.0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < colls; j++) {;
			expected = A.data[i * colls + j] * static_cast<double>(multiplier);
			ASSERT_EQ(C.data[i * colls + j], expected);
		}
	}

}
//randomowo dodaje 0.0001 (kiedy mnożnik nieparzysty?)

INSTANTIATE_TEST_CASE_P(Operator_Multiply_Intiger, Operator_Multiply_Intiger,
	::testing::Values(
		make_tuple(1, 4, 4),
		make_tuple(2, 3, 3),
		make_tuple(3, 2, -3),
		make_tuple(2, 3, 1),
		make_tuple(2, 2, 2),
		make_tuple(2, 2, -2),
		make_tuple(4, 4, 10),
		make_tuple(4, 5, 10),
		make_tuple(4, 9, 81),
		make_tuple(4, 81, 3),
		make_tuple(4, 3, 6),
		make_tuple(4, 6, 9),
		make_tuple(4, 4, 0),
		make_tuple(4, 6, 7),
		make_tuple(4, 6, 5),
		make_tuple(4, 6, 11),
		make_tuple(2, 3, 0)

	));

class Operator_Add : public::testing::TestWithParam<tuple<int, int, int, int>> {};
TEST_P(Operator_Add, Check_Add_Operator) {
	int a_rows = get<0>(GetParam());
	int a_colls = get<1>(GetParam());
	int b_rows = get<2>(GetParam());
	int b_colls = get<3>(GetParam());

	Matrix A(a_rows, a_colls, initializer);
	Matrix B(b_rows, b_colls, initializer);
	if (a_colls != b_colls || a_rows != b_rows) {
		ASSERT_ANY_THROW(Matrix C(A + B));
	}
	else {
		Matrix C(A + B);
		double expected = 0.0;
		for (int i = 0; i < a_rows; i++) {
			for (int j = 0; j < a_colls; j++) {
				expected = A.data[i * a_colls + j] + B.data[i * a_colls + j];
				ASSERT_EQ(C.data[i * a_colls + j], expected);
			}
		}
	}
	
}


INSTANTIATE_TEST_CASE_P(Operator_Add, Operator_Add,
	::testing::Values(
		make_tuple(1, 4, 4, 1),
		make_tuple(2, 3, 3, 7),
		make_tuple(3, 2, 3, 2),
		//make_tuple(2, 3, 1, 6), out of scope
		make_tuple(2, 2, 2, 2),
		make_tuple(2, 2, 2, 8),
		make_tuple(4, 4, 10, 2),
		make_tuple(4, 4, 4, 4),
		make_tuple(8, 4, 8, 4)

	));

class Methode_Determinant : public::testing::TestWithParam<tuple<Matrix, double>> {};

TEST_P(Methode_Determinant, Check_Methode_Determinant) {
	Matrix A = get<0>(GetParam());
	double expected_value = get<1>(GetParam());
	double determinant;
	if (A.columns != A.rows) {
		ASSERT_ANY_THROW(determinant = A.determinant());
	}
	else {
		determinant = round(A.determinant() * 1000.0) / 1000.0;
		ASSERT_EQ(determinant, expected_value);
	}
	
}

INSTANTIATE_TEST_CASE_P(Methode_Determinant, Methode_Determinant,
	::testing::Values(
		make_tuple(Matrix(2, 3, vector<double>({1.0,2.0,3.0,0.0,1.0,6.0})),  0.0), //2
		make_tuple(Matrix(3, 2, vector<double>({ 1.0,2.2,3.1,0.56,1.12,6.6456 })), -0.112), //2
		make_tuple(Matrix(5, 3, vector<double>({ 1.11,2.22,3.33,4.44,5.55,6.66,7.77,8.88,9.99,10.10,11.11,12.1,13.13,14.14,15.15 })), -0.24642), //3
		make_tuple(Matrix(3, 3, vector<double>({ 9.77,5.65,2.43,4.54,6.65,1.23,9.65,7.76,3.76 })), 51.322) //3
	));

class Methode_Rank : public::testing::TestWithParam<tuple<Matrix, int>> {};

TEST_P(Methode_Rank, Check_Methode_Determinant) {
	Matrix A = get<0>(GetParam());
	int expected_value = get<1>(GetParam());
	int rank;
	ASSERT_NO_THROW(rank = A.rank());
	ASSERT_EQ(rank, expected_value);

}

INSTANTIATE_TEST_CASE_P(Methode_Rank, Methode_Rank,
	::testing::Values(
		make_tuple(Matrix(2, 3, vector<double>({ 1.0,2.0,3.0,0.0,1.0,6.0 })), 2), //2
		make_tuple(Matrix(3, 4, vector<double>({ 1.0,2.0,3.0,0.0,1.0,6.0,1.0,2.0,3.0,0.0,1.0,6.0 })), 2), //2
		make_tuple(Matrix(3, 2, vector<double>({ 1.0,2.2,3.1,0.56,1.12,6.6456 })), 2), //2
		make_tuple(Matrix(5, 3, vector<double>({ 1.11,2.22,3.33,4.44,5.55,6.66,7.77,8.88,9.99,10.10,11.11,12.1,13.13,14.14,15.15 })), 3), //3
		make_tuple(Matrix(3, 3, vector<double>({ 9.77,5.65,2.43,4.54,6.65,1.23,9.65,7.76,3.76 })), 3) //3
	));