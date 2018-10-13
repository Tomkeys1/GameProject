cbuffer Matrices
{
    matrix mvp;
};

struct VertexIN
{
    float4 position : POSITION;
    float4 color    : COLOR;
};
struct VertexOUT
{ 
	float4 position : SV_POSITION;
	float4 color    : COLOR;
};

VertexOUT Default_VS(in VertexIN input)
{
	VertexOUT output;

    output.position = mul(mvp,float4(input.position.xyz, 1.0f));
	//output.position = float4(output.position.xyz, 1.0f);
    output.color = input.color;

    return output;
}

float4 Default_PS(in VertexOUT input) : SV_TARGET
{
    return input.color;
}
