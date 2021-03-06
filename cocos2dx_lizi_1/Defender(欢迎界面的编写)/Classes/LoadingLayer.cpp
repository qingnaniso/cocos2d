#include "LoadingLayer.h"
#include "WelComeGameLayer.h"
USING_NS_CC;
LoadingLayer::LoadingLayer(){
	this->loadingNum=0;
	this->totalNum=8;
}
bool LoadingLayer::init(){
	bool isRet=false;
	do 
	{
	CC_BREAK_IF(!BaseLayer::init());
	CC_BREAK_IF(!this->setUpdateView());
	
	CCTextureCache::sharedTextureCache()->addImageAsync("welcomebg.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 背景图片
	CCTextureCache::sharedTextureCache()->addImageAsync("coder.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 添加关于开发者背景图片
  
	CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_on.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 声音开始
	CCTextureCache::sharedTextureCache()->addImageAsync("button_sound_off.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 声音关闭

	CCTextureCache::sharedTextureCache()->addImageAsync("coder_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 开发者按钮
	CCTextureCache::sharedTextureCache()->addImageAsync("coder_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 欢迎界面 开发者按钮

	CCTextureCache::sharedTextureCache()->addImageAsync("return_down.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 返回菜单按钮
	CCTextureCache::sharedTextureCache()->addImageAsync("return_up.png",this,callfuncO_selector(LoadingLayer::loadCallBack)); // 返回菜单按钮
	
	isRet=true;
	} while (0);
	return isRet;
}
CCScene* LoadingLayer::scene(){
	CCScene* scene=CCScene::create();
	LoadingLayer* layer=LoadingLayer::create();
	scene->addChild(layer);
	return scene;
}
void LoadingLayer::loadCallBack(CCObject* ped){
	loadingNum++;	 
    CCProgressTimer* pt=(CCProgressTimer*)this->getChildByTag(1);
	float now=pt->getPercentage();
	pt->setPercentage(100/totalNum+now);
	if(loadingNum<totalNum){
		
	}else{
		// 加载完的时候跳转到响应的界面
		CCLOG("loading over");
		goWelcomeLayer();
	}
}


void LoadingLayer::goWelcomeLayer(){
	CCScene* se=WelComeGameLayer::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionMoveInR::create(1,se));
}

bool LoadingLayer::setUpdateView(){
	bool isRet=false;
	do 
	{
	// 设置进度条的背景图片 我们把他放到屏幕下方的1/5处	
    CCSprite* loadbackimg=CCSprite::create("lodingbg.png");
	CC_BREAK_IF(!loadbackimg);	
	loadbackimg->setPosition(ccp(getWinSize().width/2+getWinOrigin().x,getWinSize().height/5+getWinOrigin().y));
	this->addChild(loadbackimg,1);
	
	// 添加进度条
	CCSprite* loadimg=CCSprite::create("longding.png");
	CC_BREAK_IF(!loadimg);	
	CCProgressTimer* pt = CCProgressTimer::create(loadimg);
	pt->setType(kCCProgressTimerTypeBar);// 设置成横向的
	//可以看作是按矩形显示效果的进度条类型
	pt->setMidpoint(ccp(0,0)); 
	//  用来设定进度条横向前进的方向从左向右或是从右向左
	pt->setBarChangeRate(ccp(1,0));
	//重新设置锚点
	float tex=getWinSize().width/2+getWinOrigin().x;
	float tey=getWinSize().height/5+getWinOrigin().y-5;
	pt->setPosition(ccp(tex,tey));
	pt->setPercentage(0);
	this->addChild(pt,2,1);

	isRet=true;
	} while (0);
	return isRet;
}