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
		
	m_transformationToApply = std::vector<std::pair<sf::Vector2i,Grid::State>>();


}




void Grid::setCooState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y/100).at(x/100) = state;
}

void Grid::setIndexState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y).at(x) = state;
}
void Grid::setIndexState(const sf::Vector2i & position, Grid::State state){
	setIndexState(position.x, position.y, state);
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
				array.append(sf::Vertex(topLeft, sf::Color::Black) );
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+7,topLeft.y), sf::Color::Black));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+7,topLeft.y+7), sf::Color::Black));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x,topLeft.y+7), sf::Color::Black));
				
			}
		}
	}
	return array;
}




bool Grid::isAlive(const sf::Vector2i& position) const{
	return isAlive(position.x, position.y);
}

bool Grid::isAlive(const long long int &x, const long long int &y) const{
	try {
		return m_grid.at(y).at(x) == Grid::State::ALIVE ;
		
	} catch (std::out_of_range& e) {
		return true;
	}
}


size_t Grid::countNeighbours(const size_t &x, const size_t & y) const {
	
	
	int cpt = 0;
	int loop1 = 0;
	int loop2 = 0;

	for(int i = x-1; i < (x+2); i++ ){
		loop1++;
		for(int j = y-1; j < (y+2); j++){
			loop2++;
			if(isAlive(i, j))
				cpt++;
				
				
		}
	}
	if(isAlive(x, y))
		cpt--;
	
	return cpt;
	
	
}



size_t Grid::countNeighbours(const sf::Vector2i & position) const{
	
	return countNeighbours(position.x, position.y);
}


void Grid::computeNextIteration(){
	
	m_transformationToApply.erase(m_transformationToApply.begin(), m_transformationToApply.end());
	
	for(size_t i=0;i < 100; i++){
		for(size_t j=0; j < 100; j++){
			
			auto neighbours = countNeighbours(i, j);
			
			if(isAlive(i, j)){
				
				if(neighbours < 2)
					m_transformationToApply.push_back(std::pair<sf::Vector2i,Grid::State>(sf::Vector2i(i,j), Grid::State::DEAD));
				if(neighbours == 2 or neighbours == 3)
					;
				
				if(neighbours > 3)
					m_transformationToApply.push_back(std::pair<sf::Vector2i,Grid::State>(sf::Vector2i(i,j), Grid::State::DEAD));
			}
			else
				if(neighbours == 3)
					m_transformationToApply.push_back(std::pair<sf::Vector2i,Grid::State>(sf::Vector2i(i,j), Grid::State::ALIVE));
		}
	}
}

void Grid::commitChange(){
	
	for(const auto&p : m_transformationToApply){
		setIndexState(p.first, p.second);
	}
	m_transformationToApply.erase(m_transformationToApply.begin(), m_transformationToApply.end());
}
