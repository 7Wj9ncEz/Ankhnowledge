/*
 * Main.cpp
 *
 * Only instanciate the GameManager class
 *
 */


// specific headers
#include "GameManager.h"
#include "Log.h"

int main(int argc, char **argv){

	// Logging system
    structlog LOGCFG = {};
    LOGCFG.headers = false;
    LOGCFG.level = DEBUG;
    //---------------------------
    LOG(INFO) << "Main executed with " << (argc - 1) << " arguments";

	// Instanciating Game
	GameManager *gm = new GameManager();
	gm->run();
	delete gm;
	return 0;
}
