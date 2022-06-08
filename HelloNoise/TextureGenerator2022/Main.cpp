/******************************************************************************\
* Virtual Cow Parade -- Texture Generator                                      *
*                                                                              *
* Técnicas Avançadas de Computação Gráfica 2010-2                              *
*                                                                              *
* Este programa utiliza a libnoise (http://libnoise.sourceforge.net) para a    *
* geração de texturas procedurais                                              *
*                                                                              *
*                                                                              *
* Projeto iniciado por Rossana Queiroz  em 08/11/2010                          *
*                                                                              *
\******************************************************************************/

#include <iostream>
#include <noise/noise.h>
#include "noiseutils.h"

#include <sstream>


using namespace noise;


utils::NoiseMap BuildAHeightMap (int w, int h, float *bounds) {
	//Classe para a criação de ruído de perlin (Perlin Noise)
	module::Perlin myModule;

	// octaves 
	//myModule.SetOctaveCount(5);

	// frequency 
	//myModule.SetFrequency(5.9);

	// persistence 
	//myModule.SetPersistence(6); //0.5 a 6 | 0.75 a 2

	//Utilizando a biblioteca auxiliar noiseutils, podemos instanciar um mapa de noise, que neste caso será utilizado para gerar um heightmap
	utils::NoiseMap heightMap;

	//
   utils::NoiseMapBuilderPlane heightMapBuilder;
   heightMapBuilder.SetSourceModule (myModule);
   heightMapBuilder.SetDestNoiseMap (heightMap);
   heightMapBuilder.SetDestSize (w, h);
   heightMapBuilder.SetBounds (bounds[0], bounds[1], bounds[2], bounds[3]);
   heightMapBuilder.Build ();

   return heightMap;
}

utils::NoiseMap BuildASphericalHeightMap(int w, int h, float* bounds) {
	//Classe para a criação de ruído de perlin (Perlin Noise)
	module::Perlin myModule;

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderSphere heightMapBuilder;
	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(512, 256);
	heightMapBuilder.SetBounds(-90.0, 90.0, -180.0, 180.0);
	heightMapBuilder.Build();

	return heightMap;
}


void RenderHeightMap(utils::NoiseMap heightMap, std::string filename){
	//Renderizando...
   utils::RendererImage renderer;
   utils::Image image;
   renderer.SetSourceNoiseMap (heightMap);
   renderer.SetDestImage (image);
 
   //Para definir faixas de cores... 
  renderer.ClearGradient ();
  renderer.AddGradientPoint (-1.0000, utils::Color (255, 245, 157, 255)); // deeps
  //renderer.AddGradientPoint (-0.2500, utils::Color (  132,   165, 184, 255)); // shallow
  //renderer.AddGradientPoint ( 0.0000, utils::Color (  179, 218, 241, 255)); // shore
  renderer.AddGradientPoint ( 0.0625, utils::Color (243, 180,  139, 255)); // sand
  //renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
  renderer.AddGradientPoint ( 0.3750, utils::Color (243, 180,   139, 255)); // dirt
  renderer.AddGradientPoint ( 0.7500, utils::Color (253, 216, 53, 113)); // rock
  //renderer.AddGradientPoint ( 1.0000, utils::Color (230, 230, 230, 255)); // snow

   renderer.EnableLight ();
   renderer.SetLightContrast (3); // Triple the contrast
   renderer.SetLightBrightness (2); // Double the brightness

   renderer.Render ();

   //Escrevendo...
   utils::WriterBMP writer;
   writer.SetSourceImage (image);
   writer.SetDestFilename (filename.c_str());
   writer.WriteDestFile ();
}

int main (int argc, char** argv)
{

	
	utils::NoiseMap heightMap;
	float bounds[4] = {2.2, 5.79, 1.0, 5.0};
	// 3.7, 9.2
	// 1.9, 8.7
	// 2.2, 5.79
	// 0.2, 18.0

	
	//Modo padrão
	heightMap = BuildAHeightMap(1024, 1024, bounds);

	//Para criar o mapa com projeção esférica
	//heightMap = BuildASphericalHeightMap(1024, 1024, bounds);
	
	
	RenderHeightMap(heightMap,"../example.bmp");
	

   std::cout << "Success!\n";
  
   getchar();


  return 0;
}