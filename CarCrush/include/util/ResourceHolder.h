#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

// the class can have only one instance (singelton)

template <typename Resource, typename Identifier>
class ResourceHolder : private sf::NonCopyable
{
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;

	static ResourceHolder& instance();

	
private:
	ResourceHolder(); // hiding c'tor (singelton).

	void insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:

	std::map<Identifier, std::unique_ptr<Resource>>	m_resourceMap;
};

#include "ResourceHolder.inl"
