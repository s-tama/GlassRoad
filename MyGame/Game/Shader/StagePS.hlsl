//
// StagePS.hlsl
//

#include "MyShader.hlsli"
#include "Stage.hlsli"


float4 main(PS_INPUT i) : SV_TARGET
{
	float4 col = float4(0, 0.8f, 1, 1);

	float light = max(0, dot(i.lightDir, i.normal));
	col.rgb *= light;

	/*float alpha = 1 - abs(dot(i.viewDir, i.normal));
	col.a = alpha;*/

	float4 rimColor = float4(1, 1, 1, 1);
	float rim = 1 - saturate(dot(i.viewDir, i.normal));
	float4 emission = float4(rimColor.rgb, 1) * pow(rim, 1);

	return col + emission;
}