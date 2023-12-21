#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "func.fx"


static float3 g_vLightPos = float3(0.f, 0.f, 0.f);
static float3 g_vLightDir = float3(1.f, -1.f, 1.f);

static float3 g_vLightColor = float3(1.f, 1.f, 1.f);
static float3 g_vLightSpec = float3(0.3f, 0.3f, 0.3f);
static float3 g_vLightAmb = float3(0.15f, 0.15f, 0.15f); // ȯ�汤

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
    
    
    // ���ÿ����� Normal ������ ����� �̵�
    float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld)).xyz;
    
    // ����󿡼��� ������ ����
    g_vLightDir = normalize(g_vLightDir);
    
    // ����󿡼��� �븻���Ϳ� ������ ������ ���� (����Ʈ �ڻ��� ��Ģ)
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