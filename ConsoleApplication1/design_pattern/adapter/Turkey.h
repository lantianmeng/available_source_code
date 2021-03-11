#ifndef TURKEY_H
#define TURKEY_H

//»ð¼¦
class Turkey
{
public:
	virtual void gobble() = 0;  //¿©¿©½Ð
	virtual void fly() = 0;     //·ÉÐÐ   £¨»ð¼¦»á·É£¬µ«·ÉµÄ²»Ô¶£©
};

class WildTurkey :public Turkey
{
public:
	virtual void gobble() override
	{
		std::cout << "gobble" << std::endl;
	}

	//
	virtual void fly() override
	{
		std::cout << "i'm flying a short distance" << std::endl;
	}
};

#endif