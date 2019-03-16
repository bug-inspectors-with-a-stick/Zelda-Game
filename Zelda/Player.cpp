#include "pch.h"
#include "Player.h"

Player::Player(char const* player_Name, Room* room1)
{
	name = new char[strlen(player_Name) + 1];
	strcpy_s(name, strlen(player_Name) + 1, player_Name);

	current_Room = room1;
	princess_Pointer = nullptr;
	is_Alive = true;
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		bag[i] = nullptr;
	}
}



Player::Player()
{

}



Player::~Player()
{
	if (name)
	{
		delete[] name;
	}
}



bool Player::getCurrentState()
{
	return is_Alive;
}



void Player::setCurrentState(bool currentState)
{
	is_Alive = currentState;
}



Princess* Player::getPrincess_Pointer()
{
	return princess_Pointer;
}



char* Player::getPlayerName()
{
	return name;
}



void Player::CashUpdater()
{
	cash = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (bag[i])
		{
			cash = cash + bag[i]->getWorth();
		}
	}
}



int Player::getCash()
{
	return cash;
}



bool Player::isBagEmpty()
{
	for (int i = 0; i < 10; ++i)
	{
		if (bag[i] != nullptr)
			return false;
	}

	return true;
}



bool Player::isBagFull()
{
	bool bag_Full = true;

	for (int i = 0; i < 10 && bag_Full; ++i)
	{
		if (bag[i] == nullptr)
			bag_Full = false;
	}

	return bag_Full;
}



bool Player::Move(char const* direction, bool& exit_Castle)
{
	bool moveSuccessful = false;
	int i = 0;

	i = current_Room->directionIndex(direction);

	// -1 indicates an error
	if (i == -1) {
		HelperFunctions::color(RED);
		cout << "\nMOVE " << direction << " is an invalid command.";
		return false;
	}


	if ((i == 3) && ((current_Room->getRoomNumber()) == 1))
	{
		exit_Castle = true;
	}
	else if ((current_Room->getPaths())[i] != nullptr) {
		current_Room = (current_Room->getPaths())[i];
		moveSuccessful = true;

		if (current_Room->getPrincessPresent())
		{
			HelperFunctions::color(AQUA);
			cout << "The Princess is standing in the room, waiting for you in the dark.\n";
			princess_Pointer = current_Room->getPrincessPresent();
			current_Room->setPrincessPresent(nullptr);
		}

		HelperFunctions::color(RED);
		cout << "\nYou have successfully been moved to Room: " << current_Room->getRoomNumber();
	}
	else {
		HelperFunctions::color(RED);
		cout << "\nMOVE " << direction << " is an invalid command.";
	}

	return moveSuccessful;
}







void Player::Pick(char const* itemName)
{
	bool picked = false;
	bool itemFound = false;

	for (int i = 0; i < 5; ++i)
	{
		if ((current_Room->getItemsPresent())[i] != nullptr)
		{
			if (strcmp((((current_Room->getItemsPresent())[i])->getItemName()), itemName) == 0)
			{
				itemFound = true;

				if (!isBagFull())
				{
					int j = 0;

					for (; bag[j] != nullptr; ++j)
					{

					}

					bag[j] = (current_Room->getItemsPresent())[i];
					current_Room->setItemsPresent(i, nullptr);

					picked = true;

					CashUpdater();
				}
				else
					cout << "\nYour bag is already full.";
			}
		}
	}

	HelperFunctions::color(RED);
	if (picked)
		cout << endl << itemName << " has successfully been picked up.\n";

	else if (itemFound == false)
		cout << endl << itemName << " is not present in this room.\n";
}




