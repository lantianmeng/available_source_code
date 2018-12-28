#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

class ZuoLiao
{
public:
	ZuoLiao(std::string zl_) :zl(zl_){}
	std::string Get() { return zl; }
private:
	std::string zl;
};

class MianFen
{
public:
	MianFen(std::string mf_) :mf(mf_){}
	std::string Get() { return mf; }
private:
	std::string mf;
};;

class TiaoLiaoAbstactFactory
{
public:
	virtual ZuoLiao* CreateZuoLiao() { return nullptr; }
	virtual MianFen* CreateMianFen() { return nullptr; }
};

class ATiaoLiaoFactory :public TiaoLiaoAbstactFactory
{
public:
	virtual ZuoLiao* CreateZuoLiao() { return new ZuoLiao("AZuoLiao"); }
	virtual MianFen* CreateMianFen(){ return new MianFen("AMianFen"); }
};

class BTiaoLiaoFactory :public TiaoLiaoAbstactFactory
{
public:
	virtual ZuoLiao* CreateZuoLiao(){ return new ZuoLiao("BZuoLiao"); }
	virtual MianFen* CreateMianFen(){ return new MianFen("BMianFen"); }
};

#endif