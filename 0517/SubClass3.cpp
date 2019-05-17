#include <gtest/gtest.h>

#define class struct
#define private public
#include "User.h"

// pImpl Idioms - Qt / POCO
// 1) 보안
// 2) 컴파일 의존성을 최소화할 수 있다.
#if 0
// User.h
class User {
private:
	UserImpl* pImpl;
};

// User.cpp
class UserImpl {
private:
	int age;
};
#endif

// 한계
// : C++에서 제품 코드가 pImpl Idiom 을 사용한다면, 적용할 수 없습니다.
// => Exceptional C++
//    More Exceptional C++
//    Exceptional C++ Style


TEST(UserTest, ageTest) {
	User user;

	user.age = 100;
	ASSERT_EQ(100, user.age);
}
