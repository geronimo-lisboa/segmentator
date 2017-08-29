#pragma once
#include <vtkInteractorStyleTrackballCamera.h>
#include <iostream>
class TelaImagemInteractor : public vtkInteractorStyleTrackballCamera
{
private:
	TelaImagemInteractor(const TelaImagemInteractor&);  
	void operator=(const TelaImagemInteractor&);  
protected:
	TelaImagemInteractor();
	~TelaImagemInteractor();
public:
	static TelaImagemInteractor *New();
	void PrintSelf(ostream &os, vtkIndent indent);
};