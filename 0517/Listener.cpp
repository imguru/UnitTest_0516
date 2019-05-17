#include <gtest/gtest.h>
#include <iostream>
using namespace std;
class MyPrinter : public ::testing::EmptyTestEventListener {
	virtual void OnTestStart(const ::testing::TestInfo& info) {
		cout << "*****************************************" << endl;
		cout << "name: " << info.name() << endl;
		cout << "test_case_name: " << info.test_case_name() << endl;
	}
	virtual void OnTestPartResult(const ::testing::TestPartResult& result) {
		bool fail = result.failed();
		cout << (fail ? "실패" : "성공") << endl;
	}
	virtual void OnTestEnd(const ::testing::TestInfo& info) {
		cout << "*****************************************" << endl;
	}
}; 

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::TestEventListeners& listeners =
		::testing::UnitTest::GetInstance()->listeners();

	// delete listeners.Release(listeners.default_result_printer());
	listeners.Append(new MyPrinter);
	return RUN_ALL_TESTS();
}

TEST(SampleTest, foo) { SUCCEED(); }
TEST(SampleTest, goo) { FAIL(); }
TEST(SampleTest, hoo) { FAIL(); }
