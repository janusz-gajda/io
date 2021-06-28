#include "pch.h"

TEST(Rank, CheckRankInitializerFunc) {
	int width = 5, height = 5;
	Matrix A(height, width, [](int i, int j) {return (double)i; });
	ASSERT_EQ(A.rank(), 1);
}



class AutoTesting : public ::testing::TestWithParam<tuple<int, int, double, int, int, double>> {

};
TEST_P(AutoTesting, CheckCopyMethod) {
	Matrix A(get<0>(GetParam()), get<1>(GetParam()), get<2>(GetParam()));
	Matrix B(A);
	EXPECT_TRUE(A == B);
	Matrix C(get<3>(GetParam()), get<4>(GetParam()), get<5>(GetParam()));
	Matrix D(C);
	EXPECT_TRUE(C == D);
}

TEST_P(AutoTesting, CheckCompare) {
	int x1 = get<0>(GetParam());
	int y1 = get<1>(GetParam());
	double value1 = get<2>(GetParam());
	int x2 = get<3>(GetParam());
	int y2 = get<4>(GetParam());
	double value2 = get<5>(GetParam());
	Matrix A(x1, y1, value1);
	Matrix B(x2, y2, value2);
	Matrix C(x1, y1);
	Matrix D(x2, y2);
	Matrix E(x1, y1, value1);
	Matrix F(x2, y2, value1);
	int z = 0;
	for (int i = 0; i < x1; i++) {
		for (int j = 0; j < y1; j++) {
			EXPECT_EQ(A.data[z], value1);
			EXPECT_EQ(C.data[z++], 0.0);
		}
	}
	z = 0;
	for (int i = 0; i < x2; i++) {
		for (int j = 0; j < y2; j++) {
			EXPECT_EQ(B.data[z], value2);
			EXPECT_EQ(D.data[z++], 0.0);
		}
	}
	
		EXPECT_FALSE(A == B);
		EXPECT_FALSE(C == D);
		EXPECT_FALSE(E == F);


	
}

TEST_P(AutoTesting, CheckShape) {
	Matrix A(get<1>(GetParam()), get<2>(GetParam()));
	Matrix B(get<4>(GetParam()), get<5>(GetParam()));
	EXPECT_TRUE(A.rows == get<1>(GetParam()) && A.columns == get<1>(GetParam()) && B.rows == get<4>(GetParam()) && B.columns == get<4>(GetParam()));
}

TEST_P(AutoTesting, Check_Intialize_With_Assign) {
	vector<double> vec;
	int x = get<0>(GetParam());
	int y = get<1>(GetParam());
	double value = get<2>(GetParam());
	double** arr = new double*[x];

	for (int i = 0; i < x; i++) {
		arr[i] = new double[y];
		for (int j = 0; j < y; j++) {
			vec.push_back(value);
			arr[i][j] = value;
		}
	}
	Matrix A(x, y, [](int i, int j) {return (double)i; });
	Matrix B(x, y, vec);

	int z = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			EXPECT_EQ(A.data[z], i);
			EXPECT_EQ(B.data[z++], value);
		}
	}
}

TEST_P(AutoTesting, Check_Intialize_With_Assign_Shape) {
	vector<double> vec;
	int x = get<0>(GetParam());
	int y = get<0>(GetParam());
	double value = get<2>(GetParam());
	double** arr = new double* [x];

	for (int i = 0; i < x; i++) {
		arr[i] = new double[y];
		for (int j = 0; j < y; j++) {
			vec.push_back(value);
			arr[i][j] = value;
		}
	}
	Matrix A(x, y, [](int i, int j) {return (double)i; });
	Matrix B(x, y, vec);

	int z = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			EXPECT_EQ(A.data[z], i);
			EXPECT_EQ(B.data[z++], value);
		}
	}
}

TEST_P(AutoTesting, Check_Assign) {
	vector<double> vec;
	int x = get<0>(GetParam());
	int y = get<1>(GetParam());
	double value = get<2>(GetParam());
	double** arr = new double* [x];

	for (int i = 0; i < x; i++) {
		arr[i] = new double[y];
		for (int j = 0; j < y; j++) {
			vec.push_back(value);
			arr[i][j] = value;

		}
	}
	Matrix A(x, y);
	Matrix B(x, y);
	Matrix C(x, y);
	EXPECT_TRUE(A.load_data([](int i, int j) {return (double)i; }));
	EXPECT_TRUE(B.load_data(vec, x, y));
	EXPECT_TRUE(C.load_data(arr));
	int z = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			EXPECT_EQ(A.data[z], i);
			EXPECT_EQ(B.data[z], value);
			EXPECT_EQ(C.data[z++], value);
		}
	}
}
TEST_P(AutoTesting, CheckMultiplyOperator_Int) {
	int x1 = get<0>(GetParam());
	int y1 = get<1>(GetParam());
	double value1 = get<2>(GetParam());
	Matrix A(x1, y1, value1);
	A * x1;
	int z = 0;
	for (int i = 0; i < x1; i++) {
		for (int j = 0; j < y1; j++) {
			EXPECT_EQ(A.data[z++], value1 * x1);
		}
	}
}



