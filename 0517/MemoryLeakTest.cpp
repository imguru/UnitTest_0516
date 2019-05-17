#include <stdio.h>
#include <stdlib.h>
// SUT
// : 구글 테스트를 이용해서, 특정 기능이 수행되었을 때, 메모리 누수가 발생하였는지 여부도 검증하고 싶다.
// => C++에서는 객체에 메모리가 할당되는 new / delete 연산을 재정의할 수 있습니다.
class Image {
public:
	static int allocCount;

	void* operator new(size_t size) {
		printf("Image객체 할당\n");
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		printf("Image객체 해지\n");
		--allocCount;
		free(p);
	}
};

int Image::allocCount = 0;

void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;

	//delete p1;
}

#include <gtest/gtest.h>

class FooTest : public ::testing::Test {
protected:
	int allocCount;

	virtual void SetUp() override {
		allocCount = Image::allocCount;
	}

	virtual void TearDown() override {
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(0, diff) << "메모리 릭 발생 - " << diff << " Objects";
	}
};

TEST_F(FooTest, foo) {
	foo();
}















