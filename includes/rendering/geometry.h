
#pragma once
//EXTERNAL INCLUDES
#include <d3d11.h>
//INTERNAL INCLUDES
#include "typedefs/transform.h"

class Transform;

//Class ShaderGeometry.
class Geometry 
{
	//Declare the struct Vertex.
	struct Vertex 
	{
		fColorRGBA position;
		fColorRGBA color;
	};

//Declare public functions
public:
	void Initialize(ID3D11Device* dev);
	void Render(ID3D11DeviceContext* devcon);
	void Cleanup(void);
	Transform GetTransform(void);

//Declare private variables.
private:
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Transform transform;
};
