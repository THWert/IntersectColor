#include "framework.h"

Utility::RECT::RECT(Vector2 pivot, Vector2 scale)
{
    min.x = pivot.x - scale.x * 0.5f;
    min.y = pivot.y - scale.y * 0.5f;
    max.x = pivot.x + scale.x * 0.5f;
    max.y = pivot.y + scale.y * 0.5f;
}

Utility::CIRCLE::CIRCLE(Vector2 pivot, Vector2 scale)
{
    this->pivot = pivot;
    radius = scale.x * 0.5f;
}

bool Utility::IntersectRectCoord(RECT & rc, Vector2 coord)
{
    if (rc.min.x < coord.x && coord.x < rc.max.x &&
        rc.min.y < coord.y && coord.y < rc.max.y)
    {
        return true;
    }
    return false;
}

bool Utility::IntersectRectRect(RECT & rc1, RECT & rc2)
{
    return false;
}

bool Utility::IntersectRectRect(GameObject* ob1, GameObject* ob2)
{
    return false;
}

bool Utility::IntersectRectCircle(RECT & rc, CIRCLE & cc)
{
    return false;
}

bool Utility::IntersectCircleCoord(CIRCLE & cc, Vector2 coord)
{
    Vector2 distance = cc.pivot - coord;

    if (distance.Length() < cc.radius)
    {
        return true;
    }
    return false;
}

bool Utility::IntersectCircleCircle(CIRCLE & cc1, CIRCLE & cc2)
{
    return false;
}

float Utility::DirToRadian(Vector2 Dir)
{
    //만약 단위벡터가 아니라면
    Dir.Normalize();
    return atan2f(Dir.y, Dir.x);
}
