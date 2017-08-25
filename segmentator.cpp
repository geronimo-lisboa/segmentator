#include "Tela.h"
#include <memory>
using namespace std;
int main(int argc, char** argv)
{
	shared_ptr<Tela> tela00, tela01;
	tela00 = make_shared<Tela>();
	tela00->CriarObjetoDeTeste();
	tela00->Render();
	tela01 = make_shared<Tela>();
	tela01->CriarObjetoDeTeste();
	tela01->Render();
	tela01->StartEventLoop();
	return EXIT_SUCCESS;
}

