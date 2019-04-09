#include "..\include\Terrain.h"



Terrain::Terrain()

{
}


Terrain::~Terrain()
{
}

void Terrain::draw()
{
	objl::Loader floor;


	if (floor.LoadFile("objects/floor.obj"))
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
				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j]].Position.X,
					curMesh.Vertices[curMesh.Indices[j]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j]].Position.Z
				);

				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.X,
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j + 1]].Position.Z
				);

				glVertex3f(
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.X,
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.Y,
					curMesh.Vertices[curMesh.Indices[j + 2]].Position.Z
				);
				glEnd();
			}
		}
	}

}
