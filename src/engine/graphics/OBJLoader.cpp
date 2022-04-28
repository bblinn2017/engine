#include "OBJLoader.h"
#include "engine/util/CommonIncludes.h"

OBJLoader::OBJLoader()
{

}

OBJLoader::~OBJLoader(){

}

OBJData OBJLoader::loadOBJ(const char *path){
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::vector<float> out_vertices;
    std::vector<float> out_uvs;
    std::vector<float> out_normals;

    OBJData returnable = OBJData();

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return returnable;
    }

    while(1){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF){
            break; // EOF = End Of File. Quit the loop.
        } else{
        // else : parse lineHeader
            if (strcmp(lineHeader, "v") == 0){
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
                temp_vertices.push_back(vertex);
            } else if ( strcmp(lineHeader, "vt") == 0){
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                temp_uvs.push_back(uv);
            } else if ( strcmp(lineHeader, "vn") == 0){
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            } else if (strcmp(lineHeader, "f") == 0){
//                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

                char v[128];
                memset(v,0,sizeof(char)*128);
                for (int i = 0; i < 3; i++) {
                    fscanf(file, "%s", v);

                    int idx[3];
                    std::string curr = "";
                    int j = 0; int k = 0;
                    while (v[j] != 0) {
                        if (v[j] == '/') {
                            idx[k] = std::stoi(curr);
                            curr = "";
                            k++;
                        } else {
                            curr += v[j];
                        }
                        j++;
                    }
                    idx[k] = std::stoi(curr);

                    vertexIndices.push_back(idx[0]);
                    uvIndices.push_back(idx[1]);
                    if (k == 2) {
                        normalIndices.push_back(idx[2]);
                    }
                    memset(v,0,sizeof(char)*128);
                }

//                int matches = fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
//                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//                if (matches != 9){
//                    printf("File can't be read. Try exporting with other options\n");
//                    return returnable;
//                }
//                vertexIndices.push_back(vertexIndex[0]);
//                vertexIndices.push_back(vertexIndex[1]);
//                vertexIndices.push_back(vertexIndex[2]);
//                uvIndices.push_back(uvIndex[0]);
//                uvIndices.push_back(uvIndex[1]);
//                uvIndices.push_back(uvIndex[2]);
//                normalIndices.push_back(normalIndex[0]);
//                normalIndices.push_back(normalIndex[1]);
//                normalIndices.push_back(normalIndex[2]);
            }
        }
    }
    for(unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex-1];
        out_vertices.push_back(vertex.x);
        out_vertices.push_back(vertex.y);
        out_vertices.push_back(vertex.z);
    }
    for(unsigned int i=0; i<uvIndices.size(); i++ ){
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex-1];
        out_uvs.push_back(uv.x);
        out_uvs.push_back(uv.y);
    }
    for(unsigned int i=0; i<normalIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex-1];
        out_normals.push_back(normal.x);
        out_normals.push_back(normal.y);
        out_normals.push_back(normal.z);
    }
    returnable.positions = out_vertices;
    returnable.uvs = out_uvs;
    returnable.normals = out_normals;
    return returnable;
}
