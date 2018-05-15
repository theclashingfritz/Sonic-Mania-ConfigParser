#include "SceneInfo.h"

SceneInfo::SceneInfo(std::string new_name, std::string new_zone, std::string new_scene_id) {
	name = new_name;
	zone = new_zone;
	sceneId = new_scene_id;
}

SceneInfo::SceneInfo(Reader &reader) {
	name = std::string(reader.read_rsdk_string());
	zone = std::string(reader.read_rsdk_string());
	sceneId = std::string(reader.read_rsdk_string());
}

SceneInfo::~SceneInfo() {

}

void SceneInfo::write(Writer &writer) {
	writer.write_rsdk_string(name);
	writer.write_rsdk_string(zone);
	writer.write_rsdk_string(sceneId);
}

void SceneInfo::set_name(std::string new_name) {
	name = new_name;
}

void SceneInfo::set_zone(std::string new_zone) {
	zone = new_zone;
}

void SceneInfo::set_scene_id(std::string new_scene_id) {
	sceneId = new_scene_id;
}

std::string SceneInfo::get_name() {
	return name;
}

std::string SceneInfo::get_zone() {
	return zone;
}

std::string SceneInfo::get_scene_id() {
	return sceneId;
}