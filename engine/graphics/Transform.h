#pragma once
#include "../math/vec3.h"


class Transform {
private:
    // ======== PARAMETERS ========
    Transform &parent;
    bool firstTransform = true;
    vec3<float> pos;
    vec3<float> angle;
    vec3<float> size;

public:
    // ======== INITIALIZATION ========
    Transform(): pos(0, 0, 0), angle(0, 0, 0), size(0, 0, 0), parent(*this) {}
    Transform(vec3<float> pos, vec3<float> angle, vec3<float> size): pos(pos), angle(angle), size(size), parent(*this) {}
    Transform(vec3<float> pos, vec3<float> angle, vec3<float> size, Transform *parent): pos(pos), angle(angle), size(size), parent(*parent) { firstTransform = false; }

    // ======== GETTERS ========
    vec3<float> getPosG() { return (firstTransform) ?  pos  : pos + parent.getPosG(); }
    vec3<float> getAngleG() { return (firstTransform) ? angle : angle + parent.getAngleG(); }
    vec3<float> getSizeG() { return (firstTransform) ? size : size + parent.getSizeG(); }
    vec3<float> getPosL() { return pos; }
    vec3<float> getAngleL() { return angle; }

    // ======== SETTERS ========
    void setPos(vec3<float> value) { pos = value; }
    void setAngle(vec3<float> value) { angle = value; }
    void setSize(vec3<float> value) { size = value; }
    void setParent(Transform &_parent) { parent = _parent; if(*this == parent) { firstTransform = false; } }

    // ======== ADDITION ========
    void addPos(vec3<float> value) {pos = pos + value;}
    void addPos(vec2<float> value) {pos.x += value.x; pos.y += value.y;}
    void addAngle(vec3<float> value) {pos = pos + value;}
    void addAngle(vec2<float> value) {angle.x += value.x; angle.y += angle.y;}
    void addSize(vec3<float> value) {pos = pos + value;}
    Transform operator+(Transform const &other){ return Transform(pos + other.pos, angle + other.angle, size * other.size, this); }
    Transform& operator=(Transform other) { pos=other.pos; angle=other.angle; size=other.size; return *this; }
    bool operator==(Transform other) { return pos == other.pos && angle == other.angle && size == other.size; }
};
