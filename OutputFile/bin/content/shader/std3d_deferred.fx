#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vNormal : NORMAL;
    float3 vTangent : TANGENT;
    float3 vBinormal : BINORMAL;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;
    float3 vViewNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
};

struct PS_OUT
{
    float4 vColor : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
    float4 vEmissive : SV_Target3;
    float4 vData : SV_Target4;
};

// ======================
// Std3D_DeferredShader
// MRT      | Deferred
// Domain   | DOMAIN_DEFERRED
// RS_TYPE  | CULL_BACK
// DS_TYPE  | LESS
// BS_TYPE  | DEFAULT

// Param
#define SPEC_COEFF g_float_0 // 반사 계수
//
VS_OUT VS_Std3D_Deferred(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    // 로컬에서의 Normal 방향을 월드로 이동    
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
    
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;
       
        
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
      
    return output;
}

PS_OUT PS_Std3D_Deferred(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT) 0.f;
    
    output.vColor = float4(1.f, 0.f, 1.f, 1.f);
    float3 vViewNormal = _in.vViewNormal;
    
    // OutputTex
    if (g_btex_0)
    {
        output.vColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        output.vColor.a = 1.f;
    }
    // NormalTex
    if (g_btex_1)
    {
        float3 vNormal = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
        
        // 단위 정렬 0~1 -> -1~1
        vNormal = vNormal * 2.f - 1.f;
        
        float3x3 vRotateMat =
        {
            _in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal        
        };
        
        vViewNormal = normalize(mul(vNormal, vRotateMat));
    }
    
    output.vNormal = float4(vViewNormal, 1.f);
    output.vPosition = float4(_in.vViewPos, 1.f);
    output.vEmissive = float4(0.1f, 0.1f, 0.1f, 1.f);
    output.vData = float4(0.f, 0.f, 0.f, 1.f);
    output.vColor.a = saturate(SPEC_COEFF);
    return output;
}

#endif