
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "rendering/geometry.h"
#include "typedefs/utils.h"

//Void Initialize
void Geometry::Initialize(ID3D11Device* dev)
{

	this->transform.position = Math::Vec3{0.0f, 0.0f, 0.0f};
	this->transform.scaling = Math::Vec3::unit_scale * 100.0f;
	this->transform.rotation = Math::Quaternion::identity;

	//Initialize variables
	this->vertexBuffer = 0;
	this->indexBuffer = 0;

	Vertex* vertices = new Vertex[4];
	ui32* indicies = new ui32[6];

	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT hr;

	//Set vertices and indicies
	vertices[0].position = fColorRGBA{ -1, 1, 0, 1.0f};
	vertices[0].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };

	vertices[1].position = fColorRGBA{ 1, 1, 0, 1.0f};
	vertices[1].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };

	vertices[2].position = fColorRGBA{ 1, -1, 0, 1.0f};
	vertices[2].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };

	vertices[3].position = fColorRGBA{ -1, -1, 0, 1.0f};
	vertices[3].color = fColorRGBA{ 0.960f, 0.713f, 0.0f, 1.0f };

	indicies[0] = 3;
	indicies[1] = 0;
	indicies[2] = 1;
	indicies[3] = 3;
	indicies[4] = 1;
	indicies[5] = 2;

	//Fill Buffers
	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = NULL;
	vertexBufferDesc.MiscFlags = NULL;
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_BUFFER_DESC indexBufferDesc = { 0 };
	indexBufferDesc.ByteWidth = sizeof(ui32) * 6;
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

	//Delete temporary pointers.
	delete[] vertices;
	delete[] indicies;
	
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

Transform Geometry::GetTransform(void)
{
	return this->transform;
}
//Void Cleanup
void Geometry::Cleanup(void)
{
	//Release pointers.
	vertexBuffer->Release();
	indexBuffer->Release();
}