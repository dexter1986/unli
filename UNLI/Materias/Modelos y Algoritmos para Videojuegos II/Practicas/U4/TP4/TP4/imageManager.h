#pragma once
class ImageManager {
private:
	ImageManager();
	ImageManager( const ImageManager& );
	ImageManager& operator =( const ImageManager& );
	static ImageManager* singleton;
	sf::Font _font;
	void LoadFont();
public:
	const sf::Texture&	getImage( const std::string& filename );
	void				deleteImage( const sf::Texture& image );
	void				deleteImage( const std::string& filename );
	void				addResourceDirectory( const std::string& directory );
	void				removeResourceDirectory( const std::string& directory );
	static ImageManager* Instance();		
	~ImageManager();
	const sf::Font&			   GetFont();
private:
	std::map< std::string, sf::Texture > images_;
	std::vector< std::string > resource_directories_;
};
