#include "pch.h"
#include "Main.h"

int main()
{
	Game* zelda = new Game;
	zelda->Play();
	delete zelda;

	system("PAUSE");
	return 0;
}