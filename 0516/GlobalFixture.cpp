// Google Test에서 제공하는 고유의 기능.
// => 프로세스 단위의 초기화/해지
// => Global Fixture를 통해 프로그램이 시작할 때, 초기화하고, 프로그램이 종료되는 시점에 해지하는 코드를 작성할 수 있습니다.

#include <stdio.h>
#include <gtest/gtest.h>

TEST(SampleTest, foo) {}
TEST(SampleTest, goo) {}

class MyGlobalEnvironment : public ::testing::Environment {
protected:
	virtual void SetUp() override {
		printf("SUT 프로그램 초기화 코드\n");
	}

	virtual void TearDown() override {
		printf("SUT 프로그램 정리 코드\n");
	}
};

// 설치하는 방법 2가지
//  1) 전역 변수를 통해서 설치하는 방법
//  : C++에서는 객체에 대한 초기화를 전역변수를 통해 하는 것을 권장하지 않습니다. 표준에서 각 파일에 대한 객체 초기화 순서가 보장되지 않기 때문에, 문제가 발생할 경우, 찾기 어렵습니다.
#if 0
::testing::Environment *const env 
	= ::testing::AddGlobalTestEnvironment(new MyGlobalEnvironment);
#endif

//  2) main을 직접 작성해서, 설치하는 방법. - 권장하는 방법.
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	::testing::AddGlobalTestEnvironment(new MyGlobalEnvironment);

	return RUN_ALL_TESTS();
}


// C    -> Go
// C++  -> Rust
//  : C++ -> C++11/14 -> C++17/20

// Java -> Kotlin









