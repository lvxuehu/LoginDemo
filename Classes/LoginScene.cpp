//
//  LoginScene.cpp
//  Test
//
//  Created by jie on 14-2-10.
//
//

#include "LoginScene.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif
#include "RegisterLayer.h"

bool LoginScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    
    CCSize size=CCDirector::sharedDirector()->getWinSize();
    this->loadTexture();
    
    
    
    CCSprite *fSprite=CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_bg_en.jpg"));
    fSprite->setPosition(ccp(size.width/2,size.height/2));
    this->addChild(fSprite);
    
    CCMenuItemImage *login_btn=CCMenuItemImage::create();
    login_btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_up.png"));
    login_btn->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("login_down.png"));
    login_btn->setTarget(this, menu_selector(LoginScene::loginCallback));
    
    CCMenuItemImage *register_btn=CCMenuItemImage::create();
    register_btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("register_up.png"));
    register_btn->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("register_down.png"));
    register_btn->setTarget(this, menu_selector(LoginScene::registerCallback));
    
    CCMenuItemImage *exit_btn=CCMenuItemImage::create();
    exit_btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tc_up.png"));
    exit_btn->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("tc_down.png"));
    exit_btn->setTarget(this, menu_selector(LoginScene::exitCallback));
    
    CCMenuItemImage *more_btn=CCMenuItemImage::create();
    more_btn->setNormalSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("moregame_up.png"));
    more_btn->setSelectedSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("moregame_down.png"));
    more_btn->setPosition(ccp(size.width/2, size.height-30));
    more_btn->setTarget(this, menu_selector(LoginScene::moreGameCallback));
    
    CCMenu *pMenu=CCMenu::create(more_btn,NULL);
    pMenu->setPosition(ccp(0, 0));
    this->addChild(pMenu,2);
    
    CCMenu *menu=CCMenu::create(login_btn,register_btn,exit_btn,NULL);
    menu->alignItemsVerticallyWithPadding(40);//竖直对齐
    menu->setPosition(ccp(size.width/2,180));
    this->addChild(menu);
    
    CCScale9Sprite *user_bg=CCScale9Sprite::create("login_kong.png");
    editBoxUserName = CCEditBox::create(CCSizeMake(204,60),user_bg);
    editBoxUserName->setFontSize(10);
    editBoxUserName->setMaxLength(10);
    editBoxUserName->setTag(1701);
    editBoxUserName->setPosition(ccp(size.width/2+18,size.height/2+60));
    editBoxUserName->setFontColor(ccc3(0, 0, 0));
    editBoxUserName->setReturnType(kKeyboardReturnTypeDone);
    this->addChild(editBoxUserName,2);
    
    CCScale9Sprite *pwd_bg=CCScale9Sprite::create("login_kong.png");
    editBoxPassword = CCEditBox::create(CCSizeMake(204, 60),pwd_bg);
    editBoxPassword->setInputFlag(kEditBoxInputFlagPassword);
    editBoxPassword->setFontSize(15);
    editBoxPassword->setMaxLength(10);
    editBoxPassword->setFontColor(ccc3(0, 0, 0));
    editBoxPassword->setPosition(ccp(size.width/2+18,size.height/2-10));
    editBoxPassword->setReturnType(kKeyboardReturnTypeDone);
    this->addChild(editBoxPassword,2);
    
    return true;
}
void LoginScene::loadTexture()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("login.plist");
}

void LoginScene::loginCallback()
{
    
}

void LoginScene::registerCallback()
{
    CCLayer *rLayer=RegisterLayer::create();
    this->addChild(rLayer);
}

void LoginScene::exitCallback()
{
    CCDirector::sharedDirector()->end();
    exit(0);
}

void LoginScene::moreGameCallback()
{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo,"com/sgcommunity/test/test","getInstance","()Lcom/sgcommunity/test/test;");
    jobject jobj;
    if (isHave) {
        CCLog("静态函数存在");
        jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    isHave = JniHelper::getMethodInfo(minfo,"com/sgcommunity/test/test","moreGame","()V");
    if (isHave) {
        CCLog("非静态函数存在");
        minfo.env->CallVoidMethod(jobj, minfo.methodID);
    }
#elif(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    CCMessageBox("ok","more game");
#endif
}

LoginScene::~LoginScene()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("login.plist");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("login.png");
}

