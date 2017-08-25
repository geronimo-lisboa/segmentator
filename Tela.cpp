#include "Tela.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkCubeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

Tela::Tela()
{
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetSize(300, 300);
	renderWindow->AddRenderer(renderer);
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);
}

void Tela::Render()
{
	renderWindow->Render();
}

void Tela::StartEventLoop()
{
	interactor->Start();
}

void Tela::CriarObjetoDeTeste()
{
	vtkSmartPointer<vtkCubeSource> testeCubeSource = vtkSmartPointer<vtkCubeSource>::New();
	testeCubeSource->SetCenter(0, 0, 0);
	testeCubeSource->SetXLength(1);
	testeCubeSource->SetYLength(1);
	testeCubeSource->SetZLength(1);
	vtkSmartPointer<vtkPolyDataMapper> testeCubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	testeCubeMapper->SetInputConnection(testeCubeSource->GetOutputPort());
	vtkSmartPointer<vtkActor> testeCubeActor = vtkSmartPointer<vtkActor>::New();
	testeCubeActor->SetMapper(testeCubeMapper);
	testeCubeActor->GetProperty()->SetColor(1.0000, 0.3882, 0.2784);
	testeCubeActor->RotateX(30.0);
	testeCubeActor->RotateY(-45.0);
	renderer->AddActor(testeCubeActor);
	renderer->ResetCamera();
}