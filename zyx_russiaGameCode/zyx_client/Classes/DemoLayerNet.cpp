#include "DemoLayerNet.h"
using namespace rapidjson;

void C2GSUpdatePos(const char * msg)
{
	// ����Ϣ���͸�����ˣ��÷���������
	CGameNet::GetInstance()->SendMsg(msg);
}

void GS2CShowServerInfo(const char * msg)
{
	/*
		�������������շ���˷�����Ϣ
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

	// ��ȡ����˷��ص�json�ļ��е�action�ֶΣ�action���ַ��ͣ���ʾ��������
	const rapidjson::Value &action = pJsonDoc["action"];
	// ��ȡ����˷��ص�json�ļ��е�flag�ֶΣ�flag��bool�ͣ���ʾ�Ƿ�ͬ��˴β���
	const rapidjson::Value &flag = pJsonDoc["flag"];


	// ��ȡ��ǰ��ʾ��scene(Ҳ���� HelloWorldScene�е�HelloWorld) 
	HelloWorld* pCurrentScene = (HelloWorld*)CCDirector::getInstance()->getRunningScene();

	if (action == "left" && flag == true) {
		cout << "\n�յ�������������Ϣ������ǰ���߼��������ƶ�";
	}
	else if (action == "right"&& flag == true) {
		cout << "\n�յ�������������Ϣ������ǰ���߼��������ƶ�";
	}
	else if (action == "down"&& flag == true) {
		cout << "\n�յ�������������Ϣ������ǰ���߼��������ƶ�";
	}
	else if (action == "rotate"&& flag == true) {
		cout << "\n�յ�������������Ϣ������ǰ���߼�������";
	}
	else if (action == "currentBlock") {
		//cout << "\n�յ�������������Ϣ���յ��������ķ���������Ϣ:" << endl;
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

