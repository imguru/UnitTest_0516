#include <gtest/gtest.h>

// * 신선한 픽스쳐 전략
//  => 각각의 테스트를 독립적으로 구성할 수 있어야 한다.
//   : 신뢰성

// SampleTest()
//   SetUp()
//   foo()
//   TearDown()

// SampleTest()
//   SetUp()
//   goo()
//   TearDown()
class SampleTest : public ::testing::Test {
protected:
	SampleTest() { printf("SampleTest()\n"); }

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(SampleTest, foo) {
	printf("foo()\n");
}

TEST_F(SampleTest, goo) {
	printf("goo()\n");
}
