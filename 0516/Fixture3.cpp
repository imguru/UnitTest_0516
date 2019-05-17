class Calculator {
public:
	double Display() { return 0; }
	
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEqual() {}
};
//--------------------------------------
#include <gtest/gtest.h>
#include <stdio.h>

// 픽스쳐를 설치하는 방법 3.
//  => 암묵적 설치/해체
//  : 여러 테스트에서 같은 테스트 픽스쳐를 SetUp 함수를 통해 설치한다.

// 4단계 테스트 패턴
// : xUnit Test Pattern에서 테스트를 구성하는 방법
// 1단계
//  - 테스트 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업.
// 2단계
//  - SUT와 상호작용한다.
// 3단계
//  - 기대 결과를 확인한다.
// 4단계
//  - 테스트 픽스쳐를 해체해서, 테스트 시작 하기 전 상태로 돌려놓는다.
// => 신선한 픽스쳐의 전략!
class CalculatorTest : public ::testing::Test {
protected:
	Calculator* calc;

	virtual void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}
};

TEST_F(CalculatorTest, foo) {
	printf("  foo()\n");
}

TEST_F(CalculatorTest, plusTest) {
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
	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEqual();

	ASSERT_EQ(4, calc->Display()) << "2+2 했을 때"; 
}
