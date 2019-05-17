#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct User {
	virtual ~User() {}

	virtual void Stop() = 0;
	virtual void Move(int x, int y) = 0;

	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
};

class MockUser : public User {
 public:
  MOCK_METHOD0(Stop,
      void());
  MOCK_METHOD2(Move,
      void(int x, int y));
  MOCK_CONST_METHOD0(GetX,
      int());
  MOCK_CONST_METHOD0(GetY,
      int());
};

// 1. 호출 여부
// 2. 호출 횟수
// 3. 호출 순서
//   + 인자
void foo(User* p) {
	p->Stop();
}

TEST(SampleTest, fooTest) {
	MockUser mock;

	EXPECT_CALL(mock, Stop());

	foo(&mock);
}

void goo(User* p) {
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
	p->Stop();
}

// 호출횟수
//   EXPECT_CALL(...).Times(3);
using ::testing::AnyNumber;
TEST(SampleTest, gooTest) {
	MockUser mock;

	EXPECT_CALL(mock, Stop()).Times(AnyNumber());

	goo(&mock);
}

// 호출 순서
//   InSequence 객체만 정의하면, 자동적으로 순서를 검증합니다.
using ::testing::InSequence;
using ::testing::_; // placeholders
void hoo(User* p) {
	p->Stop();
	p->Move(10, 32);
	p->Move(20, 32);
}

TEST(SampleTest, hooTest) {
	InSequence seq;
	MockUser mock;

	EXPECT_CALL(mock, Stop());
	// EXPECT_CALL(mock, Move(_, 32));
	EXPECT_CALL(mock, Move(_, 32)).Times(2);

	hoo(&mock);
}








#if 0
int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}

$ g++ ../googletest/googlemock/src/gmock_main.cc -c -I.
$ ar rcv libgmock.a gmock-gtest-all.o gmock_main.o
#endif
