// Clase que representa una particula del efecto de particulas.
// Esta disenada para ser usada por la clase EfectoParticulas
class Particula
{
	public:
		// Coordenada x de la posicion de la particula
		float x;
		
		// Coordenada y de la posicion de la particula
		float y;
		
		// Velocidad en coordenada x
		float vX;
		
		// Velocidad en coordenada y
		float vY;
		
		// Componente de color rojo
		float red;
		
		// Componente de color verde
		float green;
		
		// Componente de color azul
		float blue;
		
		// Vida actual de la particula. Al llegar a cero muere.
		// Cada actualizacion debe disminuir.
		int life;
		
		// Vida inicial de la particula con la que nacio
		int life_initial;
		
		// Inicializa la particula cuando es recien lanzada
		void Inicializar(float pX, float pY, float Velocidad, float r, float g, float b, int amplitud, int direccion, int vida);
};
