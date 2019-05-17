// Parameterized Test(파라미터화 테스트)
//  : xUnit Test Framework
//  => 입력 데이터를 바꿔가며, 수차례 반복 검사하는 데이터 중심의 테스트 코드의 중복을 없애주는 기법. 
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

#include <gtest/gtest.h>

// 1. TestWithParam 기반의 테스트 케이스 클래스 
// ::testing::TestWithParam<InputDataType>
class PrimeTest : public ::testing::TestWithParam<int> {
protected:
	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

// 2. 데이터에 대한 정의
// INSTANTIATE_TEST_CASE_P(ValueName, TestCaseName, Data);
int data[] = { 2, 3, 7, 11, 13, 17, 23, 5 };
INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest, 
	::testing::ValuesIn(data));

// 3. 해당 데이터를 이용하는 테스트를 만들면 됩니다.
// TEST, TEST_F, TEST_P
TEST_P(PrimeTest, IsPrime) {
	ASSERT_TRUE(IsPrime( GetParam() ));
}

TEST_P(PrimeTest, IsPrime2) {
	ASSERT_TRUE(IsPrime( GetParam() ));
}

#if 0
TEST(PrimeTest, IsPrime) {
	for (int i = 0; i < 8; ++i) {
		EXPECT_TRUE(IsPrime(data[i]));
	}
}

TEST(PrimeTest, IsPrime2) {
	EXPECT_TRUE(IsPrime(data[0]));
	EXPECT_TRUE(IsPrime(data[1]));
	EXPECT_TRUE(IsPrime(data[2]));
	EXPECT_TRUE(IsPrime(data[3]));
	EXPECT_TRUE(IsPrime(data[4]));
	EXPECT_TRUE(IsPrime(data[5]));
	EXPECT_TRUE(IsPrime(data[6]));
	EXPECT_TRUE(IsPrime(data[7]));
}

// 1. 가독성
// 2. 유지보수성
// 3. 신뢰성
#endif












