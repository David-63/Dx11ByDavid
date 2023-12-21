#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "func.fx"


static float3 g_vLightPos = float3(0.f, 0.f, 0.f);
static float3 g_vLightDir = float3(1.f, -1.f, 1.f);

static float3 g_vLightColor = float3(1.f, 1.f, 1.f);
static float3 g_vLightSpec = float3(0.3f, 0.3f, 0.3f);
static float3 g_vLightAmb = float3(0.15f, 0.15f, 0.15f); // 환경광

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vNormal : NORMAL;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float fLightPow : FOG;
};


VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    
    // 로컬에서의 Normal 방향을 월드로 이동
    float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld)).xyz;
    
    // 월드상에서의 광원의 방향
    g_vLightDir = normalize(g_vLightDir);
    
    // 월드상에서의 노말벡터와 광원의 방향을 내적 (램버트 코사인 법칙)
    float fLightPow = saturate(dot(vWorldNormal, -g_vLightDir));
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    output.fLightPow = fLightPow;
    
    return output;
}


float4 PS_Std3D(VS_OUT _in) : SV_Target
{
    float4 vOutColor = (float4) 0.f;
    
    vOutColor = float4(1.f, 0.f, 1.f, 1.f);    
    vOutColor.xyz = (vOutColor.xyz * _in.fLightPow) + (vOutColor.xyz * g_vLightAmb);
    
    return vOutColor;
}

#endif