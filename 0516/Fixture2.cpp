class Calculator {
public:
	Calculator(int n) {}
	double Display() { return 0; }
	
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEqual() {}
};
//--------------------------------------
#include <gtest/gtest.h>
//  2) 위임 설치
// 1) 동일한 픽스쳐를 가지는 테스트 함수를 동일한 테스트 케이스 클래스로 묶는다.
class CalculatorTest : public ::testing::Test {
// 3) TEST_F로 만들어진 함수는 자식 클래스의 함수이므로,
// 테스트 함수에서 접근하기 위해서는 protected를 사용해야
// 합니다.
protected:
	Calculator* CreateCalc() { return new Calculator(0); }
	// 테스트 유틸리티 함수.
};

// 2) 테스트 함수를 만들 때,
//    TEST 매크로가 아닌 TEST_F 매크로를 통해 만들어야 합니다.
TEST_F(CalculatorTest, plusTest) {
	// Arrange
	Calculator* calc = CreateCalc();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEqual();

	// Assert
	if (calc->Display() == 4) {
		SUCCEED();
	} else {
		FAIL();
	}
}

TEST_F(CalculatorTest, PressPlus_AddingTwoPlusTwo_DisplaysFour) {
	// Arrange
	Calculator* calc = CreateCalc();

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEqual();

	ASSERT_EQ(4, calc->Display()) << "2+2 했을 때"; 
}
