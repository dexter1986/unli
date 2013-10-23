#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <iostream>
#include <string>
#include <map>
#include <SFML/Graphics/Image.hpp>

/**
 * Clase encargada de facilitar el manejo de texturas
 * asegurando de que no haya más de una copia de cada textura
 * Para operar con la misma se provee el nombre del archivo
 * de imagen y el manejador devuelve una referencia a la misma,
 * cargandola en memoria si aún no ha sido cargada.
 * Se trata de una clase singleton, es decir, existe un unico objeto de la misma.
 */
class TextureManager {
	public:
	
	
	/**
	 * \brief devuelve el manejador de texturas unico
	 */
	static TextureManager &GetInstance();
	
	
	/**
	* \brief busca y devuelve la textura correspondiente al nombre de archivo
	* \param name nombre del archivo con la textura
	* \return referencia a la textura (almacenada en el manejador) correspondiente al nombre de archivo dado
	*/
	const sf::Image &GetTexture(const std::string &name);
	
	
	/**
	* \brief realiza la misma funcion que GetTexture() utilizando el operador []
	* \param name nombre del archivo con la textura
	* \see GetTexture
	* \return referencia a la textura (almacenada en el manejador) correspondiente al nombre de archivo dado
	*/
	const sf::Image &operator[](const std::string &name);
	
	
	
	/**
	* \brief permite activar/desactivar el filtrado lineal para las texturas cargadas
	* \param smooth si debe utilizarse filtrado en las texturas
	*/
	void SmoothTextures(bool smooth);
	
	
	private:
	static TextureManager *instance;			///< instancia unica de la clase
	std::map<std::string, sf::Image> images;	///< mapa que almacena las imagenes con sus respectivos nombres de archivos
	bool smooth;								///< bandera para saber si se debe utilizar suavizado (filtrado) en las texturas
	
	/** constructor */
	TextureManager();
	~TextureManager();
	/**
	 * \brief carga la textura cuando esta no existe en el mapeo
	 * \param name nombre del archivo que contiene la textura
	 * \return referencia a la nueva textura cargada
	 */
	const sf::Image &LoadTexture(const std::string &name);
	
	
};

#endif

