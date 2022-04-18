#pragma once

#include <string>
#include "Stats.h"

class cEngine;

namespace olc
{
	class Sprite;
}

class cDynamic
{
protected:
	float fTime; // czas aktualizacji animacji
	cEngine* engine; // wska�nik do silnika gry
	olc::Sprite* sprite; // grafika obiektu
	float fKnockbackTimer; // timer czasu w powietrzu (knockback)
	void SlowDown(float& v, float fElapsedTime, float rate);
public:
	cDynamic(cEngine* _engine);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, bool _friendly);

	enum INTERACT_NATURE	//enum mo�liwych typ�w interakcji z obiektem
	{
		INTERACT_KEY,
		WALK_ON,
		TALK
	};

	//////////////////////		KONFIGUTACJA cDynamic		//////////////////////
	std::string sName;	// nazwa

	float px;	// pozycja w �wiecie gry
	float py;
	float vx;	// pr�dko��
	float vy;
	float fWidth;	// wymiary
	float fHeight;
	bool bSolidVsSolid;	// podleganie kolizji statycznej
	bool bSolidVsDynamic;// i dynamicznej
	short nLayer;	//warstwa od kt�rej zale�y w jakiej kolejno�ci obiekt jest rysowany (0 - przedmioty na ziemii i elementy mapy, 1 - zw�oki/nieprzytomni, 2 - domy�lna, 3 - lataj�ce, 4 - emotki)
	bool bFriendly; // czy obiekt jest przyjazny graczowi
	bool bIsProjectile; // czy obiekt jest pociskiem
	bool bIsKnockbacked; // czy obiekt jest w powietrzu
	bool bIsRedundant; // czy obiekt powinien zosta� usuni�ty
	float fProjectileTime; // czas aktualizacji istnienia jako pocisk
	bool bInvincible; // nie�miertelno�� obiektu

	// Metody: //
	virtual void Knockback(float x, float y, float time) { }	// "zwyk�y" obiekt dynamiczny nie posiada obs�ugi odrzutu 
	virtual void ReceiveDamage(float dmg) { }					// ani bycia zaatakowanym
	virtual void DrawSelf(float fOffsetX, float fOffsetY);
	virtual bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* object) { return false; }	//funkcja powinna zwr�ci� true je�li g��wna p�tla gry ma si� zacz��
																											// na nowo po wykonaniu interakcji (np. teleportacja i zmiana mapy)
	//aktualizacja obiektu wywo�ywana w ka�dej klatce
	virtual void Update(float fElapsedTime, cDynamic* player = nullptr) {};				
	//////////////////////////////////////////////////////////////////////////////

	bool bIsMovedByScript;
	virtual void ZeroNewVelocities() { } // wywo�ywana przy skryptach maj�cych ca�kowicie zatrzyma� posta� po ich zako�czeniu

	enum Direction
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	} nDirection;
};

class cDynamicCreature : public cDynamic
{
public:
	enum CREATURE_STATE
	{
		STATE_STANDING,
		STATE_WALKING,
		STATE_DEAD,
		STATE_MELEE_ATTACK,
		STATE_SLEEPING,
		STATE_UNCONSCIOUS
	}	nState;
public:
	//////////////////////		KONFIGUTACJA cDynamicCreature		//////////////////////

	float fMaxHP; // zdrowie obecne i maksymalne
	float fHP;
	cCreatureStats stats; // statystyki bojowe
	float fAnimationDefaultInterval; // domy�lny okres aktualizacji animacji (kiedy obiekt si� nie porusza) (domy�lnie 1.0f)
	float fAIUpdateInterval; // okres aktualizacji AI (domy�lnie 1.0f)
	float fProneToKnockbackMultiplier; // mno�nik pocz�tkowej szybko�ci nadawanej stworowi przy byciu odrzuconym (im wi�cej tym wi�ksza pocz�tkowa pr�dko�� - efekt mniejszej masy stwora) (domy�lnie 1.0f)
	float fKnockbackSpeedDeclineMultiplier; // mno�nik szybko�ci zanikania pr�dko�ci odrzutu (im wi�cej tym szybciej stw�r spowalnia po zostaniu odrzuconym - efekt mniejszego po�lizgu) (domy�lnie 1.0f)
	bool bIsResistantToKnockback; // odporno�� na odrzut (domy�lnie false)
	float fAIActivationDistance; // dystans aktywacji AI (domy�lnie 5.0f)
	float fWalkAnimationSpeedMultiplier; // mno�nik szybko�ci wykonywania animacji podczas chodzenia (wa�ne: ta jest aktualizowana zale�nie od szybko�ci stwora) (domy�lnie 1.0f)
	bool bWalkAnimationAlwaysOn; // flaga zmieniaj�ca spos�b animowania stwora na taki w kt�rym ci�gle jest wykonywana animacja poruszania (np. stwory lataj�ce) (domy�lnie false)
	float fMaxWalkingVel; // szybko�� poruszania si� obiektu (domy�lnie (bazowa szybko�� gracza) 2.0f)

