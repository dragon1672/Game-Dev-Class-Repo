#include <Qt/qapplication.h>
#include "testing.h"
#include <Engine\Systems\BasicGui.h>
#include <Engine\Systems\SceneManager.h>
#include "SceneOne.h"
#include "SceneTwo.h"

#include "SceneThree.h"
#include "CoolScene.h"


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	//* computer Graphics


		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


		BasicGui GUI;

		//Testing widg;
		SceneManager widg;

		//SceneOne tab1;	widg.addScene(&tab1);
		//SceneTwo tab2;	widg.addScene(&tab2);
		//SceneThree tab3;	widg.addScene(&tab3);
		CoolScene tab4;	widg.addScene(&tab4);

		GUI.addScene(&widg);
		GUI.show();

	/*/ // engine refactor

		

	//*/
	return app.exec();
}