//
// SimplePS.hlsl
//

#include "MyShader.hlsli"
#include "Player.hlsli"


// 氷シェーダー
float4 Ice(PS_INPUT i)
{
	float4 col = float4(1, 1, 1, 1);
	float alpha = 1 - abs(dot(i.viewDir, i.normal));
	col.a = alpha;
	return col;
}

// リムライティングシェーダ
float4 RimLighting(PS_INPUT i, float4 v)
{
	float4 baseColor = float4(0, 1, 0, 1);
	float4 rimColor = v;

	float rim = 1 - saturate(dot(i.viewDir, i.normal));
	float4 emission = float4(rimColor.rgb, 1) * pow(rim, 1.5f);
	return baseColor + emission;
}

float4 main(PS_INPUT i) : SV_TARGET
{
	float4 col = float4(0, 1, 2, 1);
	float light = max(0, dot(i.lightDir, i.normal));
	col.rgb *= light;

	float4 rimColor = float4(0, 0, 1, 1);
	float rim = 1 - saturate(dot(i.viewDir, i.normal));
	float4 emission = rimColor * rim;

	return col + emission;
}