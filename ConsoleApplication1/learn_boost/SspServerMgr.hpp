#ifndef SSPSERVERMGR_HPP
#define SSPSERVERMGR_HPP

#include <boost/shared_ptr.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/mem_fun.hpp>

using namespace boost::multi_index;

class CRequestStream
{
public:
	CRequestStream(int vtsID, int esaID):m_vtsID(vtsID), m_esaID(esaID) {}
	virtual ~CRequestStream() {}

	int getEndpointVtsID() const { return m_vtsID;}
	int getEndpointEsaID() const {return m_esaID;}
private:
	int m_vtsID;
	int m_esaID;
};

typedef boost::shared_ptr<CRequestStream> RequestStreamPtr;

struct uris_by_uri_and_crawl_state {};

class CRequestStreamEsaLessCompare
{
public:
	bool operator()(const RequestStreamPtr & lhs, const RequestStreamPtr & rhs) const
	{
		return lhs->getEndpointEsaID() < rhs->getEndpointEsaID();
	}
};

class CRequestStreamVtsLessCompare
{
public:
	bool operator()(const RequestStreamPtr & lhs, const RequestStreamPtr & rhs) const
	{
		return lhs->getEndpointVtsID() < rhs->getEndpointVtsID();
	}
};

typedef multi_index_container<
	RequestStreamPtr, //容纳的对象是智能指针类型
	indexed_by<       //设置多维索引
	//ordered_unique<identity<RequestStreamPtr>, CRequestStreamEsaLessCompare>,
	//ordered_unique<identity<RequestStreamPtr>, CRequestStreamVtsLessCompare>
	ordered_unique<BOOST_MULTI_INDEX_CONST_MEM_FUN(CRequestStream, int, getEndpointEsaID)>,
	ordered_unique<BOOST_MULTI_INDEX_CONST_MEM_FUN(CRequestStream, int, getEndpointVtsID)>
	> 
> streamHandlerType;

class CSspServerMgr
{
public:
	CSspServerMgr() {}
	virtual ~CSspServerMgr() {}

	void addHandler(RequestStreamPtr hander) 
	{
		m_StreamHanderContainer.insert(hander);
	}

	RequestStreamPtr getHandlerByVtsID(int vtsID)
	{
		RequestStreamPtr ret;
		ret.reset();
		streamHandlerType::nth_index<1>::type::iterator it = m_StreamHanderContainer.get<1>().find(vtsID);
		if (it != m_StreamHanderContainer.get<1>().end())
		{
			ret = *it;
		}
		return ret;
	}

	RequestStreamPtr getHandlerByEsaID(int esaID)
	{
		RequestStreamPtr ret;
		ret.reset();

		nth_index_iterator<streamHandlerType, 0>::type it = get<0>(m_StreamHanderContainer).find(esaID);
		if (it != get<0>(m_StreamHanderContainer).end())
		{
			ret = *it;
		}
		return ret;
	}

	//bool deleteHandlerByVtsID(int vtsID);
	//bool deleteHandlerByEsaID(int esaID);
	//bool deleteAllHandler();
private:
	streamHandlerType m_StreamHanderContainer;
};

#endif
