
// SUT
class User {
protected:
	int age;
};

#include <stdio.h>
#include <gtest/gtest.h>

// 접근하고자 하는 멤버 변수 또는 함수가 protected로 되어 있다면, 테스트 전용 하위 클래스를 통해 해당 멤버 변수나 함수에 접근하는 것이 가능합니다.
class TestUser : public User {
public:
	// using 키워드를 통해 부모의 protected를 public으로 변경할 수 있습니다.
	using User::age;
};

TEST(UserTest, ageTest) {
	// User user;
	TestUser user;
	user.age = 42;
	printf("%d\n", user.age);
}




