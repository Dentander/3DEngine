#include "ParameterSystem.h"

paramTypes& ParameterSystem::get(const std::string& name) {
    static paramTypes exit_failure = -1;
    if (contains(name)) {
        return params[name];
    } else {
        getError();
        return exit_failure;
    }
}

void ParameterSystem::insert(const std::string& name, paramTypes &value) {
    if (!contains(name)) {
        params.insert( { name, value } );
    } else {
        getError();
    }
}

void ParameterSystem::set(const std::string& name, paramTypes value) {
    try {
        params[name] = value;
    }
    catch (...) {
        getError();
    }
}

void ParameterSystem::getError() {
    gotError = true;
}

bool ParameterSystem::gotErrors(bool _clearErrors) {
    bool tmp = gotError;
    if (_clearErrors) { clearErrors(); }
    return tmp;
}

void ParameterSystem::clearErrors() {
    gotError = false;
}

vec2f &ParameterSystem::getVec2(const std::string &name) {
    static vec2f exit_failure(-1);
    if(contains(name)) {
        return reinterpret_cast<vec2f &>(params[name]);
    } else {
        getError();
        return exit_failure;
    }
}

vec3f &ParameterSystem::getVec3(const std::string &name) {
    static vec3f exit_failure(-1);
    if (contains(name)) {
        return reinterpret_cast<vec3f &>(params[name]);
    } else {
        getError();
        return exit_failure;
    }
}

float &ParameterSystem::getFloat(const std::string &name) {
    static float exit_failure = -1;
    if (contains(name)) {
        return reinterpret_cast<float &>(params[name]);
    } else {
        getError();
        return exit_failure;
    }
}

int &ParameterSystem::getInt(const std::string &name) {
    static int exit_failure = -1;
    if (contains(name)) {
        return reinterpret_cast<int &>(params[name]);
    } else {
        getError();
        return exit_failure;
    }
}

bool ParameterSystem::contains(const std::string& name) {
    return params.find(name) != params.end();
}

std::string ParameterSystem::toUniformAll() {
    std::string result;
    for (const auto& item : params) { result += toUniform(item) + "\n"; }
    return result;
}

std::string ParameterSystem::toUniform(const std::pair<std::string, paramTypes>& object) {
    std::string name = object.first;
    paramTypes item = object.second;

    if (std::holds_alternative<int>(item)) { return "uniform int " + name + ";"; }
    else if (std::holds_alternative<float>(item)) { return "uniform float " + name + ";"; }
    else if (std::holds_alternative<vec2f>(item)) { return "uniform vec2 " + name + ";"; }
    else if (std::holds_alternative<vec3f>(item)) { return "uniform vec3 " + name + ";"; }
    return "// error";
}
