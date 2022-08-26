#pragma once
#include <map>
#include <variant>
#include <engine/math/vec3.h>
#include <engine/patterns/Singleton.h>
#define paramTypes std::variant<float, int, vec3f, vec2f>


class ParameterSystem : public Singleton<ParameterSystem> {
private:
    bool gotError = false;
    std::map<std::string, paramTypes> params;
    
    void getError();
    static std::string toUniform(const std::pair<std::string, paramTypes>& object);

public:
    ParameterSystem() = default;

    bool contains(const std::string &name);
    void insert(const std::string &name, paramTypes &value);
    paramTypes &get(const std::string &name);
    vec2f &getVec2(const std::string &name);
    vec3f &getVec3(const std::string &name);
    float &getFloat(const std::string &name);
    int &getInt(const std::string &name);
    void set(const std::string &name, paramTypes value);
    void clearErrors();
    bool gotErrors(bool clearErrors=true);
    std::string toUniformAll();
};

