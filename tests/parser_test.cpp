#include "tests.h"

void	parse_test()
{
	t_data	test;
	char	str[] = "/home/cschabra/Documents/MiniRT/GITHUB/tests/scenes/subject.rt";

	ft_bzero(&test, sizeof(t_data));
	read_file(&test, str);
	std::cout << RESET << "Parse test:\n";

	std::cout << "---------------------------------\n";
	std::cout << "Ambient\n";
	std::cout << "colour: "; print_vector(test.ambient->colour);
	std::cout << test.ambient->luminosity << std::endl;
	std::cout << "---------------------------------\n";

	std::cout << "Camera\n";
	std::cout << "fov: " << test.cam->fov << std::endl;
	std::cout << "orientation: "; print_vector(test.cam->orientation);
	std::cout << "viewpoint: "; print_vector(test.cam->viewpoint);
	std::cout << "---------------------------------\n";

	std::cout << "Cylinders\n";
	std::cout << "cyl count: " << test.cyl_count << std::endl;
	for (int i = 0; i < test.cyl_count; i++)
	{
		std::cout << "base: "; print_vector(test.cyls[i].base);
		std::cout << "top: "; print_vector(test.cyls[i].top);
		std::cout << "center: "; print_vector(test.cyls[i].center);
		std::cout << "colour: "; print_vector(test.cyls[i].colour);
		std::cout << "height: " << test.cyls[i].height << std::endl;
		std::cout << "instance: " << test.cyls[i].instance << std::endl;
		std::cout << "object t_token nr: " << test.cyls[i].object << std::endl;
		std::cout << "orientation: "; print_vector(test.cyls[i].orientation);
		std::cout << "radius: " << test.cyls[i].radius << std::endl;
		if (test.cyls[i].tex)
			std::cout << "Texture found!\n";
		else
			std::cout << "No texture found!\n";
		std::cout << "---------------------------------\n";
	}
	std::cout << "---------------------------------\n";

	// std::cout << "Light\n";
	// std::cout << "colour: "; print_vector(test.light->colour);
	// std::cout << "luminosity: " << test.light->luminosity << std::endl;
	// std::cout << "source: "; print_vector(test.light->source);
	// std::cout << "---------------------------------\n";
	
	std::cout << "Planes\n";
	std::cout << "plane count: " << test.plane_count << std::endl;
	for (int i = 0; i < test.plane_count; i++)
	{
		std::cout << "colour: "; print_vector(test.planes[i].colour);
		std::cout << "instance: " << test.planes[i].instance << std::endl;
		std::cout << "location: "; print_vector(test.planes[i].location);
		std::cout << "object t_token nr: " << test.planes[i].object << std::endl;
		std::cout << "orientation: "; print_vector(test.planes[i].orientation);
		std::cout << "rev_norm: "; print_vector(test.planes[i].rev_norm);
		if (test.planes[i].tex)
			std::cout << "Texture found!\n";
		else
			std::cout << "No texture found!\n";
		std::cout << "---------------------------------\n";
	}
	std::cout << "---------------------------------\n";
	
	std::cout << "Spheres\n";
	std::cout << "sphere count: " << test.sphere_count << std::endl;
	for (int i = 0; i < test.sphere_count; i++)
	{
		std::cout << "center: "; print_vector(test.spheres[i].center);
		std::cout << "colour: "; print_vector(test.spheres[i].colour);
		std::cout << "instance: " << test.spheres[i].instance << std::endl;
		std::cout << "object t_token nr: " << test.spheres[i].object << std::endl;
		std::cout << "radius: " << test.spheres[i].radius << std::endl;
		if (test.spheres[i].tex)
			std::cout << "Texture found!\n";
		else
			std::cout << "No texture found!\n";
		std::cout << "---------------------------------\n";
	}
	std::cout << "Done!\n";
	std::cout << std::endl;
}
