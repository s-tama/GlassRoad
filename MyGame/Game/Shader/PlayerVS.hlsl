//
// SimpleVS.hlsl
//

#include "MyShader.hlsli"
#include "Player.hlsli"


PS_INPUT main(VS_INPUT i)
{
	PS_INPUT o = (PS_INPUT)0;
	o.pos = i.pos;
	o.normal = i.normal;

	return o;
}