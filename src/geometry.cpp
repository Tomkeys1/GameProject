
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "rendering/geometry.h"
#include "typedefs/utils.h"

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

	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT hr;

	//Fill Buffers
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * this->vLength;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = NULL;
	vertexBufferDesc.MiscFlags = NULL;
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = sizeof(ui32) * this->iLength;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = NULL;
	indexBufferDesc.MiscFlags = NULL;

	//Fill Data
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	indexData.pSysMem = indicies;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Create Buffer and crash the program if it wasnt succesful.
	V_RETURN(dev->CreateBuffer(&vertexBufferDesc, &vertexData, &this->vertexBuffer));
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

Gameobject* Geometry::GetGameobject(void)
{
	return this->gameobject;
}
