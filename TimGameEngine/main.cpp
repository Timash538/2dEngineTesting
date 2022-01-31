#include <stdio.h>
#include <iostream>
#include "engine.h"
#include "tim_utils.h"


int main(int argc, char* argv[]) {
	Engine eng = Engine(argc,argv);
	eng.Init(1920,1080);
	eng.RegisterCallbacks();
	eng.Start();
	
}