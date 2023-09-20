#pragma once

#include <iostream>
#include <any>
#include <SFML/Graphics.hpp>

class GameInstance
{
	public:
		template<typename T>
		static T& get(std::string key) {
			return std::any_cast<T&>(getInstance().m_data[key]);
		}

		template<typename T>
		static void set(std::string key, T value) {
			getInstance().m_data[key] = value;
		}

		static void remove(std::string key) {
			getInstance().m_data.erase(key);
		}

		static void clear() {
			getInstance().m_data.clear();
		}

		static bool exists(std::string key) {
			return getInstance().m_data.find(key) != getInstance().m_data.end();
		}

		static void print() {
			for (auto const& x : getInstance().m_data) {
				std::cout << x.first << ": " << x.second.type().name() << std::endl;
			}
		}


	private:
		static GameInstance& getInstance() {
			static GameInstance instance;
			return instance;
		}
		GameInstance() {}
		GameInstance(GameInstance const&) = delete;
		void operator=(GameInstance const&) = delete;


		std::map<std::string, std::any> m_data;
};

