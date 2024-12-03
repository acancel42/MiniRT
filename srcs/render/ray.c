    #include "miniRT.h"
#include "camera.h"
#define EPSILON 1e-6

static double	get_light_distance(t_vec3 p1, t_vec3 p2)
{
	double	dst;

	dst = (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z);
	return (dst);
}

t_ray	create_ray_from_cam(t_minirt *minirt, int x, int y)
{
	t_ray	ray;
	//t_vec2	coord;



	float rh = 2 * tan(minirt->cam.FOV * 0.5) / WIDTH_WIN;
	float rv = 2 * tan(minirt->cam.FOV * HEIGHT_WIN /(WIDTH_WIN * 2)) / HEIGHT_WIN;

	// float rh = 2 * tan(minirt->cam.FOV * WIDTH_WIN / (HEIGHT_WIN * 2)) / WIDTH_WIN; // test
	// float rv = 2 * tan(minirt->cam.FOV * 0.5) / HEIGHT_WIN; // test
	ray.origin = minirt->cam.position;
	ray.direction.x = ((float)x - (float)WIDTH_WIN * 0.5) * rh;
	ray.direction.y = ((float)HEIGHT_WIN * 0.5 - (float)y) * rv;
	ray.direction.z = 1;
	// if ((x == 0 || x == WIDTH_WIN) && (y == 0 || y == HEIGHT_WIN))
	// 	printf("ray.c ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	// if ((x == 0 || x == WIDTH_WIN - 1) && (y == HEIGHT_WIN / 2))
	// 	printf("y=0 ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	// if ((y == 0 || y == HEIGHT_WIN - 1) && (x == WIDTH_WIN / 2))
	//	printf("centre hor ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	ray.direction = normalize_vec3(ray.direction);
	// //angle de 56.08 sur anais
	//https://www.geogebra.org/3d/vajbwuyv



	// minirt->cam.aspect_ratio = (float)HEIGHT_WIN / (float)WIDTH_WIN;
	// coord.x = (2 * (float)x / (float)WIDTH_WIN - 1)  * minirt->cam.fov_scale;
	// coord.y = (1 - 2 * (float)y / (float)HEIGHT_WIN) * minirt->cam.fov_scale * minirt->cam.aspect_ratio;
	// ray.origin = minirt->cam.position;
	// ray.direction = (t_vec3){coord.x, coord.y, 1};
	// // if ((x == 0 || x == WIDTH_WIN - 1) && (y == 0 || y == HEIGHT_WIN - 1))
	// // 	printf("coin ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	// // if ((x == 0 || x == WIDTH_WIN - 1) && (y == HEIGHT_WIN / 2))
	// // 	printf("y=0 ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	// // if ((y == 0 || y == HEIGHT_WIN - 1) && (x == WIDTH_WIN / 2))
	// // 	printf("centre hor ray direction (%f, %f, %f)\n", ray.direction.x, ray.direction.y, -ray.direction.z);
	
	// ray.direction = normalize_vec3(ray.direction);
	// // // //angle de 67.31 sur anais et 75 en 0
	// // https://www.geogebra.org/3d/hmw9wtth


	return (ray);
}


bool	check_ray_to_light(t_minirt *minirt, t_hit hit, t_vec3 light_dir)
{
	t_ray	ray;
	double	dst;
	double	light_dst;
	size_t	i;

	i = 0;
	ray.origin = hit.position;
	ray.direction = light_dir;
	ray.origin = add_vec3(ray.origin, mult_nb_vec3(hit.ray.direction, -EPSILON));
	while (i < minirt->objects.size)
	{
		light_dst = get_light_distance(minirt->light.position, hit.position);
		dst = object_intersection(ray, *minirt->objects.array[i]);
		if ((dst > EPSILON) && (dst * dst) < light_dst)	
			return (false); // intersecte un objet avant la lumiere
		i++;
	}
	return (true); // touche directement la lumiere
}
/*
Ajout d'un "bias" à l'origine du rayon : 
J'ai ajouté un petit décalage (bias) à l'origine du rayon en utilisant la normale de la surface à la position de l'impact (hit.normal). 
Cela garantit que le rayon ne commence pas à l'exact endroit où il pourrait interagir avec la surface de l'objet de manière erronée. 
Le vec3_add(ray.origin, vec3_multiply(hit.normal, EPSILON)) déplace légèrement l'origine du rayon dans la direction de la normale, 
évitant ainsi de fausses intersections dues à des problèmes de précision.

ou utiliser le ray.direction * - 1 au lieu de hit.normal
*/

// checker que l'objet est a une distance plus faible que la lumiere
// alculer la distance entre la hit position et la lumiere