TEST_P(AutoTesting, CheckMultiplyOperator_Matrix) {
	int x1 = get<0>(GetParam());
	int y1 = get<1>(GetParam());
	double value1 = get<2>(GetParam());
	int x2 = get<3>(GetParam());
	int y2 = get<4>(GetParam());
	double value2 = get<5>(GetParam());
	Matrix A(x1, x1, value1);
	Matrix B(x1, x1, value2);
	Matrix C(x1, x1, value1);
	C* B;
	int z = 0;
	for (int i = 0; i < x1; i++) {
		for (int j = 0; j < x1; j++) {
			EXPECT_EQ(C.data[i * x1 + j], A.data[i * x1 + j] * B.data[i * x1 + j]);
		}
	}
}

TEST_P(AutoTesting, CheckAddOperator) {
	int x1 = get<0>(GetParam());
	int y1 = get<1>(GetParam());
	double value1 = get<2>(GetParam());
	int x2 = get<3>(GetParam());
	int y2 = get<4>(GetParam());
	double value2 = get<5>(GetParam());

	Matrix A(x1, y1, value1);
	Matrix B(x1, y1, value2);
	A+B;
	int z = 0;
	for (int i = 0; i < x1; i++) {
		for (int j = 0; j < y1; j++) {
			EXPECT_EQ(A.data[z++], value1 + value2);
		}
	}
}

/*TEST_P(AutoTesting, CheckShapeMethod1) {
	Matrix A = get<0>(GetParam());
	Matrix B = get<1>(GetParam());
	EXPECT_TRUE(A == B);
}*/

INSTANTIATE_TEST_CASE_P(AutoTesting, AutoTesting,
	::testing::Values(
		/*make_tuple(0, 0, 0.0, 0, 0, 1.0),
		make_tuple(-1, -1, 0.0, 1, 0, 1.0),*/
		//make_tuple(1, 1, 1.1, 2, 2, 1.1),
		make_tuple(3, 2, 1.0, 3, 9, 2.0),
		make_tuple(5, 3, 1.0, 5, 4, 2.0),
		make_tuple(5, 4, 1.0, 5, 5, 10.0),
		make_tuple(5, 6, 1.0, 5, 7, 0.0),
		make_tuple(5, 7, 1.0, 5, 8, -1.0),
		make_tuple(2, 3, 1.0, 2, 7, 4.0),
		make_tuple(2, 4, 2.0, 2, 8, 4.0),
		make_tuple(2, 5, 3.0, 2, 9, 6.0),
		/*make_tuple(0, 1, 0.0, 1, 0, 0.0),
		make_tuple(0, 1, 0.0, 1, 0, 1.0),*/
		make_tuple(3, 2, 1.0, 4, 2, 2.0),
		make_tuple(5, 3, 1.0, 8, 9, 2.0),
		make_tuple(5, 4, 1.0, 2, 11, 10.0),
		make_tuple(5, 6, 1.0, 3, 9, 0.0),
		make_tuple(5, 7, 1.0, 1, 9, -1.0),
		make_tuple(2, 3, 1.0, 4, 5, 4.0),
		make_tuple(2, 4, 2.0, 3, 6, 4.0),
		make_tuple(2, 5, 3.0, 1, 6, 6.0)));



TEST(Rank, CheckRank) {
	int width = 2, height = 2;
	Matrix A(height, width, 3.0);
	EXPECT_EQ(A.rank(), 3);
}

TEST(Determinent, CheckDeterm) {
	vector<double> vec;
	vec.push_back(3.0);
	vec.push_back(4.0);
	vec.push_back(5.0);
	vec.push_back(6.0);
	vec.push_back(7.0);
	vec.push_back(8.0);
	vec.push_back(9.0);
	vec.push_back(10.0);
	vec.push_back(11.0);
	int width = 3, height = 3;
	Matrix A(height, width, vec);
	EXPECT_EQ(A.determinant(), 0);
}

TEST(Create, CheckNeg) {
	Matrix A(0, 0, 0.0);
	Matrix B(-1, -1, 2.0);
}