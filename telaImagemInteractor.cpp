#include "telaImagemInteractor.h"
#include "vtkObjectFactory.h" 
vtkStandardNewMacro(TelaImagemInteractor);

TelaImagemInteractor::TelaImagemInteractor()
{
	
}
TelaImagemInteractor::~TelaImagemInteractor()
{
	
}

void TelaImagemInteractor::PrintSelf(ostream &os, vtkIndent indent)
{
	vtkInteractorStyleTrackballCamera::PrintSelf(os, indent);
}
