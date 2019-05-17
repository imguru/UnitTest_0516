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

class DatabaseTest : public ::testing::Test {
protected:
	Database* database;

	virtual void SetUp() override {
		database = new Database;
		database->Connect();
	}

	virtual void TearDown() override {
		database->Disconnect();
		delete database;
	}
};

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















