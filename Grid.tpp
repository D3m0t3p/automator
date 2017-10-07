//
//  Grid.cpp
//  automator
//
//  Created by d3m0t3p on 14.04.17.
//  Copyright © 2017 postTenebras. All rights reserved.
//

#include "Grid.hpp"

template <long long int n>

Grid<n>::Grid(long long int xWin, long long int yWin){
	m_grid = std::array<std::array<Grid::State, n>, n>();
	for(auto &a : m_grid){
		for(auto&state : a){
			state = Grid::State::DEAD;
			
		}
	}
	xMax = xWin;
	yMax = yWin;

	m_transformationToApply = std::vector<std::pair<sf::Vector2i,Grid::State>>();


}


template <long long int n>
void Grid<n>::setCooState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y/n).at(x/n) = state;
}

template <long long int n>
void Grid<n>::setIndexState(const size_t& x, const size_t& y, Grid::State state){
	m_grid.at(y).at(x) = state;
}

template <long long int n>
void Grid<n>::setIndexState(const sf::Vector2i & position, Grid::State state){
	setIndexState(position.x, position.y, state);
}


template <long long int n>
sf::Vector2f Grid<n>::getCooFromIndex(const size_t& x, const size_t& y)const{
	
	if(x >= n or y >= n)
		throw std::out_of_range("x or y is too big");
	
	return sf::Vector2f (x*xMax/n, y*yMax/n);//top left
	
}


template <long long int n>
sf::Vector2i Grid<n>::getIndexFromCoo(const sf::Vector2f& position)const{
	
	return sf::Vector2i (position.x / xMax / n, position.y / yMax/n);
}


template <long long int n>
const sf::VertexArray Grid<n>::pointToDraw(){
	
	sf::VertexArray array(sf::Quads);
	
	for(auto line=0; line < n; line++){
		for(auto column =0; column< n; column++){
			if(isAlive(column, line) ){
				auto topLeft = getCooFromIndex(column, line);
				array.append(sf::Vertex(topLeft, sf::Color::Black) );
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+xMax/n,topLeft.y), sf::Color::Black));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x+xMax/n,topLeft.y+yMax/n), sf::Color::Black));
				array.append(sf::Vertex(sf::Vector2f(topLeft.x,topLeft.y+yMax/n), sf::Color::Black));
				
			}
		}
	}
	return array;
}



template <long long int n>
bool Grid<n>::isAlive(const sf::Vector2i& position) const{
	return isAlive(position.x, position.y);
}

template <long long int n>
bool Grid<n>::isAlive(const long long int &x, const long long int &y) const{

	try {
		return m_grid.at(y).at(x) == Grid::State::ALIVE ;
		
	} catch (std::out_of_range& e) {
		return false; //hors du cadre, considérer comme vivant
	}
}

template <long long int n>
size_t Grid<n>::countNeighbours(const long long int &x, const long long int & y) const {
	
	
	int cpt = 0;
	

	for(int i = (x-1) ; i < (x+2); i++ ){
		
		for(int j = (y-1) ; j < (y+2); j++){
			if(isAlive(i, j))
				cpt++;
				
				
		}
	}
	if(isAlive(x, y))
		cpt--;
	
	return cpt;
	
	
}


template <long long int n>
size_t Grid<n>::countNeighbours(const sf::Vector2i & position) const{
	
	return countNeighbours(position.x, position.y);
}

template <long long int n>
void Grid<n>::computeNextIteration(){
	
	m_transformationToApply.erase(m_transformationToApply.begin(), m_transformationToApply.end());
	
	for(size_t i=0;i < n; i++){
		for(size_t j=0; j < n; j++){
			
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

template <long long int n>
void Grid<n>::commitChange(){
	
	for(const auto&p : m_transformationToApply){
		setIndexState(p.first, p.second); //position and STATE
	}
	m_transformationToApply.erase(m_transformationToApply.begin(), m_transformationToApply.end());
}
