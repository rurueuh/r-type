#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class TextureManager final
{
	public:
		TextureManager() = default;
		~TextureManager() {
			m_textures.clear();
		}

		static sf::Texture &getTexture(const std::string& filename) {
			if (m_textures.find(filename) == m_textures.end()) {
				#ifdef _DEBUG
					std::cout << "LOAD TEXTURE : " << filename << std::endl;
				#endif // _DEBUG
				std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
				texture->loadFromFile(filename);
				m_textures[filename] = texture;
				return *m_textures[filename];
			}
			else {
				return *m_textures[filename];
			}
		}

		static bool isTextureLoaded(const std::string& filename) {
			return m_textures.find(filename) != m_textures.end();
		}

		static void clear() {
			m_textures.clear();
		}

		static void clear(const std::string& filename) {
			m_textures.erase(filename);
		}

	private: 
		static std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;
};

inline std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::m_textures;

