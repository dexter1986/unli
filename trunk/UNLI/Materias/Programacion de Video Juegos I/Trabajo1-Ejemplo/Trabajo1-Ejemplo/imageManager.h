#ifndef IMAGE_MANAGER_H_
#define IMAGE_MANAGER_H_
class imageManager {

public:
	imageManager();
	~imageManager();

private:
	imageManager( const imageManager& );
	imageManager& operator =( const imageManager& );

public:
	const sf::Texture&	getImage( const std::string& filename );
	void				deleteImage( const sf::Texture& image );
	void				deleteImage( const std::string& filename );
	void				addResourceDirectory( const std::string& directory );
	void				removeResourceDirectory( const std::string& directory );

private:
	std::map< std::string, sf::Texture > images_;
	std::vector< std::string > resource_directories_;
};
#endif