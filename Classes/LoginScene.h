//
//  LoginScene.h
//  Test
//
//  Created by jie on 14-2-10.
//
//

#ifndef __Test__LoginScene__
#define __Test__LoginScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class LoginScene:public CCLayer
{
public:
    CREATE_FUNC(LoginScene);
    bool virtual init();
    
    
    void loadTexture();
    void loginCallback();
    void registerCallback();
    void exitCallback();
    void moreGameCallback();
    
    
    ~LoginScene();
    
    
public:
    CCEditBox *editBoxUserName;
    CCEditBox *editBoxPassword;
};

#endif /* defined(__Test__LoginScene__) */
