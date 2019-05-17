#include <stdio.h>

// 테스트 전용 하위 클래스 패턴
// SUT
class Engine {
public:
	// ...
	virtual void Start() { printf("Engine start...\n"); }
	virtual ~Engine() {}
};

// 정적 바인딩
//  : 변수의 타입을 기반으로 함수를 호출한다.
// => 테스트 전용 하위 클래스를 사용할 수 없습니다.

// 동적 바인딩
//  : 현재 변수가 담고 있는 객체의 타입을 기반으로 함수를 호출한다.
class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	virtual void Go() {
		// ...
		engine->Start();
	}
};

//------------------------------------------------
// Car 객체에  Go 가 호출되었을 때, engine 객체에 Start()가 호출되었는지 여부를 검증하고 싶다.
#include <gtest/gtest.h>

// 테스트 전용 하위 클래스를 사용하기 위해서는...
//  1. 테스트하고자 하는 함수가, 반드시 가상함수이어야 합니다.

// 테스트 전용 하위 클래스 패턴
// <자식 클래스> is a <부모 클래스>
class TestEngine : public Engine {
	bool isStarted;
public:
	TestEngine() : isStarted(false) {}

	virtual void Start() override {
		Engine::Start();
		isStarted = true;
	}

	// 단언문을 사용할 수 있는 함수를 하위 클래스를 통해 제공하자.
	bool IsStarted() { return isStarted; }
};

class CarTest : public ::testing::Test {
};

TEST_F(CarTest, GoTest) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// 문제점: 관찰할 수 있는 상태가 존재하지 않아서, 단언 함수를 통해 검증할 수 없다.
}

TEST_F(CarTest, GoTestWithTestSubClass) {
	TestEngine engine;
	Car car(&engine);

	car.Go();

	ASSERT_TRUE(engine.IsStarted());
}










