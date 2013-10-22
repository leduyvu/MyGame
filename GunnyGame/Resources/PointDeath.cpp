//
//  PointDeath.cpp
//  GunnyGame
//
//  Created by macbook_006 on 13/10/11.
//
//

#include "PointDeath.h"
PointDeath::PointDeath(){
}
PointDeath::~PointDeath(){}

void PointDeath::create(CCPoint start, CCPoint end){
    this->start = start;
    this->end = end;
    this->life = false;
}
bool PointDeath::getLife(){
    return this->life;
}
void PointDeath::setLife(){
    this->life = true;
}
bool PointDeath::checkLocation(CCPoint location){
    if(location.x < end.x && location.x > start.x && location.y <= start.y)
        return true;
    else return false;
}
CCPoint PointDeath::getStartPoint()
{
    return this->start;
}
CCPoint PointDeath::getEndPoint()
{
    return this->end;
}