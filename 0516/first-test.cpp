// 1. 반드시 들어가야 하는 헤더파일!
#include <gtest/gtest.h>
#include <stdio.h>

#if 0
// 2. main()
int main(int argc, char** argv) {
	// 라이브러리를 초기화합니다.
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
#endif

// 3. 이제는 테스트 함수를 추가하면 됩니다.
// TEST(테스트 케이스 이름, 테스트 이름)
TEST(ATest, foo) {
	printf("foo\n");
}

// 테스트에서 아무것도 수행하지 않을 경우, 성공합니다.
// => 테스트 코드가 작성 중이면, 반드시 실패해야 합니다.

// FAIL(): 명시적으로 테스트를 실패할 수 있습니다.
// => 테스트에 실패할 경우, 실패의 이유를 반드시 명시해야 합니다.
TEST(SampleTest, foo) {
	// 작성중인 테스트 함수입니다.
	FAIL() << "작성중인 테스트입니다.";
}

// g++ first-test.cpp -I. -lgtest -L. -pthread







