#include <gtest/gtest.h>
#include <unistd.h>
#include <time.h>

// gettimeofday - POSIX(micro)
// clock_gettime - Linux(nano)
//  : 고해상도 타이머를 사용해야 합니다.

void foo() {
	sleep(3);
}

template <class T, int N>
class TimeTest : public ::testing::Test {
protected:
	time_t startTime;

	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t duration = time(0) - startTime;
		ASSERT_TRUE(duration <= N) << "2초안에 실행되어야 한다. 하지만 " 
			<< duration << " 초 걸렸음.";
	}
};

// TimeTest<2>
// class Sec2TimeTest2 : public TimeTest<Sec2TimeTest2, 2> {

// CRTP
//  : Curiosly Recurring Template Pattern
//   (이상하게 반복되는 템플릿 패턴)
//  => 부모가 템플릿인데, 부모에게 자신의 타입을 정보를 넘겨서 상속하는 설계 방식.

// 주의사항
//  : 공통된 기능을 부모 클래스를 통해서 캡슐화하는 것이 좋습니다.
//  하지만 SetUp과 TearDown을 자식 클래스가 오버라이드 한경우, 반드시 부모의 기능을 명시적으로 호출해주어야 합니다.
class Sec2TimeTest : public TimeTest<Sec2TimeTest, 2> {
protected:
	virtual void SetUp() override {
		TimeTest<Sec2TimeTest, 2>::SetUp(); // !!
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		TimeTest<Sec2TimeTest, 2>::TearDown(); // !!
		printf("TearDown()\n");
	}
};

TEST_F(Sec2TimeTest, foo) {
	foo();
}

class Sec4TimeTest: public TimeTest<Sec4TimeTest, 4> {};
TEST_F(Sec4TimeTest, foo) {
	foo();
}






