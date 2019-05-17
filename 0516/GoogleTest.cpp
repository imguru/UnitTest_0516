#include <gtest/gtest.h>
#include <stdio.h>

// ASSERT_EQ
// ASSERT_NE
// ASSERT_GT / LT / GE / LE
// ASSERT_TRUE
// ASSERT_FALSE
// 1. ASSERT 매크로
//  주의할점
//  : 첫번째 단언 함수가 실패할 경우, 이후의 동작은 수행하지 않는다.
//  => 죽은 단언문.

//  * 하나의 테스트 함수 안에서는 오직 하나의 단언문만 존재해야 한다.
//   > 너무 많은 테스트 함수를 만들어야 한다.
//    ; 유지 보수성이 떨어진다.

//  * Google Test가 사용하는 방식으로 많이 사용합니다.
//    - ASSERT_XX
//    - EXPECT_XX
//     : 하나의 단언문이 실패하더라도, 이후의 단언문을 수행합니다.
//      => 죽은 단언문의 문제를 해결할 수 있고, 다른 테스트로 분리할 필요도 없습니다.


#if 1
// 주석을 통해 테스트를 비활성화하면, 아무도 관리하지 않는 잊혀진 테스트가 될 수 있다.
//  => 테스트 프레임워크가 제공하는 비활성화기능을 사용해야 한다.
//  => 테스트 케이스의 이름 또는 테스트의 이름이 DISABLED_로 시작하면, 수행되지 않습니다.
TEST(DISABLED_GoogleTestSample, Sample1) {
	int expected = 10;
	
	int actual1 = 42;
	int actual2 = 30;

	ASSERT_EQ(expected, actual1) << "이유 1";
	ASSERT_EQ(expected, actual2) << "이유 2";
}

TEST(GoogleTestSample, DISABLED_Sample2) {
	int expected = 10;
	
	int actual1 = 42;
	int actual2 = 30;

	EXPECT_EQ(expected, actual1) << "이유 1";
	EXPECT_EQ(expected, actual2) << "이유 2";
}
#endif

#include <string>
// 2. 문자열 비교
//   C++
//     std::string
//     const char*
TEST(GooleTestSample, Sample3) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	ASSERT_EQ(s1, s2);
	// == 연산자를 사용합니다.
	// std::string은 == 연산자를 재정의하였으므로, 안전하게 사용하는 것이 가능하다.

	const char *s3 = "hello";
	const char *s4 = s1.c_str();

	// ASSERT_EQ(s3, s4);
	// C 문자열(포인터)에 대해서는 절대 사용하면 안됩니다.

	ASSERT_STREQ(s3, s4);
	// strcmp로 구현되어 있으므로, 포인터에 대해서 안전하게 사용 가능합니다.
}

// 3. 부동 소수점 비교
//   (Floating Point 타입은 절대 ==, !=을 통해 비교하면 안됩니다.)
TEST(GoogleTestSample, Sample4) {
	double a = 0.7;
	double b = 0.1 * 7;

	// ASSERT_EQ(a, b);
	ASSERT_DOUBLE_EQ(a, b); // 4ULP

	// 오차 범위를 직접 지정가능하다.
	ASSERT_NEAR(a, b, 0.0000001);
}

// 4. 예외 테스트
//  : SUT가 특정 상황에서 기대한 예외가 제대로 발생하는지 여부를 검증하고 싶다.
void CheckUserId(const std::string& userId) {
	// return;
	// throw 1;
	if (userId.empty()) {
		throw std::invalid_argument("User Id가 빈문자열 입니다.");
	}
}

// CheckUserId 함수에 빈문자열을 보냈을 때, std::invalid_argument 예외가 발생하는지 여부를 검증하고 싶다.
TEST(GoogleTestSample, ExceptionTest1) {
	ASSERT_THROW(CheckUserId(""), std::invalid_argument);
	ASSERT_ANY_THROW(CheckUserId(""));
}

#if 0
TEST(GoogleTestSample, ExceptionTest1) {
	try {
		CheckUserId("");
		FAIL() << "예외가 발생하지 않음...";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류 예외 발생";
	}
}
#endif

// 5. 테스트 비활성화
// * 테스트를 비활성화할 때, 주석을 사용하면 안됩니다.
// => 비활성화 하는 방법
//   DISABLED_
//   $ ./a.out --gtest_also_run_disabled_tests
