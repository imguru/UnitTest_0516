#include <stdio.h>
#include <gtest/gtest.h>

#if 0
#define FRIEND_TEST(test_case_name, test_name)\
friend class test_case_name##_##test_name##_Test
#endif

class User {
private:
	int age;

	// friend class FriendTest_ageTest_Test;
	FRIEND_TEST(FreindTest, ageTest);
};

// 테스트에서 SUT의 private에 접근하고 싶다.
// => FRIEND_TEST

// ::testing::Test

// class FriendTest_ageTest_Test {};
TEST(FreindTest, ageTest) {
	User user;
	
	user.age = 100;

	printf("user.age: %d\n", user.age); 
}

