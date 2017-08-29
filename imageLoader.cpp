#include "imageLoader.h"
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkCommand.h>
#include <sstream>
#include <itkOrientImageFilter.h>

//Typedefs
typedef itk::Image<float, 3> ImageType;
typedef itk::ImageSeriesReader<ImageType> ReaderType;
typedef itk::GDCMImageIO ImageIOType;
typedef itk::GDCMSeriesFileNames NamesGeneratorType;
typedef std::vector< std::string >    SeriesIdContainer;
typedef std::vector< std::string >   FileNamesContainer;
typedef itk::OrientImageFilter<ImageType, ImageType> OrientImageFilterType;
//O observador do progresso da carga para eu ter alguma resposta do que está acontecendo.
namespace itk
{
	class myProgressObserver :public Command
	{
	public:
		//ITK macro - takes care of defining the static New() that all
		//itk object must have to be compatible with ITK's memory manegement.
		itkNewMacro(myProgressObserver);

		void Execute(itk::Object *caller, const itk::EventObject & event)
		{
			Execute((const itk::Object *)caller, event);
		}

		void Execute(const itk::Object * object, const itk::EventObject & event)
		{
			const itk::ProcessObject  *processObj = dynamic_cast<const itk::ProcessObject*>(object);
			std::cout << processObj->GetProgress() << std::endl;
		}
	};
}

itk::Image<float, 3>::Pointer ImageLoader::LoadImage(std::string dir, std::string nomeSerie)
{
	ReaderType::Pointer reader = ReaderType::New();
	ImageIOType::Pointer imageIOObject = ImageIOType::New();
	reader->SetImageIO(imageIOObject);
	itk::myProgressObserver::Pointer obs = itk::myProgressObserver::New();
	NamesGeneratorType::Pointer nameGenerator = NamesGeneratorType::New();
	nameGenerator->AddObserver(itk::ProgressEvent(), obs);
	nameGenerator->SetUseSeriesDetails(true);
	nameGenerator->SetDirectory(dir);
	//This list has all the images in the directory
	SeriesIdContainer seriesUID = nameGenerator->GetSeriesUIDs();
	for(std::string str : seriesUID)
	{
		std::cout << "id = " << str << std::endl;
	}
	FileNamesContainer fileNames;
	if(seriesUID.size()==1)
	{
		fileNames = nameGenerator->GetFileNames(seriesUID[0]);
	}
	else
	{
		for(auto i=0; i<seriesUID.size(); i++)
		{
			if(seriesUID[i]==nomeSerie)
			{
				fileNames = nameGenerator->GetFileNames(seriesUID[0]);
				break;
			}
		}
		//Se chegou até aqui tá errado.
		std::stringstream ss;
		ss <<__FUNCTION__<< " nenhuma serie com o id = " << nomeSerie << " encontrada no diretório = " << dir;
		throw std::exception(ss.str().c_str());
	}
	reader->SetFileNames(fileNames);
	try
	{
		//Carrega
		reader->AddObserver(itk::ProgressEvent(), obs);
		reader->Update();
		ImageType::Pointer result = reader->GetOutput();
		result->Print(std::cout);
		//Reorienta pra que a imagem esteja sempre RIP
		OrientImageFilterType::Pointer reorientador = OrientImageFilterType::New();
		reorientador->SetInput(result);
		reorientador->AddObserver(itk::ProgressEvent(), obs);
		reorientador->UseImageDirectionOn();
		reorientador->SetDesiredCoordinateOrientation(itk::SpatialOrientation::ITK_COORDINATE_ORIENTATION_RIP);
		reorientador->Update();
		//Copia o resultado do reorientador pq ele vai morrer.
		ImageType::Pointer output = ImageType::New();
		const int inSzX = reorientador->GetOutput()->GetLargestPossibleRegion().GetSize()[0];
		const int inSzY = reorientador->GetOutput()->GetLargestPossibleRegion().GetSize()[1];
		const int inSzZ = reorientador->GetOutput()->GetLargestPossibleRegion().GetSize()[2];
		const double inSpacingX = reorientador->GetOutput()->GetSpacing()[0];
		const double inSpacingY = reorientador->GetOutput()->GetSpacing()[1];
		const double inSpacingZ = reorientador->GetOutput()->GetSpacing()[2];
		output->SetRegions(reorientador->GetOutput()->GetLargestPossibleRegion());
		output->Allocate();
		itk::ImageRegionConstIterator<ImageType> inputIterator(reorientador->GetOutput(), reorientador->GetOutput()->GetLargestPossibleRegion());
		itk::ImageRegionIterator<ImageType> outputIterator(output, output->GetLargestPossibleRegion());
		const double inSpacing[] = { inSpacingX, inSpacingY, inSpacingZ };
		output->SetSpacing(inSpacing);
		while (!inputIterator.IsAtEnd())
		{
			outputIterator.Set(inputIterator.Get());
			++inputIterator;
			++outputIterator;
		}
		//resultado
		return output;
	}
	catch (itk::ExceptionObject& ex)
	{
		ex.Print(std::cout);
	}
}
