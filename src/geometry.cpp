
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "rendering/geometry.h"
#include "typedefs/utils.h"

Geometry::Geometry(Gameobject* gb, fColorRGBA col, Meshes mesh)
{
	this->color = col;
	this->meshType = mesh;
	
	switch (mesh)
	{
	case Meshes::BOX:
		this->vertices = new Vertex[4];
		this->indicies = new ui32[6];

		this->vertices[0].position = fColorRGBA{ -1, 1, 0, 1.0f };
		this->vertices[0].color = this->color;

		this->vertices[1].position = fColorRGBA{ 1, 1, 0, 1.0f };
		this->vertices[1].color = this->color;

		this->vertices[2].position = fColorRGBA{ 1, -1, 0, 1.0f };
		this->vertices[2].color = this->color;

		this->vertices[3].position = fColorRGBA{ -1, -1, 0, 1.0f };
		this->vertices[3].color = this->color;

		this->indicies[0] = 3;
		this->indicies[1] = 0;
		this->indicies[2] = 1;
		this->indicies[3] = 3;
		this->indicies[4] = 1;
		this->indicies[5] = 2;

		this->vLength = 4;
		this->iLength = 6;
		break;

	case Meshes::TRIANGLE:
		this->vertices = new Vertex[3];
		this->indicies = new ui32[3];

		this->vertices[0].position = fColorRGBA{ -1, -1, 0, 1.0f };
		this->vertices[0].color = this->color;

		this->vertices[1].position = fColorRGBA{ 0, 0, 0, 1.0f };
		this->vertices[1].color = this->color;

		this->vertices[2].position = fColorRGBA{ 1, -1, 0, 1.0f };
		this->vertices[2].color = this->color;

		this->indicies[0] = 0;
		this->indicies[1] = 1;
		this->indicies[2] = 2;

		this->vLength = 3;
		this->iLength = 3;
		break;

	}

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

fColorRGBA Geometry::GetColor(void)
{
	return this->color;
}

Meshes Geometry::GetMeshType(void)
{
	return this->meshType;
}
