#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

class TextureManager final
{
	public:
		TextureManager() {
			std::cout << "TextureManager worker : " << std::thread::hardware_concurrency() << std::endl;
            for (int i = 0; i < std::thread::hardware_concurrency(); i++) {
				m_threadsWorking.push_back(std::thread([]() {
					while (true) {
						std::this_thread::sleep_for(std::chrono::milliseconds(100));
					}
				}));
			}
        }
		~TextureManager() {
			m_textures.clear();
		}

        static void loadTexture(std::string path)
        {

        }

		static sf::Texture &getTexture(const std::string& filename) {
			if (m_textures.find(filename) == m_textures.end()) {
				#ifdef _DEBUG
					std::cout << "LOAD TEXTURE : " << filename << std::endl;
				#endif // _DEBUG
				return *m_textures[filename];
			}
			else {
				return *m_textures[filename];
			}
		}

        static void loadTextureInMemory(std::vector<std::string> filenames) {
            std::for_each(filenames.begin(), filenames.end(), [](const std::string& filename) {
            });
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
        static std::mutex m_mutex;
        static std::vector<std::thread> m_threadsWorking;
		static std::pair<std::vector<std::string>, std::mutex> m_toLoad;
};

inline std::map<std::string, std::shared_ptr<sf::Texture>> TextureManager::m_textures;
inline std::mutex TextureManager::m_mutex;
inline std::vector<std::thread> TextureManager::m_threadsWorking;
inline std::pair<std::vector<std::string>, std::mutex> TextureManager::m_toLoad;