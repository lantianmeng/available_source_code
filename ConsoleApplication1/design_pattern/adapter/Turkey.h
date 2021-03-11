#ifndef TURKEY_H
#define TURKEY_H

//��
class Turkey
{
public:
	virtual void gobble() = 0;  //������
	virtual void fly() = 0;     //����   ���𼦻�ɣ����ɵĲ�Զ��
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