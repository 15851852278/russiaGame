#pragma once
#include <functional>
#include <map>
#include <string>
#include <iostream>
#include "DemoLayerNet.h"
using namespace std;

function<void(const char* sJson)> callFunc;


// ����Э���봦������Ӧ��ϵ����
const map<string, function<void(const char* sJson)>>::value_type init_value[] = {
	map<string, function<void(const char* sJson)>>::value_type("left", GS2CShowServerInfo),
	map<string, function<void(const char* sJson)>>::value_type("right", GS2CShowServerInfo),
	map<string, function<void(const char* sJson)>>::value_type("down", GS2CShowServerInfo),
    map<string, function<void(const char* sJson)>>::value_type("rotate", GS2CShowServerInfo),
	map<string, function<void(const char* sJson)>>::value_type("currentBlock", GS2CShowServerInfo),
};

// �ö�Ӧ��ϵ�����ʼ�� Э���봦������Ӧ��ϵ�ֵ�
map<string, function<void(const char* sJson)>> funcMap(init_value, init_value + 5);
map<string, function<void(const char* sJson)>>::iterator funcIter;



