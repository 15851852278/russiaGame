# -*- coding: utf-8 -*-
"""
记录登录
"""
import dbctrl.saveobject
import timecontrol
import pubcore
import pubdefines
import pubglobalmanager
import math

class CDemo(dbctrl.saveobject.CSaveData):
    def GetKey(self):
        return "loginrecord"

    def Init(self):
        super(CDemo, self).Init()
        self.CheckTimer()

    def CheckTimer(self):
        timecontrol.Remove_Call_Out("loginrecord")
        pubdefines.FormatPrint("定时器统计：目前总连接记录 %s" % self.m_Data.get("total", 0))
        timecontrol.Call_Out(pubcore.Functor(self.CheckTimer), 300, "loginrecord")

    def NewItem(self):
        self.m_Data.setdefault("total", 0)
        self.m_Data["total"] += 1
        self.Save()

    def CalPos(self, oClient, dData):
        r1 = dData["radius1"]
        r2 = dData["radius2"]
        lPos1 = dData["pos1"]
        lPos2 = dData["pos2"]
        iDicstacne = int(math.sqrt(pow(lPos1[0]-lPos2[0],2) + pow(lPos1[1]-lPos2[1],2)))
        dReturn = {
            "action": "show",
            "flag" : iDicstacne <= r1+r2,
        }
        oClient.Send(dReturn)

def Init():
    if pubglobalmanager.GetGlobalManager("demo"):
        return
    oManger = CDemo()
    pubglobalmanager.SetGlobalManager("demo", oManger)
    oManger.Init()

def Record():
    pubglobalmanager.CallManagerFunc("demo", "NewItem")

def OnCommand(oClient, dData):
    pubglobalmanager.CallManagerFunc("demo", "CalPos", oClient, dData)
        