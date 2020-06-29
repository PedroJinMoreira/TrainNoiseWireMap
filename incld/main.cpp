#include <SimplexNoise.c>

#define SIZE   16*20
#define OFFSET SIZE/2

float tm=0;
int sz[3]={0,0,0};
float *points=NULL;

float wirecolor[4]={0.25f, 0.25f, 0.25f, 1};
float pointcolor[4]={1, 1, 1, 1};
float bgcolor[4]={0, 0, 0, 1};


float noise(float x, float z){
	float aux_x = x*0.01054092553f;
	float aux_z = z*0.01054092553f;
	return 15*(SimplexNoise::noise(aux_x, aux_z) + (0.5f*SimplexNoise::noise(aux_x*2, aux_z*2))  + (0.25f*SimplexNoise::noise(aux_x*4, aux_z*4)));
}

inline void start(){
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	sz[0]=SIZE;
	sz[1]=SIZE;
	sz[2]=SIZE*SIZE;
	points = new float[sz[2]];

	if(argc>=4){
		bgcolor[0]=atof(argv[1]);
		bgcolor[1]=atof(argv[2]);
		bgcolor[2]=atof(argv[3]);
		bgcolor[3]=atof(argv[4]);
		if(argc>=8){
			wirecolor[0]=atof(argv[5]);
			wirecolor[1]=atof(argv[6]);
			wirecolor[2]=atof(argv[7]);
			wirecolor[3]=atof(argv[8]);
			if(argc>=12){
				pointcolor[0]=atof(argv[9]);
				pointcolor[1]=atof(argv[10]);
				pointcolor[2]=atof(argv[11]);
				pointcolor[3]=atof(argv[12]);
			}	
		}
	}
}

inline void update(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);
	//Camera
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)_WDHT/(float)_HGHT,0.1, 10000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-OFFSET, -32, -OFFSET);

	//gen height map
	uint i=0;
	for(uint x=0; x < sz[0]; x++){
		for(uint z=0; z < sz[1]; z++, i++){
			points[i]= noise((x+tm)/2, z+tm/2);
		}
	}

	//DrawMesh
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_LINES);
	glColor4f(wirecolor[0], wirecolor[1], wirecolor[2], wirecolor[3]);
	for(uint z=0; z < sz[1]-1; z++){
		for(uint x=0; x < sz[0]-1; x++){
			glVertex3f(x,   points[x+z*sz[0]], z);
			glVertex3f(x+1, points[x+1+z*sz[0]], z);

			glVertex3f(x,   points[x+z*sz[0]], z);
			glVertex3f(x,   points[x+(z+1)*sz[0]], z+1);

			glVertex3f(x+1, points[x+1+z*sz[0]], z);
			glVertex3f(x+1, points[x+1+(z+1)*sz[0]], z+1);
		}
	}
	glEnd();


	//DrawPoints
	glDisable(GL_DEPTH_TEST);
	glBegin(GL_POINTS);
	glColor4f(pointcolor[0], pointcolor[1], pointcolor[2], pointcolor[3]);
	for(uint x=0; x < sz[0]; x++){
		for(uint z=0; z < sz[1]; z++){
			glVertex3f(x,   points[x+z*sz[0]], z);
		}
	}
	glEnd();
	tm -=10.0f;
}

inline void exit(){
	free(points);
}
