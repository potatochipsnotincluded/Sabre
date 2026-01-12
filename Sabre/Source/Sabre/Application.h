#pragma once
#include <vector>

#include "Sabre/Sabre.h"

namespace Sabre {

	class Layer
	{
	public:
		Layer(int argc, char* argv[]);
		virtual ~Layer() = default;

		virtual void OnInit() = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender() = 0;	
	public:
		int ArgC;
		char** ArgV;
	};

	class Application
	{
	public:
		~Application();

		template <typename T>
		void PushLayer();

		void Run();

	private:
		std::vector<Layer*> m_Layers;

		int m_ArgC;
		char* m_ArgV[];
	};

	template<typename T>
	inline void Application::PushLayer()
	{
		T* t = new T(m_ArgC, m_ArgV);

		m_Layers.push_back(t);
	}

}