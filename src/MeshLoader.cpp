#include "MeshLoader.h"

#include <fstream>
#include <regex>
#include <iostream>
#include <unordered_map>
#include "Debug.h"

std::regex vec3_regex("(-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*)");
glm::vec3 match_vec3(const std::string& text) {
	std::smatch match;
	std::regex_search(text, match, vec3_regex);
	return glm::vec3(std::stof(match[1]), std::stof(match[2]), std::stof(match[3]));
}

std::regex vec2_regex("(-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*)");
glm::vec2 match_vec2(const std::string& text) {
	std::smatch match;
	std::regex_search(text, match, vec2_regex);
	return glm::vec2(std::stof(match[1]), std::stof(match[2]));
}

std::regex header_regex("^[a-z]+");
std::regex float_regex("-?[0-9]+.?[0-9]*");
std::regex vertex_regex("([0-9]+)\\/([0-9]*)\\/([0-9]*)");

std::shared_ptr<Mesh> MeshLoader::load(const std::string& filename) const {
    auto mesh = std::make_shared<Mesh>();
	mesh->name = filename;
	std::ifstream infile(filename);

	if (!infile.good()) {
		Debug::Log(LogSeverity::Error, "Mesh file " + filename + " does not exist.");
		return mesh;
	}
	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::vector<unsigned int> vertIndices, texcoordIndices, normalIndices;

	std::unordered_map<std::string, std::pair<Vertex, unsigned int>> vertCombinations;

	std::string line;

	while (std::getline(infile, line)) {
		std::smatch match;
		std::regex_search(line, match, header_regex);
		std::string header = match[0];
		if (header == "v") {
			glm::vec3 position = match_vec3(line);
			temp_positions.push_back(position);
		} else if (header == "vt") {
			glm::vec2 texcoord = match_vec2(line);
			temp_uvs.push_back(texcoord);
		} else if (header == "vn") {
			glm::vec3 normal = match_vec3(line);
			temp_normals.push_back(normal);
		} else if (header == "f") {
			std::string::const_iterator start = line.begin();
			std::string::const_iterator end = line.end();
			int num_verts = 0; //Count the number of vertices, so that if there's a fourth the quad completing triangle can be added
			while (std::regex_search(start, end, match, vertex_regex)) {
				num_verts++;
				Vertex vertex;
				auto vert_pair = vertCombinations.find(match[0]);
				unsigned int index;
				if (vert_pair == vertCombinations.end()) {
					//subtracting to account for 1-indexing instead of 0-indexing
					glm::vec3 position = (temp_positions[std::stoi(match[1]) - 1]);
					glm::vec2 uv = (match[2].str().size() != 0 ? temp_uvs[std::stoi(match[2]) - 1] : glm::vec2(0.0f, 0.0f));
					glm::vec3 normal = (match[3].str().size() != 0 ? temp_normals[std::stoi(match[3]) - 1] : glm::vec3(0.0f, 0.0f, 0.0f));
					vertex.position = position;
					vertex.normal = normal;
					vertex.uv = uv;
					index = mesh->vertices.size();
					mesh->vertices.push_back(vertex);
					vertCombinations[match[0]] = std::pair<Vertex, unsigned int>(vertex, index); //Add the new string to VertextFormat mapping
				} else {
					index = vert_pair->second.second;
				}
				if (num_verts < 4) {
					mesh->triangles.push_back(index);
				} else {
					int curr_triangle_size = mesh->triangles.size();
					mesh->triangles.push_back(mesh->triangles[curr_triangle_size - 3]);
					mesh->triangles.push_back(mesh->triangles[curr_triangle_size - 1]);
					mesh->triangles.push_back(index);
				}

				start = match[0].second;
			}
		}
	}
	mesh->Stream();
	return mesh;
}

std::shared_ptr<Mesh> MeshLoader::load(const std::string& name, const std::vector<Vertex> vertices, const std::vector<unsigned int> triangles) const {
	auto mesh = std::make_shared<Mesh>();
	mesh->name = name;
	if (*std::max_element(triangles.begin(), triangles.end()) > vertices.size()) {
		Debug::Log(LogSeverity::Error, "Error creating mesh " + name + ", triangles contain vertex index that exceeds vertex count.");
	} else {
		mesh->vertices = vertices;
		mesh->triangles = triangles;
	}
	mesh->Stream();
	return mesh;
}