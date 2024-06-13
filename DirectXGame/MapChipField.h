#include <iostream>



class MapChipField {

static inline const float kBlockWidth = 1.0f;

static inline const float kBlockHeight = 1.0f;


static inline const uint32_t kNumBlockVirtical = 20;

static inline const uint32_t kNumBlockHorizontal = 100;

MapChipData mapChipData_;



void RasetMapChipDate();


};

enum class MapChipType {

	kBlank,
	kBlock,



};


struct MapChipData {

std::vector<std::vector<MapChipType>> data;

};