	//////////////////////////////////////////////////////////////////////////////////////
protected:
	int nFrame; // klatka animacji - albo 0, albo 1
	float fAnimationInterval; // okres aktualizacji animacji (przy ruchu obliczany dynamicznie w zale�no�ci od pr�dko�ci)
	float fTime2; // czas aktualizacji AI
public:
	float fTime3; // czas aktualizacji ataku wr�cz
	float fTime4; // czas aktualizacji okresu bezruchu po wykonaniu ataku wr�cz
	short nDefaultLayer; // domy�lna warstwa rysowania
protected:
	float fScalarSpeed; // pr�dko�c skalarna (obliczana przez ClampWalkingVel())

	float fNewvx; // potencjalne nowe pr�dko�ci
	float fNewvy; // (aktualizowane przez AI)
public:
	cDynamicCreature(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, 
		float _sizex, float _sizey, CREATURE_STATE _state, float _maxHP, bool _friendly, short _layer = 2);

	////////////
	// Przyk�adowe AI:
	void AI_SimpleFollow(float fElapsedTime, cDynamic* player); // outdated!
	void AI_SimpleFollowHostile(float fElapsedTime, cDynamic* player);
	void AI_Default(float fElapsedTime, cDynamic* player);
	/////////////

	float fMaxAxisSpeed; // szybko�� poruszania si� obiektu w osiach ( aktualizowane automatycznie )
	
	// wywo�ywana przy skryptach maj�cych ca�kowicie zatrzyma� posta� po ich zako�czeniu
	void ZeroNewVelocities()	{	fNewvx = 0.0f;	fNewvy = 0.0f;	}
	void SetState(CREATURE_STATE _state);
	void ReceiveDamage(float dmg);
	virtual void PerformAttack(cDynamic* target);
	virtual void PerformInstantAttack(cDynamic* target);
	void DrawSelf(float fOffsetX, float fOffsetY);
	virtual void Update(float fElapsedTime, cDynamic* player);

	// domy�lne AI - nie robi nic, przekazuje dalej potencjalne nowe pr�dko�ci w niezmienionej formie - takie AI ma tylko gracz i obiekty kt�rych nie da si� zatakowa�
	virtual void UpdateAI(float fElapsedTime, cDynamic* player) {	fNewvx = vx;	fNewvy = vy;	}
	void ClampWalkingVel(); // wa�ne: aktualizuje skalarn� szybko�� obiektu
	virtual void Knockback(float x, float y, float time); // odrzut
};

class c3FrameAnimatedDynamic : public cDynamic
{
private:
	short nFrame;
	float fFrameTime;
public:
	void DrawSelf(float fOffsetX, float fOffsetY);
	void Update(float fElapsedTime, cDynamic* player = nullptr);
	c3FrameAnimatedDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, float _frametime = 1.0f);
	c3FrameAnimatedDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, float _frametime = 1.0f);
};

class cOpenable : public cDynamic
{
protected:
	bool bOpen;
	short nFrame;
	bool bAnimOpening;
	bool bAnimClosing;
	float fFrameTime;
	bool bHasBeenYetOpened;
public:
	void Open() { bAnimOpening = true; }
	virtual void FirstOpen() { }
	bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* target) override;
	void DrawSelf(float fOffsetX, float fOffsetY);
	virtual void Update(float fElapsedTime, cDynamic* player = nullptr);
	cOpenable(cEngine* _engine, float _px, float _py, olc::Sprite* _sprite, std::string _name, bool _solidvssolid, bool _solidvsdynamic, float _frametime = 0.3f);
};
