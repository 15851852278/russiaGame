# -*- coding: utf-8 -*-
"""
俄罗斯方块逻辑，主要有四个目标：移动、旋转、消除逻辑，利用定时器实现自动下落过程
author:zyx  date:2018.6.16
"""
import dbctrl.saveobject
import timecontrol
import pubcore
import pubdefines
import pubglobalmanager
import math

from Tkinter import *
from random import *
import thread
from tkMessageBox import showinfo
import threading
from time import sleep

class CTetris(dbctrl.saveobject.CSaveData):

    #返回客户端的方块数组信息
    blockArrayInfo = []
    #返回客户端的方块数组位置
    blockArrayPosi = []
    #返回客户端的方块信息
    returnArrayInfo = None

    #是否向左移动
    isMoveLeft = True
    #是否向右移动
    isMoveRight = True
    #是否向下移动
    isMoveDown = True
    #是否变形
    isRotate = True

    #是否开始
    start = True
    #是否到达底部
    isDown = True

    #边界
    tag = True

    #玩家
    player = None
    #得分
    score = 0
    #下一个图形
    nextBrick = None
    #下一个方块数组
    nextArr = None
    #游戏结束
    gameOver = False

    #行和列
    rows = 20
    cols = 10
    
    #几种方块
    brick = [
      
      [
           [
               [1,1,1],
               [0,0,1],
               [0,0,0]
           ],
           [
                [0,0,1],
                [0,0,1],
                [0,1,1]
           ],
           [
                [0,0,0],
                [1,0,0],
                [1,1,1]
           ],
           [
                [1,1,0],
                [1,0,0],
                [1,0,0]
           ]
      ],
      [
           [
                 [0,0,0],
                 [0,1,1],
                 [0,1,1]
           ],
           [
                  [0,0,0],
                  [0,1,1],
                  [0,1,1]
           ],
           [
                  [0,0,0],
                  [0,1,1],
                  [0,1,1]
           ],
           [
                  [0,0,0],
                  [0,1,1],
                  [0,1,1]
           ]         
      ],
      [
           [
                  [1,1,1],
                  [0,1,0],
                  [0,1,0]
           ],
           [
                  [0,0,1],
                  [1,1,1],
                  [0,0,1]
           ],
           [
                  [0,1,0],
                  [0,1,0],
                  [1,1,1]
           ],
           [
                  [1,0,0],
                  [1,1,1],
                  [1,0,0]
           ]
      ],
      [
           [
                  [0,1,0],
                  [0,1,0],
                  [0,1,0]
           ],
           [
                  [0,0,0],
                  [1,1,1],
                  [0,0,0]
           ],
           [
                  [0,1,0],
                  [0,1,0],
                  [0,1,0]
           ],
           [
                  [0,0,0],
                  [1,1,1],
                  [0,0,0]
           ]
      ]
    ]
    
    #当前的方块
    curBrick = None
    #当前方块数组
    arr = None
    #当前方块形状
    shape = -1
    #当前方块的行和列（最左上角）
    curRow = -10
    curCol = -10
    #背景
    back = list()
    #格子
    gridBack = list()

    def GetKey(self):
        return "loginrecord"
    
    #初始化
    def Init(self):
        super(CTetris, self).Init()
        self.CheckTimer()

        for i in range(0,self.rows):
          
          self.back.insert(i,list())
          self.gridBack.insert(i,list())
        
        for i in range(0,self.rows):
          
          for j in range(0,self.cols):
            
            self.back[i].insert(j,0)
            self.gridBack[i].insert(j,0)
    
      #绘制游戏的格子
    def drawRect(self):
        
        for i in range(0,self.rows):
              
              for j in range(0,self.cols):
                
              
                if self.back[i][j]==1:
                  
                  #self.canvas.itemconfig(self.gridBack[i][j],fill="blue",outline="white")
                  self.gridBack[i][j] = 1
                  
                elif self.back[i][j]==0:
                  
                  #self.canvas.itemconfig(self.gridBack[i][j],fill="black",outline="white")
                  self.gridBack[i][j] = 0
                  
        #绘制当前正在运动的方块
        if self.curRow!=-10 and self.curCol!=-10:
          
          for i in range(0,len(self.arr)):
            
            for j in range(0,len(self.arr[i])):
              
              if self.arr[i][j]==1:          
                
                #self.canvas.itemconfig(self.gridBack[self.curRow+i][self.curCol+j],fill="blue",outline="white")
                self.gridBack[self.curRow+i][self.curCol+j] = 1

        #判断方块是否已经运动到达底部
        if self.isDown:
          
          for i in range(0,3):
            
            for j in range(0,3):
              
              if self.arr[i][j]!=0:
                
                self.back[self.curRow+i][self.curCol+j] = self.arr[i][j]
                
          #判断整行消除
          self.removeRow()

          self.isDead()

          #获得下一个方块  
          self.getCurBrick() 
    #判断是否有整行需要消除
    def removeRow(self):
        
        for i in range(0,self.rows):
 
          self.tag1 = True      
          for j in range(0,self.cols):
            
            if self.back[i][j]==0:
              
              self.tag1 = False
              break
          
          if self.tag1==True:
            
            self.score+=100
            #从上向下挪动
            for m in xrange(i-1,0,-1):
              
              for n in range(0,self.cols):
                
                self.back[m+1][n] = self.back[m][n]
          
    #获得当前的方块
    def getCurBrick(self):

        self.curBrick = randint(0,len(self.brick)-1)

        if self.nextBrick!=None and self.curBrick!=self.nextBrick:
          self.curBrick = self.nextBrick

        self.nextBrick = randint(0,len(self.brick)-1)
 
        self.shape = 0
        #当前方块数组
        self.arr = self.brick[self.curBrick][self.shape]

        #下一个方块数组
        self.nextArr = self.brick[self.nextBrick][self.shape]

        self.curRow = 0
        self.curCol = 1
        
        #是否到底部为False
        self.isDown = False
      

        
    #监听客户端鼠标的输入
    def onChangeEvent(self,oClient,event):
        
        #未开始，不必监听键盘输入
        if self.start == False:
          
          return

        #记录原来的值
        tempCurCol = self.curCol
        tempCurRow = self.curRow
        tempShape = self.shape  
        tempArr = self.arr
        direction = -1
        
        if event=="left":
          
          #左移
          self.curCol-=1
          direction = 1
        elif event=="rotate":
          #变化方块的形状
          self.shape+=1
          direction = 2
          
          if self.shape>=4:
            
            self.shape=0
          self.arr = self.brick[self.curBrick][self.shape]
        elif event=="right":
          
          direction = 3
          #右移
          self.curCol+=1
        elif event=="down":
          
          direction = 4
          #下移
          self.curRow+=1
          
        if self.isEdge(direction)==False:
          
          self.curCol = tempCurCol
          self.curRow = tempCurRow
          self.shape = tempShape
          self.arr = tempArr
            
        self.drawRect()
          
        return True
        
    #判断当前方块是否到达边界
    def isEdge(self,direction):
        
        self.tag = True
        
        #向左，判断边界
        if direction==1:
          
          for i in range(0,3):
            
            for j in range(0,3):
              
              if self.arr[j][i]!=0 and (self.curCol+i<0 or self.back[self.curRow+j][self.curCol+i]!=0):
                
                self.tag = False
                break
        #向右，判断边界
        elif direction==3:
          
          for i in range(0,3):
            
            for j in range(0,3):
              
              if self.arr[j][i]!=0 and (self.curCol+i>=self.cols or self.back[self.curRow+j][self.curCol+i]!=0):
                
                self.tag = False
                break
        #向下，判断底部
        elif direction==4:
          
          for i in range(0,3):
            
            for j in range(0,3):
              
              if self.arr[i][j]!=0 and (self.curRow+i>=self.rows or self.back[self.curRow+i][self.curCol+j]!=0):
                
                self.tag = False 
                self.isDown = True
                break
        #进行变形，判断边界
        elif direction==2:
          
          if self.curCol<0:
            
            self.curCol=0
          
          if self.curCol+2>=self.cols:
            
            self.curCol = self.cols-3
            
          if self.curRow+2>=self.rows:
            
            self.curRow = self.curRow-3
        
        
        return self.tag
        
    #方块向下移动
    def brickDown(self):
        
        while True:
          
          if self.start==False:
            
            print("exit thread")
            break
          
          tempRow = self.curRow
          self.curRow+=1
          
          if self.isEdge(4)==False:
            
            self.curRow = tempRow
          
          self.blockArrayPosi = [self.curRow,self.curCol]
      
          if(self.isDown):
            self.blockArrayInfo = {"blockSprite":self.back,
                                 "nextblockSprite":self.nextArr,
                                 "score":self.score,
                                 "gameOver":self.gameOver,
                                 "blockPosi":self.blockArrayPosi,
                                 "isDown":self.isDown}
          else:
            self.blockArrayInfo = {"blockSprite":self.arr,
                                 "nextblockSprite":self.nextArr,
                                 "score":self.score,
                                 "gameOver":self.gameOver,
                                 "blockPosi":self.blockArrayPosi,
                                 "isDown":self.isDown}

          
          dReturn = {
              "action": "currentBlock",
              "flag" : self.blockArrayInfo,
          }
          self.returnArrayInfo = dReturn
          
          self.drawRect()
             
          #每一秒下降一格
          sleep(1)  
      


    #定时器，实现自动下落
    def CheckTimer(self):
        timecontrol.Remove_Call_Out("loginrecord")
        pubdefines.FormatPrint("定时器统计：目前总连接记录 %s" % self.m_Data.get("total", 0))
        timecontrol.Call_Out(pubcore.Functor(self.CheckTimer), 300, "loginrecord")

    def NewItem(self):
        self.m_Data.setdefault("total", 0)
        self.m_Data["total"] += 1
        self.Save()

    #初始化界面
    def updateStage(self, oClient, dData):

        if self.start==False:
          print("exit thread")

        print self.returnArrayInfo
        oClient.Send(self.returnArrayInfo)


    #判断是否死了  
    def isDead(self):  
        
      for j in range(0,len(self.back[0])):  
          
        if self.back[0][j]!=0:
          showinfo("提示","你挂了，再来一盘吧！");  
          self.start = False  
          break; 

    #移动
    def CalMove(self, oClient, dData):
        change = dData["actionType"]
        self.onChangeEvent(oClient,change)
        if change == "down":
            action = "down"
        elif change == "left":
            action = "left"
        elif change == "right":
            action = "right"      
        dReturn = {
            "action": action,
            "flag": self.tag,
        }
        print dReturn
        oClient.Send(dReturn)
    
    #旋转
    def CalRotate(self, oClient, dData):
        change = dData["actionType"]
        self.onChangeEvent(oClient,change)
        if change == "rotate":
            action = "rotate"       
        dReturn = {
            "action": action,
            "flag": True,
        }
        print dReturn
        oClient.Send(dReturn)

    #初始化
    def initGame(self, oClient, dData):
        print "init"
        #获得当前的方块
        self.getCurBrick()
        #按照数组，绘制格子
        self.drawRect()
        #启动方块下落线程
        self.downThread = threading.Thread(target=self.brickDown,args=())  
        self.downThread.start()
        
        self.updateStage(oClient, dData)


def Init():
    if pubglobalmanager.GetGlobalManager("tetris"):
        return
    oManger = CTetris()
    pubglobalmanager.SetGlobalManager("tetris", oManger)
    oManger.Init()

def Record():
    pubglobalmanager.CallManagerFunc("tetris", "NewItem")

def OnCommand(oClient, dData):
    if dData["actionType"] == "left" or  dData["actionType"] == "right" or  dData["actionType"] == "down":
         pubglobalmanager.CallManagerFunc("tetris", "CalMove", oClient, dData)
    elif dData["actionType"] == "rotate":
        pubglobalmanager.CallManagerFunc("tetris", "CalRotate", oClient, dData)

def OnCommand2(oClient, dData):
    if dData["actionType"] == "initGame":
        print "initGame"
        pubglobalmanager.CallManagerFunc("tetris", "initGame", oClient, dData)

def OnCommand3(oClient, dData):
    if dData["actionType"] == "updateGame":
        pubglobalmanager.CallManagerFunc("tetris", "updateStage", oClient, dData)