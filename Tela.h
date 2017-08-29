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
 * 2)Invocar Render(). A tela, caso n�o tenha sido criada, ser� criada nesse momento.
 * 3)Quando estiver pronto para come�ar o event loop, invocar StartEventLoop.
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
	/*Construtor - Cria a tela, mas para ela come�ar a captar os eventos, ativar o loop de 
	 * eventos, a ultima tela a ser criada ter� que invocar StartEventLoop();*/
	Tela( int left, int top, int width, int height);
	/*Renderiza a tela.*/
	void Render();
	/*Come�a o loop de eventos. O thread principal ir� entrar nessa fun��o e s� voltar� quando 
	 * a janela for fechada, ent�o deve ser a �ltima coisa a ser invocada porque o que vier depois
	 * dela s� ser� chamado quando a janela fechar.*/
	void StartEventLoop();

	void AddVolume(MyVolume& vol);

	void CriarObjetoDeTeste();

	void SetInteractorStyle(vtkSmartPointer<vtkInteractorStyle> style);
};
