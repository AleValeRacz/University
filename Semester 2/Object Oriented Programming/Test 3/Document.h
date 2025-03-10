#pragma once
#include <string>
using namespace std;
class Document
{
private:
	string name, keywords, content;
public:
	Document(string name, string keywords, string content) : name{ name }, keywords{ keywords }, content{ content } {};
	~Document() {};
	string get_name() { return name; }
	string get_keywords() { return keywords; }
	string get_content() { return content; }
	string toString() { return name + "; " + keywords; }
};

