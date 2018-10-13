
#pragma once
//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "fileinterface.h"
#include "typedefs/types.h"

class WinFile : public IFile
{
//Declare public functions
public:
	WinFile(const char* path);

	virtual std::string GetName() override;
	virtual std::string GetDirectory() override;
	virtual i64 GetSize() override;
	virtual bool FindFile(const char* path) override;
	virtual byte* Read() override;
private:
	virtual void Initialize(const char* path) override;
	std::string mFileName;
	std::string mDirectory;
	byte* mBuffer;
	iptr mHandle;
	ui64 mSize;
};
