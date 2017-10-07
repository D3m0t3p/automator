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

template <long long int n>

class Grid {
	
public:
	enum State{
		DEAD,
		ALIVE
	};
	
	


	
	Grid (long long int xWin, long long int yWin);
	
	void setCooState(const size_t& x, const size_t& y, Grid::State state);
	
	void setIndexState(const sf::Vector2i & position, Grid::State state);
	void setIndexState(const size_t& x, const size_t& y, Grid::State state);
	
	sf::Vector2f getCooFromIndex(const size_t& x, const size_t& y) const; // return top left
	sf::Vector2i getIndexFromCoo(const sf::Vector2f& position) const;
	
	bool isAlive(const sf::Vector2i& position) const;
	bool isAlive(const long long int &x, const long long int &y)const ;
	
	size_t countNeighbours(const long long int &x, const long long int & y) const ;
	size_t countNeighbours(const sf::Vector2i & position) const;
	
	void computeNextIteration();
	void commitChange();
	const sf::VertexArray pointToDraw();
	
private:
	
	std::array<std::array<State, n>, n> m_grid;
	std::vector<std::pair<sf::Vector2i, Grid::State>> m_transformationToApply; //posittion, next State after rules
	long long int xMax, yMax;
};
#include "Grid.tpp"

#endif /* Grid_hpp */
