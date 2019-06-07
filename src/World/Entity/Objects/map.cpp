#include "map.hpp"
#include "Base/gameData.hpp"
#include "Utilities/xml.hpp"
#include "Utilities/csv.hpp"
#include "Utilities/math.hpp"

using PopHead::World::Entity::Map;
using PopHead::Utilities::Xml;

Map::Map(PopHead::Base::GameData* gameData, std::string name, const std::string& xmlFilename, float scale)
	: Object(gameData, name, Renderer::LayerID::floorEntities)
{
	Xml document;
	document.loadFromFile(xmlFilename);

	const Xml mapNode = document.getChild("map");
	const std::string orientation = mapNode.getAttribute("orientation").toString();
	if (orientation != "orthogonal")
		PH_EXCEPTION("Used unsupported map orientation: " + orientation);
	const std::string infinite = mapNode.getAttribute("infinite").toString();
	if (infinite != "0")
		PH_EXCEPTION("Infinite maps are not supported");
	const sf::Vector2u mapSize(
		mapNode.getAttribute("width").toUnsigned(),
		mapNode.getAttribute("height").toUnsigned()
	);
	const sf::Vector2u tileSize(
		mapNode.getAttribute("tilewidth").toUnsigned(),
		mapNode.getAttribute("tileheight").toUnsigned()
	);

	const std::vector<Xml> tilesetNodes = mapNode.getChildren("tileset");
	/*
		TODO:
		Is it better to use reserve and push_back() instead of
		size() in constructor and operator[] in below loop?
	*/
	TilesetsData tilesets;
	tilesets.sources.resize(tilesetNodes.size());
	tilesets.columnsCounts.resize(tilesetNodes.size());
	tilesets.gid.resize(tilesetNodes.size());
	tilesets.tileCounts.resize(tilesetNodes.size());
	for (std::size_t i = 0; i < tilesetNodes.size(); ++i) {
		tilesets.columnsCounts[i] = tilesetNodes[i].getAttribute("columns").toUnsigned();
		tilesets.gid[i] = tilesetNodes[i].getAttribute("firstgid").toUnsigned();
		tilesets.tileCounts[i] = tilesetNodes[i].getAttribute("tilecount").toUnsigned();

		const Xml imageNode = tilesetNodes[i].getChild("image");
		tilesets.sources[i] = imageNode.getAttribute("source").toString();
		tilesets.sources[i] = Utilities::Path::toFilename(tilesets.sources[i], '/');
	}

	// TODO: What if there are no layers? Change Xml impl or just do something here?
	const std::vector<Xml> layerNodes = mapNode.getChildren("layer");
	// TODO: Just use resize and replace push_back with [] in below loop?
	mSprites.reserve(mapSize.x * mapSize.y * layerNodes.size());
	for (const Xml& layerNode : layerNodes) {
		const Xml dataNode = layerNode.getChild("data");
		const std::string encoding = dataNode.getAttribute("encoding").toString();
		if (encoding != "csv")
			PH_EXCEPTION("Used unsupported data encoding: " + encoding);
		const std::vector<unsigned> values = Utilities::Csv::toUnsigneds(dataNode.toString());
		for (std::size_t i = 0; i < values.size(); ++i) {
			if (values[i]) {
				for (std::size_t j = 0; j < tilesets.gid.size(); ++j) {
					const unsigned lastTileGid = tilesets.gid[j] + tilesets.tileCounts[j] - 1;
					if (values[i] >= tilesets.gid[j] && values[i] <= lastTileGid) {
						sf::Vector2u tilePosition = 
							Utilities::Math::toTwoDimensional(values[i] - tilesets.gid[j], tilesets.columnsCounts[j]);
						tilePosition.x *= tileSize.x;
						tilePosition.y *= tileSize.y;
						const sf::IntRect tileRect(
							static_cast<sf::Vector2i>(tilePosition),
							static_cast<sf::Vector2i>(tileSize)
						);
						// TODO: Move map resources path to some better place and make it static const for example?
						sf::Sprite sprite(mGameData->getTextures().get("textures/map/" + tilesets.sources[j]), tileRect);
						sf::Vector2f position(Utilities::Math::toTwoDimensional(i, mapSize.x));
						position.x *= tileSize.x;
						position.y *= tileSize.y;
						sprite.setPosition(position);
						// TODO: Scale sprite? (scale funtion paramiter)
						mSprites.push_back(sprite);

						break;
					}
				}
			}
		}
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const sf::Sprite& sprite : mSprites)
		target.draw(sprite, states);
}
