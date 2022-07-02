#include <stdio.h>
#include <iostream>
#include "visual_engine.h"




int main(int argc, char* argv[]) {
	VisualEngine visualEngine = VisualEngine(argc, argv);
	visualEngine.Init(800,800);
	visualEngine.RegisterCallbacks();
	visualEngine.Start();
}