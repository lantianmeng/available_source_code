#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

std::string write_json()
{
	//<br>[RapidJSON简介及使用](https://blog.csdn.net/fengbingchun/article/details/91139889)

	//rapidjson::StringBuffer buf;
	//rapidjson::Writer<rapidjson::StringBuffer> writer(buf);

	//writer.StartObject();
	//writer.Key("version");
	//writer.String("1.0.0");

	////flags对象
	//writer.Key("flags");
	//writer.StartObject();
	//writer.EndObject();

	////shapes数组,成员是对象
	//writer.Key("shapes");
	//writer.StartObject();
	//writer.StartArray();

	//writer.EndArray();
	//writer.EndObject();

	//writer.EndObject();

	rapidjson::Document doc;//生成DOM元素
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();//生成一个分配器

	//键值对
	doc.AddMember("version", "1.0.0", allocator);

	//flags对象
	rapidjson::Value flags(rapidjson::kObjectType);
	//flags.AddMember("square", true, allocator);
	//flags.AddMember("triangle", false, allocator);
	doc.AddMember("flags", flags, allocator);

	//shapes数组,成员是对象(复杂json)
	rapidjson::Value shapes(rapidjson::kArrayType);
	rapidjson::Value shape_unit(rapidjson::kObjectType);
	shape_unit.AddMember("label", "xxx", allocator);

	rapidjson::Value shape_line_color(rapidjson::kNullType);
	shape_unit.AddMember("line_color", shape_line_color, allocator);
	shape_unit.AddMember("fill_color", shape_line_color, allocator);

	rapidjson::Value shape_points(rapidjson::kArrayType);
	shape_points.PushBack(1, allocator);
	shape_points.PushBack(1, allocator);
	shape_unit.AddMember("points", shape_points, allocator);

	shape_unit.AddMember("shape_type", "yyyy", allocator);
	shapes.PushBack(shape_unit,allocator);
	//shapes.PushBack(shape_unit1, allocator);
	doc.AddMember("shapes", shapes, allocator);

	//lineColor数组
	rapidjson::Value line_color(rapidjson::kArrayType);
	line_color.PushBack(255, allocator);
	line_color.PushBack(0, allocator);
	line_color.PushBack(0, allocator);
	line_color.PushBack(128, allocator);
	doc.AddMember("lineColor", line_color, allocator);

	//fillColor数组
	rapidjson::Value fill_color(rapidjson::kArrayType);
	fill_color.PushBack(255, allocator);
	fill_color.PushBack(0, allocator);
	fill_color.PushBack(0, allocator);
	fill_color.PushBack(128, allocator);
	doc.AddMember("fillColor", fill_color, allocator);

	//键值对
	//这里要注意string类型的处理
	std::string image_path = "0.jpg";
	rapidjson::Value image_path_data(rapidjson::kStringType);
	image_path_data.SetString(image_path.c_str(), image_path.length(), allocator);
	doc.AddMember("imagePath", image_path_data, allocator);

	//null数据
	rapidjson::Value image_data(rapidjson::kNullType);
	doc.AddMember("imageData", image_data, allocator);

	//键值对
	doc.AddMember("imageHeight", 512, allocator);
	doc.AddMember("imageWidth", 512, allocator);

	rapidjson::StringBuffer buf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	doc.Accept(writer);

	return std::string( buf.GetString());
}

//"points": [
//	[
//		6.0,
//		416.0
//	],
//	[
//		10,
//		10
//	]
//],
std::string write_nest_array()
{
	rapidjson::Document doc;//生成DOM元素
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();//生成一个分配器

	//键值对
	doc.AddMember("version", "1.0.0", allocator);

	//shapes数组,成员是对象(复杂json)
	rapidjson::Value shapes(rapidjson::kArrayType);
	rapidjson::Value shape_unit(rapidjson::kObjectType);
	shape_unit.AddMember("label", "xxx", allocator);

	rapidjson::Value shape_line_color(rapidjson::kNullType);
	shape_unit.AddMember("line_color", shape_line_color, allocator);
	shape_unit.AddMember("fill_color", shape_line_color, allocator);

	rapidjson::Value shape_points(rapidjson::kArrayType);

	rapidjson::Value point_unit1(rapidjson::kArrayType);
	point_unit1.PushBack(6.0, allocator);
	point_unit1.PushBack(416.0, allocator);

	rapidjson::Value point_unit2(rapidjson::kArrayType);
	point_unit2.PushBack(10, allocator);
	point_unit2.PushBack(10, allocator);

	shape_points.PushBack(point_unit1, allocator);
	shape_points.PushBack(point_unit2, allocator);
	shape_unit.AddMember("points", shape_points, allocator);

	shape_unit.AddMember("shape_type", "yyyy", allocator);
	shapes.PushBack(shape_unit, allocator);
	//shapes.PushBack(shape_unit1, allocator);
	doc.AddMember("shapes", shapes, allocator);

	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	doc.Accept(writer);

	return std::string(buf.GetString());
}
