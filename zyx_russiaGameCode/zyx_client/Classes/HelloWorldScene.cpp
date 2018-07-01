/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>
#include <cocos2d.h>
#include "../extensions/cocos-ext.h"
using namespace cocos2d::ui;

Vector<DrawNode*>  vecNow1(9);
Vector<DrawNode*>  vecNow2(9);
Vector<DrawNode*>  vecNow3(9);
Vector<DrawNode*>  vecSave(200);

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// ��ʼ���������ģ�鲢���ӷ�����
	pGameNet = CGameNet::GetInstance();
	pGameNet->init("127.0.0.1", 12080);

	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	label = Label::createWithTTF("Russia Block", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        label->setPosition(Vec2(origin.x + visibleSize.width/4,
                                origin.y + visibleSize.height/2 + 60));

        this->addChild(label, 2);
    }

	CDemoLayer * pDemoLayer = CDemoLayer::create();
	this->addChild(pDemoLayer);

	this->scheduleUpdate();

    return true;
}


void HelloWorld::update(float delta)
{
	/*
		��������: ͨ��ÿ֡���£���������Э�����������̴�������ɿ�MainLoop�������ݣ�
	*/
	pGameNet->MainLoop();

}

void HelloWorld::ShowServerInfo(int blockSprite[3][3], int nextBlockSprite[3][3],int score,int *blockPosi,bool isDown)
{
	/*
	��������: �ڽ�������ʾinfo����
	*/
	//���Ʒ���
	int maxline_row = 10;
	int maxline_column = 20;
	int block_size = 28;
	int distance_x = 300 + (maxline_row/2-2)* block_size;
	int distance_y = 720-20;
	int row = blockPosi[0] + 2;
	int col = blockPosi[1] - 2;

	//��ʾ����
	scoreLabel = Label::createWithSystemFont(to_string(score), "Arial", 24);
	scoreLabel->setPosition(Vec2(distance_x - 250, distance_y -450));

	this->addChild(scoreLabel, 1);
	//������һ������
	for (auto & obj : vecNow1)
	{
		DrawNode * spr = obj;
		spr->clear();
	}

	//����DrawNode
	DrawNode* drawNode_next = DrawNode::create();
	vecNow1.pushBack(drawNode_next);
	this->addChild(drawNode_next, 4);
	for (int i = 0; i< 3; ++i)
	{
		for (int j = 0; j < 3; ++j) {
			if (nextBlockSprite[i][j] == 1) {
				int offset_x = (1 - i)*block_size;
				int offset_y = (j - 1)*block_size;
				Vec2 point[4];
				int distanceX = distance_x - 250;
				int distanceY = distance_y - 150;
				point[0] = Vec2(distanceX + offset_y, distanceY + offset_x);
				point[1] = Vec2(distanceX + offset_y, distanceY + block_size + offset_x);
				point[2] = Vec2(distanceX + block_size + offset_y, distanceY + block_size + offset_x);
				point[3] = Vec2(distanceX + block_size + offset_y, distanceY + offset_x);
				drawNode_next->drawPolygon(point, 4, Color4F(0, 0, 1, 1), 1, Color4F(0, 0, 0, 1));
			}
		}
	}

	//�������䷽��
	for (auto & obj : vecNow2)
	{
		DrawNode * spr = obj;
		spr->clear();
	}

	//����DrawNode
	DrawNode* drawNode = DrawNode::create();
	vecNow2.pushBack(drawNode);
	this->addChild(drawNode, 4);
	for (int i = 0; i< 3; ++i)
	{
		for (int j = 0; j < 3; ++j) {
			if (blockSprite[i][j] == 1) {
				int offset_x = (1 - i)*block_size;
				int offset_y = (j - 1)*block_size;
				Vec2 point[4];
				point[0] = Vec2(distance_x + col * block_size + offset_y, distance_y - row * block_size + offset_x);
				point[1] = Vec2(distance_x + col * block_size + offset_y, distance_y + block_size - row * block_size + offset_x);
				point[2] = Vec2(distance_x + block_size + col * block_size + offset_y, distance_y + block_size - row * block_size + offset_x);
				point[3] = Vec2(distance_x + block_size + col * block_size + offset_y, distance_y - row * block_size + offset_x);
				drawNode->drawPolygon(point,4, Color4F(0, 0, 1, 1), 1, Color4F(0, 0, 0, 1));
			}
		}
	}
}

