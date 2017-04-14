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
	std::pair<sf::Vector2i, Grid::State> m_transformationToApply;
	

public:
	Grid();
	void setCooState(const size_t& x, const size_t& y, Grid::State state);
	void setIndexState(const size_t& x, const size_t& y, Grid::State state);
	
	sf::Vector2f getCooFromIndex(const size_t& x, const size_t& y) const; // return top left
	sf::Vector2i getIndexFromCoo(const sf::Vector2f& position) const;
	
	bool isAlive(const sf::Vector2i& position) const;
	bool isAlive(const size_t &x, const size_t &y)const ;
	
	int countNeibourg(const size_t &x, const size_t & y) const ;
	int countNeibourg(const sf::Vector2i & position) const;
	
	const sf::VertexArray pointToDraw();
	
	
};

#endif /* Grid_hpp */