void Player::Drop(char const* itemName)
{
	bool dropped = false;
	bool item_in_bag = false;

	for (int i = 0; i < 10; ++i)
	{
		if (bag[i] != NULL)
		{
			if (strcmp((bag[i])->getItemName(), itemName) == 0)
			{
				item_in_bag = true;

				if (!(current_Room->isRoomFull()))
				{
					int j = 0;

					for (; (current_Room->getItemsPresent())[j] != nullptr; ++j)
					{

					}

					current_Room->setItemsPresent(j, bag[i]);
					bag[i] = nullptr;

					dropped = true;

					CashUpdater();
				}
				else
				{
					HelperFunctions::color(AQUA);
					cout << "\nThe item" << itemName << " couldn't be dropped as Room " << current_Room->getRoomNumber()
						<< " is already full.";
				}
			}
		}
	}

	HelperFunctions::color(YELLOW);

	if (dropped)
		cout << endl << itemName << " has successfully been dropped.\n";

	else if (item_in_bag == false)
		cout << endl << itemName << " couldn't be dropped as it is not present in your bag.\n";
}




/* returns the name of the monster the player has slayed or
returns null, meaning failuer.

*/
const char * Player::Attack(char const* monsterName)
{
	char * killed = NULL;
	//&& strcmp(monsterName, current_Room->getMonsterPresent()->getMonsterName()) == 0
	if (current_Room->getMonsterPresent() != nullptr)
	{
		if (((current_Room->getMonsterPresent())->getLivingState()) == true)
		{
			for (int i = 0; i < 10; ++i)
			{
				if ((current_Room->getMonsterPresent())->getKillingWeapon() == bag[i])
				{
					(current_Room->getMonsterPresent())->setLivingState(false);
					HelperFunctions::color(RED);
					cout << current_Room->getMonsterPresent()->getMonsterName() << " has been killed.\n";

					killed = current_Room->getMonsterPresent()->getMonsterName();
				}
			}

			if (killed == NULL )
			{
				setCurrentState(false);
				HelperFunctions::color(RED);
				cout << "\nYour bag doesn't contain the Weapon required to kill " << monsterName << ".\n";
			}
		}

		else if ((((current_Room->getMonsterPresent())->getLivingState()) == false))
			cout << endl << monsterName << " is already dead.\n";

	}

	else
		cout << endl << monsterName << " is not present in this room.\n";

	return killed;
}



void Player::Look()
{
	HelperFunctions::color(RED);
	cout << "\nCurrently you are in Room " << current_Room->getRoomNumber() << ".\n";
	cout << current_Room->getDescription() << "\n";

	for (int i = 0; i < 4; ++i)
	{
		HelperFunctions::color(AQUA);
		if ((current_Room->getPaths())[i] != NULL)
			cout << "There is a room to your " << current_Room->directionName(i) << ".\n";
	}

	for (int i = 0; i < 5; ++i)
	{
		HelperFunctions::color(WHITE);
		if ((current_Room->getItemsPresent())[i] != NULL)
			cout << "The " << ((current_Room->getItemsPresent())[i])->getItemName() << " is lying on the floor.\n";
	}

	if (current_Room->getMonsterPresent() != NULL)
	{
		HelperFunctions::color(RED);
		if ((current_Room->getMonsterPresent())->getLivingState() == true)
			cout << (current_Room->getMonsterPresent())->getMonsterName() << " is waiting to kill you beside a locked door.\n";
		else
			cout << (current_Room->getMonsterPresent())->getMonsterName() << " is lying dead on the floor.\n";
	}

	HelperFunctions::color(PURPLE);
	if (princess_Pointer) {
		cout << "You have Princess with you.\n";
		princess_Pointer->setAlongState(true);
	}

	HelperFunctions::color(GREEN);
	cout << "\nYour bag contains the following items: ";


	if (!isBagEmpty())
	{
		for (int i = 0; i < 10; ++i)
		{
			if (bag[i])
				cout << endl << bag[i]->getItemName();
		}
	}
	else
		cout << "\nCurrently, your bag is empty.";

	HelperFunctions::color(BLUE);
	cout << "\nCurrent Cash is: " << getCash();
}



void Player::Exit()
{
	HelperFunctions::color(WHITE);
	cout << "Thank you " << getPlayerName() << " for playing Zelda.\nThe game is now exiting.\n";
}
