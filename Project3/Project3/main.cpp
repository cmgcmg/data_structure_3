#include "Manager.h"
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h> 

int main(int argc, char* argv[])
{	
	//_CrtSetBreakAlloc(192);

    const char* commandFilepath = "command.txt";
    if (argc > 1)
        commandFilepath = argv[1];

    Manager m;
    m.Run(commandFilepath);

	_CrtDumpMemoryLeaks();

    return 0;
}