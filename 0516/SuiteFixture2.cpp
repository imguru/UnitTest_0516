#include <string>
#include <stdio.h>

#include <unistd.h> // sleep

// SUT
class Database {
public:
	void Connect() { sleep(1); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return false; }
};
//---------------------------------------------------
#include <gtest/gtest.h>

// 문제점: 픽스쳐를 설치하고 해체하는 시간이 오래 걸려서, 테스트를 추가할 때마다 전체적인 테스트의 시간이 느려지는 문제가 발생한다.
//  => 느린 테스트 문제
//   : 테스트가 너무 느려서, 개발자들이 SUT가 변경되어도 테스트를 수행하지 않는다.
//     테스트가 너무 느려서, 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.

// 만약 픽스쳐를 설치하거나 해체하는 시간이 느려서 문제가 발생한다면,
//   Suite Fixture Setup / Teardown을 이용해서 문제를 해결할 수 있습니다.

// -- Suite Fixture SetUp() - Connect
// DatabaseTest()
//  SetUp()
//   LoginTest()
//  TearDown()
// DatabaseTest()
//  SetUp()
//   LogOutTest()
//  TearDown()
// -- Suite Fixture TearDown() - Disconnect()
// => 공유 픽스쳐 전략

// * 주의점
//  아래의 코드는 느린테스트의 문제가 발생하지 않을 경우, 사용하지 않는 것이 좋습니다.
// : 더 이상 각각의 테스트는 독립적이지 않습니다.
//   이전의 테스트가 픽스쳐를 망가뜨린 경우, 변덕스러운 테스트가 발생할 수 있습니다.
class DatabaseTest : public ::testing::Test {
protected:
	static Database* database;

	// Suite Fixture SetUp
	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
		database = new Database;
		database->Connect();
	}

	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
		database->Disconnect();
		delete database;
	}

	virtual void SetUp() override {
	}

	virtual void TearDown() override {
	}
};

// 정적 멤버 변수는 외부 정의가 반드시 필요합니다.
Database* DatabaseTest::database = nullptr;

TEST_F(DatabaseTest, foo) {}
TEST_F(DatabaseTest, goo) {}

TEST_F(DatabaseTest, LoginTest) {
	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인 하였을 때";

}

TEST_F(DatabaseTest, LogoutTest) {
	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "로그아웃을 했을 때";
}

#if 0
TEST_F(DatabaseTest, LoginTest) {
	Database* database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");

	ASSERT_TRUE(database->IsLogin()) << "데이터베이스에 로그인 하였을 때";

	database->Disconnect();
	delete database;
}

TEST_F(DatabaseTest, LogoutTest) {
	Database* database = new Database;
	database->Connect();

	database->Login("test_id", "test_password");
	database->Logout();

	ASSERT_FALSE(database->IsLogin()) << "로그아웃을 했을 때";

	database->Disconnect();
	delete database;
}
#endif















