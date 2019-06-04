#include "..\include\Terrain.h"






Terrain::Terrain(const char * filename, GLfloat x, GLfloat y, GLfloat z)
	:filename{ filename }
	, Figura(x, y, z)
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
				glColor3fv(color);
				//if (i == 0) glColor3f(0, 0, 1);

				if (!strcmp(filename, "objects/mars.obj"))
					glTexCoord2d(0, 0);
				else
					glTexCoord2d(curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j]].TextureCoordinate.Y);
				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j]].Position.Z
				);

				/*BB[0] = std::max(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X, BB[0]);
				BB[1] = std::max(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.Y, BB[1]);
				BB[3] = std::min(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X, BB[3]);
				BB[4] = std::min(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.Y, BB[4]);*/

				if (!strcmp(filename, "objects/mars.obj"))
					glTexCoord2d(0, 1);
				else
					glTexCoord2d(curMesh.Vertices[curMesh.Indices[j + 1]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j + 1]].TextureCoordinate.Y);

				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);


				if (!strcmp(filename, "objects/mars.obj"))
					glTexCoord2d(1, 0);
				else
					glTexCoord2d(curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.X, curMesh.Vertices[curMesh.Indices[j + 2]].TextureCoordinate.Y);

				glVertex3f(
					xpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					ypos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					zpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();

				/*BB[0] = max4(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X, xpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, xpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[0]);
				BB[1] = max4(ypos + curMesh.Vertices[curMesh.Indices[j]].Position.Y, ypos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, ypos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[1]);
				BB[2] = min4(xpos + curMesh.Vertices[curMesh.Indices[j]].Position.X, xpos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, xpos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[2]);
				BB[3] = min4(ypos + curMesh.Vertices[curMesh.Indices[j]].Position.Y, ypos + curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, ypos + curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[3]);
				*/
				BB[0] = max4(curMesh.Vertices[curMesh.Indices[j]].Position.X, curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[0]);
				BB[1] = max4(curMesh.Vertices[curMesh.Indices[j]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[1]);
				BB[2] = min4(curMesh.Vertices[curMesh.Indices[j]].Position.X, curMesh.Vertices[curMesh.Indices[j + 1]].Position.X, curMesh.Vertices[curMesh.Indices[j + 2]].Position.X, BB[2]);
				BB[3] = min4(curMesh.Vertices[curMesh.Indices[j]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y, curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y, BB[3]);
			}
		}
	}

}


GLfloat * Terrain::getBB()
{
	/*BB[0] += xpos;
	BB[1] += ypos;
	BB[2] += xpos;
	BB[3] += ypos;*/
	return BB;
}

GLfloat Terrain::max4(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
	return std::max(a, std::max(b, std::max(c, d)));
}

GLfloat Terrain::min4(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
	return std::min(a, std::min(b, std::min(c, d)));
}
