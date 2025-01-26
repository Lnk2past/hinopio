#version 430

layout(local_size_x = 32, local_size_y = 32, local_size_z = 1) in;

layout(std430, binding = 0) buffer DataBuffer {
    int data[];
};


uniform vec2 size;         // Image width - 1, height - 1
uniform vec2 cmin;         // Complex plane bottom left point
uniform vec2 cdelta;       // Complex plane visualization range


void main() {
    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy); // This pixel (x, y)
    vec2 c = cdelta * pixel / size + cmin;         // Interpolate c

    int  depth = 0;
    vec2 z     = c;
    vec2 z2    = c * c;
    for(; depth <= 1000 && z2.x + z2.y <= 4.0f; ++depth) {
        z  = vec2(z2.x - z2.y, 2 * z.x * z.y) + c;
        z2 = z * z;
    }

    data[pixel.x + pixel.y * int(size.x)] = depth;
}
