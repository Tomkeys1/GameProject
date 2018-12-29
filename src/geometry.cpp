
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "rendering/geometry.h"
#include "typedefs/utils.h"

Geometry::Geometry(Gameobject* gb, fColorRGBA col)
{
	this->color = col;

	Vertex* v = new Vertex[4];
	ui32* i = new ui32[6];

	v[0].position = fColorRGBA{ -1, 1, 0, 1.0f };
	v[0].color = this->color;
	
	v[1].position = fColorRGBA{ 1, 1, 0, 1.0f };
	v[1].color = this->color;

	v[2].position = fColorRGBA{ 1, -1, 0, 1.0f };
	v[2].color = this->color;

	v[3].position = fColorRGBA{ -1, -1, 0, 1.0f };
	v[3].color = this->color;

	i[0] = 3;
	i[1] = 0;
	i[2] = 1;
	i[3] = 3;
	i[4] = 1;
	i[5] = 2;

	
	this->vertices = v;
	this->indicies = i;
	this->vLength = 4;
	this->iLength = 6;
	this->gameobject = gb;
}

Geometry::Geometry(Vertex* vertices, ui32* indicies, ui32 vLength, ui32 iLength, Gameobject* gb)
{
	this->vertices = vertices;
	this->indicies = indicies;

	this->vLength = vLength;
	this->iLength = iLength;

	this->gameobject = gb;
}

//Void Initialize
void Geometry::Initialize(ID3D11Device* dev)
{
	//Initialize variables
	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	this->vertexData = new D3D11_SUBRESOURCE_DATA;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT hr;

	//Fill Buffers
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * this->vLength;
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = NULL;
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = sizeof(ui32) * this->iLength;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = NULL;
	indexBufferDesc.MiscFlags = NULL;

	//Fill Data
	this->vertexData->pSysMem = vertices;
	this->vertexData->SysMemPitch = 0;
	this->vertexData->SysMemSlicePitch = 0;

	indexData.pSysMem = indicies;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create Buffer and crash the program if it wasnt succesful.
	V_RETURN(dev->CreateBuffer(&vertexBufferDesc, vertexData, &this->vertexBuffer));
	V_RETURN(dev->CreateBuffer(&indexBufferDesc, &indexData, &this->indexBuffer));
}

//Void Render
void Geometry::Render(ID3D11DeviceContext* devcon)
{
	//Define the size of struct Vertex.
	ui32 pStrides = sizeof(Vertex);
	ui32 offset = 0;

	//Set Buffers to Input Assembler Stage
	devcon->IASetVertexBuffers(0, 1, &this->vertexBuffer, &pStrides, &offset);
	devcon->IASetIndexBuffer(this->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Set the Topology to Input Assembler Stage
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}

//Void Cleanup
void Geometry::Cleanup(void)
{
	//Release pointers.
	vertexBuffer->Release();
	indexBuffer->Release();
}

void Geometry::SetColor(fColorRGBA color)
{
	this->vertices[0].color = color;
	this->vertices[1].color = color;
	this->vertices[2].color = color;
	this->vertices[3].color = color;

	this->color = color;

	this->vertexData->pSysMem = vertices;
}

Gameobject* Geometry::GetGameobject(void)
{
	return this->gameobject;
}

Vertex* Geometry::GetVertices(void)
{
	return this->vertices;
}
