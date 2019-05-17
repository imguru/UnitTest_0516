#include <exception>

class NetworkException : public std::exception {
public:
	virtual const char* what() {
		return "Network disconnected...";
	}
};

class User; // !!
struct IConnection {
	virtual void Move(int x, int y) = 0;
	virtual void Attack(User* p) = 0;

	virtual ~IConnection() {}
};

class User {
	IConnection* conn;
public:
	User(IConnection* p) : conn(p) {}
	void Move(int x, int y) {
		// ...
		conn->Move(x, y);
	}

	void Attack(User* p) {
		// ...
		conn->Attack(p);
	}
};

// Test Stub
//  : 특수한 상황을 시뮬레이션 하고 싶다.
//   제어할 수 없는 협력 객체(외부 의존물)
//   : 네트워크, 시스템, 시간 ...

// => 구현하기 가장 편한, 테스트 대역
//  : 오직 하나의 동작만을 수행한다.

// 테스트 대역을 만들기 어려울 때
// 1) 의존하는 협력 객체가 많을 때
// 2) 협력객체의 인터페이스가 복잡할 때 - O
#include <gtest/gtest.h>

class BadConnection : public IConnection {
public:
	virtual void Move(int x, int y) override {
		throw NetworkException();
	}

	virtual void Attack(User* p) override {
		throw NetworkException();
	}
};


// 네트워크 연결이 끊겼을 때, NetworkException이 제대로 발생하는지 여부를 검증하고 싶다.
class UserTest : public ::testing::Test {};

TEST_F(UserTest, moveTest) {
	BadConnection stub;
	User user(&stub);

	EXPECT_THROW(user.Move(10, 32), NetworkException);
}

TEST_F(UserTest, attackTest) {
	BadConnection stub;
	User user(&stub);

	EXPECT_THROW(user.Attack(0), NetworkException);
}
