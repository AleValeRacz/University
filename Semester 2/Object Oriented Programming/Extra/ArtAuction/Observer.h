#pragma once
#include <vector>

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};

class Observable
{
private:
	
	std::vector<Observer*> observers;
public:
	virtual ~Observable() {}

	void addObserver(Observer* obs)
	{
		observers.push_back(obs);
	}
	void notify()
	{
		for (auto obs : observers)
		{
			obs->update();
		}
	}
};

