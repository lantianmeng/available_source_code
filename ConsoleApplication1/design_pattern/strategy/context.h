#ifndef CONTEXT_H
#define CONTEXT_H

#include "strategy.h"

class stratege_context
{
public:
	stratege_context(IQuoteStrategy *strategy) :m_strategy(strategy) {}
	double GetPrice(double orignal_price) { return m_strategy->GetPrice(orignal_price); }
private:
	IQuoteStrategy* m_strategy;
};

#endif