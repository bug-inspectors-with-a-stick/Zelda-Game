#include "pch.h"
#include <windows.h>
#include "Zelda.h"
// Random comment to diff this file
int main()
{
	Game* zelda = new Game;
	zelda->Play();
	delete zelda;

	system("PAUSE");
	return 0;
}