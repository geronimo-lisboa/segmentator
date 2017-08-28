#include "myVolume.h"
MyVolume::MyVolume(itk::Image<float, 3>::Pointer ptr)
{
	this->inputImage = ptr;
	importToVTK = vtkSmartPointer<vtkImageImport>::New();

	//De itk::image pra vtkImageData;
	importToVTK = vtkSmartPointer<vtkImageImport>::New();
	int szX = inputImage->GetLargestPossibleRegion().GetSize()[0];
	int szY = inputImage->GetLargestPossibleRegion().GetSize()[1];
	int szZ = inputImage->GetLargestPossibleRegion().GetSize()[2];
	double sX = inputImage->GetSpacing()[0];
	double sY = inputImage->GetSpacing()[1];
	double sZ = inputImage->GetSpacing()[2];
	double oX = inputImage->GetOrigin()[0];
	double oY = inputImage->GetOrigin()[1];
	double oZ = inputImage->GetOrigin()[2];
	importToVTK->SetDataSpacing(sX, sY, sZ);
	importToVTK->SetDataOrigin(oX, oY, oZ);
	importToVTK->SetWholeExtent(0, szX - 1, 0, szY - 1, 0, szZ - 1);
	importToVTK->SetDataExtentToWholeExtent();
	importToVTK->SetDataScalarTypeToShort();
	void* inputImagePtr = inputImage->GetBufferPointer();
	importToVTK->SetImportVoidPointer(inputImagePtr, 1);
	importToVTK->Update();
	//Agora o mapper
	mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	mapper->SetMaxMemoryFraction(0.9);
	mapper->SetInputData((vtkImageData*)importToVTK->GetOutputDataObject(0));
	mapper->Update();
	properties = vtkSmartPointer<vtkVolumeProperty>::New();
	//opacityFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	//opacityFunction->AddSegment(0, 0, 300, 0.2);
	//opacityFunction->AddSegment(301, 0.2, 800, 0.8);
	//opacityFunction->AddSegment(801, 0.8, 1200, 1);
	//properties->SetScalarOpacity(opacityFunction);
	//colorFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	//colorFunction->AddRGBSegment(0, 0, 0, 0, 300, 1, 0, 0);
	//colorFunction->AddRGBSegment(301, 1, 0, 0, 800, 1, 1, 0);
	//colorFunction->AddRGBSegment(801, 1, 1, 0, 1200, 1, 1, 1);
	//properties->SetColor(colorFunction);
	properties->ShadeOn();
	//Propriedades definindas
	actor = vtkSmartPointer<vtkVolume>::New();
	actor->SetProperty(properties);
	actor->SetMapper(mapper);
}

vtkSmartPointer<vtkVolume> MyVolume::GetActor()
{
	return actor;
}
