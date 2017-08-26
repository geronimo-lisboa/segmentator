#pragma once
#include <itkImage.h>
#include <string>
/*Respons�vel por carregar as imagens.*/
class ImageLoader
{
public:
	itk::Image<float, 3>::Pointer LoadImage(std::string dir, std::string nomeSerie = "");
};