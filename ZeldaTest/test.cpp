#include "pch.h"
#include "../Zelda/Zelda.cpp"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


//---------------------Room------------------------

TEST(RoomDirectionIndex, Capital) {
	Room* room = new Room();

	// 0 = North
	// 1 = South
	// 2 = East
	// 3 = West

	EXPECT_EQ(0, room->directionIndex("NORTH"));
	EXPECT_EQ(1, room->directionIndex("SOUTH"));
	EXPECT_EQ(2, room->directionIndex("EAST"));
	EXPECT_EQ(3, room->directionIndex("WEST"));

	delete room;
}

TEST(RoomDirectionIndex, MixedCase) {
	Room* room = new Room();

	EXPECT_EQ(0, room->directionIndex("noRth"));
	EXPECT_EQ(1, room->directionIndex("SoUtH"));
	EXPECT_EQ(2, room->directionIndex("EaSt"));
	EXPECT_EQ(3, room->directionIndex("WesT"));

	delete room;
}

TEST(RoomDirectionIndex, WrongWords) {
	Room* room = new Room();

	EXPECT_EQ(0, room->directionIndex("lkafsjlkdsajflsafd"));
	EXPECT_EQ(0, room->directionIndex("ioewuroijsafjkhsdkjfahs"));
	EXPECT_EQ(0, room->directionIndex("sjdkafhkjsn,nvxzc,mcnkds"));
	EXPECT_EQ(0, room->directionIndex("huiuysiafhsdakjfhdakj"));

	delete room;
}

TEST(RoomDirectionIndex, SpecialCharacters) {
	Room* room = new Room();

	EXPECT_EQ(0, room->directionIndex("%*(#&%(*#&%*(#$@&%$"));
	EXPECT_EQ(0, room->directionIndex("98375@(*#%&*(&@#$*(%3"));
	EXPECT_EQ(0, room->directionIndex("(*#&%(*#$%&(*#&#$%*(#$,n"));
	EXPECT_EQ(0, room->directionIndex("*&(#*%&#*(%&#$*(%#$&%#(*"));

	delete room;
}

TEST(RoomDirectionName, IntegerInput) {
	Room* room = new Room();

	EXPECT_STREQ("North", room->directionName(0));
	EXPECT_STREQ("South", room->directionName(1));
	EXPECT_STREQ("East",  room->directionName(2));
	EXPECT_STREQ("West", room->directionName(3));

	delete room;
}

TEST(RoomDirectionName, OutsideNormalRange) {
	Room* room = new Room();

	EXPECT_STREQ("", room->directionName(4));

	delete room;
}

TEST(RoomDirectionName, FloatInput) {
	Room* room = new Room();

	EXPECT_STREQ("", room->directionName(4.0));

	delete room;
}

TEST(RoomGettersSetters, SurroundingRooms) {
	Room* room = new Room();
	Room* room2 = new Room();
	Room* room3 = new Room();
	Room* room4 = new Room();
	Room* room5 = new Room();

	room->setNorth(room2);
	room->setSouth(room3);
	room->setEast(room4);
	room->setWest(room5);

	EXPECT_EQ(room2, room->getPaths()[0]);
	EXPECT_EQ(room3, room->getPaths()[1]);
	EXPECT_EQ(room4, room->getPaths()[2]);
	EXPECT_EQ(room5, room->getPaths()[3]);

	// Reset to another value
	room->setNorth(room5);
	room->setSouth(room4);
	room->setEast(room3);
	room->setWest(room2);

	EXPECT_EQ(room5, room->getPaths()[0]);
	EXPECT_EQ(room4, room->getPaths()[1]);
	EXPECT_EQ(room3, room->getPaths()[2]);
	EXPECT_EQ(room2, room->getPaths()[3]);


	delete room;
	delete room2;
	delete room3;
	delete room4;
	delete room5;
}

