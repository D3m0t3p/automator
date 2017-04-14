//
//  Grid.cpp
//  automator
//
//  Created by d3m0t3p on 14.04.17.
//  Copyright © 2017 postTenebras. All rights reserved.
//

#include "Grid.hpp"

Grid::Grid(){
	m_grid = std::array<std::array<Grid::State, 100>, 100>();
	for(auto &a : m_grid){
		for(auto&b : a){
			b = Grid::State::DEAD;
		}
	}
	m_grid.at(10).at(10) = Grid::State::ALIVE;
}




void Grid::setCooState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y).at(x) = state;
}



const sf::Vector2f Grid::getCooFromIndex(const size_t& x, const size_t& y){
	
	if(x >= 100 or y >= 100)
		throw std::out_of_range("x or y is too big");
	
	return sf::Vector2f (x*7, y*7);//top left
	
}


const sf::Vector2i Grid::getIndexFromCoo(const sf::Vector2f& position){
	
	return sf::Vector2i (position.x/7, position.y/ 7);
}

const sf::VertexArray Grid::pointToDraw(){
	sf::VertexArray array;
	for(size_t y; y < 100; y++){
		for(size_t x; x< 100; x++ ){
			if(m_grid.at(y).at(x) == Grid::State::ALIVE){
				sf::Vertex pt(getCooFromIndex(x, y));
				array.append(pt);
				array.append(sf::Vertex(sf::Vector2f(pt.position.x+7, pt.position.y)));
				array.append(sf::Vertex(sf::Vector2f(pt.position.x, pt.position.y+7)));
				array.append(sf::Vertex(sf::Vector2f(pt.position.x+7, pt.position.y+7)));


			}
		}
	}
}




