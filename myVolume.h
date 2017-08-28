#pragma once
#include <itkImage.h>
#include <vtkImageImport.h>
#include <vtkImageData.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolume.h>
#include <vtkSmartPointer.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
class MyVolume
{
private:
	itk::Image<float, 3>::Pointer inputImage;
	vtkSmartPointer<vtkImageImport> importToVTK;
	vtkSmartPointer<vtkGPUVolumeRayCastMapper> mapper;
	vtkSmartPointer<vtkVolumeProperty> properties;
	vtkSmartPointer<vtkVolume> actor;
	vtkSmartPointer<vtkPiecewiseFunction> opacityFunction;
	vtkSmartPointer<vtkColorTransferFunction> colorFunction;
public:
	MyVolume(itk::Image<float, 3>::Pointer ptr);
	vtkSmartPointer<vtkVolume> GetActor();
};