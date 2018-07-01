#include "DemoLayer.h"

bool CDemoLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	// 设置可触摸
	setTouchEnabled(true);
	// 设置为单点模式
	setTouchMode(kCCTouchesOneByOne);

	//创建游戏蓝色背景图
	CCSprite * pBackground = CCSprite::create("background.png");
	pBackground->setPosition(ccp(480, 320));
	this->addChild(pBackground);

	//画出场景的网格图
	maxline_row = 10;
	maxline_column = 20;
	block_size = 28;
	distance_x = 300;
	distance_y = 720 - block_size * maxline_column - 20;
	cout << "画网格图";
	//创建DrawNode
	DrawNode* drawNode = DrawNode::create();
	this->addChild(drawNode);
	for (int i = 0; i<maxline_column + 1; i++) {
		drawNode->drawSegment(Vec2(0 + distance_x, i * block_size + distance_y), Vec2(maxline_row * block_size + distance_x, i * block_size + distance_y), 1, Color4F(0, 0, 0, 1));//绘制21条横线
	}
	for (int i = 0; i<maxline_row + 1; i++) {
		drawNode->drawSegment(Vec2(i * block_size + distance_x, 0 + distance_y), Vec2(i * block_size + distance_x, maxline_column * block_size + distance_y), 1, Color4F(0, 0, 0, 1));//绘制11条竖线
	}


	// 创建按钮并加到layer
	CCSprite * pLeftButton = CCSprite::create("left_arrow.png");
	pLeftButton->setPosition(ccp(100, 80));
	pLeftButton->setScale(0.4, 0.4);
	pLeftButton->setTag(left);
	this->addChild(pLeftButton);

	// 创建按钮并加到layer
	CCSprite * pRightButton = CCSprite::create("right_arrow.png");
	pRightButton->setPosition(ccp(230, 80));
	pRightButton->setScale(0.4, 0.4);
	pRightButton->setTag(right);
	this->addChild(pRightButton);

	// 创建按钮并加到layer
	CCSprite * pRotateButton = CCSprite::create("rotate.png");
	pRotateButton->setPosition(ccp(360, 80));
	pRotateButton->setScale(0.4, 0.4);
	pRotateButton->setTag(rotate);
	this->addChild(pRotateButton);

	// 创建按钮并加到layer
	CCSprite * pDownButton = CCSprite::create("down_arrow.png");
	pDownButton->setPosition(ccp(490, 80));
	pDownButton->setScale(0.4, 0.4);
	pDownButton->setTag(down);
	this->addChild(pDownButton);

	// 创建旁边的信息显示，下一个图形
	CCSprite * nextShape = CCSprite::create("bg_small.png");
	nextShape->setPosition(ccp(150, 550));
	nextShape->setScale(1.7, 0.4);
	this->addChild(nextShape);

	// 创建旁边的信息显示，得分
	CCSprite * scoreShow = CCSprite::create("bg_small.png");
	scoreShow->setPosition(ccp(150, 250));
	scoreShow->setScale(1.7, 0.4);
	this->addChild(scoreShow);

	Label* lb1 = Label::createWithSystemFont("Next Shape:", "Arial", 24);
	lb1->setPosition(ccp(150, 670));
	this->addChild(lb1);

	Label* lb2 = Label::createWithSystemFont("Score:", "Arial", 24);
	lb2->setPosition(ccp(150, 370));
	this->addChild(lb2);


	//blockmanager = BlockManager::create();
	//this->addChild(blockmanager);
	initGame();

	this->schedule(schedule_selector(CDemoLayer::updateGame),0.5, -1, 0);

	return true;
}

void CDemoLayer::changeBlock(CCObject* pSender)
{
	/*blockmanager->changeBlock();*/
}

void CDemoLayer::initGame()
{
	/*初始化游戏*/
	cout << "\n初始化游戏";
	packInfo("initGame");
}

void CDemoLayer::updateGame(float dt)
{
	/*更新游戏*/;
	packInfo("updateGame");
}

