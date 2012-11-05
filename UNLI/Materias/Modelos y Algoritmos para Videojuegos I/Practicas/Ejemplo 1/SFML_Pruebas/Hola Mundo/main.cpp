////////////////////////////////////////////////////////////
// Librerías
////////////////////////////////////////////////////////////
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
////////////////////////////////////////////////////////////
/// Punto de entrada a la aplicación
////////////////////////////////////////////////////////////
int main(){
	// Creamos la ventana
	sf::RenderWindow App(sf::VideoMode(800, 600, 32),
	"Que ventana horrible");
	// Loop principal
	while (App.IsOpened())
	{
		// Limpiamos la ventana
		App.Clear();
		//Dibujamos la escena
		// Mostramos la ventana
		App.Display();
	}
	return 0;
}