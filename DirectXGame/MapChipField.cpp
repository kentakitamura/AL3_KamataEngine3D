#include <map>
#include "MapChipField.h"



void MapChipField::RasetMapChipDate() {

mapChipData_.deta.clear();



}


std::map<std::string, MapChipType> mapChipTable = {

    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock}
};