TEST(RoomGettersSetters, Description) {
	Room* room = new Room();

	room->setDesription("Room0");

	EXPECT_STREQ("Room0", room->getDescription());

	char const* name = "57572983570832975032485032498739873047258347598275098327503428753409285732409857342089"
		"5834285-3492853420958324-0958342-958342-095834-0258342-09583-095832-589324";

	room->setDesription(name);

	EXPECT_STREQ(name, room->getDescription());

	delete room;
}

TEST(RoomGettersSetters, Items) {
	Room* room = new Room();
	Item* weapon = new Weapon("weaponWEAPON");
	Item* treasure = new Treasure("TESTtresureName", INT_MAX);

	EXPECT_EQ(false, room->isRoomFull());

	room->setItemsPresent(0, weapon);
	room->setItemsPresent(1, treasure);
	room->setItemsPresent(2, weapon);
	room->setItemsPresent(3, treasure);
	room->setItemsPresent(4, weapon);
	room->setItemsPresent(5000, treasure);

	Item** items = room->getItemsPresent();

	EXPECT_EQ(weapon, items[0]);
	EXPECT_EQ(treasure, items[1]);
	EXPECT_EQ(weapon, items[2]);
	EXPECT_EQ(treasure, items[3]);
	EXPECT_EQ(weapon, items[4]);
	EXPECT_EQ(treasure, items[5000]);

	EXPECT_EQ(true, room->isRoomFull());

	delete room;
	delete weapon;
	delete treasure;
}

TEST(RoomGettersSetters, PrincessMonster) {
	Room* room = new Room();
	Item* weapon = new Weapon("weaponWEAPON");
	Monster* monster = new Monster("TESTmonsterName", weapon);
	Princess* princess = new Princess();

	room->setPrincessPresent(princess);
	EXPECT_EQ(princess, room->getPrincessPresent());

	room->setMonsterPresent(monster);
	EXPECT_EQ(monster, room->getMonsterPresent());

	delete room;
	delete weapon;
	delete monster;
	delete princess;
}


TEST(RoomGettersSetters, RoomNumber) {
	Room* room = new Room();

	int number = 0;
	room->setRoomNumber(0);
	EXPECT_EQ(number, room->getRoomNumber());

	number = 9437489724;
	room->setRoomNumber(number);
	EXPECT_EQ(number, room->getRoomNumber());

	number = -100;
	room->setRoomNumber(number);
	EXPECT_EQ(number, room->getRoomNumber());
}

//---------------------Castle------------------------

TEST(CastleLinking, LinkRoom5and8) {
	Castle* castle = new Castle();

	// paths[0] = North
	// paths[1] = South
	// paths[2] = East
	// paths[3] = West

	// Check that the rooms are not currently linked
	Room* room5Paths = castle->getRoom(5)->getPaths()[1];
	Room* room8Paths = castle->getRoom(8)->getPaths()[0];

	EXPECT_EQ(room5Paths, nullptr);
	EXPECT_EQ(room8Paths, nullptr);

	// Link the rooms
	castle->LinkRoom5and8();

	// Test that they were successfully linked
	room5Paths = castle->getRoom(5)->getPaths()[1];
	room8Paths = castle->getRoom(8)->getPaths()[0];

	EXPECT_EQ(room5Paths, castle->getRoom(8));
	EXPECT_EQ(room8Paths, castle->getRoom(5));

	delete castle;
}

TEST(CastleLinking, LinkRoom6and9) {
	Castle* castle = new Castle();

	// Check that the rooms are not currently linked
	Room* room6Paths = castle->getRoom(6)->getPaths()[1];
	Room* room9Paths = castle->getRoom(9)->getPaths()[0];

	EXPECT_EQ(room6Paths, nullptr);
	EXPECT_EQ(room9Paths, nullptr);

	// Link the rooms
	castle->LinkRoom6and9();

	// Test that they were successfully linked
	room6Paths = castle->getRoom(6)->getPaths()[1];
	room9Paths = castle->getRoom(9)->getPaths()[0];

	EXPECT_EQ(room6Paths, castle->getRoom(9));
	EXPECT_EQ(room9Paths, castle->getRoom(6));

	delete castle;
}

