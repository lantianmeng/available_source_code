#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <memory>

class GumballMachine;

class State
{
public:
	State(GumballMachine* dev) :m_dev(dev) {}
	virtual void InsertQuarter() = 0;
	virtual void EnjectQuarter() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
protected:
	GumballMachine* m_dev;
};

class NoQuarterState :public State
{
public:
	NoQuarterState(GumballMachine* dev) :State(dev) {}
	virtual void InsertQuarter() override
	{
		std::cout << "Insert Quarter" << std::endl;
		m_dev->SetState(m_dev->GetHasQuarterState());
	}

	virtual void EnjectQuarter() override
	{
		std::cout << "do not Insert Quarter" << std::endl;
	}

	virtual void TurnCrank() override
	{
		std::cout << "there is no quarter" << std::endl;
	}

	virtual void Dispense() override
	{
		std::cout << "there is no quarter" << std::endl;
	}
};

class HasQuarterState :public State
{
public:
	HasQuarterState(GumballMachine* dev) : State(dev) {}
	virtual void InsertQuarter() override
	{
		std::cout << "has  Quarter, do not Need Insert" << std::endl;
	}

	virtual void EnjectQuarter() override
	{
		std::cout << "Enject Quarter" << std::endl;
		m_dev->SetState(m_dev->GetNoQuarterState());
	}

	virtual void TurnCrank() override
	{
		std::cout << "turned crank" << std::endl;
		m_dev->SetState(m_dev->GetSoldState());
	}

	virtual void Dispense() override
	{
		std::cout << " no gumball dispensed" << std::endl;
	}
};

class SoldState :public State
{
public:
	SoldState(GumballMachine* dev) : State(dev) {}
	virtual void InsertQuarter() override
	{
		std::cout << "wait,already giving gumball" << std::endl;
	}

	virtual void EnjectQuarter() override
	{
		std::cout << "sorry, already turned crank" << std::endl;
	}

	virtual void TurnCrank() override
	{
		std::cout << "cannot turned twice " << std::endl;
	}

	virtual void Dispense() override
	{
		m_dev->ReleaseGumball();
		if (m_dev->GetGumballNum() > 0)
		{
			m_dev->SetState(m_dev->GetNoQuarterState());
		}
		else
		{
			m_dev->SetState(m_dev->GetSoldOutState());
		}
	}
};

class SoldOutState :public State
{
public:
	SoldOutState(GumballMachine* dev) : State(dev) {}
	virtual void InsertQuarter() override
	{
		std::cout << "insert, no gumball" << std::endl;
	}

	virtual void EnjectQuarter() override
	{
		std::cout << "enject, no quarter" << std::endl;
	}

	virtual void TurnCrank() override
	{
		std::cout << "turn, no gumball " << std::endl;
	}

	virtual void Dispense() override
	{
		std::cout << "dispense, no gumball " << std::endl;
	}
};
#endif