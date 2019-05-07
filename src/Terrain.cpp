#include "..\include\Terrain.h"






Terrain::Terrain(const char * filename, GLfloat x, GLfloat y, GLfloat z)
	:filename{ filename }
	,Figura(x, y, z)
{
}

Terrain::~Terrain()
{
}

void Terrain::draw()
{
	objl::Loader floor;


	if (floor.LoadFile(filename))
	{
		for (int i = 0; i < floor.LoadedMeshes.size(); i++)
		{
			objl::Mesh curMesh = floor.LoadedMeshes[i];

			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				glBegin(GL_TRIANGLES);
				//double random = 0.5f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.55f - 0.5f)));
				glColor3f(1, 0, 0);
				if (i == 0) glColor3f(0, 0, 1);
				glTexCoord2d(
					curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.X,
					curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.Y
				);
				
				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j]].Position.Z
				); 

				glTexCoord2d(
					curMesh.Vertices[curMesh.Indices[j+1]].TextureCoordinate.X,
					curMesh.Vertices[curMesh.Indices[j+1]].TextureCoordinate.Y
				);
				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);
				glTexCoord2d(
					curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.X,
					curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.Y
				);
				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();
			}
		}
	}

}
