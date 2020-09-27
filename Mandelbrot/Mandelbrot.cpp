#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctgmath>
#include <complex>
#define PI 3.141592653589793285
#define BOUNDARY 15000

using namespace std::complex_literals;
float divCoeff = 180.0f / PI;
int initRed = 255;

// Function to set the color for each pixel
int mandelbrotFunc(std::complex<float> c, unsigned int maxIt)
{
	unsigned int it = 0;
	std::complex<float> z(0,0); // z is defined as 0,0 at iteration 0
	
	// While the absolute value of our z is held under a constant boundary and we're under the maximum number of iteration, we run the Mandelbrot function
	while (abs(z) <= BOUNDARY && it <= maxIt)
	{
		// f_c(z) = z^2 + c
		z = pow(z, 2) + c;
		++it;
	}
	// We set the color of the pixel based on when it explodes. If we never reach the max. iterations, it means the value has exploded => it gets a shade of red
	// If the iterations match the max. iterations, it means the values stay relatively silent. => it gets black
	if (it < maxIt)
	{
		return ((255 * it) / 33);
	}
	else
	{
		return 0;
	}
}

//// Converts the carthesian coordinates to polar ones for further processing (Radial)
//float carthToPolRad(float x, float y) 
//{
//	float rad = sqrt((x * x) + (y * y));
//	return rad;
//}
//
//// Converts the carthesian coordinates to polar ones for further processing (Angular)
//float carthToPolAng(float x, float y)
//{
//	float ang = (float) atan(y/x) * divCoeff;
//	return ang;
//}

int main()
{
	float convx, convy; //polRad, polAng;
	// Defining the max iterations
	unsigned int maxIt = 1000, op;
	sf::RenderWindow window(sf::VideoMode(1560, 840), "Mandelbrot Set (do not resize)", sf::Style::Default);
	sf::RectangleShape pixel(sf::Vector2f(2.0f, 2.0f));
	// Setting default pixel settings
	pixel.setOutlineColor(sf::Color::White);
	pixel.setOutlineThickness(4.0f);
	pixel.setPosition(0.0f, 0.0f);

	// Looping through the grid using raw values
	for (int rawx = 0; rawx < (window.getSize().x); rawx++)
	{
		for (int rawy = 0; rawy < (window.getSize().y); rawy++)
		{
			// Only considering the "trimmed" region for the Mandelbrot-Set to conserve the original ratio
			if (rawx > 150 && rawx < 1410)
			{
				// Calculating cartesian coordinates, i.e converting the raw values
				convx = ((rawx - 150.0f) / 420.0f) - 2;
				convy = 1.0f - (rawy / 420.0f);

				// Transferring the cartesian coordinates into a complex number
				std::complex<float> z(convx, convy);
				// Drawing either Mandelbrot Set or Julia Set
				// mandelbrotFunc() returns the R-value
				pixel.setOutlineColor(sf::Color(mandelbrotFunc(z, maxIt), 0, 0));
			}
			else
			{
				// Setting the color to black on the edges
				pixel.setOutlineColor(sf::Color::Black);
			}
			// Pixel is printed
			pixel.setPosition(rawx,rawy);
			window.draw(pixel);
			window.display();
		}
	}

	while (window.isOpen())
	{
		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (evnt.type == sf::Event::Resized)
			{
				window.setSize(sf::Vector2u(evnt.size.width, evnt.size.height));
			}
		}
		window.display();
	}
}
