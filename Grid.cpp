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
		for(auto&state : a){
			state = Grid::State::DEAD;
			
		}
	}
	m_grid.at(10).at(10) = Grid::State::ALIVE;
	m_grid.at(11).at(11) = Grid::State::ALIVE;
	m_grid.at(0).at(0) = Grid::State::ALIVE;
	m_grid.at(99).at(99) = Grid::State::ALIVE;



}




void Grid::setCooState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y/100).at(x/100) = state;
}

void Grid::setIndexState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y).at(x) = state;
}


sf::Vector2f Grid::getCooFromIndex(const size_t& x, const size_t& y)const{
	
	if(x >= 100 or y >= 100)
		throw std::out_of_range("x or y is too big");
	
	return sf::Vector2f (x*7, y*7);//top left
	
}


sf::Vector2i Grid::getIndexFromCoo(const sf::Vector2f& position)const{
	
	return sf::Vector2i (position.x/7, position.y/ 7);
}


const sf::VertexArray Grid::pointToDraw(){
	
	sf::VertexArray array(sf::Quads);
	
	for(auto line=0; line < 100; line++){
		for(auto column =0; column< 100; column++){
			if(isAlive(column, line) ){
				auto topLeft = getCooFromIndex(column, line);
				array.append(sf::Vertex(topLeft) );
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+7,topLeft.y)));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+7,topLeft.y+7)));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x,topLeft.y+7)));
				
			}
		}
	}
	return array;
}




bool Grid::isAlive(const sf::Vector2i& position) const{
	return m_grid.at(position.y).at(position.x) == Grid::State::ALIVE ;
}
bool Grid::isAlive(const size_t &x, const size_t &y) const{
	return m_grid.at(y).at(x) == Grid::State::ALIVE ;
}


int Grid::countNeibourg(const size_t &x, const size_t & y) const {
	
}



int Grid::countNeibourg(const sf::Vector2i & position) const{
	
}
