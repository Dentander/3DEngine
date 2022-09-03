#version 330 core

out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec3 u_camera_position;
uniform vec2 u_camera_rotation;
uniform vec3 u_background_color = vec3(0.5, 0.8, 0.9);

const float FOV = 1;
const int MAX_STEPS = 256;
const int MAX_REFLECTIONS = 100;
const float MAX_DIST = 500;
const float EPSILON = 0.001;

mat2 rot(float a) {
    float s = sin(a);
    float c = cos(a);
    return mat2(c, -s, s, c);
}
float sgn(float x) {
    return (x<0)?-1:1;
}
vec2 sgn(vec2 v) {
    return vec2((v.x<0)?-1:1, (v.y<0)?-1:1);
}
float square (float x) {
    return x*x;
}
vec2 square (vec2 x) {
    return x*x;
}
vec3 square (vec3 x) {
    return x*x;
}
float lengthSqr(vec3 x) {
    return dot(x, x);
}
float vmax(vec2 v) {
    return max(v.x, v.y);
}
float vmax(vec3 v) {
    return max(max(v.x, v.y), v.z);
}
float vmax(vec4 v) {
    return max(max(v.x, v.y), max(v.z, v.w));
}
float vmin(vec2 v) {
    return min(v.x, v.y);
}
float vmin(vec3 v) {
    return min(min(v.x, v.y), v.z);
}
float vmin(vec4 v) {
    return min(min(v.x, v.y), min(v.z, v.w));
}
float fSphere(vec3 p, float r) {
    return length(p) - r;
}
float fPlane(vec3 p, vec3 n, float distanceFromOrigin) {
    return dot(p, n) + distanceFromOrigin;
}
float fBox(vec3 p, vec3 b) {
    vec3 d = abs(p) - b;
    return length(max(d, vec3(0))) + vmax(min(d, vec3(0)));
}

/*vec2 unionMaterial(vec2 res1, vec2 res2) {
    if (res1.x > res2.x) { return res2; }
    return res1;
}*/

struct Object {
    float dist;
    vec3 color;
    int material;
};

Object unionMaterial(Object res1, Object res2) {
    if (res1.dist > res2.dist) { return res2; }
    return res1;
}

Object map(vec3 p) {
    // plane
    /*float planeDist = fPlane(p, vec3(0, 1, 0), 1.0);
    float planeMaterial = 2.0;
    vec2 plane = vec2(planeDist, planeMaterial);*/

    // sphere
    float sphereDist = fSphere(vec3(p.x + 2, p.y - 2, p.z), 1);
    int sphereMaterial = 0;
    Object sphere = Object(sphereDist, vec3(1, 0, 0), sphereMaterial);
    // sphere 2
    float sphereDist2 = fSphere(vec3(p.x, p.y - 2, p.z), 1);
    int sphereMaterial2 = 0;
    Object sphere2 = Object(sphereDist2, vec3(0, 1, 0), sphereMaterial2);
    // sphere 3
    float sphereDist3 = fSphere(vec3(p.x, p.y - 4, p.z), 1);
    int sphereMaterial3 = 1;
    Object sphere3 = Object(sphereDist3, vec3(1, 1, 1), sphereMaterial3);
    // result
    Object result = Object(sphereDist, vec3(1, 0, 0), sphereMaterial);
    result = unionMaterial(sphere2, sphere3);
    result = unionMaterial(result, sphere);
    return result;
}

Object rayMarch(vec3 ro, vec3 rd) {
    Object object, hit;
    for (int i = 0; i < MAX_STEPS; ++i) {
        vec3 p = ro + object.dist * rd;
        hit = map(p);
        object.dist += hit.dist;
        object.color = hit.color;
        object.material = hit.material;
        if (abs(hit.dist) < EPSILON || object.dist > MAX_DIST) { break; }
    }
    return object;
}

