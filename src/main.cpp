#include "ofMain.h"
#include "ofApp.h"
#include "GuiApp.h"
#include "VideoApp.h"
#include "ofAppGLFWWindow.h"
#include "Constants.h"


//========================================================================
int main(){
	
	ofGLFWWindowSettings settings;

    settings.setSize(WSCREENVIDEO, HSCREENVIDEO);
    settings.setPosition(ofVec2f( 0,0));
    settings.resizable = true;
    settings.decorated = true;
    settings.multiMonitorFullScreen = true;
    settings.numSamples = 8;
    shared_ptr<ofAppBaseWindow> videoWindow = ofCreateWindow(settings);
    
    settings.setSize(WSCREEN, HSCREEN);
    settings.setPosition(ofVec2f( WSCREENVIDEO,0));
    settings.resizable = true;
    settings.decorated = true;
    settings.multiMonitorFullScreen = true;
    settings.numSamples = 8;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.setSize(400, 400);	
	settings.setPosition(ofVec2f( 0,0));
	settings.resizable = true;
	settings.decorated = true;
	settings.multiMonitorFullScreen = false;
	settings.numSamples = 8 ;
	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);

	shared_ptr<ofApp> mainApp(new ofApp);
    shared_ptr<GuiApp> guiApp(new GuiApp);
    shared_ptr<VideoApp> videoApp(new VideoApp);

    mainApp->gui = guiApp;
    mainApp->video = videoApp;
	mainApp->window = mainWindow;
	mainApp->gl = dynamic_pointer_cast<ofBaseGLRenderer>(mainWindow->renderer());

    ofRunApp(videoWindow, videoApp);
    ofRunApp(guiWindow, guiApp);
	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}

