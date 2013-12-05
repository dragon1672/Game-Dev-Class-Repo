#include "StartScreen.h"
#include "StaticPos.h"
#include "DynamicPosRandom.h"

const char* StartScreen::TITLE_TEXT     = "Space Wars!";
Core::RGB   StartScreen::TITLE_COLOR    = RGB(255,255,0);//yellow
const char* StartScreen::SUBTITLE_TEXT  = "Created By:\n-=AnthonyCorbin=-";
Core::RGB   StartScreen::SUBTITLE_COLOR = RGB(34,155,56);//green
Core::RGB   StartScreen::BUTTON_COLOR   = RGB(100,100,100);
Core::RGB   StartScreen::BUTTON_MOUSE_OVER_COLOR = RGB(150,150,150);
const char* FONT_FILE_LOCATION = "../FONT.txt";

void StartScreen::initTitleText() {
	//consts
	int titleAndSubTitlePadding = 10;
	int titleHorzOffsetFromCenter = -200;
	Vector2D centerOfTitle((float)SCREEN_WIDTH/2,(float)SCREEN_HEIGHT/2+titleHorzOffsetFromCenter);
	
	DynamicPosRandom subTitleSpawnPoint((float)SCREEN_WIDTH,(float)SCREEN_HEIGHT);
	StaticPos titleSpawnPoint(centerOfTitle);
	//StaticPos titleSpawnPoint(Vector2D(SCREEN_WIDTH/2,0));

	//setting format
	titleFormat.init(4,3,TITLE_COLOR,10);
	titleFormat.spawnLocation = &titleSpawnPoint;
	titleFormat.slowEffect = true;
	//subtitle
	subTitleFormat.init(1,2,SUBTITLE_COLOR,10);
	subTitleFormat.spawnLocation = &subTitleSpawnPoint;
	subTitleFormat.slowEffect = false;

	int titleHeight = titleFormat.heightOfString(TITLE_TEXT);
	int titleWidth  = titleFormat.widthOfString(TITLE_TEXT);
	//int subHeight   = subTitleFormat.heightOfString(SUBTITLE_TEXT);
	int subWidth    = subTitleFormat.widthOfString(SUBTITLE_TEXT);

	Vector2D titlePos    = centerOfTitle - Vector2D((float)titleWidth/2,(float)titleHeight/2);
	Vector2D subTitlePos = centerOfTitle - Vector2D((float)subWidth/2,-(float)titleHeight/2-titleAndSubTitlePadding);
	
	textManager.initText(titlePos,TITLE_TEXT,&myFont,&titleFormat);
	textManager.initText(subTitlePos,SUBTITLE_TEXT,&myFont,&subTitleFormat);
}
void StartScreen::initButtons(const char* optionText[], int numOfOptions) {
	numOfButtons = numOfOptions;

	//statics
	int buttonWidth  = 100;
	int buttonHeight = 30;
	int buttonOffset = 3*buttonHeight/4;
	Vector2D buttonPos((float)(SCREEN_WIDTH-buttonWidth)/2,(float)(SCREEN_HEIGHT-buttonWidth)/2);
	Vector2D offset(0,buttonHeight+buttonOffset);


	for(int i=0;i<numOfButtons;i++) {
		options[i].init(&cursor,buttonPos,optionText[i],buttonWidth,buttonHeight,BUTTON_COLOR,BUTTON_MOUSE_OVER_COLOR);
		buttonPos = buttonPos+offset;
	}
}

void StartScreen::init(int screenWidth, int screenHeight,const char* optionText[], int numOfOptions) {
	statusCode = WINDOW_STILL_ACTIVE;

	SCREEN_WIDTH  = screenWidth;
	SCREEN_HEIGHT = screenHeight;
	
	myFont.init(FONT_FILE_LOCATION);

	initTitleText();

	initButtons(optionText,numOfOptions);
	
}

void StartScreen::update(float dt) {
	textManager.update(dt);
	for(int i=0;i<numOfButtons;i++) {
		if(options[i].isPressed()) statusCode = i;
	}
}
void StartScreen::draw(MyGraphics& graphics) {
	textManager.draw(graphics);
	for(int i=0;i<numOfButtons;i++) {
		options[i].draw(graphics);
	}
}