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
	importToVTK->SetDataScalarTypeToFloat();
	void* inputImagePtr = inputImage->GetBufferPointer();
	importToVTK->SetImportVoidPointer(inputImagePtr, 1);
	importToVTK->Update();
	//Agora o mapper
	mapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	mapper->SetMaxMemoryFraction(0.9);
	mapper->GetLockSampleDistanceToInputSpacingMinValue();
	mapper->SetInputData((vtkImageData*)importToVTK->GetOutputDataObject(0));
	mapper->Update();
	properties = vtkSmartPointer<vtkVolumeProperty>::New();
	opacityFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
	opacityFunction->AddSegment(0.0, 0.0,    1000.0, 0.0);
	opacityFunction->AddSegment(1000.0, 0.0, 1400.0, 0.2);
	opacityFunction->AddSegment(1400.0, 0.2, 2000.0, 0.8);
	opacityFunction->AddSegment(2000.0, 0.8, 3000.0, 1.0);

	opacityFunction->ClampingOn();
	properties->SetScalarOpacity(opacityFunction);
	colorFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
	colorFunction->AddRGBSegment(0.0, 0.0,0.0,0.0, 1000.0, 0.0,0.0,0.0);
	colorFunction->AddRGBSegment(1000.0, 1.0, 0.0, 0.0, 1400.0, 1.0, 0.0, 0.0);
	colorFunction->AddRGBSegment(1400.0, 1.0, 1.0, 0.0, 2000.0, 1.0, 1.0, 0.0);
	colorFunction->AddRGBSegment(2000.0, 1.0, 1.0, 1.0, 3000.0, 1.0, 1.0, 1.0);

	colorFunction->ClampingOn();
	properties->SetColor(colorFunction);
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
