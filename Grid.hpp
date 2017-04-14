//
//  Grid.hpp
//  automator
//
//  Created by d3m0t3p on 14.04.17.
//  Copyright © 2017 postTenebras. All rights reserved.
//

#ifndef Grid_hpp
#define Grid_hpp

#include <SFML/Graphics.hpp>

#include <iostream>
#include <random>
#include <vector>
#include <array>

class Grid {
	enum State{
		DEAD,
		ALIVE
	};
	
	std::array<std::array<State, 100>, 100> m_grid;
	

public:
	Grid();
	void setCooState(const size_t& x, const size_t& y, Grid::State state);
	const sf::Vector2f getCooFromIndex(const size_t& x, const size_t& y); // return top left
	const sf::Vector2i getIndexFromCoo(const sf::Vector2f& position);
	const sf::VertexArray pointToDraw();
	
	
};

#endif /* Grid_hpp */
