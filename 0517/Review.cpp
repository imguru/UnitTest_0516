#include <gtest/gtest.h>

TEST(TestCaseName, TestName) {
	printf("Test\n");
}

// ::testing::Test의 자식 클래스가 만들어집니다.
class TestCaseName2 : public ::testing::Test {
protected:
	TestCaseName2() { printf("TestCaseName2()\n"); }
	~TestCaseName2() { printf("~TestCaseName2()\n"); }

	// Suite Fixture SetUp / TearDown
	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
	}

	// Fixture SetUp / TearDown
	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

TEST_F(TestCaseName2, TestName) {
	printf("Test\n");
}

TEST_F(TestCaseName2, TestName2) {
	printf("Test2\n");
}

class MyEnvironment : public ::testing::Environment {
protected:
	virtual void SetUp() override {
		printf("Env SetUp()\n");
	}

	virtual void TearDown() override {
		printf("Env TearDown()\n");
	}
};

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	// Global Fixture SetUp / TearDown
	::testing::AddGlobalTestEnvironment(new MyEnvironment);

	return RUN_ALL_TESTS();
}

// 사용자가 정의한 TestCaseName2의 자식 클래스로 만들어집니다.
// 픽스쳐를 공유하는 모든 테스트를 사용자가 정의한 테스트 케이스 클래스의 자식으로 관리할 수 있습니다.
