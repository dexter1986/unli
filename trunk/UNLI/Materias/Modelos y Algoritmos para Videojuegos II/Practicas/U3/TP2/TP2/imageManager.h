#pragma once
class ImageManager {
private:
	ImageManager();
	ImageManager( const ImageManager& );
	ImageManager& operator =( const ImageManager& );
	static ImageManager* singleton;
public:
	const sf::Texture&	getImage( const std::string& filename );
	void				deleteImage( const sf::Texture& image );
	void				deleteImage( const std::string& filename );
	void				addResourceDirectory( const std::string& directory );
	void				removeResourceDirectory( const std::string& directory );
	static ImageManager* Instance();		
	~ImageManager();
private:
	std::map< std::string, sf::Texture > images_;
	std::vector< std::string > resource_directories_;
};
