#include "Tela.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkCubeSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"

#include <vtkObjectFactory.h>




Tela::Tela( int left, int top, int width, int height)
{
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->SetPosition(left, top);
	renderWindow->SetSize(width, height);
	renderWindow->AddRenderer(renderer);
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(renderWindow);

	lightPass = vtkSmartPointer<vtkLightsPass>::New();
	defaultPass = vtkSmartPointer<vtkDefaultPass>::New();
	passes = vtkSmartPointer<vtkRenderPassCollection>::New();
	passes->AddItem(lightPass);
	passes->AddItem(defaultPass);
	sequencePass = vtkSmartPointer<vtkSequencePass>::New();
	sequencePass->SetPasses(passes);
	cameraPass = vtkSmartPointer<vtkCameraPass>::New();
	cameraPass->SetDelegatePass(sequencePass);
	renderer->SetPass(cameraPass);
}

void Tela::Render()
{
	renderWindow->Render();
}

void Tela::StartEventLoop()
{
	interactor->Start();
}

void Tela::AddVolume(MyVolume& vol)
{
	renderer->AddVolume(vol.GetActor());
	renderer->ResetCamera();
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

void Tela::SetInteractorStyle(vtkSmartPointer<vtkInteractorStyle> style)
{
	interactor->SetInteractorStyle(style);
}