TEST(CastleLinking, LinkAllRoomsNull) {
	Castle* castle = new Castle();

	castle->LinkRoomsWithOtherThings(nullptr, nullptr, nullptr);

	EXPECT_EQ(castle->getRoom(1)->getPaths()[2], castle->getRoom(2));

	delete castle;
}

TEST(CastleLinking, LinkAllRooms) {
	Castle* castle = new Castle();
	Item** itemsPtr = new Item*[5];
	itemsPtr[0] = new Treasure("GOLDEN EGG", 500000);
	itemsPtr[1] = new Treasure("GOLDEN CHALICE", 500000);
	itemsPtr[2] = new Treasure("PROOF", 1000000);
	itemsPtr[3] = new Weapon("SHIELD");
	itemsPtr[4] = new Weapon("DAGGER");
	Monster** monstersPtr = new Monster*[5];
	monstersPtr[0] = new Monster("MEDUSA", itemsPtr[3]);
	monstersPtr[1] = new Monster("DRACULA", itemsPtr[4]);
	Princess* princessPtr = new Princess;

	castle->LinkRoomsWithOtherThings(itemsPtr, monstersPtr, princessPtr);

	EXPECT_EQ(castle->getRoom(1)->getPaths()[2], castle->getRoom(2));

	delete castle;
	delete [] itemsPtr;
	delete [] monstersPtr;
	delete princessPtr;
}

TEST(CastleGetSet, roomNumbers) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	for (int ii = 1; ii < 10; ++ii) {
		EXPECT_EQ(castle->getRoom(ii)->getRoomNumber(), ii);
	}
	
	delete castle;
}

TEST(CastleGetSet, getRooms100) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	EXPECT_EQ(castle->getRoom(100)->getItemsPresent(), nullptr);

	delete castle;
}


TEST(CastleGetSet, getRoomsNegative) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	EXPECT_EQ(castle->getRoom(-1)->getItemsPresent(), nullptr);

	delete castle;
}

TEST(CastleGetSet, getRooms1Through10) {
	Castle* castle = new Castle();

	castle->setNumbersofRooms();

	for (int ii = 1; ii < 10; ++ii) {
		EXPECT_EQ(castle->getRoom(ii)->getRoomNumber(), ii);
	}

	delete castle;
}


//---------------------Monster------------------------
TEST(MonsterConstructor, ConstructorWithParameter) {
	Weapon* weapon = new Weapon("weapon");
	Monster* monster = new Monster("monster", weapon);
	EXPECT_STREQ("monster", monster->getMonsterName());
	EXPECT_STREQ("weapon", monster->getKillingWeapon()->getItemName());
	EXPECT_EQ(true, monster->getLivingState());
	delete monster;
	delete weapon;
}

TEST(MonsterConstructor, ConstructorWithoutParameter) {
	Monster* monster = new Monster();
	EXPECT_EQ(nullptr, monster->getMonsterName());
	EXPECT_EQ(nullptr, monster->getKillingWeapon());
	EXPECT_EQ(true, monster->getLivingState());
	delete monster;
}

TEST(MonsterGetterSetter,WeaponGetSet) {
	Weapon* weapon = new Weapon("weapon");
	Monster* monster = new Monster();
	monster->setKillingWeapon(weapon);
	EXPECT_STREQ("weapon", monster->getKillingWeapon()->getItemName());
	delete monster;
	delete weapon;
}

TEST(MonsterGetterSetter, LivingGetSet) {
	Monster* monster = new Monster();
	monster->setLivingState(false);
	EXPECT_EQ(false, monster->getLivingState());
	delete monster;
}