vec3 getNormal(vec3 p) {
    float epsilon = 0.005;
    float centerDistance = map(p).dist;
    float xDistance = map(p + vec3(epsilon, 0, 0)).dist;
    float yDistance = map(p + vec3(0, epsilon, 0)).dist;
    float zDistance = map(p + vec3(0, 0, epsilon)).dist;
    vec3 normal = (vec3(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
    return normal;
}

float getAmbientOcclusion(vec3 p, vec3 normal) {
    float occ = 0.0;
    float weight = 1.0;
    for (int i = 0; i < 8; i++) {
        float len = 0.01 + 0.02 * float(i * i);
        float dist = map(p + normal * len).dist;
        occ += (len - dist) * weight;
        weight *= 0.85;
    }
    return 1.0 - clamp(0.4 * occ, 0.0, 1.0);
}

float getSoftShadow(vec3 p, vec3 lightPos) {
    float res = 1.0;
    float dist = 0.01;
    float lightSize = 0.3;
    for (int i = 0; i < MAX_STEPS; i++) {
        float hit = map(p + lightPos * dist).dist;
        res = min(res, hit / (dist * lightSize));
        dist += hit;
        if (hit < 0.000001 || dist > 60.0) break;
    }
    return clamp(res, 0.0, 1.0);
}

vec3 getLight(vec3 p, vec3 rd, vec3 color) {
    vec3 lightPos = vec3(20.0, 55.0, -25.0);
    vec3 L = normalize(lightPos - p);
    vec3 N = getNormal(p);
    vec3 V = -rd;
    vec3 R = reflect(-L, N);

    vec3 specColor = vec3(0.6, 0.5, 0.4);
    vec3 specular = 1.3 * specColor * pow(clamp(dot(R, V), 0.0, 1.0), 10.0);
    vec3 diffuse = 0.9 * color * clamp(dot(L, N), 0.0, 1.0);
    vec3 ambient = 0.05 * color;
    vec3 fresnel = 0.15 * color * pow(1.0 + dot(rd, N), 3.0);

    // shadows
    float shadow = getSoftShadow(p + N * 0.02, normalize(lightPos));
    // occ
    float occ = getAmbientOcclusion(p, N);
    // back
    vec3 back = 0.05 * color * clamp(dot(N, -L), 0.0, 1.0);

    return  (back + ambient + fresnel) * occ + (specular * occ + diffuse) * shadow;
}

vec3 getPixelColor(vec3 p, vec3 rd, Object object) {
    vec3 color = vec3(-1);
    switch (object.material) {
        case 0:
        color = getLight(p, rd, object.color);
        break;

        case 1:
        color = object.color;
        float attenuationCoef = 1;
        float attenuation = 1.0;
        for (int i = 0; i < MAX_REFLECTIONS; ++i) {
            // attenuation
            attenuation *= attenuationCoef;
            // reflection
            vec3 N = getNormal(p);
            rd = normalize(reflect(rd, N));
            Object reflectedObject = rayMarch(p + rd * 0.02, rd);
            p += reflectedObject.dist * rd;
            // hit detection
            if (reflectedObject.dist < MAX_DIST && reflectedObject.material != 1) {
                color = mix(color, getLight(p, rd, reflectedObject.color), attenuation);
                break;
            } else if (reflectedObject.dist < MAX_DIST && reflectedObject.material == 1) {
                color = mix(color, getLight(p, rd, reflectedObject.color), attenuation);
            } else if (reflectedObject.dist >= MAX_DIST) {
                color = mix(color, u_background_color - max(0.6 * rd.y, 0.0), attenuation);
                break;
            }
        }
        break;
    }
    return color;
}

vec3 render(vec2 uv) {
    vec3 color;
    vec3 ro = u_camera_position;
    vec3 rd = normalize(vec3(uv, FOV));
    // rotate
    rd.zy *= rot(u_camera_rotation.y);
    rd.xz *= rot(-u_camera_rotation.x);
    // raymarching
    Object object = rayMarch(ro, rd);
    // hit detection
    if (object.dist < MAX_DIST) {
        // color
        vec3 p = ro + object.dist * rd;
        color = getPixelColor(p, rd, object);
        color = mix(color, u_background_color, 1 - exp(-0.0004 * object.dist * object.dist));
    } else {
        color = u_background_color - max(0.6 * rd.y, 0.0);
    }
    return color;
}

vec2 getUV(vec2 offset) {
    vec2 uv =  (2.0 * (gl_FragCoord.xy + offset) - u_resolution.xy) / u_resolution.y;
    uv.y = -uv.y;
    return uv;
}

vec3 AAx4() {
    vec4 e = vec4(0.125, -0.125, 0.375, -0.375);
    vec3 colorAAx4 = render(getUV(e.xz)) + render(getUV(e.yw)) + render(getUV(e.wx)) + render(getUV(e.zy));
    return colorAAx4 / 4.0;
}

void main() {
    vec3 color = AAx4();
    // gamma correctiom
    color = pow(color, vec3(0.4545));
    fragColor = vec4(color, 1.0);
}