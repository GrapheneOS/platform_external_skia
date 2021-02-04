#include <metal_stdlib>
#include <simd/simd.h>
using namespace metal;
struct Uniforms {
    float4 colorGreen;
};
struct Inputs {
};
struct Outputs {
    float4 sk_FragColor [[color(0)]];
};

fragment Outputs fragmentMain(Inputs _in [[stage_in]], constant Uniforms& _uniforms [[buffer(0)]], bool _frontFacing [[front_facing]], float4 _fragCoord [[position]]) {
    Outputs _out;
    (void)_out;
    int i1 = 0;
    i1++;
    int i2 = 305441740;
    i2++;
    int i3 = 2147483646;
    i3++;
    int i4 = -2147483647;
    i4++;
    int i5 = -48879;
    i5++;
    _out.sk_FragColor = _uniforms.colorGreen;
    return _out;
}
