#pragma once
#include <vtkRenderer.h>
#include <vtkCameraPass.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>
#include "MyVolume.h"
#include <vtkInteractorStyle.h>
#include <vtkLightsPass.h>
#include <vtkDefaultPass.h>
#include <vtkSequencePass.h>
#include <vtkRenderPassCollection.h>
#include <AntTweakBar.h>

/*A minha tela.
 * Forma de usar:
 * 1)Construir o objeto
 * 2)Invocar Render(). A tela, caso não tenha sido criada, será criada nesse momento.
 * 3)Quando estiver pronto para começar o event loop, invocar StartEventLoop.
 */
class Tela
{
private:
	vtkSmartPointer<vtkRenderWindow> renderWindow;
	vtkSmartPointer<vtkRenderer> renderer;
	vtkSmartPointer<vtkRenderWindowInteractor> interactor;
	
	vtkSmartPointer<vtkCameraPass> cameraPass;
	vtkSmartPointer<vtkLightsPass> lightPass;
	vtkSmartPointer<vtkDefaultPass> defaultPass;
	vtkSmartPointer<vtkSequencePass> sequencePass;
	vtkSmartPointer<vtkRenderPassCollection> passes;

public:
	/*Construtor - Cria a tela, mas para ela começar a captar os eventos, ativar o loop de 
	 * eventos, a ultima tela a ser criada terá que invocar StartEventLoop();*/
	Tela( int left, int top, int width, int height);
	/*Renderiza a tela.*/
	void Render();
	/*Começa o loop de eventos. O thread principal irá entrar nessa função e só voltará quando 
	 * a janela for fechada, então deve ser a última coisa a ser invocada porque o que vier depois
	 * dela só será chamado quando a janela fechar.*/
	void StartEventLoop();

	void AddVolume(MyVolume& vol);

	void CriarObjetoDeTeste();

	void SetInteractorStyle(vtkSmartPointer<vtkInteractorStyle> style);
};
