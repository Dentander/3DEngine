#version 330 core
layout (location = 0) out vec4 fragColor;

uniform vec2 u_resolution;
uniform vec3 u_camera_position;
uniform vec2 u_camera_rotation;

const float FOV = 1.0;
const int MAX_STEPS = 256;
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

vec2 unionMaterial(vec2 res1, vec2 res2) {
    if (res1.x > res2.x) { return res2; }
    return res1;
}

vec2 map(vec3 p) {
    // plane
    float planeDist = fPlane(p, vec3(0, 1, 0), 1.0);
    float planeMaterial = 2.0;
    vec2 plane = vec2(planeDist, planeMaterial);
    // sphere
    float sphereDist = fSphere(p, 1);
    float sphereMaterial = 3.0;
    vec2 sphere = vec2(sphereDist, sphereMaterial);
    // sphere 2
    float sphereDist2 = fBox(vec3(p.x+2,p.y,p.z), vec3(1));
    float sphereMaterial2 = 1.0;
    vec2 sphere2 = vec2(sphereDist2, sphereMaterial2);
    // result
    vec2 result = unionMaterial(plane, sphere);
    result = unionMaterial(result, sphere2);
    return result;
}

vec2 rayMarch(vec3 ro, vec3 rd) {
    vec2 hit, object;
    for (int i = 0; i < MAX_STEPS; ++i) {
        vec3 p = ro + object.x * rd;
        hit = map(p);
        object.x += hit.x;
        object.y = hit.y;
        if (abs(hit.x) < EPSILON || object.x > MAX_DIST) { break; }
    }
    return object;
}

vec3 getNormal(vec3 p) {
    float epsilon = 0.0001;
    float centerDistance = map(p).x;
    float xDistance = map(p + vec3(epsilon, 0, 0)).x;
    float yDistance = map(p + vec3(0, epsilon, 0)).x;
    float zDistance = map(p + vec3(0, 0, epsilon)).x;
    vec3 normal = (vec3(xDistance, yDistance, zDistance) - centerDistance) / epsilon;
    return normal;
}

vec3 getLight(vec3 p, vec3 rd, vec3 color) {
    vec3 lightPos = vec3(20.0, 40.0, -30.0);
    vec3 L = normalize(lightPos - p);
    vec3 N = getNormal(p);

    vec3 diffuse = color * clamp(dot(L, N), 0, 1);

    // shadows
    float d = rayMarch(p + N * 0.02, normalize(lightPos)).x;
    if (d < length(lightPos - p)) { return vec3(0); }
    return diffuse;
}

vec3 myMix(vec3 a, vec3 b) {
    return (a + b) / 2.0;
}

vec3 getMaterial(vec3 p, vec3 rd, float material) {
    vec3 m;
    switch (int(material)) {
        case 1:
        m = vec3(1, 1, 1);
        for (int i = 2; i < 3; ++i) {
            vec3 N = getNormal(p);
            vec3 reflected = normalize(reflect(rd, N));
            vec2 object = rayMarch(p + reflected * 0.02, reflected);
            if (object.x < MAX_DIST && object.y != 1) { m *= vec3(0.0, 0.5, 0.5); break; }

            else { m *= vec3(0); }
        }
        break;

        case 2:
        m = vec3(0.0, 0.5, 0.5);
        break;
        case 3:
        m = vec3(0.9, 0.5, 0.5);
        break;
    }
    return normalize(m);
}

void render(inout vec3 color, in vec2 uv) {
    vec3 ro = u_camera_position;
    vec3 rd = normalize(vec3(uv, FOV));
    rd.zy *= rot(u_camera_rotation.y);
    rd.xz *= rot(-u_camera_rotation.x);
    vec2 object = rayMarch(ro, rd);
    if (object.x < MAX_DIST) {
        vec3 p = ro + object.x * rd;
        vec3 material = getMaterial(p, rd, object.y);
        color += getLight(p, rd, material);
    }
}

void main() {
    vec2 uv = (2.0 * gl_FragCoord.xy - u_resolution.xy) / u_resolution.y;
    uv.y = -uv.y;

    vec3 color;
    render(color, uv);

    // gamma correctiom
    color = pow(color, vec3(0.4545));
    fragColor = vec4(color, 1.0);
}