#include "DemoLayerNet.h"
using namespace rapidjson;

void C2GSUpdatePos(const char * msg)
{
	// 将信息发送给服务端，让服务端来检测
	CGameNet::GetInstance()->SendMsg(msg);
}

void GS2CShowServerInfo(const char * msg)
{
	/*
		功能描述：接收服务端返回信息
	*/
	Document pJsonDoc;
	pJsonDoc.Parse<0>(msg);
	int blockSpriteArray[3][3];
	int nextBlockSpriteArray[3][3];
	int blockSpriteArray2[20][10];
	int blockPosiArray[2];
	int scoreNum;
	bool isDown;
	bool gameIsOver;


	if (pJsonDoc.HasParseError()) {
		cout << "error, when parse json data in GS2CShowServerInfo";
		return;
	}

	if (!pJsonDoc.IsObject())
		return;

	if (!pJsonDoc.HasMember("flag")) {
		cout << "error, not find key word action in json data in GS2CShowServerInfo";
		return;
	}

	// 获取服务端返回的json文件中的action字段，action是字符型，表示操作名称
	const rapidjson::Value &action = pJsonDoc["action"];
	// 获取服务端返回的json文件中的flag字段，flag是bool型，表示是否同意此次操作
	const rapidjson::Value &flag = pJsonDoc["flag"];


	// 获取当前显示的scene(也即是 HelloWorldScene中的HelloWorld) 
	HelloWorld* pCurrentScene = (HelloWorld*)CCDirector::getInstance()->getRunningScene();

	if (action == "left" && flag == true) {
		cout << "\n收到服务器返回消息，处理前端逻辑，向左移动";
	}
	else if (action == "right"&& flag == true) {
		cout << "\n收到服务器返回消息，处理前端逻辑，向右移动";
	}
	else if (action == "down"&& flag == true) {
		cout << "\n收到服务器返回消息，处理前端逻辑，向下移动";
	}
	else if (action == "rotate"&& flag == true) {
		cout << "\n收到服务器返回消息，处理前端逻辑，变形";
	}
	else if (action == "currentBlock") {
		//cout << "\n收到服务器返回消息，收到服务器的方块数组信息:" << endl;
		rapidjson::Value &block = pJsonDoc["flag"];

		rapidjson::Value & isdown = block["isDown"];
		if (isdown.IsBool()) {
			isDown = isdown.GetBool();
		}

		rapidjson::Value & blockSprite = block["blockSprite"];
		if (blockSprite.IsArray()) {
			for (size_t i = 0; i < blockSprite.Size(); ++i) {
				rapidjson::Value & v = blockSprite[i];
				if (v.IsArray()) {
					for (size_t j = 0; j < v.Size(); ++j) {
						rapidjson::Value & w = v[j];
						if (isDown) {
							blockSpriteArray2[i][j] = w.GetInt();
						}
						else {
							blockSpriteArray[i][j] = w.GetInt();
						}
					}
				}
			}
		}

		rapidjson::Value & nextBlock = block["nextblockSprite"];
		if (nextBlock.IsArray()) {
			for (size_t _i = 0; _i < nextBlock.Size(); ++_i) {
				rapidjson::Value & x = nextBlock[_i];
				if (x.IsArray()) {
					for (size_t _j = 0; _j < x.Size(); ++_j) {
						rapidjson::Value & y = x[_j];
						nextBlockSpriteArray[_i][_j] = y.GetInt();
					}
				}
			}
		}

		rapidjson::Value & blockPosi = block["blockPosi"];
		if (blockPosi.IsArray()) {
			for (size_t k = 0; k < blockPosi.Size(); ++k) {
				rapidjson::Value & z = blockPosi[k];
				blockPosiArray[k] = z.GetInt();
			}
		}

		rapidjson::Value & score = block["score"];
		if (score.IsInt()) {
			rapidjson::Value & c = score;
			scoreNum = c.GetInt();
		}

		rapidjson::Value & gameOver = block["gameOver"];
		if (gameOver.IsBool()) {
			gameIsOver = gameOver.GetBool();
		}

		if (isDown) {
			pCurrentScene->ShowServerInfo2(blockSpriteArray2, nextBlockSpriteArray, blockPosiArray, isDown);
		}
		else {
			pCurrentScene->ShowServerInfo(blockSpriteArray, nextBlockSpriteArray, scoreNum, blockPosiArray, isDown);
		}

		if (gameIsOver) {
			cout << gameIsOver;
			pCurrentScene->ShowRecordScore(gameIsOver);
		}
	}
}

