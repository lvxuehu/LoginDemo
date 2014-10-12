#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "LoginScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    CCSize size=CCDirector::sharedDirector()->getWinSize();
    
    CCDirector::sharedDirector()->setDepthTest(false);
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCSize frameSize=CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize IsSize=CCSizeMake(640, 960);
    float scaleX=(float)frameSize.width/IsSize.width;//算出宽比
    float scaleY=(float)frameSize.height/IsSize.height;//算出高比
    float scale=0.0f;
    if(scaleX>scaleY)//确定使用那种宽高比
    {
        scale=scaleX/(frameSize.height/(float)IsSize.height);
    }
    else
    {
        scale=scaleY/(frameSize.width/(float)IsSize.width);
        
    }
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(IsSize.width*scale, IsSize.height*scale, kResolutionNoBorder);
#else
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(640, 960, kResolutionShowAll);
#endif

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();
    CCScene *scene=CCScene::create();
    CCLayer *layer=LoginScene::create();
    scene->addChild(layer);
    // run
    pDirector->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
