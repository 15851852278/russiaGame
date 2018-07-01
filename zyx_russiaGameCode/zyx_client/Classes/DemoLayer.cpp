#include "DemoLayer.h"

bool CDemoLayer::init() {
	if (!CCLayer::init()) {
		return false;
	}
	// ���ÿɴ���
	setTouchEnabled(true);
	// ����Ϊ����ģʽ
	setTouchMode(kCCTouchesOneByOne);

	//������Ϸ��ɫ����ͼ
	CCSprite * pBackground = CCSprite::create("background.png");
	pBackground->setPosition(ccp(480, 320));
	this->addChild(pBackground);

	//��������������ͼ
	maxline_row = 10;
	maxline_column = 20;
	block_size = 28;
	distance_x = 300;
	distance_y = 720 - block_size * maxline_column - 20;
	cout << "������ͼ";
	//����DrawNode
	DrawNode* drawNode = DrawNode::create();
	this->addChild(drawNode);
	for (int i = 0; i<maxline_column + 1; i++) {
		drawNode->drawSegment(Vec2(0 + distance_x, i * block_size + distance_y), Vec2(maxline_row * block_size + distance_x, i * block_size + distance_y), 1, Color4F(0, 0, 0, 1));//����21������
	}
	for (int i = 0; i<maxline_row + 1; i++) {
		drawNode->drawSegment(Vec2(i * block_size + distance_x, 0 + distance_y), Vec2(i * block_size + distance_x, maxline_column * block_size + distance_y), 1, Color4F(0, 0, 0, 1));//����11������
	}


	// ������ť���ӵ�layer
	CCSprite * pLeftButton = CCSprite::create("left_arrow.png");
	pLeftButton->setPosition(ccp(100, 80));
	pLeftButton->setScale(0.4, 0.4);
	pLeftButton->setTag(left);
	this->addChild(pLeftButton);

	// ������ť���ӵ�layer
	CCSprite * pRightButton = CCSprite::create("right_arrow.png");
	pRightButton->setPosition(ccp(230, 80));
	pRightButton->setScale(0.4, 0.4);
	pRightButton->setTag(right);
	this->addChild(pRightButton);

	// ������ť���ӵ�layer
	CCSprite * pRotateButton = CCSprite::create("rotate.png");
	pRotateButton->setPosition(ccp(360, 80));
	pRotateButton->setScale(0.4, 0.4);
	pRotateButton->setTag(rotate);
	this->addChild(pRotateButton);

	// ������ť���ӵ�layer
	CCSprite * pDownButton = CCSprite::create("down_arrow.png");
	pDownButton->setPosition(ccp(490, 80));
	pDownButton->setScale(0.4, 0.4);
	pDownButton->setTag(down);
	this->addChild(pDownButton);

	// �����Աߵ���Ϣ��ʾ����һ��ͼ��
	CCSprite * nextShape = CCSprite::create("bg_small.png");
	nextShape->setPosition(ccp(150, 550));
	nextShape->setScale(1.7, 0.4);
	this->addChild(nextShape);

	// �����Աߵ���Ϣ��ʾ���÷�
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
	/*��ʼ����Ϸ*/
	cout << "\n��ʼ����Ϸ";
	packInfo("initGame");
}

void CDemoLayer::updateGame(float dt)
{
	/*������Ϸ*/;
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

	//// �жϵ����pFirstCircle������ʱ�ſɽ��д����ƶ�
	//if (pFirstCircle->boundingBox().containsPoint(pTouchPoint)) {
	//	pFirstCircle->setPosition(pFirstCircle->getPosition() + pPointDelta);
	//	// ʵʱ�������Ϣ���д����json
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
		cout << "\n�����ť";
		pLeftButton->setScale(0.4, 0.4);
			// ʵʱ�������Ϣ���д����json
		packInfo("left");
	}
	else if (pRightButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n����Ұ�ť";
		pRightButton->setScale(0.4, 0.4);
		packInfo("right");
	}
	else if (pRotateButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n������ΰ�ť";
		pRotateButton->setScale(0.4, 0.4);
		packInfo("rotate");
	}
	else if (pDownButton->boundingBox().containsPoint(pTouchPoint)) {
		cout << "\n����°�ť";
		pDownButton->setScale(0.4, 0.4);
		packInfo("down");
	}
}

void CDemoLayer::packInfo(char *action)
{
	/* 
	���������� ����Ҫ�����˴������Ϣ�������ϣ��������ϳ���json�ļ����������
	*/

	//����Json��
	rapidjson::Document jsonDoc;
	rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();
	jsonDoc.SetObject();

	//�������
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

	//����array
	/*rapidjson::Value moveArray(rapidjson::kArrayType);
	moveArray.PushBack(action, allocator);
	jsonDoc.AddMember("moveData", moveArray, allocator);*/

	//����array
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	jsonDoc.Accept(writer);

	std::string strJson = buffer.GetString();
	C2GSUpdatePos(strJson.c_str());


}
