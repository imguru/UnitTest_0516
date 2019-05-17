// 3A.cpp
// 테스트 함수를 구성하는 방법.

// SUT(System Under Test): 테스트 대상 시스템
//  => CUT(Class or Code Under Test)

class Calculator {
public:
	double Display() { return 0; }
	
	void Enter(double value) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEqual() {}
};


// xUnit                Google Test
//   Test Suite            Test Case
//      Test Case             Test 함수
//-----------------------------------------
#include <gtest/gtest.h>

// TEST(TestCase Name, Test Name)
//  Test Case의 이름은 테스트하고자 하는 클래스나 모듈의 이름에 의해서 결정된다.
//  => SUT: Calculator  ->   TestCase: CalculatorTest
//          Processing  ->             ProcessingTest

// 3A
// 1. Arrange: 객체를 생성하거나, 적절하게 설정하는 작업.
// 2. Act: 객체에 작용을 가한다.
// 3. Assert: 객체의 상태에 대해서 기대하는 바를 단언하다.
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

// 단위 테스트 품질
// 1. 가독성
// 2. 신뢰성
// 3. 유지보수성

// * 테스트 함수 안에서 절대 제어 구문을 사용하면 안됩니다.
//   => 테스트를 검증하는 테스트는 존재하지 않습니다.
//   => 테스트의 코드는 유지보수가 쉬어야 한다.
//   => 테스트의 코드는 오류가 최소화될 수 있는 형태가 되어야 한다.
//   => 제어구문이 필요하다면, 별도의 유틸리티 함수로 관리해야 합니다.
// TEST(CalculatorTest, plusTest2) {
// 테스트대상함수_시나리오_기대값
TEST(CalculatorTest, PressPlus_AddingTwoPlusTwo_DisplaysFour) {
	// Arrange
	Calculator* calc = new Calculator;

	// Act
	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(2);
	calc->PressEqual();

	// Assert
	// : Google Test에서는 ASSERT 함수가 매크로 함수로 구현되어 있습니다. 
	// ASSERT_EQ 함수를 사용할 때, 주의할 점은 바로 인자의 순서를 정확하게 전달해야 합니다.
	// ASSERT_EQ(기대값, 실제결과값)
	// -> X ASSERT_EQ(calc->Display(), 4);
	ASSERT_EQ(4, calc->Display()) << "2+2 했을 때"; 
}

// TDD: 3A
// BDD: 행위 주도 개발.
//  1) 용어(가독성)
//  2) 테스트 더블(행위 검증)
// Arrange -> Given
// Act     -> When
// Assert  -> Then
