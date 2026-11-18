#pragma once
#include "GameCharacter.h"
class Enemy :
    public GameCharacter
{
public:
    float MoveCooldown;
    float MinMoveInterval = 1.5;
    float MaxMoveInterval = 2;
  //  void UpdateNavigation(double _deltaTime);
};

