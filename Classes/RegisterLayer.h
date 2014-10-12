//
//  RegisterLayer.h
//  Test
//
//  Created by jie on 14-2-10.
//
//

#ifndef __Test__RegisterLayer__
#define __Test__RegisterLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
class RegisterLayer:public CCLayerColor{
public:
    
    virtual bool init();
    void menuCallBackClose();
    void menuCallBackRegister();
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    
    static   size_t process_data(void *buffer, size_t size, size_t nmemb, void *user_p);
    
    
    void registerSuccess();
    
    
public:
    CCSize size;
    CCMenu * menu;
    bool menuflag;
    CCEditBox * registerusername;
    CCEditBox * firPassword;
    bool firFlag;
    bool secFlag;
    CCEditBox * secPassword;
    bool registerBool;
    CREATE_FUNC(RegisterLayer);
};

#endif /* defined(__Test__RegisterLayer__) */
