#ifndef MACHINE_H
#define MACHINE_H

#include <memory>

class State;

class GumballMachine
{
public:
	explicit GumballMachine(int Count);

	void SetState(std::shared_ptr<State> ss);
	std::shared_ptr<State> GetNoQuarterState(){ return m_NoQuarter; }
	std::shared_ptr<State> GetHasQuarterState(){ return m_HasQuarter; }
	std::shared_ptr<State> GetSoldState(){ return m_Sold; }
	std::shared_ptr<State> GetSoldOutState(){ return m_SoldOut; }

	int GetGumballNum(){ return m_GumballNum; }
	void ReleaseGumball();

	void InsertQuarter();
	void EnjectQuarter();
	void TurnCrank();
	void Dispense();

private:
	std::shared_ptr<State> m_NoQuarter;
	std::shared_ptr<State> m_HasQuarter;
	std::shared_ptr<State> m_Sold;
	std::shared_ptr<State> m_SoldOut;

	std::shared_ptr<State> m_CurrentState;
	int m_GumballNum;
};

#endif