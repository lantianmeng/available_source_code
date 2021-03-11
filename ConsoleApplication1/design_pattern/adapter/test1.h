
#include <memory>

class A
{
public:
	bool Read(unsigned char* buf, int len)
	{
		memcpy_s(buf, len, " A hello ", strlen("A hello "));
		return true;
	}
};

class B
{
public:
	virtual bool Read(char* buf, int len)
	{
		memcpy_s(buf, len, "B hello ", strlen("B hello "));
		return true;
	}
};

class A_adapter:public B
{
public:
	A_adapter(std::shared_ptr<A> aa_) :aa(aa_) {}
	bool Read(char* buf, int len) override
	{
		unsigned char temp[1024] = {0};
		aa->Read(temp, len);
		memcpy_s(buf, len, temp, len);
		return true;
	}

private:
	std::shared_ptr<A> aa;
};