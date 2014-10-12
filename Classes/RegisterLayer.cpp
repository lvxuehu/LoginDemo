//
//  RegisterLayer.cpp
//  Test
//
//  Created by jie on 14-2-10.
//
//

#include "RegisterLayer.h"
#include "curl/curl.h"
static const char * messag="";
bool RegisterLayer::init()
{
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
    {
        return false;
    }
    
    
    setTouchEnabled(true);
    
    
    size= CCDirector::sharedDirector()->getWinSize();
    
    
    CCSprite * bg= CCSprite::create("register_bg.png");
    bg->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg);
    CCSprite * bg2=CCSprite::create("register_bg1.png");
    bg2->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(bg2,1);
    
    
    //注册消息
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(RegisterLayer::registerSuccess), "Register", NULL);
    
    
    
    
    CCMenuItemImage * btn1=CCMenuItemImage::create("register_sure_up.png", "register_sure_down.png", "register_sure_dis.png", this, menu_selector(RegisterLayer::menuCallBackRegister));
    
    CCMenuItemImage * btn2= CCMenuItemImage::create("close_up.png", "close_down.png", this, menu_selector(RegisterLayer::menuCallBackClose));
    btn2->setPosition(ccp(240, 150));//以屏幕的中心点为0点。
    btn1->setPosition(ccp(0, -300));
    menu=CCMenu::create(btn1,btn2,NULL);
    bg->addChild(menu);
    
    
    
    
    CCScale9Sprite * bg01=CCScale9Sprite::create();
    CCScale9Sprite * bg02=CCScale9Sprite::create();
    CCScale9Sprite * bg03=CCScale9Sprite::create();
    
    
    registerusername =CCEditBox::create(CCSizeMake(430, 40), bg01);//500,60
    registerusername->setText("");
    //registerusername->setFontSize(20);
    registerusername->setMaxLength(10);
    registerusername->setFontColor(ccc3(0, 0, 0));
    registerusername->setPosition(ccp(size.width/2+145,size.height/2+2));//182
    registerusername->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(registerusername);
    
    
    firPassword =CCEditBox::create(CCSizeMake(500, 60), bg02);
    firPassword->setText("");
    //secPassword->setFontSize(20);
    firPassword->setMaxLength(10);
    firPassword->setFontColor(ccc3(0, 0, 0));
    firPassword->setPosition(ccp(size.width/2+180,size.height/2-100));
    firPassword->setInputFlag(kEditBoxInputFlagPassword);
    firPassword->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(firPassword);
    
    
    secPassword =CCEditBox::create(CCSizeMake(500, 60), bg03);
    secPassword->setText("");
    //secPassword->setFontSize(20);
    secPassword->setMaxLength(10);
    secPassword->setInputFlag(kEditBoxInputFlagPassword);
    secPassword->setFontColor(ccc3(0, 0, 0));
    secPassword->setPosition(ccp(size.width/2+180,size.height/2-200));
    secPassword->setReturnType(kKeyboardReturnTypeDone);
    bg->addChild(secPassword);
    
    
    
    
    return true;
    
}


//处理消息
void RegisterLayer::registerSuccess()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "Register");
    CCMessageBox("注册成功", "成 功");
    this->removeFromParent();
    
}

void RegisterLayer::menuCallBackClose()
{
    this->removeFromParent();
}

void RegisterLayer::menuCallBackRegister()
{
    
    CCLog("menuCallBackRegister");
    std::string str= firPassword->getText();
    std::string str2= secPassword->getText();
    if (!strcmp(str.c_str(), str2.c_str())&&strcmp(firPassword->getText(), "")&&strcmp(secPassword->getText(), "")&&strcmp(registerusername->getText(), ""))
    {
        CURL *curl;
        CURLcode res;
        //http协议
        
        curl = curl_easy_init();
        if (curl)
        {
            char ipstr[100]="";
            sprintf(ipstr, "http://172.27.35.4:8080/test/index.jsp?username=%s&password=%s",registerusername->getText(),secPassword->getText());
//            sprintf(ipstr, "http://182.50.2.240:11008/register?username=%s&password=%s",registerusername->getText(),secPassword->getText());
            CCLog("ipstr=%s",ipstr);
            char output[500]="";
            curl_easy_setopt(curl, CURLOPT_URL, ipstr);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RegisterLayer::process_data);
            CCLog("output %s",output);
            
            res = curl_easy_perform(curl);
            
            if(res==0)
            {
                CCLog("Succeed!");
                
            }else
            {
                
            }
            curl_easy_cleanup(curl);
            
        }
    }
    else
    {
        CCMessageBox("出错了,请重试", "出错了");
    }
}

size_t RegisterLayer::process_data(void *buffer, size_t size, size_t nmemb, void *user_p)
{
    FILE *fp = (FILE *)user_p;
    size_t return_size = fwrite(buffer, size, nmemb, fp);
    messag=(char *)buffer;
    CCLog("return messag=%s",messag);
    if(!strcmp(messag, "b"))
    {
        CCNotificationCenter::sharedNotificationCenter()->postNotification("Register");
        std::cout <<" notification Register =" <<(char *)buffer << std::endl;
    }
    else
    {
        CCMessageBox("此用户已经注册过，请重试", "警告！");
    }
    return return_size;
}

void RegisterLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,-9999, true);
    CCLayer::registerWithTouchDispatcher();
}

bool RegisterLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
//    CCEditBox * registerusername;
    registerBool = registerusername->ccTouchBegan(touch, event);
    menuflag=menu->ccTouchBegan(touch, event);
    firFlag= firPassword->ccTouchBegan(touch, event);
    secFlag= secPassword->ccTouchBegan(touch, event);
    
    return true;
}

void RegisterLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    if(registerBool)
    {
        registerusername->ccTouchMoved(touch, event);
    }
    if(menuflag)
    {
        menu->ccTouchMoved(touch, event);
    }
    if(firFlag)
    {
        firPassword->ccTouchMoved(touch, event);
    }
    if(secFlag)
    {
        secPassword->ccTouchMoved(touch, event);
    }
}

void RegisterLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    if(registerBool)
    {
        registerusername->ccTouchEnded(touch, event);
        registerBool=false;
    }
    if(menuflag)
    {
        menu->ccTouchEnded(touch, event);
        menuflag=false;
    }
    if(firFlag)
    {
        firPassword->ccTouchEnded(touch, event);
        firFlag=false;
    }
    if(secFlag)
    {
        secPassword->ccTouchEnded(touch, event);
        secFlag=false;
    }
}


