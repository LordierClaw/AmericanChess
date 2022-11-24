#include "GameMath.h"

float GameMath::getAngle(sf::Vector2f firstPos, sf::Vector2f secondPos) {
    float d, r, h;
    h = secondPos.y - firstPos.y;
    d = secondPos.x - firstPos.x;
    if (d == 0) d = 0.00001; //we dont want divide by zero
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

float GameMath::degreeToRad(float angle) {
    return angle * PI / 180;
}

int GameMath::getRandom(int start, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(start, end);
    return dist(gen);
}
