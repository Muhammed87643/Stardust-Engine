#pragma once
#include "SpriteAdvanced.h"
#include <Math/AABB.h>

namespace Stardust::Graphics::Render2D {

	enum TileRotations {
		TILE_ROTATION_CW_0 = 0,
		TILE_ROTATION_CW_90 = 2,
		TILE_ROTATION_CW_180 = 4,
		TILE_ROTATION_CW_270 = 6,
	};

	struct Tile {
		glm::vec2 offset;
		glm::vec2 extent;

		short texIndex;
		char layer;
		char rotation;
		unsigned int rgba;
		bool physics;
	};

	class Tilemap {
	public:
		Tilemap(TextureAtlas* atlas, Texture* texture);

		int addTile(Tile* t);
		void updateTile(int tileNum, Tile* t);
		void clearTiles();

		void buildMap();

		bool checkPhysics(const Math::AABB2D& aabb);

		inline Tile* getTile(int idx) {
			if(idx < m_Tiles.size())
				return m_Tiles[idx];
			
			return nullptr;
		}

		void drawMap();

		void loadTileFromJSON(std::string path);

	private:
		TextureAtlas* m_Atlas;
		std::vector<Tile*> m_Tiles;
		std::vector<Vertex> vertices;
		Texture* texRef;


	};

}