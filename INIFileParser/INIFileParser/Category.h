#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"
#include "SceneInfo.h"

#include <algorithm>
#include <vector>
#include <iterator>

class EXPORT Category {

	public:
		Category(Reader &reader);
		~Category();

		void write(Writer &writer);

		void add_scene_info(SceneInfo info);
		void add_scene_info(std::string new_name, std::string new_zone, std::string new_scene_id);

		void insert_scene_info(SceneInfo info, unsigned int position);
		void insert_scene_info(std::string new_name, std::string new_zone, std::string new_scene_id, unsigned int position);

		void set_name(std::string new_name);

		std::string get_name();

		SceneInfo &get_scene_info(std::string name, std::string zone, std::string scene_id);

		std::vector<SceneInfo> info_list;

	private:
		std::string name;
};

