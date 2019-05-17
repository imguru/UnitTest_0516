// Fake Object
#include <string>

// DO
class User {
	std::string id_;
	int level_;
	int gold_;
public:
	User(const std::string& id, int level, int gold) 
		: id_(id), level_(level), gold_(gold) {}

	int GetGold() const      { return gold_;  }
	int GetLevel() const     { return level_; }
	std::string GetId() const { return id_;    }
};

struct IDatabase {
	virtual void Save(const std::string& id, User* user) = 0;
	virtual User* Load(const std::string& id) = 0;

	virtual ~IDatabase() {}
};

// User 객체를 데이터베이스 저장하고, 로드하는 역활
class UserManager {
	IDatabase* db;
public:
	UserManager(IDatabase* p) : db(p) {}
	
	void Save(User* user) {
		db->Save(user->GetId(), user);
	}

	User* Load(const std::string& id) {
		return db->Load(id);
	}
};

//-----------------------------------------------------
// 1) 아직 데이터베이스 구현체가 존재하지 않아서, 테스트할 수 없다.
// 2) 협력 객체인 데이터베이스가 너무 느려서, 느린 테스트의 문제가 발생하고 있다.
// 3) 데이터베이스를 직접 설치해서 검증해야 한다.
//  => 협력 객체로 인해서 테스트가 어려울 때, 동일하게 동작하지만, 훨씬 가볍게 동작하는 테스트 대역.
#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	virtual void Save(const std::string& id, User* user) {
		data[id] = user;
	}

	virtual User* Load(const std::string& id) {
		return data[id];
	}
};

class UserManagerTest : public ::testing::Test {
};

// * 사용자 정의 객체에 대해서, == / != 연산을 사용하기 위해서는 연산자 재정의가 반드시 필요합니다.
// * ASSERT_EQ / ASSERT_NE 연산을 사용하기 위해서는, 연산자 재정의가 필요하다.
bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetId() == rhs.GetId() &&
		   lhs.GetLevel() == rhs.GetLevel() &&
		   lhs.GetGold() == rhs.GetGold();
}

TEST_F(UserManagerTest, saveTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string id = "test_id";
	int level = 10;
	int gold = 0;
	User user(id, level, gold);

	manager.Save(&user);
	User *actual = manager.Load(id);

	// 사용자 정의 객체의 내용을 비교하고 있습니다.
	// user == *actual
	EXPECT_EQ(user, *actual);
}

// 개발계
// 운영계

//  boost::asio(고성능 네트워크 라이브러리)
//  => VM
//  => Docker



































