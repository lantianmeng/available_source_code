#include "stdafx.h"
#include "Machine.h"
#include "state.h"

GumballMachine::GumballMachine(int Count) :m_GumballNum(Count)
{
	m_NoQuarter = std::make_shared<NoQuarterState>(this);
	m_HasQuarter = std::make_shared<HasQuarterState>(this);
	m_Sold = std::make_shared<SoldState>(this);
	m_SoldOut = std::make_shared<SoldOutState>(this);

	if (Count > 0)
	{
		m_CurrentState = m_NoQuarter;
	}
}

void GumballMachine::SetState(std::shared_ptr<State> ss)
{
	m_CurrentState = ss;
}

void GumballMachine::ReleaseGumball()
{
	if (m_GumballNum > 0)
	{
		m_GumballNum -= 1;
	}
}

void GumballMachine::InsertQuarter()
{
	m_CurrentState->InsertQuarter();
}

void GumballMachine::EnjectQuarter()
{
	m_CurrentState->EnjectQuarter();
}

void GumballMachine::TurnCrank()
{
	m_CurrentState->TurnCrank();
}

void GumballMachine::Dispense()
{
	m_CurrentState->Dispense();
}