TEST(MonsterGetterSetter, NameGetSet) {
	Monster* monster = new Monster("monster", nullptr);
	//monster has not setter for name
	EXPECT_STREQ("monster",monster->getMonsterName());
	delete monster;
}

//---------------------Princess------------------------
TEST(PrincessConstructor, Constructor) {
	Princess* princess=new Princess();
	EXPECT_EQ(true,princess->getLivingState());
	delete princess;
}

TEST(PrincessGetSet, LivingState) {
	Princess* princess=new Princess();
	princess->setLivingState(false);
	EXPECT_EQ(false,princess->getLivingState());
	delete princess;
}


//---------------------Treasure------------------------

TEST(TreasureCreation, StandardCase) {
	Treasure* treasure = new Treasure("The Holy Grail", 62);

	EXPECT_STREQ("The Holy Grail", treasure->getItemName());
	EXPECT_EQ(62, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, LongName) {
	Treasure* treasure = new Treasure("The Holy Grail is a really great thing to have perhaps we should go on a long quest for it and make the best movie in the world about said quest", 0);

	EXPECT_STREQ("The Holy Grail is a really great thing to have perhaps we should go on a long quest for it and make the best movie in the world about said quest", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, AllCaps) {
	Treasure* treasure = new Treasure("THE HOLY GRAIL", 0);

	EXPECT_STREQ("THE HOLY GRAIL", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, MixedCases) {
	Treasure* treasure = new Treasure("ThE HoLy GrAiL", 0);

	EXPECT_STREQ("ThE HoLy GrAiL", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, SpecialCharacters) {
	Treasure* treasure = new Treasure("\n\t\0", 0);

	EXPECT_STREQ("\n\t\0", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, NoInput) {
	Treasure* treasure = new Treasure("", 0);

	EXPECT_STREQ("", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, WhiteSpace) {
	Treasure* treasure = new Treasure("		", 0);

	EXPECT_STREQ("	", treasure->getItemName());

	delete treasure;
}

TEST(TreasureCreation, ZeroWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 0);

	EXPECT_EQ(0, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, NegativeWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", -1);

	EXPECT_EQ(-1, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, HugeWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 10000000);

	EXPECT_EQ(10000000, treasure->getWorth());

	delete treasure;
}

TEST(TreasureCreation, FractionalWorth) {
	Treasure* treasure = new Treasure("The Holy Grail", 0.5);

	EXPECT_EQ(0.5, treasure->getWorth());

	delete treasure;
}

//---------------------Weapon------------------------

TEST(WeaponCreation, StandardCase) {
	Weapon* weapon = new Weapon("Gurthang");

	EXPECT_STREQ("Gurthang", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, AllCaps) {
	Weapon* weapon = new Weapon("A DUCK");

	EXPECT_STREQ("A DUCK", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, LongName) {
	Weapon* weapon = new Weapon("How do you know she is a witch? She looks like one! Bring her forward. I'm not a witch. I'm not a witch. But you are dressed as one. They dressed me up like this. No, no we didn't -- no. And this isn't my nose, it's a false one.");

	EXPECT_STREQ("How do you know she is a witch? She looks like one! Bring her forward. I'm not a witch. I'm not a witch. But you are dressed as one. They dressed me up like this. No, no we didn't -- no. And this isn't my nose, it's a false one.", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, MixedCases) {
	Weapon* weapon = new Weapon("a duCK");

	EXPECT_STREQ("a duCK", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, NoInput) {
	Weapon* weapon = new Weapon("");

	EXPECT_STREQ("", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, WhiteSpace) {
	Weapon* weapon = new Weapon("	");

	EXPECT_STREQ("	", weapon->getItemName());

	delete weapon;
}

TEST(WeaponCreation, SpecialCharacters) {
	Weapon* weapon = new Weapon("\n\t\0");

	EXPECT_STREQ("\n\t\0", weapon->getItemName());

	delete weapon;
}

