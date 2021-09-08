#include <bangtal>
using namespace bangtal;

int main()
{
	auto room1 = Scene::create("룸1", "Images/배경-1.png");
	auto room2 = Scene::create("룸2", "Images/배경-2.png");
	auto room3 = Scene::create("룸3", "Images/배경-2.png");

	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", room1, 800, 270);
	auto door4 = Object::create("Images/검은문-닫힘.png", room1, 220, 290, false);

	auto lights = Object::create("Images/조명.png", room1, 500, 600);
	lights->setScale(0.7f);

	auto beam = Object::create("Images/빛.png", room1, 200, 350, false);
	beam->setScale(0.3f);

	auto hammer = Object::create("Images/망치.png", room1, 235, 40);
	hammer->setScale(0.2f);

	auto pot = Object::create("Images/화분.png", room1, 200, 50);
	pot->setScale(1.2f);

	auto picture = Object::create("Images/작은그림.png", room1, 1000, 500);
	auto picture_scr = Object::create("Images/그림.png", room1, 350, 0, false);
	picture_scr->setScale(2.5f);

	auto key1 = Object::create("Images/액자열쇠.png", room1, 500, 80, false);
	key1->setScale(0.1f);

	auto door2 = Object::create("Images/문-왼쪽-열림.png", room2, 220, 250);
	auto door3 = Object::create("Images/비밀문-오른쪽-닫힘.png", room2, 920, 270);
	door3->setScale(0.3f);

	auto wall = Object::create("Images/벽지.png", room2, 850, 254);
	wall->setScale(0.3f);

	auto crowbar = Object::create("Images/쇠지렛대.png", room2, 1200, 50);
	crowbar->setScale(0.05f);

	auto key2 = Object::create("Images/검은문열쇠.png", room2, 500, 320);
	key2->setScale(0.1f);

	auto couch = Object::create("Images/소파.png", room2, 370, 240);
	couch->setScale(1.1f);

	auto sunflower = Object::create("Images/해바라기.png", room2, 120, 230);
	sunflower->setScale(0.2f);	

	auto bag = Object::create("Images/자루.png", room2, 620, 320);
	bag->setScale(0.1f);

	auto button = Object::create("Images/스위치왼벽.png", room2, 150, 400);
	auto door5 = Object::create("Images/문-오른쪽-열림.png", room3, 900, 273);
	auto hamster = Object::create("Images/햄스터.png", room3, 500, 100);
	auto key3 = Object::create("Images/최종열쇠.png", room3, 550, 150);
	key3->setScale(0.3f);

	auto picture2 = Object::create("Images/사진.png", room3, 100, 380);
	picture2->setScale(0.2f);

	bool door1_open = false;
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door1_open == true)
			room2->enter();
		
		else if (key1->isHanded()) {
			door1_open = true;
			object->setImage("Images/문-오른쪽-열림.png");
		}

		else
			showMessage("문이 잠겨있다");

		return true;
		});

	key1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key1->pick();
		return true;
		});

	picture_scr->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		picture_scr->hide();
		key1->hide();
		return true;
		});

	picture->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		picture_scr->show();
		key1->show();
		return true;
		});

	hammer->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		object->pick();
		return true;
		});

	bool pot_moved = false;
	pot->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (!pot_moved) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				object->locate(room1, 50, 50);
				pot_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				object->locate(room1, 350, 50);
				pot_moved = true;
			}
		}
		return true;
		});

	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room1->enter();
		return true;
		});

	bool door3_open = false;
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (key3->isHanded() == false) {
			if (key2->isHanded() || key1->isHanded())
				showMessage("열쇠가 맞지 않아");
			else
				showMessage("문이 잠겨있다");
		}
		
		else if (door3_open == false) {
			object->setImage("Images/비밀문-오른쪽-열림.png");
			showMessage("문이 열렸다!");
			door3_open = true;
		}
		else {
			endGame();
		}
		return true;
		});

	wall->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (hammer->isHanded()) {
			object->hide();
		}
		else
			showMessage("벽 뒤가 수상하다");
		return true;
		});

	crowbar->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		object->pick();
		return true;
		});

	bool key_picked = false;
	couch->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (crowbar->isHanded()) {
			key2->pick();
			key_picked = true;
			showMessage("열쇠를 얻었다");
		}
		else if (key_picked == false)
			showMessage("소파 아래 무언가 반짝인다");

		return true;
		});

	bool door4_open = false;
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door4_open == true)
			room3->enter();
		
		else if (key2->isHanded()) {
			door4_open = true;
			object->setImage("Images/검은문-열림.png");
		}

		else
			showMessage("문이 잠겨있다");

		return true;
		});

	beam->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door4_open == true)
			room3->enter();

		else if (key2->isHanded()) {
			door4_open = true;
			door4->setImage("Images/검은문-열림.png");
		}

		else
			showMessage("문이 잠겨있다");

		return true;
		});

	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("딸깍");
		if (lighted) {
			room1->setLight(0.8f);
			lighted = false;
			door4->show();
			beam->show();
		}

		else {
			if (door4_open) {
				room1->setLight(1.0f);
				beam->hide();
				lighted = true;
			}
			else {
				room1->setLight(1.0f);
				lighted = true;
				door4->hide();
				beam->hide();
			}
		}

		return true;
		});

	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		room1->enter();
		return true;
		});

	bool solved = false;
	hamster->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (solved == false) {
			showMessage("내가 가장 좋아하는 것을 맞추면 이걸 줄게");
			showKeypad("SEED", key3);
		}
		else
			showMessage("해바라기 씨가 세상에서 제일 좋아");

		return true;
		});

	key3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		object->pick();
		solved = true;
		showMessage("정답이야~");

		return true;
		});

	startGame(room1);

	return 0;

}