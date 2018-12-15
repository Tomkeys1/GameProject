
#pragma once
//EXTERNAL INCLUDES
#include <d3d11.h>
//INTERNAL INCLUDES
#include "typedefs/transform.h"

class Gameobject;

//Class ShaderGeometry.
class Geometry 
{
//Declare public functions
public:
	Geometry(Gameobject* gb, fColorRGBA col);
	Geometry(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength, Gameobject* gb);

	void Initialize(ID3D11Device* dev);
	void Render(ID3D11DeviceContext* devcon);
	void Cleanup(void);
	void SetColor(fColorRGBA color);

	Gameobject* GetGameobject(void);

	ui32 vLength;
	ui32 iLength;

//Declare private variables.
private:
	D3D11_SUBRESOURCE_DATA* vertexData;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	Gameobject* gameobject;

	Vertex* vertices;
	ui32* indicies;

	fColorRGBA color;

};
