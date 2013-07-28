#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

typedef struct s_resolutionData {
    CCSize size;
    char path[100];
} resolutionData;

resolutionData lowRes = {CCSizeMake(480, 320),"lr"};
resolutionData highRes = {CCSizeMake(960, 640),"hr"};

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

    pEGLView->setDesignResolutionSize(480, 320, kResolutionNoBorder);

    CCSize psize=pEGLView->getDesignResolutionSize();
    CCSize fsize=pEGLView->getFrameSize();
    printf("d %f %f\n",psize.width,psize.height);
    printf("f %f %f\n",fsize.width,fsize.height);


    vector<string> searchPaths;

    if (fsize.width>lowRes.size.width) {
        searchPaths.push_back("hr");
        printf("high res display\n");
        pDirector->setContentScaleFactor(2);
    } else {
        searchPaths.push_back("lr");        
        printf("low res display\n");
        pDirector->setContentScaleFactor(1);
    }
    
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

    
    //psize=pEGLView->getDesignResolutionSize();
    
    
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //    CCScene *pScene = HelloWorld::scene();

    // run
    // pDirector->runWithScene(theLoadScene);
    
    struct timeval paraeltime;
    gettimeofday(&paraeltime, NULL);
    int seed=paraeltime.tv_usec;
    printf("SEED= %u\n",seed);
    srand(seed);
    setLoadSceneAndStart(pDirector);

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
