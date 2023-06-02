#include<windows.h>

#include "header.h"

extern HDC hdc;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

VirtualPoint::VirtualPoint(int InitX, int InitY)
{
	Visible = false;
	X = InitX;
	Y = InitY;
}

VirtualPoint::~VirtualPoint() {}

int VirtualPoint::GetX()
{
	return X;
};

int VirtualPoint::GetY()
{
	return Y;
};

void VirtualPoint::SetX(int NewX) {
	X = NewX;
}

void VirtualPoint::SetY(int NewY) {
	Y = NewY;
}

void VirtualPoint::Show()
{
	Visible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}

void VirtualPoint::Hide()
{
	Visible = false;
	SetPixel(hdc, X, Y, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}

bool VirtualPoint::IsVisible()
{
	return Visible;
};

void VirtualPoint::MoveTo(int NewX, int NewY)
{
	Hide();
	X = NewX;
	Y = NewY;
	Show();
};

void VirtualPoint::Drag(int Step)
{
	int FigX, FigY;
	FigX = GetX();
	FigY = GetY();

	if (KEY_DOWN(VK_ESCAPE)) {
		return;
	}

	if (KEY_DOWN(VK_LEFT))
	{
		FigX -= Step;
		MoveTo(FigX, FigY);
		Sleep(100);
	}

	if (KEY_DOWN(VK_RIGHT))
	{
		FigX += Step;
		MoveTo(FigX, FigY);
		Sleep(100);
	}

	if (KEY_DOWN(VK_DOWN))
	{
		FigY += Step;
		MoveTo(FigX, FigY);
		Sleep(100);
	}

	if (KEY_DOWN(VK_UP))
	{
		FigY -= Step;
		MoveTo(FigX, FigY);
		Sleep(100);
	}

}

ABC_Bus::ABC_Bus(int InitX, int InitY, int InitSide) : VirtualPoint(InitX, InitY) {
	Side = InitSide;
}

ABC_Bus::~ABC_Bus() {}

int ABC_Bus::GetSide() {
	return Side;
}

Bus::Bus(int InitX, int InitY, int InitSide) : ABC_Bus(InitX, InitY, InitSide) {}

Bus::~Bus() {};

void Bus::Paint() {
	SelectObject(hdc, BlackPen);
	Ellipse(hdc, X + 2.2 * Side, Y + Side - Side / 5, X + 2.6 * Side, Y + Side + Side / 5);
	Ellipse(hdc, X + 0.5 * Side, Y + Side - Side / 5, X + 0.9 * Side, Y + Side + Side / 5);
	Rectangle(hdc, X + 2 * Side, Y, X + 2.75 * Side, Y + Side / 3);
	Rectangle(hdc, X, Y, X + 2 * Side, Y + Side);
	Rectangle(hdc, X, Y - Side / 3, X + 2.5 * Side, Y);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 3 * Side, Y + Side);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 2.75 * Side, Y + Side);
	Rectangle(hdc, X + 0.2 * Side, Y + 0.1 * Side, X + 0.5 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 0.6 * Side, Y + 0.1 * Side, X + 0.9 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + Side, Y + 0.1 * Side, X + 1.3 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 1.4 * Side, Y + 0.1 * Side, X + 1.7 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 2.1 * Side, Y + Side / 2.6, X + 2.2 * Side, Y + Side / 2.3);
}

void Bus::Show() {
	Visible = true;
	Bus::Paint();
}

void Bus::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Rectangle(hdc, X, Y - Side / 3, X + 3 * Side, Y + Side + Side / 5);
}


ABC_Car::ABC_Car(int InitX, int InitY, int InitCarSide) : VirtualPoint(InitX, InitY)
{
	carSide = InitCarSide;
}

ABC_Car::~ABC_Car() {};

int ABC_Car::GetSide() {
	return carSide;
}

EnemyCar::EnemyCar(int InitX, int InitY, int InitCarSide) : ABC_Car(InitX, InitY, InitCarSide){}

EnemyCar::~EnemyCar() {};

EnemyVan::EnemyVan(int InitX, int InitY, int InitCarSide) : ABC_Car(InitX, InitY, InitCarSide) {}

EnemyVan::~EnemyVan() {};

void EnemyVan::Paint() {
	SelectObject(hdc, RedPen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 3, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
}

void EnemyCar::Paint() {
	SelectObject(hdc, RedPen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 2, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X + carSide * 2, Y, X + carSide * 3, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
	Rectangle(hdc, X + carSide / 1.5, Y, X + carSide * 1.5, Y - carSide / 2);
}

void EnemyVan::Show() {
	Visible = true;
	EnemyVan::Paint();
}

void EnemyCar::Show() {
	Visible = true;
	EnemyCar::Paint();
}

void EnemyVan::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 2, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X + carSide * 2, Y, X + carSide * 3, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
	Rectangle(hdc, X + carSide / 1.5, Y, X + carSide * 1.5, Y - carSide / 2);
}

void EnemyCar::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 2, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X + carSide * 2, Y, X + carSide * 3, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
	Rectangle(hdc, X + carSide / 1.5, Y, X + carSide * 1.5, Y - carSide / 2);
}

FriendCar::FriendCar(int InitX, int InitY, int InitCarSide) : ABC_Car(InitX, InitY, InitCarSide) {}

FriendCar::~FriendCar() {};

