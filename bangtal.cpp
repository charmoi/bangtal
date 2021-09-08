#include <bangtal>
using namespace bangtal;

int main()
{
	auto room1 = Scene::create("��1", "Images/���-1.png");
	auto room2 = Scene::create("��2", "Images/���-2.png");
	auto room3 = Scene::create("��3", "Images/���-2.png");

	auto door1 = Object::create("Images/��-������-����.png", room1, 800, 270);
	auto door4 = Object::create("Images/������-����.png", room1, 220, 290, false);

	auto lights = Object::create("Images/����.png", room1, 500, 600);
	lights->setScale(0.7f);

	auto beam = Object::create("Images/��.png", room1, 200, 350, false);
	beam->setScale(0.3f);

	auto hammer = Object::create("Images/��ġ.png", room1, 235, 40);
	hammer->setScale(0.2f);

	auto pot = Object::create("Images/ȭ��.png", room1, 200, 50);
	pot->setScale(1.2f);

	auto picture = Object::create("Images/�����׸�.png", room1, 1000, 500);
	auto picture_scr = Object::create("Images/�׸�.png", room1, 350, 0, false);
	picture_scr->setScale(2.5f);

	auto key1 = Object::create("Images/���ڿ���.png", room1, 500, 80, false);
	key1->setScale(0.1f);

	auto door2 = Object::create("Images/��-����-����.png", room2, 220, 250);
	auto door3 = Object::create("Images/��й�-������-����.png", room2, 920, 270);
	door3->setScale(0.3f);

	auto wall = Object::create("Images/����.png", room2, 850, 254);
	wall->setScale(0.3f);

	auto crowbar = Object::create("Images/��������.png", room2, 1200, 50);
	crowbar->setScale(0.05f);

	auto key2 = Object::create("Images/����������.png", room2, 500, 320);
	key2->setScale(0.1f);

	auto couch = Object::create("Images/����.png", room2, 370, 240);
	couch->setScale(1.1f);

	auto sunflower = Object::create("Images/�عٶ��.png", room2, 120, 230);
	sunflower->setScale(0.2f);	

	auto bag = Object::create("Images/�ڷ�.png", room2, 620, 320);
	bag->setScale(0.1f);

	auto button = Object::create("Images/����ġ�޺�.png", room2, 150, 400);
	auto door5 = Object::create("Images/��-������-����.png", room3, 900, 273);
	auto hamster = Object::create("Images/�ܽ���.png", room3, 500, 100);
	auto key3 = Object::create("Images/��������.png", room3, 550, 150);
	key3->setScale(0.3f);

	auto picture2 = Object::create("Images/����.png", room3, 100, 380);
	picture2->setScale(0.2f);

	bool door1_open = false;
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door1_open == true)
			room2->enter();
		
		else if (key1->isHanded()) {
			door1_open = true;
			object->setImage("Images/��-������-����.png");
		}

		else
			showMessage("���� ����ִ�");

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
				showMessage("���谡 ���� �ʾ�");
			else
				showMessage("���� ����ִ�");
		}
		
		else if (door3_open == false) {
			object->setImage("Images/��й�-������-����.png");
			showMessage("���� ���ȴ�!");
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
			showMessage("�� �ڰ� �����ϴ�");
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
			showMessage("���踦 �����");
		}
		else if (key_picked == false)
			showMessage("���� �Ʒ� ���� ��¦�δ�");

		return true;
		});

	bool door4_open = false;
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door4_open == true)
			room3->enter();
		
		else if (key2->isHanded()) {
			door4_open = true;
			object->setImage("Images/������-����.png");
		}

		else
			showMessage("���� ����ִ�");

		return true;
		});

	beam->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door4_open == true)
			room3->enter();

		else if (key2->isHanded()) {
			door4_open = true;
			door4->setImage("Images/������-����.png");
		}

		else
			showMessage("���� ����ִ�");

		return true;
		});

	auto lighted = true;
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showMessage("����");
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
			showMessage("���� ���� �����ϴ� ���� ���߸� �̰� �ٰ�");
			showKeypad("SEED", key3);
		}
		else
			showMessage("�عٶ�� ���� ���󿡼� ���� ����");

		return true;
		});

	key3->setOnKeypadCallback([&](ObjectPtr object)->bool {
		object->pick();
		solved = true;
		showMessage("�����̾�~");

		return true;
		});

	startGame(room1);

	return 0;

}