#include "SceneEditorMetadata.h"

SceneEditorMetadata::SceneEditorMetadata() {
	unknown_byte = 0x03;
	background_color_1 = Color();
	background_color_2 = Color();
	unsigned char init_bytes[8] = {0x1, 0x1, 0x4, 0x0, 0x1, 0x4, 0x0, '\0'};
	strlcpy(unknown_bytes, init_bytes, 7);
	delete[] init_bytes;
	unknown_bytes[7] = '\0';
	unknown_byte_2 = 0x00;
}

SceneEditorMetadata::SceneEditorMetadata(Reader &reader) {
	unknown_byte = reader.read_byte();
	background_color_1 = Color(reader);
	background_color_2 = Color(reader);
	unsigned char *read_bytes = reinterpret_cast<unsigned char *>(reader.read_bytes(7));
	strlcpy(unknown_bytes, read_bytes, 7);
	delete read_bytes;
	unknown_bytes[7] = '\0';
	bin_name = reader.read_rsdk_string();
	unknown_byte_2 = reader.read_byte();
}

SceneEditorMetadata::~SceneEditorMetadata() {

}

void SceneEditorMetadata::write(Writer &writer) {
	writer.write_byte(unknown_byte);
	background_color_1.write(writer);
	background_color_2.write(writer);
	writer.write_bytes(unknown_bytes);
	writer.write_rsdk_string(bin_name);
	writer.write_byte(unknown_byte_2);
}