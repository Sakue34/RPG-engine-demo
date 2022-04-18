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
	cEngine* engine; // wskaŸnik do silnika gry
	olc::Sprite* sprite; // grafika obiektu
	float fKnockbackTimer; // timer czasu w powietrzu (knockback)
	void SlowDown(float& v, float fElapsedTime, float rate);
public:
	cDynamic(cEngine* _engine);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic);
	cDynamic(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, bool _friendly);

	enum INTERACT_NATURE	//enum mo¿liwych typów interakcji z obiektem
	{
		INTERACT_KEY,
		WALK_ON,
		TALK
	};

	//////////////////////		KONFIGUTACJA cDynamic		//////////////////////
	std::string sName;	// nazwa

	float px;	// pozycja w œwiecie gry
	float py;
	float vx;	// prêdkoœæ
	float vy;
	float fWidth;	// wymiary
	float fHeight;
	bool bSolidVsSolid;	// podleganie kolizji statycznej
	bool bSolidVsDynamic;// i dynamicznej
	short nLayer;	//warstwa od której zale¿y w jakiej kolejnoœci obiekt jest rysowany (0 - przedmioty na ziemii i elementy mapy, 1 - zw³oki/nieprzytomni, 2 - domyœlna, 3 - lataj¹ce, 4 - emotki)
	bool bFriendly; // czy obiekt jest przyjazny graczowi
	bool bIsProjectile; // czy obiekt jest pociskiem
	bool bIsKnockbacked; // czy obiekt jest w powietrzu
	bool bIsRedundant; // czy obiekt powinien zostaæ usuniêty
	float fProjectileTime; // czas aktualizacji istnienia jako pocisk
	bool bInvincible; // nieœmiertelnoœæ obiektu

	// Metody: //
	virtual void Knockback(float x, float y, float time) { }	// "zwyk³y" obiekt dynamiczny nie posiada obs³ugi odrzutu 
	virtual void ReceiveDamage(float dmg) { }					// ani bycia zaatakowanym
	virtual void DrawSelf(float fOffsetX, float fOffsetY);
	virtual bool OnInteract(cDynamic* player, INTERACT_NATURE nature, cDynamic* object) { return false; }	//funkcja powinna zwróciæ true jeœli g³ówna pêtla gry ma siê zacz¹æ
																											// na nowo po wykonaniu interakcji (np. teleportacja i zmiana mapy)
	//aktualizacja obiektu wywo³ywana w ka¿dej klatce
	virtual void Update(float fElapsedTime, cDynamic* player = nullptr) {};				
	//////////////////////////////////////////////////////////////////////////////

	bool bIsMovedByScript;
	virtual void ZeroNewVelocities() { } // wywo³ywana przy skryptach maj¹cych ca³kowicie zatrzymaæ postaæ po ich zakoñczeniu

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
	float fAnimationDefaultInterval; // domyœlny okres aktualizacji animacji (kiedy obiekt siê nie porusza) (domyœlnie 1.0f)
	float fAIUpdateInterval; // okres aktualizacji AI (domyœlnie 1.0f)
	float fProneToKnockbackMultiplier; // mno¿nik pocz¹tkowej szybkoœci nadawanej stworowi przy byciu odrzuconym (im wiêcej tym wiêksza pocz¹tkowa prêdkoœæ - efekt mniejszej masy stwora) (domyœlnie 1.0f)
	float fKnockbackSpeedDeclineMultiplier; // mno¿nik szybkoœci zanikania prêdkoœci odrzutu (im wiêcej tym szybciej stwór spowalnia po zostaniu odrzuconym - efekt mniejszego poœlizgu) (domyœlnie 1.0f)
	bool bIsResistantToKnockback; // odpornoœæ na odrzut (domyœlnie false)
	float fAIActivationDistance; // dystans aktywacji AI (domyœlnie 5.0f)
	float fWalkAnimationSpeedMultiplier; // mno¿nik szybkoœci wykonywania animacji podczas chodzenia (wa¿ne: ta jest aktualizowana zale¿nie od szybkoœci stwora) (domyœlnie 1.0f)
	bool bWalkAnimationAlwaysOn; // flaga zmieniaj¹ca sposób animowania stwora na taki w którym ci¹gle jest wykonywana animacja poruszania (np. stwory lataj¹ce) (domyœlnie false)
	float fMaxWalkingVel; // szybkoœæ poruszania siê obiektu (domyœlnie (bazowa szybkoœæ gracza) 2.0f)

	//////////////////////////////////////////////////////////////////////////////////////
protected:
	int nFrame; // klatka animacji - albo 0, albo 1
	float fAnimationInterval; // okres aktualizacji animacji (przy ruchu obliczany dynamicznie w zale¿noœci od prêdkoœci)
	float fTime2; // czas aktualizacji AI
public:
	float fTime3; // czas aktualizacji ataku wrêcz
	float fTime4; // czas aktualizacji okresu bezruchu po wykonaniu ataku wrêcz
	short nDefaultLayer; // domyœlna warstwa rysowania
protected:
	float fScalarSpeed; // prêdkoœc skalarna (obliczana przez ClampWalkingVel())

	float fNewvx; // potencjalne nowe prêdkoœci
	float fNewvy; // (aktualizowane przez AI)
public:
	cDynamicCreature(cEngine* _engine, std::string _name, float _px, float _py, olc::Sprite* spr, bool _solidvssolid, bool _solidvsdynamic, 
		float _sizex, float _sizey, CREATURE_STATE _state, float _maxHP, bool _friendly, short _layer = 2);

	////////////
	// Przyk³adowe AI:
	void AI_SimpleFollow(float fElapsedTime, cDynamic* player); // outdated!
	void AI_SimpleFollowHostile(float fElapsedTime, cDynamic* player);
	void AI_Default(float fElapsedTime, cDynamic* player);
	/////////////

	float fMaxAxisSpeed; // szybkoœæ poruszania siê obiektu w osiach ( aktualizowane automatycznie )
	
	// wywo³ywana przy skryptach maj¹cych ca³kowicie zatrzymaæ postaæ po ich zakoñczeniu
	void ZeroNewVelocities()	{	fNewvx = 0.0f;	fNewvy = 0.0f;	}
	void SetState(CREATURE_STATE _state);
	void ReceiveDamage(float dmg);
	virtual void PerformAttack(cDynamic* target);
	virtual void PerformInstantAttack(cDynamic* target);
	void DrawSelf(float fOffsetX, float fOffsetY);
	virtual void Update(float fElapsedTime, cDynamic* player);

	// domyœlne AI - nie robi nic, przekazuje dalej potencjalne nowe prêdkoœci w niezmienionej formie - takie AI ma tylko gracz i obiekty których nie da siê zatakowaæ
	virtual void UpdateAI(float fElapsedTime, cDynamic* player) {	fNewvx = vx;	fNewvy = vy;	}
	void ClampWalkingVel(); // wa¿ne: aktualizuje skalarn¹ szybkoœæ obiektu
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
