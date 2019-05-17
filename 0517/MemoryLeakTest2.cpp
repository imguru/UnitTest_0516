#include <stdio.h>
#include <stdlib.h>

// C, C++은 메모리 할당 연산을 변경하는 것이 가능합니다.
// => jemalloc(Facebook), tcmalloc(Google)
#ifdef MEMORY_TEST
#define DECLARE_MEMORY_TEST()              \
public:                       			   \
	static int allocCount;                 \
	void* operator new(size_t size) {      \
		++allocCount;                      \
		return malloc(size);               \
	}                                      \
	void operator delete(void* p, size_t) {\
		--allocCount;                      \
		free(p);                           \
	}

#define IMPLEMENTS_MEMORY_TEST(classname)  \
	int classname::allocCount = 0
#else
#define DECLARE_MEMORY_TEST()
#define IMPLEMENTS_MEMORY_TEST(classname)
#endif

class Image {
	DECLARE_MEMORY_TEST()
};

IMPLEMENTS_MEMORY_TEST(Image);

void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;

	//delete p1;
}

#include <gtest/gtest.h>

class FooTest : public ::testing::Test {
protected:
#ifdef MEMORY_TEST
	int allocCount;

	virtual void SetUp() override {
		allocCount = Image::allocCount;
	}

	virtual void TearDown() override {
		int diff = Image::allocCount - allocCount;
		EXPECT_EQ(0, diff) << "메모리 릭 발생 - " << diff << " Objects";
	}
#endif
};

TEST_F(FooTest, foo) {
	foo();
}