void HelloWorld::ShowServerInfo2(int blockSprite[20][10], int nextBlockSprite[3][3],int *blockPosi, bool isDown)
{
	/*
	��������: �ڽ�������ʾinfo����
	*/
	//���Ʒ���
	int maxline_row = 10;
	int maxline_column = 20;
	int block_size = 28;
	int distance_x = 300 + (maxline_row / 2 - 2)* block_size;
	int distance_y = 720 - 20;

	//���Ƶ��׷���
	cout << "����" << endl;
	for (auto & obj : vecSave)
	{
		DrawNode * spr = obj;
		spr->clear();
	}
	//����DrawNode
	DrawNode* drawSaveNode = DrawNode::create();
	vecSave.pushBack(drawSaveNode);
	this->addChild(drawSaveNode, 4);
	for (int i = 0; i< 20; ++i)
	{
		for (int j = 0; j < 10; ++j) {
			if (blockSprite[i][j] == 1) {
				int offset_x = (1 - i)*block_size;
				int offset_y = (j - 1)*block_size;
				int col2 = -2;
				int row2 = 2;
				Vec2 point[4];
				point[0] = Vec2(distance_x + col2 * block_size + offset_y, distance_y - row2 * block_size + offset_x);
				point[1] = Vec2(distance_x + col2 * block_size + offset_y, distance_y + block_size - row2 * block_size + offset_x);
				point[2] = Vec2(distance_x + block_size + col2 * block_size + offset_y, distance_y + block_size - row2 * block_size + offset_x);
				point[3] = Vec2(distance_x + block_size + col2 * block_size + offset_y, distance_y - row2 * block_size + offset_x);
				drawSaveNode->drawPolygon(point, 4, Color4F(0, 0, 1, 1), 1, Color4F(0, 0, 0, 1));
			}
		}
	}
}

void HelloWorld::ShowRecordScore(bool gameIsOver) {
	
	if (gameIsOver) {
		auto exchage_bg = Sprite::create("bg_normal.png");
		exchage_bg->setPosition(Vec2(300, 400));
		exchage_bg->setScale(1,1);
		this->addChild(exchage_bg,1);


		/**
		*  �����ؼ�
		*  1.Size �����Ĵ�С
		*  2.Scale9Sprite ����򱳾����������Ĵ�С��������򱳾��Ĵ�С���������ǲ�û�д�������������Լ�������һ������򱳾���
		*/
		auto editBox = EditBox::create(Size(400, 70), Scale9Sprite::create("exchage_input_frame.png"));
		editBox->setPosition(Vec2(300, 250));
		editBox->setMaxLength(8);   //����������������ٸ��ַ�
		editBox->setText("Please enter your name here!"); //��ʼ������
		editBox->setFontColor(Color3B(255, 0, 0));   //������ɫ
		editBox->setFontSize(20);   //���ֵĴ�С��ע�⣡����  �������û���κ�Ч������Ҳ��ΪʲôҪ�Լ�����������һ������
		exchage_bg->addChild(editBox);


		//�һ���ť
		auto Exchangebuttom = MenuItemImage::create("exchage_button.png", "exchage_button.png");
		Exchangebuttom->setPosition(Vec2(300, 50));
		exchage_bg->setScale(0.7, 0.8);
		Exchangebuttom->setCallback([&, editBox](Ref*obj) {

			//ȡ���������������֣����������̨
			log("%s", editBox->getText());
		});


		auto menu = Menu::create(Exchangebuttom, NULL);
		menu->setPosition(Point::ZERO);
		exchage_bg->addChild(menu);
	}
}