bool CDemoLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
	CCSprite *pLeftButton = (CCSprite *)getChildByTag(left);
	CCSprite *pRightButton = (CCSprite *)getChildByTag(right);
	CCSprite *pRotateButton = (CCSprite *)getChildByTag(rotate);
	CCSprite *pDownButton = (CCSprite *)getChildByTag(down);

	CCPoint pTouchPoint = touch->getLocation();

	if (pLeftButton->boundingBox().containsPoint(pTouchPoint)) {
		pLeftButton->setScale(0.44, 0.44);
		return true;
	}
	else if (pRightButton->boundingBox().containsPoint(pTouchPoint)) {
		pRightButton->setScale(0.44, 0.44);
		return true;
	}
	else if (pRotateButton->boundingBox().containsPoint(pTouchPoint)) {
		pRotateButton->setScale(0.44, 0.44);
		return true;
	}
	else if (pDownButton->boundingBox().containsPoint(pTouchPoint)) {
		pDownButton->setScale(0.44, 0.44);
		return true;
	}
	return false;
}

void CDemoLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
	//CCSprite *pFirstCircle = (CCSprite *)getChildByTag(first);
	//CCSprite *pSecondCircle = (CCSprite *)getChildByTag(second);

	//CCPoint pTouchPoint = touch->getLocation();
	//CCPoint pPointDelta = touch->getDelta();

	//// 判断点击在pFirstCircle精灵上时才可进行触摸移动
	//if (pFirstCircle->boundingBox().containsPoint(pTouchPoint)) {
	//	pFirstCircle->setPosition(pFirstCircle->getPosition() + pPointDelta);
	//	// 实时将相关信息进行打包成json
	//	packInfo(pFirstCircle, pSecondCircle);
	//}
}

void CDemoLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
	CCSprite *pLeftButton = (CCSprite *)getChildByTag(left);
	CCSprite *pRightButton = (CCSprite *)getChildByTag(right);
	CCSprite *pRotateButton = (CCSprite *)getChildByTag(rotate);
	CCSprite *pDownButton = (CCSprite *)getChildByTag(down);

	CCPoint pTouchPoint = touch->getLocation();

	if (pLeftButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n点击左按钮";
		pLeftButton->setScale(0.4, 0.4);
			// 实时将相关信息进行打包成json
		packInfo("left");
	}
	else if (pRightButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n点击右按钮";
		pRightButton->setScale(0.4, 0.4);
		packInfo("right");
	}
	else if (pRotateButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n点击变形按钮";
		pRotateButton->setScale(0.4, 0.4);
		packInfo("rotate");
	}
	else if (pDownButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n点击下按钮";
		pDownButton->setScale(0.4, 0.4);
		packInfo("down");
	}
}

void CDemoLayer::packInfo(char *action)
{
	/* 
	功能描述： 将需要向服务端传输的信息进行整合，这里整合成了json文件，整合完后
	*/

	//生成Json串
	rapidjson::Document jsonDoc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();
	jsonDoc.SetObject();

	//添加属性
	//jsonDoc.AddMember("picture", picture->getContentSize().width / 2, allocator);
	if (action == "left") {
		jsonDoc.AddMember("action", "move", allocator);
		jsonDoc.AddMember("actionType", "left", allocator);
	}
	else if (action == "right") {
		jsonDoc.AddMember("action", "move", allocator);
		jsonDoc.AddMember("actionType", "right", allocator);
	}
	else if (action == "down") {
		jsonDoc.AddMember("action", "move", allocator);
		jsonDoc.AddMember("actionType", "down", allocator);
	}
	else if (action == "rotate") {
		jsonDoc.AddMember("action", "move", allocator);
		jsonDoc.AddMember("actionType", "rotate", allocator);
	}
    if(action == "initGame") {
		jsonDoc.AddMember("action", "init", allocator);
		jsonDoc.AddMember("actionType", "initGame", allocator);
	}
	if (action == "updateGame") {
		jsonDoc.AddMember("action", "update", allocator);
		jsonDoc.AddMember("actionType", "updateGame", allocator);
	}

	//生成array
	/*rapidjson::Value moveArray(rapidjson::kArrayType);
	moveArray.PushBack(action, allocator);
	jsonDoc.AddMember("moveData", moveArray, allocator);*/

	//生成array
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	jsonDoc.Accept(writer);

	std::string strJson = buffer.GetString();
	C2GSUpdatePos(strJson.c_str());


}
