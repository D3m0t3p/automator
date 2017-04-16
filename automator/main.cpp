
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//


// Here is a small helper for you! Have a look.
#include "Grid.hpp"

std::random_device rd;

void checkEvent(sf::RenderWindow &window, Grid& grid){
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type){
			case sf::Event::Closed :
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				grid.computeNextIteration();
				grid.commitChange();
				
			default:
				std::cout <<"i don't care";
		}
	}
}

long long int randomInt(long long int min, long long int max){
	
 
	std::default_random_engine e1(rd());
	std::uniform_int_distribution<long long int> uniform_dist(min, max);
	return uniform_dist(e1);
}

long long int randomFloat(){

	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	 std::uniform_real_distribution<> dis(0, 1);
	return dis(gen);
}


int main(int, char const**)
{
	std::cout <<"hello";
	
	
    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML window");
	size_t max = 100;
	window.setFramerateLimit(60);
	
	/*
	//les lignes
	sf::VertexArray linesH(sf::Lines, max );
	sf::VertexArray linesV(sf::Lines, max );
	
	for(unsigned int i = 0; i< max; i++){
		if(i%2 == 0)
			linesH[i].position = sf::Vector2f(0, i*7+1);
		else
			linesH[i].position = sf::Vector2f(700, (i-1)*7+1);
	}
	
	for(unsigned int i = 0; i< max; i++){
		if(i%2 == 0)
			linesV[i].position = sf::Vector2f(i*window.getSize().x/100+1, 0 );
		else
			linesV[i].position = sf::Vector2f((i-1)*window.getSize().x/100+1, window.getSize().y );
	}
	//TODO: vertexArray from squares;

	
	
	//std::vector<std::pair<sf::Vector2f coordinate top left, size_t size of square>> squares;
	
	for(size_t y = 0; y < window.getSize().x/7+1; y++){
		for(size_t x = 0; x < window.getSize().x/7+1; x++){
			squares.push_back(std::pair<sf::Vector2f,size_t>(sf::Vector2f( x*7, y*7), 7 ));
		}
	}
	*/
	
	Grid grid{};
	auto v = grid.countNeighbours(0, 0);
	/*for(auto i = 0; i< 10; i++){
		
		grid.setIndexState(randomInt(0, 99), randomInt(0, 99), Grid::State::ALIVE);
		grid.setIndexState(randomInt(0, 99), randomInt(0, 99), Grid::State::ALIVE);
		grid.setIndexState(randomInt(0, 99), randomInt(0, 99), Grid::State::ALIVE);
		
		

	}*/
	/*int z = 45;
	while(z--){
		auto a = randomInt(0, 99);
		auto b = randomInt(0, 99);

		grid.setIndexState(a,b, Grid::State::ALIVE);
		grid.setIndexState(a,b+1, Grid::State::ALIVE);
		grid.setIndexState(a+1,b, Grid::State::ALIVE);
		grid.setIndexState(a,b-1, Grid::State::ALIVE);
	}
	
*/
//	grid.setIndexState(70,70, Grid::State::ALIVE);
//	grid.setIndexState(71,71, Grid::State::ALIVE);
//	grid.setIndexState(71,72, Grid::State::ALIVE);
//	grid.setIndexState(70,72, Grid::State::ALIVE);
//	grid.setIndexState(69,72, Grid::State::ALIVE);



	/*
	 ...***
	 ...*..***
	 ....*.*
	 **.......*
	 *.*....*..*
	 *........**
	 .**
	 .*..*.....*.**
	 .*.........**.*
	 ...*.*......**..*
	 ....**.*....**...*
	 ........*.......*
	 .......****...*.*
	 .......*.**...****
	 ........*...**.*
	 .............**
	 .........*.***
	 ..........*..*
	 
	 */
	
	
	

	while (window.isOpen()) {
		
		checkEvent(window,grid);
		
		auto array = grid.pointToDraw();
		auto a = grid.countNeighbours(91, 91);
		
		window.clear(sf::Color::White);
		window.draw(array);
		//grid.computeNextIteration();
		//grid.commitChange();
		window.display();
		
		
	}
    return EXIT_SUCCESS;
}

/*
 
 // Set the Icon
 sf::Image icon;
 if (!icon.loadFromFile(resourcePath() + "icon.png")) {
 return EXIT_FAILURE;
 }
 window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
 
 // Load a sprite to display
 sf::Texture texture;
 if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
 return EXIT_FAILURE;
 }
 sf::Sprite sprite(texture);
 
 // Create a graphical text to display
 sf::Font font;
 if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
 return EXIT_FAILURE;
 }
 sf::Text text("Hello SFML", font, 50);
 text.setFillColor(sf::Color::Black);
 
 // Load a music to play
 sf::Music music;
 if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
 return EXIT_FAILURE;
 }
 
 // Play the music
 music.play();
 
 // Start the game loop
 while (window.isOpen())
 {
 // Process events
 sf::Event event;
 while (window.pollEvent(event))
 {
 // Close window: exit
 if (event.type == sf::Event::Closed) {
 window.close();
 }
 
 // Escape pressed: exit
 if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
 window.close();
 }
 }
 
 // Clear screen
 window.clear();
 
 // Draw the sprite
 window.draw(sprite);
 
 // Draw the string
 window.draw(text);
 
 // Update the window
 window.display();
 }


*/
