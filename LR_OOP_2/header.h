using namespace std;

#include<iostream>

extern HPEN WhitePen;
extern HPEN BlackPen;
extern HPEN RedPen;
extern HPEN GreenPen;
const int CarCount = 3;
const int BusCount = 4;

class InterfacePoint {
public:
	virtual void Hide() = 0;
	virtual void Show() = 0;
};

class VirtualPoint : public InterfacePoint
{
protected:
	bool Visible;
	int X;
	int Y;

public:
	VirtualPoint(int InitX, int InitY);
	virtual ~VirtualPoint();

	int GetX();
	int GetY();

	bool IsVisible();
	void Drag(int Step);

	void SetX(int NewX);
	void SetY(int NewY);

	void MoveTo(int NewX, int NewY);

	virtual void Show();
	virtual void Hide();
};

class ABC_Bus : public VirtualPoint {
protected: 
	int Side;

public:
	ABC_Bus(int InitX, int InitY, int InitSide);
	virtual ~ABC_Bus();

	virtual void Paint() = 0;
	int GetSide();
};

class ABC_Car : public VirtualPoint
{
protected:
	int carSide;

public:
	ABC_Car(int InitX, int InitY, int initCarSide);
	virtual ~ABC_Car();

	virtual void Paint() = 0;
	int GetSide();
};

class EnemyCar : public ABC_Car
{
public:
	EnemyCar(int InitX, int InitY, int carSide);
	~EnemyCar();

	void Paint();

	void Show();
	void Hide();
};

class EnemyVan : public ABC_Car
{
public:
	EnemyVan(int InitX, int InitY, int carSide);
	~EnemyVan();

	void Paint();

	void Show();
	void Hide();
};

class FriendCar : public ABC_Car
{
public:
	FriendCar(int InitX, int InitY, int carSide);
	~FriendCar();

	void Paint();

	void Show();
	void Hide();
};

class Bus : public ABC_Bus
{
public:
	Bus(int InitX, int InitY, int side);
	~Bus(); 

	void Paint();

	void Show();
	void Hide();

	
};

class BusWithBonnet : public ABC_Bus
{
public:
	BusWithBonnet(int InitX, int InitY, int side);
	~BusWithBonnet();

	void Paint();

	void Show();
	void Hide();
};

class BusWithRoof : public ABC_Bus
{
public:
	BusWithRoof(int InitX, int InitY, int side);
	~BusWithRoof();

	void Paint();

	void Show();
	void Hide();
};

class BusWithRoofAndBonnet : public ABC_Bus
{
public:
	BusWithRoofAndBonnet(int InitX, int InitY, int side);
	~BusWithRoofAndBonnet();

	void Paint();

	void Show();
	void Hide();
};