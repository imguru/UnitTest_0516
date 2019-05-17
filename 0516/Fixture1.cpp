class Calculator {
public:
	double Display() { return 0; }
	
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEqual() {}
};
//--------------------------------------

// xUnit Test Pattern
//  Fixture
//  정의: xUnit Test Pattern에서  SUT를 실행하기 위해 준비해야하는 모든 과정을 픽스쳐라고 부릅니다.
//  픽스쳐를 구성하는 모든 로직 부분을 '픽스쳐를 설치한다'라고 합니다.(Fixture Setup)

// * 픽스쳐를 설치하는 방법
//  1) 인라인 픽스쳐 설치
//    : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//    장점
//     - 픽스쳐 설치하는 로직과 검증하는 로직이 테스트 함수안에 존재함으로, 테스트의 인과 관계를 쉽게 파악할 수 있다.
//    단점
//     - 모든 테스트 함수 안에서 코드 중복이 발생한다.
//     - 픽스쳐 설치의 과정이 복잡하면, 테스트 코드를 이해하기 어렵게 만들 수 있다.

//  2) 위임 설치
//  3) 암묵적 설치 - O
#include <gtest/gtest.h>

TEST(CalculatorTest, plusTest) {
	// Arrange
	Calculator* calc = new Calculator;

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

TEST(CalculatorTest, PressPlus_AddingTwoPlusTwo_DisplaysFour) {
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEqual();

	ASSERT_EQ(4, calc->Display()) << "2+2 했을 때"; 
}
