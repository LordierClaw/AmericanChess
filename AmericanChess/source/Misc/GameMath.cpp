#include "GameMath.h"

float GameMath::getAngle(sf::Vector2f firstPos, sf::Vector2f secondPos) {
    float d, r, h;
    h = secondPos.y - firstPos.y;
    d = secondPos.x - firstPos.x;
    r = (float)sqrt(d * d + h * h);
    float angle = (float)acos((d * d + r * r - h * h) / (2 * d * r));
    if (h < 0) angle = 2 * PI - angle;
    return angle;
}

float GameMath::getDistance(sf::Vector2f firstPos, sf::Vector2f secondPos) {
    float d, h;
    h = secondPos.y - firstPos.y;
    d = secondPos.x - firstPos.x;
    return sqrt(d * d + h * h);
}

float GameMath::getHarmonicMotion(float length, float duration, float currentTime, float initialPhase) {
    return length * cos(PI / duration * currentTime + PI*initialPhase);
}

sf::Vector2f GameMath::getMovingEquation(sf::Vector2f firstPos, sf::Vector2f secondPos, float duration, float currentTime) {
    float x = firstPos.x + (secondPos.x - firstPos.x) * currentTime/duration;
    float y = firstPos.y + (secondPos.y - firstPos.y) * currentTime/duration;
    return sf::Vector2f(x, y);
}

float GameMath::radToDegree(float angle) {
    return angle * 180 / PI;
}