void FriendCar::Paint() {
	SelectObject(hdc, GreenPen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 2, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X + carSide * 2, Y, X + carSide * 3, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
	Rectangle(hdc, X + carSide / 1.5, Y, X + carSide * 1.5, Y - carSide / 2);
}

void FriendCar::Show() {
	Visible = true;
	FriendCar::Paint();
}

void FriendCar::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Ellipse(hdc, X - 2.25 * carSide, Y + 1.4 * carSide, X - carSide, Y);
	Ellipse(hdc, X + 2.5 * carSide, Y + 1.4 * carSide, X + 1.25 * carSide, Y);
	Rectangle(hdc, X - carSide, Y + carSide, X + carSide * 2, Y - carSide);
	Rectangle(hdc, X - carSide, Y, X - carSide * 2.5, Y + carSide);
	Rectangle(hdc, X + carSide * 2, Y, X + carSide * 3, Y + carSide);
	Rectangle(hdc, X - carSide / 2, Y, X + carSide / 3, Y - carSide / 2);
	Rectangle(hdc, X + carSide / 1.5, Y, X + carSide * 1.5, Y - carSide / 2);
}

BusWithBonnet::BusWithBonnet(int InitX, int InitY, int InitSide) : ABC_Bus(InitX, InitY, InitSide) {}

BusWithBonnet::~BusWithBonnet() {};

void BusWithBonnet::Paint() {
	SelectObject(hdc, BlackPen);
	Ellipse(hdc, X + 2.2 * Side, Y + Side - Side / 5, X + 2.6 * Side, Y + Side + Side / 5);
	Ellipse(hdc, X + 0.5 * Side, Y + Side - Side / 5, X + 0.9 * Side, Y + Side + Side / 5);
	Rectangle(hdc, X + 2 * Side, Y, X + 2.75 * Side, Y + Side / 3);
	Rectangle(hdc, X, Y, X + 2 * Side, Y + Side);
	Rectangle(hdc, X, Y - Side / 3, X + 2.5 * Side, Y);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 2.75 * Side, Y + Side);
	Rectangle(hdc, X + 0.2 * Side, Y + 0.1 * Side, X + 0.5 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 0.6 * Side, Y + 0.1 * Side, X + 0.9 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + Side, Y + 0.1 * Side, X + 1.3 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 1.4 * Side, Y + 0.1 * Side, X + 1.7 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 2.1 * Side, Y + Side / 2.6, X + 2.2 * Side, Y + Side / 2.3);
}

void BusWithBonnet::Show() {
	Visible = true;
	BusWithBonnet::Paint();
}

void BusWithBonnet::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Rectangle(hdc, X, Y - Side / 3, X + 3 * Side, Y + Side + Side / 5);
}

BusWithRoof::BusWithRoof(int InitX, int InitY, int InitSide) : ABC_Bus(InitX, InitY, InitSide) {}

BusWithRoof::~BusWithRoof() {};

void BusWithRoof::Paint() {
	SelectObject(hdc, BlackPen);
	Ellipse(hdc, X + 2.2 * Side, Y + Side - Side / 5, X + 2.6 * Side, Y + Side + Side / 5);
	Ellipse(hdc, X + 0.5 * Side, Y + Side - Side / 5, X + 0.9 * Side, Y + Side + Side / 5);
	Rectangle(hdc, X + 2 * Side, Y, X + 2.75 * Side, Y + Side / 3);
	Rectangle(hdc, X, Y, X + 2 * Side, Y + Side);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 3 * Side, Y + Side);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 2.75 * Side, Y + Side);
	Rectangle(hdc, X + 0.2 * Side, Y + 0.1 * Side, X + 0.5 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 0.6 * Side, Y + 0.1 * Side, X + 0.9 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + Side, Y + 0.1 * Side, X + 1.3 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 1.4 * Side, Y + 0.1 * Side, X + 1.7 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 2.1 * Side, Y + Side / 2.6, X + 2.2 * Side, Y + Side / 2.3);
}

void BusWithRoof::Show() {
	Visible = true;
	BusWithRoof::Paint();
}

void BusWithRoof::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Rectangle(hdc, X, Y - Side / 3, X + 3 * Side, Y + Side + Side / 5);
}

BusWithRoofAndBonnet::BusWithRoofAndBonnet(int InitX, int InitY, int InitSide) : ABC_Bus(InitX, InitY, InitSide) {}

BusWithRoofAndBonnet::~BusWithRoofAndBonnet() {};

void BusWithRoofAndBonnet::Paint() {
	SelectObject(hdc, BlackPen);
	Ellipse(hdc, X + 2.2 * Side, Y + Side - Side / 5, X + 2.6 * Side, Y + Side + Side / 5);
	Ellipse(hdc, X + 0.5 * Side, Y + Side - Side / 5, X + 0.9 * Side, Y + Side + Side / 5);
	Rectangle(hdc, X + 2 * Side, Y, X + 2.75 * Side, Y + Side / 3);
	Rectangle(hdc, X, Y, X + 2 * Side, Y + Side);
	Rectangle(hdc, X + 2 * Side, Y + Side / 3, X + 2.75 * Side, Y + Side);
	Rectangle(hdc, X + 0.2 * Side, Y + 0.1 * Side, X + 0.5 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 0.6 * Side, Y + 0.1 * Side, X + 0.9 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + Side, Y + 0.1 * Side, X + 1.3 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 1.4 * Side, Y + 0.1 * Side, X + 1.7 * Side, Y + 0.3 * Side);
	Rectangle(hdc, X + 2.1 * Side, Y + Side / 2.6, X + 2.2 * Side, Y + Side / 2.3);
}

void BusWithRoofAndBonnet::Show() {
	Visible = true;
	BusWithRoofAndBonnet::Paint();
}

void BusWithRoofAndBonnet::Hide() {
	Visible = false;
	SelectObject(hdc, WhitePen);
	Rectangle(hdc, X, Y - Side / 3, X + 3 * Side, Y + Side + Side / 5);
}