
// Junit 같은 테스트 프레임워크는 비기능테스트을 제공합니다.
//  비기능 테스트
//   : 성능 또는 메모리 같은 부분을 통해 테스트를 수행하는 방법.
#include <gtest/gtest.h>
#include <unistd.h>
#include <time.h>

// 아래 함수는 2초 안에 수행되어야 합니다.
void foo() {
	sleep(3);
}

class FooTest : public ::testing::Test {
protected:
	time_t startTime;

	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t duration = time(0) - startTime;
		ASSERT_TRUE(duration <= 2) << "2초안에 실행되어야 한다. 하지만 " 
			<< duration << " 초 걸렸음.";
	}
};

TEST_F(FooTest, foo) {
	foo();
}
