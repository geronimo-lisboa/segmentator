#include "Tela.h"
#include <memory>
#include "imageLoader.h"
#include "myVolume.h"
#include "telaImagemInteractor.h"
using namespace std;

int main(int argc, char** argv)
{
	////Criação das telas
	shared_ptr<Tela> tela00, tela01;
	tela00 = make_shared<Tela>(0,0, 300, 300);
	tela00->Render();
	vtkSmartPointer<TelaImagemInteractor> tela00Interactor = vtkSmartPointer<TelaImagemInteractor>::New();
	tela00->SetInteractorStyle(tela00Interactor);
	tela01 = make_shared<Tela>(301, 0, 300, 300);
	tela01->CriarObjetoDeTeste();
	tela01->Render();
	//Carga da imagem e po-la na tela
	ImageLoader imgLoader;
	itk::Image<float, 3>::Pointer imagem = imgLoader.LoadImage("C:\\dicom\\Marching Man");
	MyVolume volume(imagem);
	tela00->AddVolume(volume);
	//Começa o loop de eventos
	tela01->StartEventLoop();
	return EXIT_SUCCESS;
}

