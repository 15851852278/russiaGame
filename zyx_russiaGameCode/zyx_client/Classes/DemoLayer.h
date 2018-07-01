#pragma once
#include "cocos2d.h"
#include <iostream>
#include "DemoLayerNet.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
USING_NS_CC;

class CDemoLayer :public CCLayer
{
public:
	enum SpriteEnum {
		left, right, rotate, down
	};

	CREATE_FUNC(CDemoLayer);
	bool init();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void changeBlock(CCObject* pSender);

	void initGame();
	void updateGame(float dt);

	void packInfo(char *action);

private:
	int maxline_row;//网格行数
	int maxline_column;//网格列数
	int block_size;//网格大小
	int distance_x;//边框距离
	int distance_y;//边框距离
};

