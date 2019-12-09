#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

int CreateXml()
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(rot);

	rapidxml::xml_node<>* root_node = doc.allocate_node(rapidxml::node_element, "message", NULL);
	doc.append_node(root_node);

	root_node->append_node(doc.allocate_node(rapidxml::node_element, "message_id", "I"));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "system_byte", "AOI_01-COMPONENT_DC_REPORT-20170603142001789"));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "eqp_id", "AOI_01"));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "component_id", "163700002AC01"));

	rapidxml::xml_node<>* data_list_node = doc.allocate_node(rapidxml::node_element, "data_list", NULL);
	root_node->append_node(data_list_node);

	rapidxml::xml_node<>* data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "ITO_RESULT"));
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", "NG"));
	data_list_node->append_node(data_node);

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	std::cout << text << std::endl;

	std::ofstream out("report.xml");
	out << doc;

	return 0;
}

void GetDefectInfo(int num, string& s_value_code, string& s_value_x, string& s_value_y)
{
	switch (num)
	{
	case 1:
	    {
	    	s_value_code = "c1";
	    	s_value_x = "x1";
	    	s_value_y = "y1";
	    }
		break;
	case 2:
	    {
	    	s_value_code = "c2";
	    	s_value_x = "x2";
	    	s_value_y = "y2";
	    }
		break;
	case 3:
	    {
	    	s_value_code = "c3";
	    	s_value_x = "x3";
	    	s_value_y = "y3";
	    }
		break;
	case 4:
	    {
	    	s_value_code = "c4";
	    	s_value_x = "x4";
	    	s_value_y = "y4";
	    }
		break;
	case 5:
	    {
		    s_value_code = "c5";
		    s_value_x = "x5";
		    s_value_y = "y5";
	    }
		break;
	default:
	    {
	    	s_value_code = "";
	    	s_value_x = "";
	    	s_value_y = "";
	    }
	}
}

std::string ReportXml(const std::string &eqp_id, const std::string & component_id, const std::string ito_result, const std::string& aoi_result)
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
	doc.append_node(rot);

	rapidxml::xml_node<>* root_node = doc.allocate_node(rapidxml::node_element, "message", NULL);
	doc.append_node(root_node);

	//Time oTime = current_datetime();
	//string cur_time = to_datetime2(oTime);
	string cur_time = "20190820101923";

	string system_byte = eqp_id;
	system_byte += "-COMPONENT_DC_REPORT-";
	system_byte += cur_time;

	root_node->append_node(doc.allocate_node(rapidxml::node_element, "message_id", "I"));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "system_byte", system_byte.c_str()));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "eqp_id", eqp_id.c_str()));
	root_node->append_node(doc.allocate_node(rapidxml::node_element, "component_id", component_id.c_str()));

	rapidxml::xml_node<>* data_list_node = doc.allocate_node(rapidxml::node_element, "data_list", NULL);
	root_node->append_node(data_list_node);

	rapidxml::xml_node<>* data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "ITO_RESULT"));
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", ito_result.c_str()));
	data_list_node->append_node(data_node);

	data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_RESULT"));
	data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", aoi_result.c_str()));
	data_list_node->append_node(data_node);

	std::string s_value_code1 = "101";
	std::string s_value_x1 = "5";
	std::string s_value_y1 = "7";
	std::string s_value_code2 = "102";
	std::string s_value_x2 = "50";
	std::string s_value_y2 = "60";

	if (!s_value_code1.empty())
	{
		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT1"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_code1.c_str()));
		data_list_node->append_node(data_node);

		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT1_X"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_x1.c_str()));
		data_list_node->append_node(data_node);

		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT1_Y"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_y1.c_str()));
		data_list_node->append_node(data_node);
	}

	if (!s_value_code2.empty())
	{
		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT2"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_code2.c_str()));
		data_list_node->append_node(data_node);

		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT2_X"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_x2.c_str()));
		data_list_node->append_node(data_node);

		data_node = doc.allocate_node(rapidxml::node_element, "data", NULL);
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item", "API_DEFECT2_Y"));
		data_node->append_node(doc.allocate_node(rapidxml::node_element, "item_data", s_value_y2.c_str()));
		data_list_node->append_node(data_node);
	}

	

	std::string text;
	rapidxml::print(std::back_inserter(text), doc, 0);

	return text;
}

int CreateXml_weixinnuo()
{
	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* root_node = doc.allocate_node(rapidxml::node_element, "PANEL_INFO", NULL);
	doc.append_node(root_node);

	rapidxml::xml_node<>* root_node_cdata = doc.allocate_node(rapidxml::node_cdata, "PANEL_INFO", "EQUIPMENT_ID^UNIT_ID:");
	root_node->append_node(root_node_cdata);

	rapidxml::xml_node<>* gamma_node = doc.allocate_node(rapidxml::node_element, "GAMMA", NULL);
	rapidxml::xml_node<>* gamma_node_cdata = doc.allocate_node(rapidxml::node_cdata, "GAMMA", "GAMMA_DEFECT_NO^GAMMA_IMAGE_NAME:");
	gamma_node->append_node(gamma_node_cdata);
	root_node->append_node(gamma_node);

	rapidxml::xml_document<> doc_end;
	rapidxml::xml_node<>* root_node_end = doc_end.allocate_node(rapidxml::node_element, "EOF", NULL);
	doc_end.append_node(root_node_end);

	std::ofstream out("report1.xml");
	out << doc;

	out << doc_end;
	//std::string text;
	//rapidxml::print(std::back_inserter(text), doc_end, 0);
	//out << text;

	out.close();
	return 0;
}
