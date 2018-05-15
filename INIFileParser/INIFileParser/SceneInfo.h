#pragma once

#include "INIFileParser.h"
#include "Reader.h"
#include "Writer.h"

class EXPORT SceneInfo {

	public:
		SceneInfo(std::string new_name, std::string new_zone, std::string new_scene_id);
		SceneInfo(Reader &reader);
		virtual ~SceneInfo();

		void write(Writer &writer);

		void set_name(std::string new_name);
		void set_zone(std::string new_zone);
		void set_scene_id(std::string new_scene_id);

		std::string get_name();
		std::string get_zone();
		std::string get_scene_id();

	private:
		std::string name;
		std::string zone;
		std::string sceneId;
};

