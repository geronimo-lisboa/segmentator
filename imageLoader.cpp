#include "imageLoader.h"
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkCommand.h>
#include <sstream>

//Typedefs
typedef itk::Image<float, 3> ImageType;
typedef itk::ImageSeriesReader<ImageType> ReaderType;
typedef itk::GDCMImageIO ImageIOType;
typedef itk::GDCMSeriesFileNames NamesGeneratorType;
typedef std::vector< std::string >    SeriesIdContainer;
typedef std::vector< std::string >   FileNamesContainer;
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
		reader->AddObserver(itk::ProgressEvent(), obs);
		reader->Update();
		ImageType::Pointer result = reader->GetOutput();
		result->Print(std::cout);
		return result;
	}
	catch (itk::ExceptionObject& ex)
	{
		ex.Print(std::cout);
	}
}
