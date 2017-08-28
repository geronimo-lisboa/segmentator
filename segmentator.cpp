#include "Tela.h"
#include <memory>
#include "imageLoader.h"
#include "myVolume.h"
#include <vtkSmartVolumeMapper.h>
#include <vtkDICOMImageReader.h>
using namespace std;

int main(int argc, char** argv)
{
	//ImageLoader imgLoader;
	//itk::Image<float, 3>::Pointer imagem = imgLoader.LoadImage("C:\\dicom\\Marching Man");
	//vtkSmartPointer<vtkImageImport> importToVTK = vtkSmartPointer<vtkImageImport>::New();
	//int szX = imagem->GetLargestPossibleRegion().GetSize()[0];
	//int szY = imagem->GetLargestPossibleRegion().GetSize()[1];
	//int szZ = imagem->GetLargestPossibleRegion().GetSize()[2];
	//double sX = imagem->GetSpacing()[0];
	//double sY = imagem->GetSpacing()[1];
	//double sZ = imagem->GetSpacing()[2];
	//double oX = imagem->GetOrigin()[0];
	//double oY = imagem->GetOrigin()[1];
	//double oZ = imagem->GetOrigin()[2];
	//importToVTK->SetDataSpacing(sX, sY, sZ);
	//importToVTK->SetDataOrigin(oX, oY, oZ);
	//importToVTK->SetWholeExtent(0, szX - 1, 0, szY - 1, 0, szZ - 1);
	//importToVTK->SetDataExtentToWholeExtent();
	//importToVTK->SetDataScalarTypeToFloat();
	//void* inputImagePtr = imagem->GetBufferPointer();
	//importToVTK->SetImportVoidPointer(inputImagePtr, 1);
	//importToVTK->Update();
	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName("C:\\dicom\\Marching Man");
	reader->Update();

	vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> ren1 = vtkSmartPointer<vtkRenderer>::New();
	ren1->SetBackground(0.1, 0.4, 0.2);
	renWin->AddRenderer(ren1);
	renWin->SetSize(301, 300); // intentional odd and NPOT  width/height
	vtkSmartPointer<vtkRenderWindowInteractor> iren = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	iren->SetRenderWindow(renWin);
	renWin->Render(); // make sure we have an OpenGL context.
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	volumeMapper->SetBlendModeToComposite(); // composite first
	volumeMapper->SetInputConnection(reader->GetOutputPort());
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->ShadeOff();
	volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	compositeOpacity->AddPoint(0.0, 0.0);
	compositeOpacity->AddPoint(900.0, 0.0);
	compositeOpacity->AddPoint(1500.0, 1.0);
	compositeOpacity->AddPoint(3000.0, 0.2);
	compositeOpacity->ClampingOn();
	volumeProperty->SetScalarOpacity(compositeOpacity); // composite first.

	vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
	color->AddRGBPoint(0.0, 0.0, 0.0, 1.0);
	color->AddRGBPoint(40.0, 1.0, 0.0, 0.0);
	color->AddRGBPoint(255.0, 1.0, 1.0, 1.0);
	color->ClampingOn();
	volumeProperty->SetColor(color);

	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	ren1->AddViewProp(volume);
	ren1->ResetCamera();

	renWin->Render();
	iren->Start();
	////Criação das telas
	//shared_ptr<Tela> tela00, tela01;
	//tela00 = make_shared<Tela>();
	//tela00->Render();
	//tela01 = make_shared<Tela>();
	//tela01->CriarObjetoDeTeste();
	//tela01->Render();
	////Carga da imagem e po-la na tela
	//ImageLoader imgLoader;
	//itk::Image<float, 3>::Pointer imagem = imgLoader.LoadImage("C:\\dicom\\Marching Man");
	//MyVolume volume(imagem);
	//tela00->AddVolume(volume);
	////Começa o loop de eventos
	//tela01->StartEventLoop();
	//return EXIT_SUCCESS;
}

