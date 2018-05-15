#include "Category.h"

Category::Category(Reader &reader) {
	name = std::string(reader.read_rsdk_string());

	uint8_t scenes_count = reader.read_byte();
	for (int i = 0; i < scenes_count; ++i) {
		info_list.push_back(SceneInfo(reader));
	}
}

Category::~Category() {

}

void Category::write(Writer &writer) {
	writer.write_rsdk_string(name);
	writer.write_byte(uint8_t(info_list.size()));
	for (auto &i : info_list) {
		i.write(writer);
	}
}

void Category::add_scene_info(SceneInfo info) {
	info_list.push_back(info);
}

void Category::add_scene_info(std::string new_name, std::string new_zone, std::string new_scene_id) {
	info_list.push_back(SceneInfo(new_name, new_zone, new_scene_id));
}

void Category::insert_scene_info(SceneInfo info, unsigned int position) {
	info_list.insert(info_list.begin() + position, info);
}

void Category::insert_scene_info(std::string new_name, std::string new_zone, std::string new_scene_id, unsigned int position) {
	info_list.insert(info_list.begin() + position, SceneInfo(new_name, new_zone, new_scene_id));
}

void Category::set_name(std::string new_name) {
	name = new_name;
}

std::string Category::get_name() {
	return name;
}

SceneInfo &Category::get_scene_info(std::string name, std::string zone, std::string scene_id) {
	auto it = std::find_if(info_list.begin(), info_list.end(), [&name, &zone, &scene_id](SceneInfo& obj) {return (obj.get_name() == name && obj.get_zone() == zone && obj.get_scene_id() == scene_id); });
	if (it != info_list.end()) {
		return *it;
	} else {
		throw std::runtime_error("SceneInfo info input was not equal to any SceneInfo elements in the info list!");
		return SceneInfo("bad_find", "bad_find", "bad_find");
	}
}